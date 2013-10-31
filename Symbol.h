// -*- C++ -*-

//==============================================================================
/**
 *  @file        Symbol.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_SYMBOL_H_
#define _OASIS_PIN_SYMBOL_H_

#include "pin.H"
#include "Iterator.h"

#include "Pin_export.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Symbol
 *
 * Wrapper class for the Pin SYM object.
 */
class OASIS_PIN_Export Symbol
{
public:
  /// Type definition of the Pin type.
  typedef SYM pin_type;

  /// Type definition of the iterator type.
  typedef Iterator <Symbol, &SYM_Prev, &SYM_Next> iterator_type;

  /// Default constructor.
  Symbol (SYM & sym);

  /// Destructor.
  ~Symbol (void);

  static const SYM invalid;

  /// Convert the object to a BBL type.
  operator SYM () const;

  /// {@ Comparison Operators
  bool operator == (const Symbol & rhs) const;
  bool operator != (const Symbol & rhs) const;
  /// @}

  iterator_type make_iter (void) const;

  /// Undecorate a symbol.
  static std::string undecorate (const std::string & name, UNDECORATION style);

  /// Name of the symbol.
  const string & name (void) const;

  BOOL is_valid (void) const;
  BOOL is_dynamic (void) const;
  BOOL is_ifunc (void) const;

  /// Value of the symbol.
  ADDRINT value (void) const;

  /// Index of the symbol.
  UINT32 index (void) const;

  /// Address of the symbol.
  ADDRINT address (void) const;

  /// Undecorate the current symbol.
  std::string undecorate (UNDECORATION style) const;

private:
  SYM & sym_;
};

/**
 * @class Iterator <Symbol, &SYM_Prev, &SYM_Next specalization
 */
template <>
class Iterator <Symbol, &SYM_Prev, &SYM_Next>
{
public:
  typedef typename Symbol::pin_type pin_type;

  /// Default constructor.
  Iterator (void);

  /// Initializing constructor.
  Iterator (const Symbol & t);

  /// Initializing constructor.
  Iterator (const pin_type & t);

  /// Copy constructor.
  Iterator (const Iterator & iter);

  /// Destructor.
  ~Iterator (void);

  /// Assignment operator
  const Iterator & operator = (const Iterator & rhs);

  /// {@ Reference/Dereference Operators
  Symbol & operator * (void);
  Symbol * operator -> (void);
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
  Symbol wrapper_;
};

} // namespace OASIS
} // namespace Pin

#include "Symbol.inl"

#endif  // _OASIS_PIN_SYMBOL_H_
