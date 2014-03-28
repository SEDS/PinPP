// -*- C++ -*-

//========================================================================
/**
 * @file      Copy.h

 * @author    James H. Hill
 */
//========================================================================

#ifndef _OASIS_PIN_COPY_H_
#define _OASIS_PIN_COPY_H_

namespace OASIS
{

namespace Pin
{
  
/**
 * @class Copy
 *
 * Wrapper class for PIN_SafeCopy methods. The template parameter defines
 * the type to be copied. The size of memory to copy into this object is 
 * defined by the size of T.
 */
template <typename T>
class Copy
{
public:
  /// Default cosntructor.
  Copy (void);
  
  /**
   * Initializing constructor. This version of the constructor performs
   * a safe copy during the creation process.
   */
  Copy (const VOID * src);
  
  /// Copy the value from source into this object.
  void operator = (const VOID * src);
  
  /// Get the copied value.
  operator const T & () const;
  
private:
  /// Perform the safe copy.
  void perform_copy (const VOID * src);
  
  /// Target location for copied value.
  T value_;

  // prevent the following operations
  Copy (const Copy &);
  const Copy & operator = (const Copy &);
};
  
}
}

#include "Copy.inl"

#endif
