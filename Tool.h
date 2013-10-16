// -*- C++ -*-

//==============================================================================
/**
 *  @file        PINtool.h
 *
 *  $Id: Tool.h 2306 2013-10-07 05:03:46Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TOOL_H_
#define _OASIS_PIN_TOOL_H_

#include "Context.h"
#include "Exception.h"

namespace OASIS
{
namespace Pin
{
class Image;

/**
 * @class Tool
 *
 * Base class for all Pintool implementations. Clients can receive callbacks
 * from Pin events once registered via the Pintool class. Likewise, this class
 * exposes Pin methods that can be executed at runtime.
 */
template <typename T>
class Tool
{
public:
  /// Default constructor.
  Tool (void);

  /// Destructor.
  ~Tool (void);

  /// @{ Symbol Initialization
  void init_symbols (void);
  void init_symbols (SYMBOL_INFO_MODE mode);
  /// @}

  /// {@ Control and Initialization Callback Registration
  void enable_fini_callback (void);
  void enable_fini_unlocked_callback (void);

  void enable_thread_start_callback (void);
  void enable_thread_fini_callback (void);

  void enable_syscall_entry_callback (void);
  void enable_syscall_exit_callback (void);

  void enable_internal_exception_handler_callback (void);

  void enable_detach_callback (void);
  void enable_detach_probed_callback (void);

  void enable_follow_child_process_callback (void);

  void enable_fetch_callback (void);

  void enable_out_of_memory_callback (void);

  void enable_memory_address_trans_callback (void);

  void enable_thread_attach_probed_callback (void);
  void enable_thread_detach_probed_callback (void);

  void enable_application_start_callback (void);

  void enable_context_change_callback (void);

  void enable_probes_inserted_callback (void);

  void disable_fini_callbacks (void);

  // TODO Create Fork_Function object
  template <typename CALLBACK>
  void add_fork_function (FPOINT location, CALLBACK * callback);
  /// @}

  void detach (void);

  /// {@ Stateless PIN call wrappers
  static void get_source_location (ADDRINT address, INT32 * column, INT32 * line, string * filename);
  static bool is_process_exiting (void);
  static void exit_process (const INT32 code);
  static void exit_application (const INT32 code);
  static int get_pid (void);
   /// @}

protected:
  /// {@ Callback Handler Methods
  void handle_fini (INT32 code);
  void handle_fini_unlocked (INT32 code);
  void handle_detach (void);
  void handle_detach_probed (void);
  void handle_fetch (void *buf, ADDRINT addr, size_t size, const Exception & ex);

  void handle_thread_start (THREADID threadIndex, Context & ctxt, INT32 flags);
  void handle_thread_fini (THREADID threadIndex, const Const_Context & ctxt, INT32 flags);
  void handle_destroy_thread_data (void * data);

  void handle_syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std);
  void handle_syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std);
  EXCEPT_HANDLING_RESULT handle_internal_exception (THREADID, Exception & ex, PHYSICAL_CONTEXT *);

  BOOL handle_follow_child_process (CHILD_PROCESS child);

  void handle_out_of_memory (size_t size);
  void handle_memory_address_trans (PIN_MEM_TRANS_INFO *info);

  void handle_thread_attach_probed (VOID * sigmask);
  void handle_thread_detach_probed (void);

  void handle_application_start (void);
  void handle_context_change (THREADID threadIndex, CONTEXT_CHANGE_REASON reason, const CONTEXT *from, CONTEXT *to, INT32 info);
  void handle_probes_inserted (const Image & img);

  /// @}

private:
  /// {@ Pin Callbacks
  static void __fini (INT32 code, void * obj);
  static void __fini_unlocked (INT32 code, void * obj);
  static void __detach (void * obj);
  static void __detach_probed (void * obj);
  static void __thread_start (THREADID threadIndex, CONTEXT *ctxt, INT32 flags, VOID *v);
  static void __thread_fini (THREADID threadIndex, const CONTEXT *ctxt, INT32 flags, VOID *v);
  static void __syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj);
  static void __syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj);
  static BOOL __follow_child_process (CHILD_PROCESS child, VOID *val);
  static EXCEPT_HANDLING_RESULT __internal_exception_handler (THREADID threadIndex, EXCEPTION_INFO *, PHYSICAL_CONTEXT * pPhysCtxt, VOID *v);
  static size_t __fetch (void *buf, ADDRINT addr, size_t size, EXCEPTION_INFO *pExceptInfo, VOID *v);
  static void __out_of_memory (size_t size, VOID *v);
  static ADDRINT __memory_address_trans (PIN_MEM_TRANS_INFO *memTransInfo, VOID *v);

  static void __thread_attach_probed (VOID *sigmask, VOID *v);
  static void __thread_detach_probed (void);

  static void __application_start (void);
  static void __context_change (THREADID threadIndex, CONTEXT_CHANGE_REASON reason, const CONTEXT *from, CONTEXT *to, INT32 info, VOID *v);
  static void __probes_inserted (IMG img, VOID *v);
  /// @}

  Tool (const Tool &);
  const Tool & operator = (const Tool &);
};

} // namespace Pin
} // namespace OASIS

#include "Tool.inl"
#include "Tool.cpp"

#endif  // _OASIS_PIN_TOOL_H_
