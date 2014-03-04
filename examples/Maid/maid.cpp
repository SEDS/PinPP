#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <memory>

#include "pin.H"
#include "pin_isa.H"
#include "call_stack.h"
#include "argv_readparam.h"

#include "pin++/Callback.h"
#include "pin++/Image_Instrument.h"
#include "pin++/Trace_Instrument.h"
#include "pin++/Symbol.h"
#include "pin++/Pintool.h"
#include "pin++/Guard.h"

///////////////////////// Prototypes //////////////////////////////////////////

string Target2RtnName(ADDRINT target);
string Target2LibName(ADDRINT target);

///////////////////////// Global Variables ////////////////////////////////////

ostream *Output;

CallStack callStack (Target2RtnName, Target2LibName);

bool main_entry_seen = false;
bool prevIpDoesPush = FALSE;

set <void *> addrsToDump;
set <ADDRINT> pushIps;

///////////////////////// Utility functions ///////////////////////////////////

void RecordPush (const OASIS::Pin::Ins & ins)
{
  pushIps.insert (ins.address ());
}

bool IpDoesPush (ADDRINT ip)
{
  return pushIps.find (ip) != pushIps.end ();
}

std::string Target2RtnName (ADDRINT target)
{
  std::string name = OASIS::Pin::Routine::find_name (target);
  return !name.empty () ? name : "[Unknown routine]";
}

std::string Target2LibName (ADDRINT target)
{
  // TODO Create a guard object for the Client.
  OASIS::Pin::Client_Guard guard;
  OASIS::Pin::Routine rtn = OASIS::Pin::Routine::find (target);

  return rtn.valid () ? rtn.section ().image ().name () : "[Unknown image]";
}

///////////////////////// Analysis Functions //////////////////////////////////

class register_addr : public OASIS::Pin::Callback <register_addr (OASIS::Pin::ARG_FUNCARG_CALLSITE_VALUE)>
{
public:
  void handle_analyze (ADDRINT addr)
  {
    addrsToDump.insert ((void *)addr);
  }
};

class unregister_addr : public OASIS::Pin::Callback <unregister_addr (OASIS::Pin::ARG_FUNCARG_CALLSITE_VALUE)>
{
public:
  void handle_analyze (ADDRINT addr)
  {
    if (addrsToDump.find ((void*)addr) != addrsToDump.end ())
      addrsToDump.erase ((void *)addr);
    else
      std::cerr << "MAID ERROR: unregistered address " << hex << addr << dec << std::endl;
  }
};

class process_inst : public OASIS::Pin::Callback <process_inst (OASIS::Pin::ARG_INST_PTR)>
{
public:
  void handle_analyze (ADDRINT ip)
  {
    prevIpDoesPush = IpDoesPush (ip);
  }
};

/*
class process_syscall : public OASIS::Pin::Callback <process_syscall (OASIS::Pin::ARG_INST_PTR,
                                                                      OASIS::Pin::ARG_SYSCALL_NUMBER,
                                                                      OASIS::Pin::ARG_REG_VALUE,
                                                                      OASIS::Pin::ARG_SYSARG_CALLSITE_VALUE)>
{
public:
  void handle_analyze (ADDRINT ip, UINT32 num, ADDRINT sp, ADDRINT arg0)
  {
 if( main_entry_seen ) {
 //cout << callStack.Depth() << ":" << SYS_SyscallName(num) << endl;
 }
 //callStack.ProcessSysCall(sp, target);

  }
};
*/

class process_directcall : public OASIS::Pin::Callback <process_directcall (OASIS::Pin::ARG_INST_PTR,
                                                                            OASIS::Pin::ARG_REG_VALUE)>
{
public:
  process_directcall (ADDRINT target)
    : target_ (target)
  {

  }

  void handle_analyze (ADDRINT ip, ADDRINT sp)
  {
    callStack.ProcessCall (sp, this->target_);
  }
private:
  ADDRINT target_;
};

void A_ProcessDirectCall(ADDRINT ip, ADDRINT target, ADDRINT sp)
{
  //cout << "Direct call: " << Target2String(target) << endl;
  callStack.ProcessCall(sp, target);
}

class process_indirect_call : public OASIS::Pin::Callback <process_indirect_call (OASIS::Pin::ARG_INST_PTR,
                                                                                  OASIS::Pin::ARG_BRANCH_TARGET_ADDR,
                                                                                  OASIS::Pin::ARG_REG_VALUE)>
{
public:
  void handle_analyze (ADDRINT ip, ADDRINT target, ADDRINT sp)
  {
    callStack.ProcessCall (sp, target);
  }
};

class process_stub : public OASIS::Pin::Callback <process_stub (OASIS::Pin::ARG_INST_PTR,
                                                                OASIS::Pin::ARG_BRANCH_TARGET_ADDR,
                                                                OASIS::Pin::ARG_REG_VALUE)>
{
public:
  void handle_analyze (ADDRINT ip, ADDRINT target, ADDRINT sp)
  {
    callStack.ProcessCall (sp, target);
  }
};

