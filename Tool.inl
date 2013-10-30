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
inline
void Tool <T>::init_symbols (void)
{
  PIN_InitSymbols ();
}

template <typename T>
inline
void Tool <T>::init_symbols (SYMBOL_INFO_MODE mode)
{
  PIN_InitSymbolsAlt (mode);
}


template <typename T>
void Tool <T>::enable_fini_callback (void)
{
  PIN_AddFiniFunction (&Tool::__fini, this);
}

template <typename T>
void Tool <T>::enable_fini_unlocked_callback (void)
{
  PIN_AddFiniUnlockedFunction (&Tool::__fini_unlocked, this);
}

template <typename T>
inline
void Tool <T>::enable_thread_start_callback (void)
{
  PIN_AddThreadStartFunction (&Tool::__thread_start, this);
}

template <typename T>
inline
void Tool <T>::enable_thread_fini_callback (void)
{
  PIN_AddThreadFiniFunction (&Tool::__thread_fini, this);
}

template <typename T>
inline
void Tool <T>::enable_syscall_entry_callback (void)
{
  PIN_AddSyscallEntryFunction (&Tool::__syscall_entry, this);
}

template <typename T>
inline
void Tool <T>::enable_syscall_exit_callback (void)
{
  PIN_AddSyscallExitFunction (&Tool::__syscall_exit, this);
}

template <typename T>
inline
void Tool <T>::enable_detach_callback (void)
{
  PIN_AddDetachFunction (&Tool::__detach, this);
}

template <typename T>
inline
void Tool <T>::enable_detach_probed_callback (void)
{
  PIN_AddDetachFunctionProbed (&Tool::__detach_probed, this);
}

template <typename T>
inline
void Tool <T>::enable_thread_attach_probed_callback (void)
{
  PIN_AddThreadAttachProbedFunction (&Tool::__thread_attach_probed, this);
}

template <typename T>
inline
void Tool <T>::enable_thread_detach_probed_callback (void)
{
  PIN_AddThreadDetachProbedFunction (&Tool::__thread_detach_probed, this);
}

template <typename T>
inline
void Tool <T>::enable_internal_exception_handler_callback (void)
{
  PIN_AddInternalExceptionHandler (&Tool::__internal_exception_handler, this);
}

template <typename T>
inline
void Tool <T>::enable_follow_child_process_callback (void)
{
  PIN_AddFollowChildProcessFunction (&Tool::__follow_child_process, this);
}

template <typename T>
inline
void Tool <T>::enable_fetch_callback (void)
{
  PIN_AddFetchFunction (&Tool::__fetch, this);
}

template <typename T>
inline
void Tool <T>::enable_out_of_memory_callback (void)
{
  PIN_AddOutOfMemoryFunction (&Tool::__out_of_memory, this);
}

template <typename T>
inline
void Tool <T>::enable_memory_address_trans_callback (void)
{
  PIN_AddMemoryAddressTransFunction (&Tool::__memory_address_trans, this);
}

template <typename T>
inline
void Tool <T>::enable_application_start_callback (void)
{
  PIN_AddApplicationStartFunction (&Tool::__application_start, this);
}

template <typename T>
inline
void Tool <T>::enable_context_change_callback (void)
{
  PIN_AddContextChangeFunction (&Tool::__context_change, this);
}

template <typename T>
inline
void Tool <T>::enable_probes_inserted_callback (void)
{
  PIN_AddProbesInsertedFunction (&Tool::__probes_inserted, this);
}

template <typename T>
inline
void Tool <T>::enable_unload_callback (void)
{
  IMG_AddUnloadFunction (&Tool::__unload, this);
}

template <typename T>
inline
void Tool <T>::disable_fini_callbacks (void)
{
  PIN_RemoveFiniFunctions ();
}

template <typename T>
inline
void Tool <T>::enable_fork_before_callback (void)
{
  PIN_AddForkFunction (FPOINT_BEFORE, &Tool::__fork_before, this);
}
  
template <typename T>
inline
void Tool <T>::enable_fork_after_in_child_callback (void)
{
  PIN_AddForkFunction (FPOINT_AFTER_IN_CHILD, &Tool::__fork_after_in_child, this);
}
  
template <typename T>
inline
void Tool <T>::enable_fork_after_in_parent_callback (void)
{
  PIN_AddForkFunction (FPOINT_AFTER_IN_PARENT, &Tool::__fork_after_in_parent, this);
}
  
template <typename T>
inline
void Tool <T>::handle_fini (INT32)
{

}

template <typename T>
inline
void Tool <T>::handle_fini_unlocked (INT32)
{

}

template <typename T>
inline
void Tool <T>::handle_detach (void)
{

}

template <typename T>
inline
void Tool <T>::handle_detach_probed (void)
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
BOOL Tool <T>::handle_follow_child_process (CHILD_PROCESS)
{

}

template <typename T>
inline
void Tool <T>::handle_fetch (void *, ADDRINT, size_t, const Exception &)
{

}

template <typename T>
inline
void Tool <T>::handle_out_of_memory (size_t size)
{

}

template <typename T>
inline
void Tool <T>::handle_memory_address_trans (PIN_MEM_TRANS_INFO *info)
{

}

template <typename T>
inline
void Tool <T>::handle_thread_attach_probed (VOID * sigmask)
{

}

template <typename T>
inline
void Tool <T>::handle_thread_detach_probed (void)
{

}

template <typename T>
inline
void Tool <T>::handle_application_start (void)
{

}

template <typename T>
inline
void Tool <T>::handle_context_change (THREADID threadIndex, CONTEXT_CHANGE_REASON reason, const CONTEXT *from, CONTEXT *to, INT32 info)
{

}

template <typename T>
inline
void Tool <T>::handle_probes_inserted (const Image & img)
{

}

template <typename T>
inline
void Tool <T>::handle_fork_before (THREADID threadid, const Const_Context & ctx)
{
  
}
  
template <typename T>
inline
void Tool <T>::handle_fork_after_in_child (THREADID threadid, const Const_Context & ctx)
{
    
}
  
template <typename T>
inline
void Tool <T>::handle_fork_after_in_parent (THREADID threadid, const Const_Context & ctx)
{
    
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
