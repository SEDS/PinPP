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
 * @class Context_Base
 *
 * Templated base class for Context wrappers.  Implements the getter methods.
 */
template <typename T>
class Context_Base
{
public:
  /// Initalizing constructor.
  Context_Base (T ctx);

  /// Destructor.
  ~Context_Base (void);

  /// CONTEXT conversion
  operator T () const;

  /// {@ PIN wrapper methods
  static bool supports_processor_state (PROCESSOR_STATE state);
  
#if (PIN_PRODUCT_VERSION_MAJOR < 2) || (PIN_PRODUCT_VERSION_MAJOR == 2 && PIN_PRODUCT_VERSION_MINOR <= 13)
  void get_regval (REG reg, REGVAL * val) const;
#else
  void get_regval (REG reg, UINT8 * val) const;
#endif

  ADDRINT get_reg (REG reg) const;

  ADDRINT get_syscall_return (SYSCALL_STANDARD std) const;
  ADDRINT get_syscall_number (SYSCALL_STANDARD std) const;
  ADDRINT get_syscall_argument (SYSCALL_STANDARD std, UINT32 argNum) const;

  void execute_at (void) const;
  /// @}

protected:
  /// The context
  T ctx_;
};

/**
 * @class Const_Context
 *
 * Wrapper class for a const PIN Context.
 */
class Const_Context : public Context_Base <const CONTEXT *>
{
public:
  /// Initalizing constructor.
  Const_Context (const CONTEXT * ctx);

  /// Destructor
  ~Const_Context (void);
};

/**
 * @class Context
 *
 * Wrapper class for the PIN Context. This is the mutable version,
 * so it has setters.
 */
class Context : public Context_Base <CONTEXT *>
{
public:
  Context (const Context & ctx);

  /// Initializing constructor.
  Context (CONTEXT * ctx);

  /// Destructor.
  ~Context (void);

  /// {@ Processor Methods
  static bool supports_processor_state (PROCESSOR_STATE state);
  bool contains_state (PROCESSOR_STATE state);
  /// @}

  /// @{ Register Methods
#if (PIN_PRODUCT_VERSION_MAJOR < 2) || (PIN_PRODUCT_VERSION_MAJOR == 2 && PIN_PRODUCT_VERSION_MINOR <= 13)
  void set_regval (REG reg, const REGVAL *val);
#else
  void set_regval (REG reg, const UINT8 * val);
#endif

  void set_reg (REG reg, ADDRINT val);
  /// @}
};

} // namespace OASIS
} // namespace Pin

#include "Context.inl"

#endif  // _OASIS_PIN_CONTEXT_H_
