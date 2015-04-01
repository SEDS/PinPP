// -*- C++ -*-

//==============================================================================
/**
 *  @file        Routine.h
 *
 *  $Id: Routine.h 2299 2013-10-05 05:32:11Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_ROUTINE_H_
#define _OASIS_PIN_ROUTINE_H_

#include "Ins.h"
#include "Symbol.h"

namespace OASIS
{
namespace Pin
{
// Forward decl.
class Section;

/**
 * @class Routine
 *
 * Wrapper class for the RTN object in Pin. Unlike the other wrapper classes,
 * this class does not store a reference to the object. This is because routine's
 * can be created, and passed around. It is thereforehard (or incorr ect) to
 * store a reference since the original RTN object is not dynamically allocated.
 */
class Routine
{
public:
  /// Type definition of the Pin type.
  typedef RTN pin_type;

  /// Type definition of the iterator type.
  typedef Iterator <Routine, &RTN_Prev, &RTN_Next> iterator_type;
  typedef Iterator <Routine, &RTN_NExt, &RTN_Prev> reverse_iterator_type;

  /// Pointer to INS_InsertCall
  static const Insert_Call_T <Routine>::funcptr_type __insert_call;
  /// @}

  /// Initializing constructor.
  Routine (RTN rtn);

  /// Copy constructor.
  Routine (const Routine & rtn);

  /// Destructor.
  ~Routine (void);

  /// Invalid type.
  static const RTN invalid;

  /// Assignment operator for pin++ type.
  const Routine & operator = (const Routine & rtn);

  /// Assignment operator for pin type.
  const Routine & operator = (const RTN & rtn);

  /// {@ Comparison Operators
  bool operator == (const Routine & rhs) const;
  bool operator != (const Routine & rhs) const;
  /// @}

  /// Conversion operator.
  operator RTN () const;

  /// Test if the routine is valid.
  bool valid (void);

  /// Get the parent section.
  Section section (void) const;

  /// Get the name of the routine.
  const std::string & name (void) const;

  /// Get the routine's id.
  INT32 id (void) const;

  /// Get the function pointer for the routine. This is useful for
  /// invoking the routine from the tool.
  AFUNPTR function_ptr (void) const;

  /// Get the routine's size.
  USIZE size (void) const;

  /// Get the routine's range.
  USIZE range (void) const;

#if PIN_BUILD_NUMBER < 67254
  /// Clear history of routine check
  static VOID delete_check_history (void);
#endif

  /// @{ Search Methods
  static std::string find_name (ADDRINT addr);
  static Routine find (ADDRINT addr);
  /// @}

  /// Create iterator starting at the current routine.
  iterator_type make_iterator (void) const;

  /// Create a new routine.
  static Routine create (ADDRINT address, string name);

  /// Open a routine for usage.
  void open (void) const;

  /// Close the current routine.
  void close (void) const;

  /// Get symbol representation of the routine.
  const Symbol & symbol (void) const;

  /// @{ Instruction Methods
  Ins::iterator_type begin (void) const;
  Ins::iterator_type end (void) const;

  Ins::reverse_iterator_type rbegin (void) const;
  Ins::reverse_iterator_type rend (void) const;

  Ins::iterator_type begin_only (void) const;
  UINT32 instruction_count (void) const;
  /// @}

  template <typename REPLACEMENT>
  void replace (void);

  template <typename REPLACEMENT>
  void replace_signature (CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  ADDRINT address (void) const;

  /// @{ Probe Mode
  bool is_safe_for_probed_insertion (void) const;
  bool is_safe_for_probed_insertion_ex (PROBE_MODE mode) const;
  bool is_safe_for_probed_replacement (void) const;
  bool is_safe_for_probed_replacement_ex (PROBE_MODE mode) const;

  template <typename REPLACEMENT>
  void replace_probed (void);

  template <typename REPLACEMENT>
  void replace_probed (PROBE_MODE mode);

  template <typename REPLACEMENT>
  void replace_signature_probed (CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  template <typename REPLACEMENT>
  void replace_signature_probed (PROBE_MODE mode, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  INT32 code_ranges_probed (INT32 num, PIN_CODE_RANGE *buffer);
  /// @}

private:
  RTN rtn_;
  
  /// Symbol associated with routine.
  mutable SYM sym_;
  
  /// Wrapper for the symbol.
  Symbol symbol_;
};

/**
 * @class Routine_Guard
 *
 * Utility class for open/closing a routine within a scope.
 */
class Routine_Guard
{
public:
  /// Initializing constructor.
  Routine_Guard (const Routine & rtn);

  /// Destructor.
  ~Routine_Guard (void);

private:
  const Routine & rtn_;
};

} // namespace OASIS
} // namespace Pin

#include "Routine.inl"
#include "Routine_T.cpp"

#endif  // _OASIS_PIN_Ins_H_
