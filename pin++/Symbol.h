// -*- C++ -*-

//==============================================================================
/**
 *  @file        Symbol.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      James H. Hill
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
  typedef Iterator2 <Symbol, &SYM_Prev, &SYM_Next> iterator_type;
  typedef Iterator2 <Symbol, &SYM_Next, &SYM_Prev> reverse_iterator_type;

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

  /// Undecorate a symbol.
  static std::string undecorate (const std::string & name, UNDECORATION style);

  /// Name of the symbol.
  const string & name (void) const;

  BOOL is_valid (void) const;
  BOOL is_dynamic (void) const;

#if PIN_BUILD_NUMBER < 71313
  BOOL is_ifunc (void) const;
#else
  BOOL is_ifunc_implementation (void) const;
  BOOL is_ifunc_resolver (void) const;
#endif

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

// Forward decl.
class Image;
  
/**
 * @class Symbols
 *
 * Adapter class that provides the interface expected for iteration. This class
 * acts like a containerb by providing the begin() and end() methods.
 */
class OASIS_PIN_Export Symbols
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       img         Source image
   */
  Symbols (const Image & img);
  
  /**
   * Copy constructor
   *
   * @param[in]       symbols     Source
   */
  Symbols (const Symbols & symbols);
  
  /// Destructor.
  ~Symbols (void);
  
  /// @{ Iterator Methods
  
  Symbol::iterator_type begin (void) const;
  Symbol::iterator_type end (void) const;

  Symbol::reverse_iterator_type rbegin (void) const;
  Symbol::reverse_iterator_type rend (void) const;
  
  /// @}
  
private:
  /// The target image for extracting the symbols.
  const Image & img_;
};
  
} // namespace OASIS
} // namespace Pin

#include "Symbol.inl"

#endif  // _OASIS_PIN_SYMBOL_H_
