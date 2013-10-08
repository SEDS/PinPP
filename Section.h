// -*- C++ -*-

//==============================================================================
/**
 *  @file        Section.h
 *
 *  $Id: Section.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_SECTION_H_
#define _OASIS_PIN_SECTION_H_

#include "Routine.h"

namespace OASIS
{
namespace Pin
{
// Forward decl.
class Image;

/**
 * @class Section
 *
 * Wrapper class for the INS object in Pin.
 */
class OASIS_PIN_Export Section
{
public:
  /// Type definition of the Pin type need for the iterator.
  typedef SEC pin_type;

  /// Type definition of the iterator type.
  typedef Iterator <Section, &SEC_Prev, &SEC_Next> iterator_type;

  Section (SEC sec);
  Section (const Section & sec);

  /// Destructor.
  ~Section (void);

  /// Assignment operator.
  const Section & operator = (const Section & sec);

  static const SEC invalid;

  /// Make an iterator from this section.
  iterator_type make_iter (void) const;

  /// Convert the object to a SEC type.
  operator SEC () const;

  /// Get the parent image.
  Image image (void) const;

  /// Test if the section if valid.
  BOOL valid (void) const;

  /// @{ Iterator Methods
  Routine::iterator_type routine_head (void) const;
  Routine::iterator_type routine_tail (void) const;
  /// @}

  const string & name (void) const;
  SEC_TYPE type (void) const;
  BOOL mapped (void) const;
  const VOID * data (void) const;
  ADDRINT address (void) const;
  BOOL is_readable (void) const;
  BOOL is_writeable (void) const;
  BOOL is_executable (void) const;
  USIZE size (void) const;

private:
  SEC sec_;
};

} // namespace OASIS
} // namespace Pin

#include "Section.inl"

#endif  // _OASIS_PIN_Ins_H_
