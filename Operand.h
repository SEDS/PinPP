// -*- C++ -*-

//==============================================================================
/**
 *  @file        Operand.h
 *
 *  $Id: Operand.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_OPERAND_H_
#define _OASIS_PIN_OPERAND_H_

namespace OASIS
{
namespace Pin
{
// Forward decl.
class Ins;

/**
 * @class Operand
 *
 * Helper class for PIN Operand methods
 */
class OASIS_PIN_Export Operand
{
public:
  Operand (const Ins & ins, int index);
  Operand (const Operand & rhs);

  /// Destructor.
  ~Operand (void);

  /// Assignment operator
  const Operand & operator = (const Operand & sec);

private:
  const Ins & ins_;
  int index_;
};

} // namespace OASIS
} // namespace Pin

#include "Operand.inl"

#endif  // _OASIS_PIN_OPERAND_H_
