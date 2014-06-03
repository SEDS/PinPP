#include "pin++/Routine_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"
#include "pin++/Guard.h"
#include "pin++/Lock.h"
#include "ExPAD_Call_Graph.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <list>
#include <memory>
#include <stack>
#include <map>
#include <unordered_set>


typedef std::stack <ExPAD_Routine_Info *> stack_type;
typedef std::map <THREADID, stack_type> map_type1;
typedef std::map <THREADID, ExPAD_Call_Graph *> map_type2;

class before : public OASIS::Pin::Callback <before (OASIS::Pin::ARG_THREAD_ID)>
{
public:
  before (ExPAD_Routine_Info * ri, map_type1 & call_stacks, ExPAD_Call_Graph & call_graph)
    : ri_ (ri), 
    call_stacks_ (call_stacks),
    call_graph_ (call_graph)
  {
  
  }

  ExPAD_Routine_Info * ri_;
  map_type1 & call_stacks_;
  ExPAD_Call_Graph & call_graph_;
  OASIS::Pin::Lock lock_;
  
  void handle_analyze (THREADID thr_id)
  {
    map_type1::iterator it = this->call_stacks_.find (thr_id);
    if (it == this->call_stacks_.end ())
    {
      stack_type s;
      s.push (this->ri_);
      this->call_stacks_.insert (std::pair <UINT32, stack_type> (thr_id, s));
    }
    else
    {
      this->call_stacks_ [thr_id].push (this->ri_);
    }
    this->lock_.acquire (thr_id + 1);
    this->call_graph_.insert_vertex (this->ri_->id_, this->ri_);
    this->lock_.release ();
  }
};

class after : public OASIS::Pin::Callback <after (OASIS::Pin::ARG_THREAD_ID)>
{
public:
  after (map_type1 & call_stacks, ExPAD_Call_Graph & call_graph)
    : call_stacks_ (call_stacks),
      call_graph_ (call_graph)
  {
  
  }

  void handle_analyze (THREADID thr_id)
  {
    if (this->call_stacks_[thr_id].empty ())
    {
      return;
    }
      
    //// Save the stack top
    UINT32 callee_id = this->call_stacks_[thr_id].top ()->id_;
    std::string callee_name = this->call_stacks_[thr_id].top ()->name_;
    
    //// pop from the stack
    this->call_stacks_[thr_id].pop ();

    if (this->call_stacks_[thr_id].empty ())
    {
      return;
    }
    //
    //// Create the link with the current stack top
    UINT32 caller_id = this->call_stacks_[thr_id].top ()->id_;
    std::string caller_name = this->call_stacks_[thr_id].top ()->name_;

   // std::cerr << caller_name << " ----> " << callee_name << " (" << thr_id << ")" << std::endl;
   this->lock_.acquire (thr_id + 1);
   this->call_graph_.connect (caller_id, callee_id);
   this->lock_.release ();
  }

  map_type1 & call_stacks_;
  ExPAD_Call_Graph & call_graph_;
  OASIS::Pin::Lock lock_;
  
};


 class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>
{
public:
  Instrument (void)
    : a_ (call_stacks_, call_graph_)
  {
  }

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

    if (rtn.name ().find ("function") == std::string::npos)
      return;

    // Allocate an object for this routine
    ExPAD_Routine_Info * ri = new ExPAD_Routine_Info ();
    ri->id_ = rtn.id ();
    ri->name_ = rtn.name ();
    const std::string & image_name = rtn.section ().image ().name ();
#if defined (TARGET_WINDOWS)
    ri->image_ = image_name.substr (image_name.find_last_of ('\\') + 1);
#else
    ri->image_ = image_name.substr (image_name.find_last_of ('/') + 1);
#endif
    ri->address_ = rtn.address ();

    /*if (kernal_check (ri))
    {
      delete ri;
      return;
    }*/
    
    before * b = new before (ri, this->call_stacks_, this->call_graph_);

    OASIS::Pin::Routine_Guard guard (rtn);
    rtn.insert_call (IPOINT_BEFORE, b);
    rtn.insert_call (IPOINT_AFTER, &this->a_);
  }

  bool kernal_check (ExPAD_Routine_Info * ri)
  {
    std::unordered_set <std::string> system_images;
    std::array<std::string, 5> temp = {"kernel32.dll", "KERNELBASE.dll", "ntdll.dll", "MSVCR110D.dll", "ACEd.dll"};
    system_images.insert (temp.begin (), temp.end ());
    
    std::unordered_set <std::string>::iterator it = 
      system_images.find (ri->image_);

    if (it == system_images.end ())
      return false;
    else
      return true;
  }

  const map_type1 & call_stacks (void) const
  {
    return this->call_stacks_;
  }

  const ExPAD_Call_Graph & call_graph (void) const
  {
    return this->call_graph_;
  }

private:
  
  map_type1 call_stacks_;
  ExPAD_Call_Graph call_graph_;
  after a_;
};


class ExPAD_Instrumenter : public OASIS::Pin::Tool <ExPAD_Instrumenter>
{
public:
  ExPAD_Instrumenter (void)
  : file_ (fopen ("threaddata.out", "w"))
  {
    this->init_symbols ();
    this->enable_fini_callback ();
    this->enable_thread_start_callback ();
    this->enable_thread_fini_callback ();
  }

 void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctxt, INT32 code)
 {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_, thr_id + 1);
    fprintf (this->file_, "thread begin %d\n", thr_id);
    fflush (this->file_);
  }

  void handle_thread_fini (THREADID thr_id, const OASIS::Pin::Const_Context & ctxt, INT32 code)
  {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_, thr_id + 1);
    fprintf (this->file_, "thread end %d code %d\n",thr_id, code);
    fflush (this->file_);
  }

  void handle_fini (INT32)
  {
    fclose (this->file_);

    const ExPAD_Call_Graph & cg = this->inst_.call_graph ();
    ExPAD_Vertex_Writer<ExPAD_Call_Graph_Type> vw(cg.graph ());
    
    ofstream fout("graph.dot");
    boost::write_graphviz (fout, cg.graph (), vw);
  }

private:
  Instrument inst_;
  OASIS::Pin::Lock lock_;
  FILE * file_;
};

DECLARE_PINTOOL (ExPAD_Instrumenter);
