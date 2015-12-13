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
#include "Symbol.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Image
 *
 * Wrapper class for the IMG object in Pin.
 */
class OASIS_PIN_Export Image
{
public:
  /// Type definition of the Pin type need for the iterator.
  typedef IMG pin_type;

  /// Type definition of the iterator type.
  typedef Iterator <Image, &IMG_Prev, &IMG_Next> iterator_type;
  typedef Iterator <Image, &IMG_Next, &IMG_Prev> reverse_iterator_type;
  
  /// Initializing constructor.
  Image (const IMG & img);
  Image (const Image & img);

  /// Destructor.
  ~Image (void);

  /// Invalid identifier for an image.
  static const IMG invalid;

  /**
   * Convert the object to an INS value.
   */
  operator IMG () const;

  const Image & operator = (const Image & img);
  const Image & operator = (const IMG & img);

  /// {@ Comparison Operators
  bool operator == (const Image & rhs) const;
  bool operator != (const Image & rhs) const;
  /// @}

  /// @{ Search Methods
  static Image find_by_id (UINT32 id);
  static Image find_by_address (ADDRINT addr);
  /// @}

  /// Open image based on a filename.
  static Image open (const std::string & filename);

  /// Open first image loaded into memory
  static Image head (void);

  /// Open last image loaded into memory
  static Image tail (void);

  bool valid (void) const;
  iterator_type make_iter (void) const;

  /// Get an iterator to the head of the regular symbols.
  Symbols symbols (void) const;

  /// @{ Section Methods
  Section::iterator_type begin (void) const;
  Section::iterator_type end (void) const;
  
  Section::reverse_iterator_type rbegin (void) const;
  Section::reverse_iterator_type rend (void) const;
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

  Routine find_routine (const std::string & name) const;
  Routine find_routine (const char * name) const;
  
private:
  /// Reference to target image object.
  IMG img_;
};

} // namespace OASIS
} // namespace Pin

#include "Image.inl"

#endif  // _OASIS_PIN_Ins_H_
