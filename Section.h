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

/**
 * @class Section
 *
 * Wrapper class for the INS object in Pin.
 */
class Section
{
public:
  Section (SEC sec);
  Section (const Section & sec);

  /// Destructor.
  ~Section (void);

  /// Convert the object to a SEC type.
  operator SEC () const;

  IMG image (void) const;

  /// {@ Iterator Methods
  void next (void);
  void prev (void);
  bool valid (void) const;
  /// @}

  /// @{ Routine Methods
  Routine routine_head (void) const;
  Routine routine_tail (void) const;
  /// @}

  const string & name (void) const;
  SEC_TYPE type (void) const;
  bool mapped (void) const;
  const VOID * data (void) const;
  ADDRINT address (void) const;
  bool is_readable (void) const;
  bool is_writeable (void) const;
  bool is_executable (void) const;
  USIZE size (void) const;

private:
  SEC sec_;
};

} // namespace OASIS
} // namespace Pin

#include "Section.inl"

#endif  // _OASIS_PIN_Ins_H_
