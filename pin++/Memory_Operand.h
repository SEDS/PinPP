// -*- C++ -*-

//==============================================================================
/**
 *  @file        Memory_Operand.h
 *
 *  @author      James H. Hill <hillj@cs.iupui.edu>
 */
//==============================================================================

#ifndef _OASIS_PIN_MEMORY_OPERAND_H_
#define _OASIS_PIN_MEMORY_OPERAND_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Memory_Operand
 *
 * Wrapper class for Operand specificlly for memory operands.
 */
class Memory_Operand
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       ins       The parent instruction
   * @param[in]       index     Index of the operand
   */
  Memory_Operand (INS ins, int index);
  Memory_Operand (const Memory_Operand & copy);
  
  /// Destructor.
  ~Memory_Operand (void);

  bool is_read (void) const;
  bool is_written (void) const;

  /// Get the size of the memory operand.
  USIZE size (void) const;
  
  void rewrite (REG reg) const;

  /// Copy constructor.
  const Memory_Operand & operator = (const Memory_Operand & rhs);
  
private:
  /// The parent instruction of the memory operand.
  INS ins_;
  
  /// The index of the operand.
  int index_;
};

} // namespace OASIS
} // namespace Pin

#include "Memory_Operand.inl"

#endif  // _OASIS_PIN_MEMORY_OPERAND_H_
