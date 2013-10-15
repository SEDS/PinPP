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

  /// {@ ControlIinitalization Callback Registration
  void register_fini_callback (void);
  void unregister_fini_callbacks (void);

  template <typename CALLBACK>
  void add_fork_function (FPOINT location, CALLBACK * callback);

  template <typename CALLBACK>
  void add_follow_child_process_function (CALLBACK * callback);
  /// @}

  /// {@ Execute control/initalizion callbacks
  void detach (void);
  /// @}

  /// {@ Callback Handler Methods
  void handle_fini (int code);
  void handle_detach (void);

  void handle_thread_start (THREADID threadIndex, Context & ctxt, INT32 flags);
  void handle_thread_fini (THREADID threadIndex, const Const_Context & ctxt, INT32 flags);
  void handle_destroy_thread_data (void * data);

  void handle_syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std);
  void handle_syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std);
  EXCEPT_HANDLING_RESULT handle_internal_exception (THREADID, Exception & ex, PHYSICAL_CONTEXT *);
  /// @}

  /// {@ Stateless PIN call wrappers
  static void get_source_location (ADDRINT address, INT32 * column, INT32 * line, string * filename);
  static bool is_process_exiting (void);
  static void exit_process (const INT32 code);
  static void exit_application (const INT32 code);
  static int get_pid (void);
   /// @}

private:
  /// {@ Pin Callbacks
  static void __fini (int code, void * obj);
  /// @}

  Tool (const Tool &);
  const Tool & operator = (const Tool &);
};

} // namespace Pin
} // namespace OASIS

#include "Tool.inl"

#endif  // _OASIS_PIN_TOOL_H_