class process_return : public OASIS::Pin::Callback <process_return (OASIS::Pin::ARG_INST_PTR,
                                                                    OASIS::Pin::ARG_REG_VALUE)>
{
public:
  void handle_analyze (ADDRINT ip, ADDRINT sp)
  {
    callStack.ProcessReturn (sp, prevIpDoesPush);
  }
};


static void
A_ProcessReturn(ADDRINT ip, ADDRINT sp) {
  callStack.ProcessReturn(sp, prevIpDoesPush);
}

class enter_main_image : public OASIS::Pin::Callback <enter_main_image (OASIS::Pin::ARG_INST_PTR,
                                                                        OASIS::Pin::ARG_REG_VALUE)>
{
public:
  enter_main_image (void)
    : target_ (0)
  {

  }

  void target (ADDRINT target)
  {
    this->target_ = target;
  }

  void handle_analyze (ADDRINT ip, ADDRINT sp)
  {
    main_entry_seen = true;
    callStack.ProcessMainEntry (sp, this->target_);
  }

private:
  ADDRINT target_;
};

static void
A_EnterMainImage(ADDRINT ip, ADDRINT target, ADDRINT sp)
{

  //assert(current_pc == main_entry_addr);
  //cout << "main" << endl;
  main_entry_seen = true;
  callStack.ProcessMainEntry(sp, target);
}

class do_mem_base
{
public:
  do_mem_base (bool is_store)
  : is_store_ (is_store)
  {

  }

  void handle_analyze (ADDRINT ea, ADDRINT pc)
  {
    string filename;
    int lineno;

    if (addrsToDump.find ((void *)ea) != addrsToDump.end() )
    {
      do
      {
        OASIS::Pin::Client_Guard guard;
        PIN_GetSourceLocation (pc, 0, &lineno, &filename);
      } while (false);

      *Output << (this->is_store_ ? "store" : "load")

      << " pc=" << (void*)pc
      << " ea=" << ea << endl;

      if (filename != "")
        *Output << filename << ":" << lineno;
      else
        *Output << "UNKNOWN:0";

      *Output << endl;
      callStack.DumpStack(Output);
      *Output << endl;
    }
  }

private:
  bool is_store_;
};

class do_mem :
  public OASIS::Pin::Callback <do_mem (OASIS::Pin::ARG_MEMORYWRITE_EA, OASIS::Pin::ARG_INST_PTR)>,
  public do_mem_base
{
public:
  do_mem (bool is_store)
  : do_mem_base (is_store) { }
};

/*
class do_mem2 :
  public OASIS::Pin::Callback <do_mem2 (OASIS::Pin::ARG_MEMORYWRITE_EA2, OASIS::Pin::ARG_INST_PTR)>,
  public do_mem_base
{
public:
  do_mem2 (bool is_store)
  : do_mem_base (is_store) { }
};
*/

///////////////////////// Instrumentation functions ///////////////////////////

static BOOL IsPLT (const OASIS::Pin::Trace & trace)
{
  OASIS::Pin::Routine rtn = trace.routine ();

  // All .plt thunks have a valid RTN
  if (!rtn.valid ())
    return false;

  return rtn.section ().name () == ".plt";
}

class trace : public OASIS::Pin::Trace_Instrument <trace>
{
public:
  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // FIXME if (PIN_IsSignalHandler()) {Sequence_ProcessSignalHandler(head)};

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
    for each (OASIS::Pin::Bbl & bbl in trace)
#else
    for (OASIS::Pin::Bbl & bbl : trace)
#endif
    {
      OASIS::Pin::Ins tail = *bbl.end ();

      // All memory reads/writes
#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
      for each (OASIS::Pin::Ins & ins in bbl)
#else
      for (OASIS::Pin::Ins & ins : bbl)
#endif
      {
        bool is_memory_write = ins.is_memory_write ();
        bool is_memory_read = ins.is_memory_read ();

        if (is_memory_write || is_memory_read || ins.has_memory_read2 ())
        {
          if (is_memory_write || is_memory_read)
          {
            std::shared_ptr <do_mem> callback (new do_mem (is_memory_write));
            ins.insert_call (IPOINT_BEFORE, callback.get ());

            this->do_mems_.push_back (callback);
          }
          else
            ; //ins.insert_call (IPOINT_BEFORE, new do_mem2 (is_memory_write));
        }

#if defined(TARGET_IA32)  && defined (TARGET_WINDOWS)
        // on ia-32 windows need to identify
        // push
        // ret
        // in order to process callstack correctly
        if (ins != tail)
        {
          ins.insert_call (IPOINT_BEFORE, &this->process_inst_);

          if (ins.opcode () == XED_ICLASS_PUSH)
            RecordPush (ins);
        }
#endif
      }


      // All calls and returns
      if (tail.is_syscall ())
      {
        // tail.insert_call (IPOINT_BEFORE, &this->process_syscall_, REG_STACK_PTR, 0);
      }
      else
      {
        if (tail.is_call ())
        {
          if (tail.is_direct_branch_or_call ())
          {
            ADDRINT target = tail.direct_branch_or_call_target_address ();
            std::shared_ptr <process_directcall> callback (new process_directcall (target));

            tail.insert_predicated_call (IPOINT_BEFORE, callback.get (), REG_STACK_PTR);
            this->direct_calls_.push_back (callback);
          }
          else if (!IsPLT (trace))
          {
            tail.insert_call (IPOINT_BEFORE,
                              &this->process_indirect_call_,
                              REG_STACK_PTR);
          }
        }

        if (IsPLT (trace))
          tail.insert_call (IPOINT_BEFORE, &this->process_stub_, REG_STACK_PTR);

        if (tail.is_return ())
          tail.insert_predicated_call (IPOINT_BEFORE, &this->process_return_, REG_STACK_PTR);
      }
    }
  }

