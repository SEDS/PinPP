// -*- C++ -*-

//==============================================================================
/**
 *  @file        Buffer.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_BUFFER_H_
#define _OASIS_PIN_BUFFER_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Buffer
 *
 * Utility buffer designed to be used in STL containers. Unlike std::vector,
 * the buffer is not released in the destructor. Instead, you must manually
 * release the buffer using the release() method.
 */
template <typename T>
class Buffer
{
public:
  typedef T item_type;
  typedef T * pointer_type;

  typedef T * iterator;
  typedef const T * const_iterator;

  /// Default constructor.
  Buffer (size_t count);

  /// Copy constructor.
  Buffer (const Buffer & buf);

  /// Destructor.
  ~Buffer (void);

  const Buffer & operator = (const Buffer & buf);

  /// Release the buffer.
  void release (void);

  /// @{ Iterator Methods
  iterator begin (void);
  const_iterator begin (void) const;

  iterator end (void);
  const_iterator end (void) const;
  /// @}

private:
  /// Items in the buffer.
  T * items_;

  /// Number of items in the buffer.
  size_t count_;
};

} // namespace OASIS
} // namespace Pin

#include "Buffer.inl"
#include "Buffer.cpp"

#endif  // _OASIS_PIN_BUFFER_H_
