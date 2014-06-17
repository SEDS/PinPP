#include "pin++/Routine_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"
#include "pin++/Guard.h"
#include "pin++/Lock.h"
#include "ExPAD_Call_Graph.h"
#include "ExPAD_Config.h"
#include "ExPAD_Graph_Writer.h"

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
    : a_ (call_stacks_, call_graph_),
      filter_ (true)
  {
  }

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

    ExPAD_Routine_Info * ri = this->get_function (rtn);

    if (!ri)
      return;
    
    before * b = new before (ri, this->call_stacks_, this->call_graph_);

    OASIS::Pin::Routine_Guard guard (rtn);
    b->insert (IPOINT_BEFORE, rtn);
    this->a_.insert (IPOINT_AFTER, rtn);
  }

  bool build_config (const std::string & conf_file_name)
  {
    if (!this->expad_config_.read_config (conf_file_name))
    {
      std::cerr << "Problem with the config file" << std::endl;
      return false;
    }
    else
      return true;
  }

  ExPAD_Routine_Info * get_function (const OASIS::Pin::Routine & rtn)
  {
    const std::string & temp_image_name = rtn.section ().image ().name ();
    std::string image_name;
#if defined (TARGET_WINDOWS)
    image_name = temp_image_name.substr (temp_image_name.find_last_of ('\\') + 1);
#else
    image_name = temp_image_name.substr (temp_image_name.find_last_of ('/') + 1);
#endif

    std::string rtn_name = rtn.name ();

    if (!filter_)
    {
      ExPAD_Routine_Info * ri = new ExPAD_Routine_Info ();
      ri->id_ = rtn.id ();
      ri->name_ = rtn.name ();
      ri->image_ = image_name;
      ri->address_ = rtn.address ();
      
      return ri;
    }
    else
    {
      if (this->expad_config_.ignore_routine (image_name, rtn_name))
      {
        return 0; 
      }
      else
      {
        ExPAD_Routine_Info * ri = new ExPAD_Routine_Info ();
        ri->id_ = rtn.id ();
        ri->name_ = rtn.name ();
        ri->image_ = image_name;
        ri->address_ = rtn.address ();
        return ri;
      }
    }
    
  }

  const map_type1 & call_stacks (void) const
  {
    return this->call_stacks_;
  }

  const ExPAD_Call_Graph & call_graph (void) const
  {
    return this->call_graph_;
  }

  void filter (bool filt)
  {
    this->filter_ = filt;
  }

private:
  
  map_type1 call_stacks_;
  ExPAD_Call_Graph call_graph_;
  after a_;
  ExPAD_Config expad_config_;
  bool filter_;
};


class ExPAD_Instrumenter : public OASIS::Pin::Tool <ExPAD_Instrumenter>
{
public:
  ExPAD_Instrumenter (void)
  : file_ (fopen ("threaddata.out", "w"))
  {
    this->init_symbols ();
    this->enable_fini_callback ();
    
    if (this->config_file_.Value ().empty ())
    {
      this->inst_.filter (false);
    }
    else
    {
      this->inst_.filter (true);
      this->inst_.build_config (this->config_file_.Value ());
    }
  }

  void handle_fini (INT32)
  {
    fclose (this->file_);

    const ExPAD_Call_Graph & cg = this->inst_.call_graph ();
    
    if (this->outfile_.Value ().empty ())
    {
      ExPAD_Graphviz_Writer gw;
      ofstream fout ("graph.dot");
      gw.write_graph (fout, cg);
    }
    else
    {
      ExPAD_Simple_Graph_Writer gw;
      ofstream fout (this->outfile_.Value ().c_str ());
      gw.write_graph (fout, cg);
    }
  }

private:
  Instrument inst_;
  OASIS::Pin::Lock lock_;
  FILE * file_;
  static KNOB <string> outfile_;
  static KNOB <string> config_file_;
};

KNOB <string> ExPAD_Instrumenter::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "", "specify output file name");
KNOB <string> ExPAD_Instrumenter::config_file_ (KNOB_MODE_WRITEONCE, "pintool", "c", "", "specify config file name");

DECLARE_PINTOOL (ExPAD_Instrumenter);