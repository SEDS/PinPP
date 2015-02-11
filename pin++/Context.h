// -*- C++ -*-

//==============================================================================
/**
 *  @file        Context.h
 *
 *  $Id: Context.h 2289 2013-09-20 05:01:08Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_CONTEXT_H_
#define _OASIS_PIN_CONTEXT_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Context
 *
 * Wrapper facade class for the CONTEXT in Pin.
 */
class Context
{
public:
  /// Initalizing constructor.
  Context (CONTEXT * ctx);

  /// Destructor.
  ~Context (void);

  /**
   * Query if Pin supports the specified PROCESSOR_STATE.
   */
  static bool supports_processor_state (PROCESSOR_STATE state);
  bool contains_state (PROCESSOR_STATE state) const;
  
  /// @{ Type Conversion Operators
  
  operator CONTEXT * (void);
  operator const CONTEXT * (void) const;
  
  /// @}
  
#if (PIN_BUILD_NUMBER <= 61206)
  void get_regval (REG reg, REGVAL * val) const;
  void set_regval (REG reg, const REGVAL *val);
#else
  void get_regval (REG reg, UINT8 * val) const;
  void set_regval (REG reg, const UINT8 * val);
#endif

  ADDRINT get_reg (REG reg) const;
  void set_reg (REG reg, ADDRINT val);

  ADDRINT get_syscall_return (SYSCALL_STANDARD std) const;
  ADDRINT get_syscall_number (SYSCALL_STANDARD std) const;
  ADDRINT get_syscall_argument (SYSCALL_STANDARD std, UINT32 argNum) const;

  /**
   * A tool can call this API to abandon the current analysis function and resume 
   * execution of the calling thread at a new application register state. Note that 
   * this API does not return back to the caller's analysis function.
   */
  void execute_at (void) const;

private:
  /// Pointer to the Pin context.
  CONTEXT * ctx_;
  
  // prevent the following operations
  Context (const Context &);
  const Context & operator = (const Context &);
};

} // namespace OASIS
} // namespace Pin

#include "Context.inl"

#endif  // _OASIS_PIN_CONTEXT_H_
