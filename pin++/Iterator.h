// -*- C++ -*-

//==============================================================================
/**
 *  @file        Iterator.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_ITERATOR_H_
#define _OASIS_PIN_ITERATOR_H_

namespace OASIS
{
namespace Pin
{

/**
 * @class Iterator
 *
 * STL-like iterator used by all objects that support iteration.
 */
template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
class Iterator
{
public:
  typedef typename T::pin_type pin_type;

  /// Default constructor.
  Iterator (void);

  /// Initializing constructor.
  Iterator (const T & t);

  /// Initializing constructor.
  Iterator (const pin_type & t);

  /// Copy constructor.
  Iterator (const Iterator & iter);

  /// Destructor.
  ~Iterator (void);

  /// Assignment operator
  const Iterator & operator = (const Iterator & rhs);

  /// {@ Reference/Dereference Operators
  T & operator * (void);
  T * operator -> (void);
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
  /// Pin++ wrapper to iterate over.
  T wrapper_;
};
  
/**
 * @class Iterator2
 *
 * Implementation of iterator for wrapper classes that store their Pin
 * types by reference.
 */
template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
class Iterator2
{
public:
  typedef typename T::pin_type pin_type;
    
  /// Default constructor.
  Iterator2 (void);
    
  /// Initializing constructor.
  Iterator2 (const T & t);
    
  /// Initializing constructor.
  Iterator2 (const pin_type & t);
    
  /// Copy constructor.
  Iterator2 (const Iterator2 & iter);
    
  /// Destructor.
  ~Iterator2 (void);
    
  /// Assignment operator
  const Iterator2 & operator = (const Iterator2 & rhs);
    
  /// {@ Reference/Dereference Operators
  T & operator * (void);
  T * operator -> (void);
  /// @}
    
  /// Make an end iterator.
  Iterator2 make_end (void) const;
    
  /// @{ Prefix Operators
  Iterator2 & operator ++ (void);
  Iterator2 & operator -- (void);
  /// @}
    
  /// @{ Postfix Operators
  Iterator2 operator ++ (int);
  Iterator2 operator -- (int);
  /// @}
    
  /// {@ Comparision Operators
  bool operator == (const Iterator2 & rhs) const;
  bool operator != (const Iterator2 & rhs) const;
  /// @}
    
private:
  /// The current iterator position.
  pin_type curr_;
    
  /// Wrapper to pin_type_. The value of this object should
  /// never change after construction.
  T wrapper_;
};

} // namespace OASIS
} // namespace Pin

#include "Iterator.inl"
#include "Iterator.cpp"

#endif  // _OASIS_PIN_ITERATOR_H_
