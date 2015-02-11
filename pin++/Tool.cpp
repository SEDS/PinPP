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
  Context context (ctx);
  reinterpret_cast <T *> (obj)->handle_thread_start (index, context, flags);
}

template <typename T>
void Tool <T>::__thread_fini (THREADID index, const CONTEXT * ctx, INT32 flags, VOID * obj)
{
  // Strip the const from the CONTEXT, and let the const wrapper class
  // handle the const.
  const Context context (const_cast <CONTEXT *> (ctx));
  reinterpret_cast <T *> (obj)->handle_thread_fini (index, context, flags);
}

template <typename T>
void Tool <T>::__syscall_entry (THREADID thr_index, CONTEXT * ctx, SYSCALL_STANDARD std, VOID * obj)
{
  Context context (ctx);
  reinterpret_cast <T *> (obj)->handle_syscall_entry (thr_index, context, std);
}

template <typename T>
void Tool <T>::__syscall_exit (THREADID thr_index, CONTEXT * ctx, SYSCALL_STANDARD std, VOID * obj)
{
  Context context (ctx);
  reinterpret_cast <T *> (obj)->handle_syscall_exit (thr_index, context, std);
}

template <typename T>
EXCEPT_HANDLING_RESULT Tool <T>::
__internal_exception_handler (THREADID thr, EXCEPTION_INFO * ex, PHYSICAL_CONTEXT * ctx, VOID *v)
{
  Exception e (ex);
  return reinterpret_cast <T *> (v)->handle_internal_exception (thr, e, ctx);
}

template <typename T>
BOOL Tool <T>::__follow_child_process (CHILD_PROCESS child, VOID * val)
{
  return reinterpret_cast <T *> (val)->handle_follow_child_process (child);
}

template <typename T>
size_t Tool <T>::__fetch (void *buf, ADDRINT addr, size_t size, EXCEPTION_INFO *ex, VOID *v)
{
  Exception e (ex);
  return reinterpret_cast <T *> (v)->handle_fetch (buf, addr, size, e);
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
void Tool <T>::__thread_detach_probed (VOID *v)
{
  reinterpret_cast <T *> (v)->handle_thread_detach_probed ();
}

template <typename T>
void Tool <T>::__application_start (VOID *v)
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
  Image image (img);
  reinterpret_cast <T *> (v)->handle_probes_inserted (image);
}

template <typename T>
void Tool <T>::__unload (IMG img, VOID *v)
{
  Image image (img);
  reinterpret_cast <T *> (v)->handle_unload (image);
}
  
template <typename T>
void Tool <T>::__fork_before (THREADID thr_id, const CONTEXT * ctx, VOID * v)
{
  // Strip the const from the CONTEXT, and let the const wrapper class
  // handle the const.
  const Context context (const_cast <CONTEXT *> (ctx));
  reinterpret_cast <T *> (v)->handle_fork_before (thr_id, context);
}

template <typename T>
void Tool <T>::__fork_after_in_child (THREADID thr_id, const CONTEXT * ctx, VOID *v)
{
  // Strip the const from the CONTEXT, and let the const wrapper class
  // handle the const.
  const Context context (const_cast <CONTEXT *> (ctx));
  reinterpret_cast <T *> (v)->handle_fork_after_in_child (thr_id, context);
}
  
template <typename T>
void Tool <T>::__fork_after_in_parent (THREADID thr_id, const CONTEXT * ctx, VOID *v)
{
  // Strip the const from the CONTEXT, and let the const wrapper class
  // handle the const.
  const Context context (const_cast <CONTEXT *> (ctx));
  reinterpret_cast <T *> (v)->handle_fork_after_in_parent (thr_id, context);
}

} // namespace Pin
} // namespace OASIS