private:
  process_inst process_inst_;

  //process_syscall process_syscall_;

  process_indirect_call process_indirect_call_;

  process_stub process_stub_;

  process_return process_return_;

  // TODO Update to a std::shared_ptr object.
  std::vector < std::shared_ptr <process_directcall> > direct_calls_;
  std::vector < std::shared_ptr <do_mem> > do_mems_;
};

/**
 * @class image_load
 */
class image_load : public OASIS::Pin::Image_Instrument <image_load>
{
public:
  image_load (void)
    : main_rtn_instrumented_ (false)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    if (!this->main_rtn_instrumented_)
    {
      OASIS::Pin::Routine rtn = img.find_routine ("main");

      if (!rtn.valid ())
        rtn = img.find_routine ("__libc_start_main");

      // Instrument main
      if (rtn.valid ())
      {
        this->main_rtn_instrumented_ = true;
        OASIS::Pin::Routine_Guard guard (rtn);

        this->enter_main_image_.target (rtn.address ());
        rtn.insert_call (IPOINT_BEFORE, &this->enter_main_image_, REG_STACK_PTR);
      }
    }

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
    for each (OASIS::Pin::Symbol & sym in img.symbols ())
#else
    for (OASIS::Pin::Symbol & sym : img.symbols ())
#endif
    {
      std::string name = sym.name ();

      if (strstr (name.c_str (), "MAID_register_address"))
      {
        OASIS::Pin::Routine rtn = img.find_routine (name);
        ASSERTX (rtn.valid ());

        OASIS::Pin::Routine_Guard guard (rtn);
        rtn.insert_call (IPOINT_BEFORE, &this->register_addr_, 0);
      }
      else if (strstr (name.c_str (), "MAID_unregister_address"))
      {
        OASIS::Pin::Routine rtn = img.find_routine (name);
        ASSERTX (rtn.valid ());

        OASIS::Pin::Routine_Guard guard (rtn);
        rtn.insert_call (IPOINT_BEFORE, &this->unregister_addr_, 0);
      }
    }
  }

private:
  bool main_rtn_instrumented_;
  enter_main_image enter_main_image_;

  register_addr register_addr_;
  unregister_addr unregister_addr_;
};

///////////////////////// main ////////////////////////////////////////////////

class maid : OASIS::Pin::Tool <maid>
{
public:
  maid (void)
  : delete_outfile_ (false),
    out_ (0)
  {
    // Determine where the output is to written.
    if (!outfile_.Value ().empty ())
    {
      this->delete_outfile_ = true;
      this->out_ = new std::ofstream (outfile_.Value ().c_str ());
    }
    else
    {
      this->out_ = &std::cout;
    }

    // Read the address file, if one is specified.
    if (!addrfile_.Value ().empty ())
    {
      std::string s;
      std::ifstream infile (addrfile_.Value ().c_str ());

      if (!infile)
      {
        perror(s.c_str());
        exit(1);
      }

      infile >> hex;

      while (!infile.eof ())
      {
        static void *addr;
        infile >> addr;

        addrsToDump.insert((void *)addr);
      }
    }
  }

private:
  /// @{ Instruments
  image_load img_load_;
  trace trace_;
  /// @}

  bool delete_outfile_;
  std::ostream * out_;

  /// @{ KNOBS
  static KNOB <string> addrfile_;
  static KNOB <string> outfile_;
  /// @}
};

KNOB <string> maid::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "outfile", "", "specify output file name");
KNOB <string> maid::addrfile_ (KNOB_MODE_WRITEONCE, "pintool", "addrfile", "", "specify output file name");

DECLARE_PINTOOL (maid);
