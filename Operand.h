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

#include "Ins.h"

namespace OASIS
{
namespace Pin
{

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

  /// {@ Memory ops

  BOOL is_memory_read (void) const;
  BOOL is_memory_written (void) const;
  BOOL is_memory (void) const;
  REG memory_base_reg (void) const;
  REG memory_index_reg (void) const;
  REG memory_segment_reg (void) const;
  UINT32 memory_scale (void) const;
  INT64 memory_displacement (void) const;
  BOOL is_fixed_memop (void) const;

  /// @}

  /// {@ Generic ops

  BOOL is_address_generator (void) const;
  BOOL is_branch_displacememt (void) const;
  BOOL is_reg (void) const;
  REG reg (void) const;
  BOOL is_immediate (void) const;
  UINT64 immediate (void) const;
  BOOL is_implicit (void) const;
  UINT32 width (void) const;

  /// @}

private:
  const Ins & ins_;
  int index_;
};

} // namespace OASIS
} // namespace Pin

#include "Operand.inl"

#endif  // _OASIS_PIN_OPERAND_H_
