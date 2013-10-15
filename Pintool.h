// -*- C++ -*-

//==============================================================================
/**
 *  @file        Pintool.h
 *
 *  $Id: Pintool.h 2306 2013-10-07 05:03:46Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_PINTOOL_H_
#define _OASIS_PIN_PINTOOL_H_

#include "Exception.h"
#include "Tool.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Pintool
 *
 * Utility class for instantiating a loaded tool in Pin. This wrapper
 * class prevents the implementation from needing virtual methods.
 */
template <typename T>
class Pintool
{
public:
  /// Type definition of the tool.
  typedef T type;

  /**
   * Initializing constructor.
   */
  Pintool (int argc, char * argv []);

  /// Destructor.
  ~Pintool (void);

  /// Initialize the symbols.
  Pintool & init_symbols (void);

  /// Initialize the symbols in a certain mode.
  Pintool & init_symbols (SYMBOL_INFO_MODE mode);

  /// {@ Enable control/initalization callbacks
  Pintool & enable_thread_start (void);
  Pintool & enable_thread_fini (void);
  Pintool & enable_syscall_entry (void);
  Pintool & enable_syscall_exit (void);
  Pintool & enable_internal_exception_handler (void);
  Pintool & enable_detach (void);
  /// @}

  /// Start the program in JIT mode.
  void start_program (void);

  /// Start the program in probed mode. It is recommended that the
  /// program is only started in this mode when instrumenting at
  /// routine or image level.
  ///
  /// @TODO Add a static check validates T is of type Routine_Tool or
  /// Image_Tool when this method is invoked.
  void start_program_probed (void);

private:
  /// {@ Pin Callbacks
  static void __detach (void * obj);
  static void __thread_start (THREADID threadIndex, CONTEXT *ctxt, INT32 flags, VOID *v);
  static void __thread_fini (THREADID threadIndex, const CONTEXT *ctxt, INT32 flags, VOID *v);
  static void __syscall_entry (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj);
  static void __syscall_exit (THREADID thr_index, CONTEXT * ctxt, SYSCALL_STANDARD std, VOID * obj);
  static EXCEPT_HANDLING_RESULT __internal_exception_handler (THREADID threadIndex, EXCEPTION_INFO *, PHYSICAL_CONTEXT * pPhysCtxt, VOID *v);
  /// @}

  /// Implementation of the tool.
  T * tool_;
};

} // namespace OASIS
} // namespace Pin

#include "Pintool.inl"
#include "Pintool.cpp"

#endif  // _OASIS_PIN_PINTOOL_H_
