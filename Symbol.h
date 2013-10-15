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
  Symbol (const SYM & sym);

  /// Destructor.
  ~Symbol (void);

  static const SYM invalid;

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

} // namespace OASIS
} // namespace Pin

#include "Symbol.inl"

#endif  // _OASIS_PIN_SYMBOL_H_
