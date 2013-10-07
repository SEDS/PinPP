// -*- C++ -*-

//==============================================================================
/**
 *  @file        Bbl.h
 *
 *  $Id: Bbl.h 2299 2013-10-05 05:32:11Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_BBL_H_
#define _OASIS_PIN_BBL_H_

#include "pin.H"
#include "Ins.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Bbl
 *
 * Wrapper class for the INS object in Pin.
 */
class Bbl
{
public:
  /// Initializing constructor.
  Bbl (const BBL & bbl);

  /// Destructor.
  ~Bbl (void);

  /// Convert the object to a BBL type.
  operator BBL () const;

  /// @{ Instruction Methods
  UINT32 ins_count (void) const;
  Ins ins_head (void) const;
  Ins ins_tail (void) const;
  /// @}


  /// @{ Iterator Methods
  Bbl & next (void);
  Bbl & prev (void);
  /// @}

  /// @{ Inspection Methods
  bool is_valid (void) const;
  bool original (void) const;
  ADDRINT address (void) const;
  USIZE size (void) const;
  bool has_fall_through (void) const;
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

  /// @{ Insert If Call Methods
  template <typename CALLBACK>
  void insert_if_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert Then Call Methods
  template <typename CALLBACK>
  void insert_then_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

private:
  /// The target INS
  BBL bbl_;
};

} // namespace OASIS
} // namespace Pin

#include "Bbl.inl"

#endif  // _OASIS_PIN_Ins_H_
