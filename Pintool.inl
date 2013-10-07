// -*- C++ -*-
// $Id: Pintool.inl 2305 2013-10-07 03:23:23Z hillj $

namespace OASIS
{
namespace Pin
{

//
// ~Pintool
//
template <typename T>
inline
Pintool <T>::~Pintool (void)
{

}

//
// enable_thread_start
//
template <typename T>
inline
Pintool <T> & Pintool <T>::enable_thread_start (void)
{
  PIN_AddThreadStartFunction (&Pintool::__thread_start, this->tool_);
  return *this;
}

//
// enable_thread_fini
//
template <typename T>
inline
Pintool <T> & Pintool <T>::enable_thread_fini (void)
{
  PIN_AddThreadFiniFunction (&Pintool::__thread_fini, this->tool_);
  return *this;
}

//
// enable_syscall_entry
//
template <typename T>
inline
Pintool <T> & Pintool <T>::enable_syscall_entry (void)
{
  PIN_AddSyscallEntryFunction (&Pintool::__syscall_entry, this->tool_);
  return *this;
}

template <typename T>
inline
Pintool <T> & Pintool <T>::enable_syscall_exit (void)
{
  PIN_AddSyscallExitFunction (&Pintool::__syscall_exit, this->tool_);
  return *this;
}

template <typename T>
inline
Pintool <T> & Pintool <T>::enable_detach (void)
{
  PIN_AddDetachFunction (&Pintool::__detach, this->tool_);
  return *this;
}

template <typename T>
inline
Pintool <T> & Pintool <T>::enable_internal_exception_handler (void)
{
  PIN_AddInternalExceptionHandler (&Pintool::__internal_exception_handler, this->tool_);
  return *this;
}

template <typename T>
inline
void Pintool <T>::start_program (void)
{
  PIN_StartProgram ();
}

template <typename T>
inline
void Pintool <T>::start_program_probed (void)
{
  PIN_StartProgramProbed ();
}

} // namespace OASIS
} // namespace Pin
