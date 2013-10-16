// $Id: Tool.cpp 2288 2013-09-19 19:09:57Z hillj $

#include "Tool.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
void Tool <T>::__fini (int code, void * obj)
{
  reinterpret_cast <T *> (obj)->handle_fini (code);
}

template <typename T>
void Tool <T>::__detach (void * obj)
{
  reinterpret_cast <T *> (obj)->handle_detach ();
}

template <typename T>
void Tool <T>::__thread_start (THREADID index, CONTEXT * ctx, INT32 flags, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_thread_start (index, Context (ctx), flags);
#else
  Context c (ctx);
  reinterpret_cast <T *> (obj)->handle_thread_start (index, c, flags);
#endif
}

template <typename T>
void Tool <T>::__thread_fini (THREADID index, const CONTEXT * ctx, INT32 flags, VOID * obj)
{
  reinterpret_cast <T *> (obj)->handle_thread_fini (index, Const_Context (ctx), flags);
}

template <typename T>
void Tool <T>::__syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_syscall_entry (thr_index, Context (ctxt), std);
 #else
  Context ctx (ctxt);
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, ctx, std);
#endif

}

template <typename T>
void Tool <T>::__syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, Context (ctxt), std);
#else
  Context ctx (ctxt);
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, ctx, std);
#endif
}

template <typename T>
EXCEPT_HANDLING_RESULT Tool <T>::
__internal_exception_handler (THREADID thr, EXCEPTION_INFO * ex_info, PHYSICAL_CONTEXT * ctx, VOID *v)
{
#if defined (TARGET_WINDOWS)
  return reinterpret_cast <T *> (v)->handle_internal_exception (thr, Exception (ex_info), ctx);
#else
  Exception ex (ex_info);
  return reinterpret_cast <T *> (v)->handle_internal_exception (thr, ex, ctx);
#endif
}

template <typename T>
BOOL Tool <T>::__follow_child_process (CHILD_PROCESS child, VOID * val)
{
  return reinterpret_cast <T *> (val)->handle_follow_child_process (child);
}

} // namespace Pin
} // namespace OASIS
