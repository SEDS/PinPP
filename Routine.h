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

namespace OASIS
{
namespace Pin
{

/**
 * @class Routine
 *
 * Wrapper class for the RTN object in Pin.
 */
class Routine
{
public:
  Routine (RTN rtn);

  Routine (const Routine & rtn);

  /// Destructor.
  ~Routine (void);

  const Routine & operator = (const Routine & rtn);

  operator RTN () const;

  bool valid (void);

  /// {@ Iterator Methods
  void prev (void);
  void next (void);
  /// @}

  SEC section (void) const;
  const std::string & name (void) const;
  SYM symbol (void) const;
  INT32 id (void) const;
  AFUNPTR function_ptr (void) const;
  USIZE size (void) const;

  static string find_name_by_address (ADDRINT addr);
  static Routine find_by_address (ADDRINT addr);
  static Routine create_at (ADDRINT address, string name);

  void open (void);
  void close (void);

  /// @{ Instruction Methods
  Ins instruction_head (void) const;
  Ins instruction_head_only (void) const;
  Ins instruction_tail (void) const;
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

  /// @{ Insert Call Methods
  template <typename CALLBACK>
  void insert_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert Call Probed Methods
  template <typename CALLBACK>
  void insert_call_probed (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

private:
  RTN rtn_;
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
  Routine_Guard (Routine & rtn);

  /// Destructor.
  ~Routine_Guard (void);

private:
  /// Target routine.
  Routine & rtn_;
};

} // namespace OASIS
} // namespace Pin

#include "Routine.inl"
#include "Routine.cpp"

#endif  // _OASIS_PIN_Ins_H_
