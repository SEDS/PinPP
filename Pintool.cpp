// $Id: Pintool.cpp 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Pintool
//
template <typename T>
Pintool <T>::Pintool (int argc, char * argv [], bool init_symbols)
: tool_ (new T ())
{
  // Initialize Pin, and our finalize method.
  if (init_symbols)
    PIN_InitSymbols ();

  PIN_Init (argc, argv);

  // Initialize standard Pin++ callback functions.
  PIN_AddFiniFunction (&Pintool::__fini, this->tool_);

  // Finish initializing the tool.
  this->tool_->handle_init (argc, argv);
}

//
// __fini
//
template <typename T>
void Pintool <T>::__fini (int code, void * obj)
{
  reinterpret_cast <T *> (obj)->handle_fini (code);
}

//
// __detach
//
template <typename T>
void Pintool <T>::__detach (void * obj)
{
  reinterpret_cast <T *> (obj)->handle_detach ();
}

//
// __thread_start
//
template <typename T>
void Pintool <T>::__thread_start (THREADID index, CONTEXT * ctx, INT32 flags, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_thread_start (index, Context (ctx), flags);
#else
  Context c (ctx);
  reinterpret_cast <T *> (obj)->handle_thread_start (index, c, flags);
#endif
}

//
// __thread_fini
//
template <typename T>
void Pintool <T>::__thread_fini (THREADID index, const CONTEXT * ctx, INT32 flags, VOID * obj)
{
  reinterpret_cast <T *> (obj)->handle_thread_fini (index, Const_Context (ctx), flags);
}

//
// __syscall_entry
//
template <typename T>
void Pintool <T>::__syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_syscall_entry (thr_index, Context (ctxt), std);
 #else
  Context ctx (ctxt);
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, ctx, std);
#endif

}

template <typename T>
void Pintool <T>::__syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, Context (ctxt), std);
#else
  Context ctx (ctxt);
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, ctx, std);
#endif
}

template <typename T>
EXCEPT_HANDLING_RESULT Pintool <T>::
__internal_exception_handler (THREADID thr, EXCEPTION_INFO * ex_info, PHYSICAL_CONTEXT * ctx, VOID *v)
{
#if defined (TARGET_WINDOWS)
  return reinterpret_cast <T *> (v)->handle_internal_exception (thr, Exception (ex_info), ctx);
#else
  Exception ex (ex_info);
  return reinterpret_cast <T *> (v)->handle_internal_exception (thr, ex, ctx);
#endif
}

} // namespace OASIS
} // namespace Pin
