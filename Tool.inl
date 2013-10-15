// -*- C++ -*-
// $Id: Tool.inl 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Tool <T>::Tool (void)
{

}

template <typename T>
inline
Tool <T>::~Tool (void)
{

}

template <typename T>
void Tool <T>::register_fini_callback (void)
{
  PIN_AddFiniFunction (&Tool::__fini, this);
}

template <typename T>
void Tool <T>::unregister_fini_callbacks (void)
{
  PIN_RemoveFiniFunctions ();
}

template <typename T>
void Tool <T>::__fini (int code, void * obj)
{
  reinterpret_cast <T *> (obj)->handle_fini (code);
}

template <typename T>
template <typename CALLBACK>
void Tool <T>::add_fork_function (FPOINT location, CALLBACK * callback)
{
  PIN_AddForkFunction (location, &CALLBACK::__analyze_fork, callback);
}

template <typename T>
template <typename CALLBACK>
void Tool <T>::add_follow_child_process_function (CALLBACK * callback)
{
  PIN_AddFollowChildProcessFunction (&CALLBACK::__analyze_follow_child_process, callback);
}

template <typename T>
inline
void Tool <T>::handle_fini (int)
{

}

template <typename T>
inline
void Tool <T>::handle_detach (void)
{

}

template <typename T>
inline
void Tool <T>::handle_thread_start (THREADID, Context &, INT32)
{

}

template <typename T>
inline
void Tool <T>::handle_thread_fini (THREADID, const Const_Context &, INT32)
{

}

template <typename T>
inline
void Tool <T>::handle_syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std)
{

}

template <typename T>
inline
void Tool <T>::handle_syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std)
{

}

template <typename T>
inline
EXCEPT_HANDLING_RESULT Tool <T>::handle_internal_exception (THREADID, Exception &, PHYSICAL_CONTEXT *)
{
  return EHR_UNHANDLED;
}

template <typename T>
inline
void Tool <T>::detach (void)
{
  PIN_Detach ();
}

template <typename T>
inline
bool Tool <T>::is_process_exiting (void)
{
  return PIN_IsProcessExiting ();
}

template <typename T>
inline
void Tool <T>::exit_process (const INT32 code)
{
  PIN_ExitProcess (code);
}

template <typename T>
inline
void Tool <T>::exit_application (const INT32 status)
{
  PIN_ExitApplication (status);
}

template <typename T>
inline
int Tool <T>::get_pid (void)
{
  return PIN_GetPid ();
}

template <typename T>
inline
void Tool <T>::get_source_location (ADDRINT address, INT32 *column, INT32 *line, string *filename)
{
  PIN_GetSourceLocation (address, column, line, filename);
}

} // namespace Pin
} // namespace OASIS
