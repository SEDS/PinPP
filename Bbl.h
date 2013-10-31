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

#include "Ins.h"
#include "Pin_export.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Bbl
 *
 * Wrapper class for the INS object in Pin.
 */
class OASIS_PIN_Export Bbl
{
public:
  /// Type definition for Iterator support.
  typedef BBL pin_type;

  /// Type definition of the iterator type.
  typedef Iterator <Bbl, &BBL_Prev, &BBL_Next> iterator_type;

  /// Initializing constructor.
  Bbl (BBL & bbl);

  /// Destructor.
  ~Bbl (void);

  static const BBL invalid;

  /// Convert the object to a BBL type.
  operator BBL () const;

  /// {@ Comparison Operators
  bool operator == (const Bbl & rhs) const;
  bool operator != (const Bbl & rhs) const;
  /// @}

  /// @{ Instruction Methods
  UINT32 ins_count (void) const;
  Ins::iterator_type ins_head (void) const;
  Ins::iterator_type ins_tail (void) const;
  /// @}

  /// @{ Inspection Methods
  bool is_valid (void) const;
  bool original (void) const;
  ADDRINT address (void) const;
  USIZE size (void) const;
  bool has_fall_through (void) const;
  /// @}

  void move_all_attributes (const Bbl & bbl);

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
  /// The target BBL
  BBL & bbl_;

  /// Temp fix since ::BBL_Invalid () does not exist. Once Pin implements
  /// BBL_Invalid (), then we will remove this function.
  static BBL BBL_Invalid (void);
};

/**
 * @class Iterator <Bbl, &BBL_PREV, &BBL_NEXT specalization
 */
template <>
class Iterator <Bbl, &BBL_Prev, &BBL_Next>
{
public:
  typedef typename Bbl::pin_type pin_type;

  /// Default constructor.
  Iterator (void);

  /// Initializing constructor.
  Iterator (const Bbl & t);

  /// Initializing constructor.
  Iterator (const pin_type & t);

  /// Copy constructor.
  Iterator (const Iterator & iter);

  /// Destructor.
  ~Iterator (void);

  /// Assignment operator
  const Iterator & operator = (const Iterator & rhs);

  /// {@ Reference/Dereference Operators
  Bbl & operator * (void);
  Bbl * operator -> (void);
  /// @}

  /// Make an end iterator.
  Iterator make_end (void) const;

  /// @{ Prefix Operators
  Iterator & operator ++ (void);
  Iterator & operator -- (void);
  /// @}

  /// @{ Postfix Operators
  Iterator operator ++ (int);
  Iterator operator -- (int);
  /// @}

  /// {@ Comparision Operators
  bool operator == (const Iterator & rhs) const;
  bool operator != (const Iterator & rhs) const;
  /// @}

private:
  /// The current iterator position.
  pin_type curr_;

  /// Wrapper to pin_type_. The value of this object should
  /// never change after construction.
  Bbl wrapper_;
};

} // namespace OASIS
} // namespace Pin

#include "Bbl.inl"

#endif  // _OASIS_PIN_Bbl_H_
