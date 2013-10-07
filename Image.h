// -*- C++ -*-

//==============================================================================
/**
 *  @file        Image.h
 *
 *  $Id: Image.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_IMAGE_H_
#define _OASIS_PIN_IMAGE_H_

#include "Section.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Image
 *
 * Wrapper class for the IMG object in Pin.
 */
class Image
{
public:
  /// Initializing constructor.
  Image (IMG img);

  /// Destructor.
  ~Image (void);

  /**
   * Convert the object to an INS value.
   */
  operator IMG () const;

  /// @{ Factory Methods
  static Image find_by_id (UINT32 id);
  static Image find_by_address (ADDRINT addr);
  static Image open (const std::string & filename);
  /// @}

  /// @{ Iterator Methods
  bool valid (void) const;
  void next (void);
  void prev (void);
  /// @}

  /// @{ Section Methods

  Section section_head (void) const;
  Section section_tail (void) const;

  /// @}

  ADDRINT entry (void) const;
  const std::string & name (void) const;
  ADDRINT gp (void) const;
  ADDRINT load_offset (void) const;
  ADDRINT low_address (void) const;
  ADDRINT high_address (void) const;
  ADDRINT start_address (void) const;
  USIZE size_mapped (void) const;
  IMG_TYPE type (void) const;
  bool is_main_executable (void) const;
  bool is_static_executable (void) const;
  UINT32 id (void) const;

  /// Close the open image.
  void close (void);

  Routine find_routine (const char * name) const;

private:
  /// Reference to target image object.
  IMG img_;
};

} // namespace OASIS
} // namespace Pin

#include "Image.inl"

#endif  // _OASIS_PIN_Ins_H_
