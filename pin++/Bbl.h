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
  typedef Iterator2 <Bbl, &BBL_Prev, &BBL_Next> iterator_type;

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
  Ins::iterator_type begin (void) const;
  Ins::iterator_type end (void) const;
  /// @}

  /// @{ Inspection Methods
  bool is_valid (void) const;
  bool original (void) const;
  ADDRINT address (void) const;
  USIZE size (void) const;
  bool has_fall_through (void) const;
  /// @}

  void move_all_attributes (const Bbl & bbl);

  /// Set the target version for all Traces in the Bbl
  void set_target_version (ADDRINT version);

  /// {@ Code Cache methods
  ADDRINT code_cache_address (void) const;
  USIZE code_cache_size (void) const;
  /// @}

  /// @{ Insert Pointers

  /// Pointer to INS_InsertCall
  static const Insert_Call_T <Bbl>::funcptr_type __insert_call;
  /// @}

private:
  /// The target BBL
  BBL & bbl_;

  /// Temp fix since ::BBL_Invalid () does not exist. Once Pin implements
  /// BBL_Invalid (), then we will remove this function.
  static BBL BBL_Invalid (void);
};

} // namespace OASIS
} // namespace Pin

#include "Bbl.inl"

#endif  // _OASIS_PIN_Bbl_H_
