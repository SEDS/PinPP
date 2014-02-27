// $Id: strace.cpp 2297 2013-10-01 20:31:06Z hillj $

#include <stdio.h>

#if defined (TARGET_MAC)
#include <sys/syscall.h>
#elif !defined (TARGET_WINDOWS)
#include <syscall.h>
#endif

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Context.h"

/**
 * @class Syscall_Before
 */
class Syscall_Before :
  public OASIS::Pin::Callback <Syscall_Before (OASIS::Pin::ARG_INST_PTR,
                                               OASIS::Pin::ARG_SYSCALL_NUMBER,
                                               OASIS::Pin::ARG_SYSARG_VALUE,
                                               OASIS::Pin::ARG_SYSARG_VALUE,
                                               OASIS::Pin::ARG_SYSARG_VALUE,
                                               OASIS::Pin::ARG_SYSARG_VALUE,
                                               OASIS::Pin::ARG_SYSARG_VALUE,
                                               OASIS::Pin::ARG_SYSARG_VALUE) >
{
public:
  Syscall_Before (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ip, ADDRINT num, ADDRINT arg0, ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5)
  {
#if defined(TARGET_LINUX) && defined(TARGET_IA32)
    // On ia32 Linux, there are only 5 registers for passing system call arguments,
    // but mmap needs 6. For mmap on ia32, the first argument to the system call
    // is a pointer to an array of the 6 arguments
    if (num == SYS_mmap)
    {
      ADDRINT * mmapArgs = reinterpret_cast<ADDRINT *>(arg0);
      arg0 = mmapArgs[0];
      arg1 = mmapArgs[1];
      arg2 = mmapArgs[2];
      arg3 = mmapArgs[3];
      arg4 = mmapArgs[4];
      arg5 = mmapArgs[5];
    }
#endif
    fprintf (this->file_ ,"0x%lx: %ld(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)",
        (unsigned long)ip,
        (long)num,
        (unsigned long)arg0,
        (unsigned long)arg1,
        (unsigned long)arg2,
        (unsigned long)arg3,
        (unsigned long)arg4,
        (unsigned long)arg5);
  }

private:
  FILE * file_;
};


/**
 * @class Syscall_After
 */
class Syscall_After :
  public OASIS::Pin::Callback <Syscall_After (OASIS::Pin::ARG_SYSRET_VALUE)>
{
public:
  Syscall_After (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ret)
  {
    fprintf (this->file_, " returns: 0x%lx\n", (unsigned long)ret);
    fflush (this->file_);
  }

private:
  FILE * file_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : syscall_before_ (file),
      syscall_after_ (file)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    if (ins.is_syscall () && ins.has_fall_through ())
    {
      // Arguments and syscall number is only available before
      ins.insert_call (IPOINT_BEFORE, &this->syscall_before_, 0, 1, 2, 3, 4, 5);
      ins.insert_call (IPOINT_AFTER, &this->syscall_after_);
    }
  }

  Syscall_Before & syscall_before (void)
  {
    return this->syscall_before_;
  }

  Syscall_After & syscall_after (void)
  {
    return this->syscall_after_;
  }

private:
  Syscall_Before syscall_before_;
  Syscall_After syscall_after_;
};

class strace : public OASIS::Pin::Tool <strace>
{
public:
  strace (void)
    : file_ (fopen ("strace.out", "w")),
      inst_ (file_)
  {
    this->enable_fini_callback ();
    this->enable_syscall_entry_callback ();
    this->enable_syscall_exit_callback ();
  }

  void handle_syscall_entry (THREADID thr_index, OASIS::Pin::Context & ctx, SYSCALL_STANDARD std)
  {
    this->inst_.syscall_before ().handle_analyze (ctx.get_reg (REG_INST_PTR),
                                                  ctx.get_syscall_number (std),
                                                  ctx.get_syscall_argument (std, 0),
                                                  ctx.get_syscall_argument (std, 1),
                                                  ctx.get_syscall_argument (std, 2),
                                                  ctx.get_syscall_argument (std, 3),
                                                  ctx.get_syscall_argument (std, 4),
                                                  ctx.get_syscall_argument (std, 5));
  }

  void handle_syscall_exit (THREADID thr_index, OASIS::Pin::Context & ctx, SYSCALL_STANDARD std)
  {
    this->inst_.syscall_after ().handle_analyze (ctx.get_syscall_return (std));
  }

  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  Instrument inst_;
};

DECLARE_PINTOOL (strace);
