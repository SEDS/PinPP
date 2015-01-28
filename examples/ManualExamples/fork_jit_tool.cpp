// $Id: fork_jit_tool.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Callback.h"
#include "pin++/Tool.h"
#include "pin++/Pintool.h"
#include "pin++/Guard.h"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#if defined (TARGET_WINDOWS)
typedef int pid_t;
#endif

class fork_jit_tool : public OASIS::Pin::Tool <fork_jit_tool>
{
public:
  fork_jit_tool (void)
  {
    this->enable_fork_before_callback ();
    this->enable_fork_after_in_child_callback ();
    this->enable_fork_after_in_parent_callback ();
  }

  void handle_fork_before (THREADID thr_id, const OASIS::Pin::Const_Context &)
  {
    do
    {
      OASIS::Pin::Guard <OASIS::Pin::Lock> (this->lock_);
      std::cerr << "TOOL: Before fork." << std::endl;
    } while (false);

    this->parent_pid_ = PIN_GetPid ();
  }

  void handle_fork_after_in_child (THREADID thr_id, const OASIS::Pin::Const_Context &)
  {
    do
    {
      OASIS::Pin::Guard <OASIS::Pin::Lock> (this->lock_);
      std::cerr << "TOOL: After fork in child." << std::endl;
    } while (false);

    if ((PIN_GetPid () == this->parent_pid_) || (getppid () != this->parent_pid_))
    {
      std::cerr << "PIN_GetPid () failes in child process" << std::endl;
      exit (-1);
    }
  }

  void handle_fork_after_in_parent (THREADID thr_id, const OASIS::Pin::Const_Context &)
  {
    do
    {
      OASIS::Pin::Guard <OASIS::Pin::Lock> (this->lock_);
      std::cerr << "TOOL: After fork in parent." << std::endl;
    } while (false);

    if (PIN_GetPid () != this->parent_pid_)
    {
      std::cerr << "PIN_GetPid () fails in parent process" << std::endl;
      exit (-1);
    }
  }

private:
  OASIS::Pin::Lock lock_;
  pid_t parent_pid_;
};

DECLARE_PINTOOL (fork_jit_tool);
