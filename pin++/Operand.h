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

#include "pin.H"
#include "Pin_export.h"

namespace OASIS
{
namespace Pin
{

// Forward decl.
class Memory_Operand;
  
/**
 * @class Operand
 *
 * Helper class for PIN Operand methods
 */
class OASIS_PIN_Export Operand
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]     ins         Parent instruction of the operand
   * @param[in]     index       Index of the operand
   */
  Operand (INS ins, int index);
  
  /**
   * Copy constructor.
   */
  Operand (const Operand & rhs);

  /// Destructor.
  ~Operand (void);

  /// Assignment operator
  const Operand & operator = (const Operand & sec);

  /// {@ Memory Operand Methods

  /// Test if the operand is a memory operand.
  bool is_memory (void) const;
  
  /// Convert this operand to a memory operand. This method should only
  /// be called if the is_memory() method returns true.
  Memory_Operand to_memory_operand (void) const;
  
  REG memory_base_reg (void) const;
  REG memory_index_reg (void) const;
  REG memory_segment_reg (void) const;
  UINT32 memory_scale (void) const;
  INT64 memory_displacement (void) const;
  bool is_fixed_memop (void) const;
  /// @}

  /// {@ Generic ops

  bool is_address_generator (void) const;
  bool is_branch_displacememt (void) const;
  bool is_reg (void) const;
  REG reg (void) const;
  bool is_immediate (void) const;
  UINT64 immediate (void) const;
  bool is_implicit (void) const;
  UINT32 width (void) const;
  UINT32 name_id (void) const;
  bool is_read (void) const;
  bool is_read_only (void) const;
  bool is_written (void) const;
  bool is_written_only (void) const;
  bool is_read_and_written (void) const;
  /// @}

protected:
  /// The parent instruction of the operand.
  INS ins_;
  
  /// The index of the operand.
  int index_;
};

/**
 * @class Memory_Operand
 *
 * Wrapper class for Operand specificlly for memory operands.
 */
class Memory_Operand : public Operand
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       ins       Parent instruction of the operand
   * @param[in]       index     Index of the operand
   */
  Memory_Operand (INS ins, int index);

  /**
   * Copy constructor
   */
  Memory_Operand (const Memory_Operand & copy);
    
  /// Destructor.
  ~Memory_Operand (void);
    
  bool is_read (void) const;
  bool is_written (void) const;
    
  /// Get the size of the memory operand.
  USIZE size (void) const;
    
  void rewrite (REG reg) const;
    
  const Memory_Operand & operator = (const Memory_Operand & rhs);
};

} // namespace OASIS
} // namespace Pin

#include "Operand.inl"

#endif  // _OASIS_PIN_OPERAND_H_
