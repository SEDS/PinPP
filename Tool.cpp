// $Id: Tool.cpp 2288 2013-09-19 19:09:57Z hillj $

#include "Image.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
void Tool <T>::__fini (INT32 code, void * obj)
{
  reinterpret_cast <T *> (obj)->handle_fini (code);
}

template <typename T>
void Tool <T>::__fini_unlocked (INT32 code, void * obj)
{
  reinterpret_cast <T *> (obj)->handle_fini_unlocked (code);
}

template <typename T>
void Tool <T>::__detach (void * obj)
{
  reinterpret_cast <T *> (obj)->handle_detach ();
}

template <typename T>
void Tool <T>::__detach_probed (void * obj)
{
  reinterpret_cast <T *> (obj)->handle_detach_probed ();
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

template <typename T>
size_t Tool <T>::__fetch (void *buf, ADDRINT addr, size_t size, EXCEPTION_INFO *ex, VOID *v)
{
  return reinterpret_cast <T *> (v)->handle_fetch (buf, addr, size, Exception (ex));
}

template <typename T>
void Tool <T>::__out_of_memory (size_t size, VOID *v)
{
  reinterpret_cast <T *> (v)->handle_out_of_memory (size);
}

template <typename T>
ADDRINT Tool <T>::__memory_address_trans (PIN_MEM_TRANS_INFO * info, VOID *v)
{
  return reinterpret_cast <T *> (v)->handle_memory_address_trans (info);
}

template <typename T>
void Tool <T>::__thread_attach_probed (VOID *sigmask, VOID *v)
{
  reinterpret_cast <T *> (v)->handle_thread_attach_probed (sigmask);
}

template <typename T>
void Tool <T>::__thread_detach_probed (void)
{
  reinterpret_cast <T *> (v)->handle_thread_detach_probed ();
}

template <typename T>
void Tool <T>::__application_start (void)
{
  reinterpret_cast <T *> (v)->handle_application_start ();
}

template <typename T>
void Tool <T>::__context_change (THREADID thr_id, CONTEXT_CHANGE_REASON reason, const CONTEXT *from, CONTEXT *to, INT32 info, VOID *v)
{
  reinterpret_cast <T *> (v)->handle_context_change (thr_id, reason, from, to, info);
}

template <typename T>
void Tool <T>::__probes_inserted (IMG img, VOID *v)
{
  reinterpret_cast <T *> (v)->handle_probes_inserted (Image (img));
}

template <typename T>
void Tool <T>::__unload (IMG img, VOID *v)
{
  reinterpret_cast <T *> (v)->handle_unload (Image (img));
}

} // namespace Pin
} // namespace OASIS
