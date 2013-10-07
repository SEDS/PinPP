// -*- C++ -*-

//==============================================================================
/**
 *  @file        Ins.h
 *
 *  $Id: Ins.h 2305 2013-10-07 03:23:23Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_INS_H_
#define _OASIS_PIN_INS_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{
/**
 * @class Ins_Base
 *
 * Base class for the INS object types. This class is responsible for
 * implementing the non-mutable methods for INS.
 */
template <typename INS_TYPE>
class Ins_Base
{
public:
  /// Invalid instruction.
  static const INS invalid;
  static std::string opcode_string_short (UINT32 opcode);
  static std::string category_string_short (UINT32 num);
  static std::string extension_string_short (UINT32 num);

  /**
   * Initializing cosntructor
   *
   * @param[in]       ins       Instruction
   */
  Ins_Base (const INS & ins);

  /// Type conversion operator
  operator INS () const;

  /// {@ Inspection Methods

  INT32 category (void) const;
  INT32 extension (void) const;
  UINT32 effective_address_width (void) const;
  USIZE memory_write_size (void) const;
  USIZE memory_read_size (void) const;
  ADDRINT address (void) const;
  USIZE size (void) const;
  SYSCALL_STANDARD syscall_std (void) const;

  /**
   * Disassemble the current instruction.
   */
  string disassemble (void) const;

  UINT32 memory_operand_count (void) const;
  BOOL is_memory_operand_read (UINT32 mem_op) const;
  BOOL is_memory_operand_written (UINT32 mem_op) const;

  std::string mnemonic (void) const;

  BOOL is_valid (void) const;
  BOOL is_syscall (void) const;
  BOOL is_memory_read (void) const;
  BOOL is_memory_write (void) const;
  BOOL has_memory_read2 (void) const;
  BOOL has_fall_through (void) const;
  BOOL is_sysenter (void) const;
  BOOL is_nop (void) const;
  BOOL is_branch (void) const;
  BOOL is_branch_or_call (void) const;
  BOOL is_pc_materialization (void) const;
  BOOL is_call (void) const;
  BOOL is_far_call (void) const;
  BOOL is_far_jump (void) const;
  BOOL is_direct_far_jump (void) const;
  VOID get_far_pointer (UINT16 &segment_selector, UINT32 &displacement) const;
  BOOL is_procedure_call (void) const;
  BOOL is_interrupt (void) const;
  BOOL is_return (void) const;
  BOOL is_far_return (void) const;
  BOOL is_prefetch (void) const;
  BOOL is_atomic_update (void) const;
  BOOL is_indirect_branch_or_call (void) const;
  BOOL is_direct_branch_or_call (void) const;
  BOOL is_rewritable_mem_op_base (MEMORY_TYPE mtype, REG &base) const;
  BOOL is_stack_read (void) const;
  BOOL is_stack_write (void) const;
  BOOL is_ip_relative_read (void) const;
  BOOL is_ip_relative_write (void) const;

  REG reg_read (UINT32 k) const;
  REG reg_write (UINT32 k) const;

  OPCODE opcode (void) const;

  UINT32 max_number_rregs (void) const;
  UINT32 max_number_wregs (void) const;

  BOOL reg_read_contain (const REG reg) const;
  BOOL reg_write_contain (const REG reg) const;
  BOOL full_reg_read_contain (const REG reg) const;
  BOOL full_reg_write_contain (const REG reg) const;

  PREDICATE get_predicate (void) const;
  BOOL is_predicated (void) const;

  BOOL is_original (void) const;
  BOOL valid (void) const;

  void remove (void) const;

  /// @{ Operand Methods
  UINT32 operand_count (void) const;
  BOOL operand_is_memory (UINT32 n) const;
  REG operand_memory_base_reg (UINT32 n) const;
  REG operand_memory_index_reg (UINT32 n) const;
  REG operand_memory_segment_reg (UINT32 n) const;
  UINT32 operand_memory_scale (UINT32 n) const;
  INT64 operand_memory_displacement (UINT32 n) const;

  BOOL operand_is_fixed_memop (UINT32 n) const;
  BOOL operand_is_address_generator (UINT32 n) const;
  BOOL operand_is_branch_displacememt (UINT32 n) const;
  BOOL operand_is_reg (UINT32 n) const;
  REG operand_reg (UINT32 n) const;
  BOOL operand_is_immediate (UINT32 n) const;
  UINT64 operand_immediate (UINT32 n) const;
  BOOL operand_is_implicit (UINT32 n) const;
  UINT32 operand_width (UINT32 n) const;
  /// @}

    //RTN   LEVEL_PINCLIENT::INS_Rtn (INS x)
  ADDRINT direct_branch_or_call_target_address (void) const;
  ADDRINT next_address (void) const;
  /// @}

  /// @{ Insert Call Methods
  template <typename CALLBACK>
  void insert_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert If Call Methods
  template <typename CALLBACK>
  void insert_if_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert Then Call Methods
  template <typename CALLBACK>
  void insert_then_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert Predicated Call Methods
  template <typename CALLBACK>
  void insert_predicated_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert If Predicated Call Methods
  template <typename CALLBACK>
  void insert_if_predicated_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

  /// @{ Insert Then Predicated Call Methods
  template <typename CALLBACK>
  void insert_then_predicated_call (IPOINT location, CALLBACK * callback) const;

  template <typename CALLBACK, typename XARG1>
  void insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const;

  template <typename CALLBACK, typename XARG1, typename XARG2>
  void insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
  void insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const;

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const;
  /// @}

protected:
  INS_TYPE ins_;
};

/**
 * @class Ins_Ref
 *
 * Reference implementation of the Ins_Base class. This class is mainly
 * used in upcalls to wrap the INS without copying it.
 */
class Ins_Ref : public Ins_Base <const INS &>
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       ins       Instruction
   */
  Ins_Ref (const INS & ins);

private:
  // prevent the following operations
  Ins_Ref (const Ins_Ref &);
  const Ins_Ref & operator = (const Ins_Ref &);
};

/**
 * @class Ins_Ref
 *
 * Reference implementation of the Ins_Base class. This class is mainly
 * used in upcalls to wrap the INS without copying it.
 */
class Ins : public Ins_Base <INS>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       ins         Instruction
   */
  Ins (const INS & ins);

  /**
   * Copy constructor
   *
   * @param[in]       ins         Instruction object
   */
  Ins (const Ins & ins);

  /// Assignment operator
  const Ins & operator = (const Ins & ins);

  /// Move to the next instruction.
  Ins & next (void);

  /// Move to the previous instruction.
  Ins & prev (void);
};

} // namespace Pin
} // namespace OASIS

#include "Ins.inl"

#endif  // _OASIS_PIN_INS_H_
