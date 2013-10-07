// -*- C++ -*-
// $Id: Tool.inl 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Tool
//
inline
Tool::Tool (void)
{
  this->current_ = this;
}

//
// ~Tool
//
inline
Tool::~Tool (void)
{

}

//
// current
//
inline
Tool * Tool::current (void)
{
  return Tool::current_;
}

//
// add_fork_function
//
template <typename CALLBACK>
void Tool::add_fork_function (FPOINT location, CALLBACK * callback)
{
  PIN_AddForkFunction (location, &CALLBACK::__analyze_fork, callback);
}

template <typename CALLBACK>
void Tool::add_follow_child_process_function (CALLBACK * callback)
{
  PIN_AddFollowChildProcessFunction (&CALLBACK::__analyze_follow_child_process, callback);
}

inline
void Tool::handle_fini (int)
{

}

inline
void Tool::handle_detach (void)
{

}

inline
void Tool::handle_thread_start (THREADID, Context &, INT32)
{

}

inline
void Tool::handle_thread_fini (THREADID, const Const_Context &, INT32)
{

}

inline
void Tool::handle_syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std)
{

}

inline
void Tool::handle_syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std)
{

}

inline
EXCEPT_HANDLING_RESULT Tool::handle_internal_exception (THREADID, Exception &, PHYSICAL_CONTEXT *)
{
  return EHR_UNHANDLED;
}

inline
void Tool::detach (void)
{
  PIN_Detach ();
}

inline
bool Tool::is_process_exiting (void)
{
  return PIN_IsProcessExiting ();
}

inline
void Tool::exit_process (const INT32 code)
{
  PIN_ExitProcess (code);
}

inline
int Tool::get_pid (void)
{
  return PIN_GetPid ();
}

inline
void Tool::exit_application (const INT32 status)
{
  PIN_ExitApplication (status);
}

inline
void Tool::get_source_location (ADDRINT address, INT32 *column, INT32 *line, string *filename)
{
  PIN_GetSourceLocation (address, column, line, filename);
}
} // namespace Pin
} // namespace OASIS
