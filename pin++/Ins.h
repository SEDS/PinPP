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
#include "Iterator.h"
#include "Insert_T.h"

#include "Pin_export.h"

namespace OASIS
{
namespace Pin
{
// Forward decl.
class Routine;
class Operand;

/**
 * @class Ins
 *
 * Wrapper class for the INS type. This class take a reference to the
 * contained INS object since an INS cannot be created. Instead, it is
 * always passed to the instrumentation object. By using a reference,
 * we are reducing the number of copies.
 */
class OASIS_PIN_Export Ins
{
public:
  /// Type definition for Iterator support.
  typedef INS pin_type;

  /// Type definition of the iterator type.
  typedef Iterator2 <Ins, &INS_Prev, &INS_Next> iterator_type;

  /// Invalid instruction.
  static const INS invalid;

  static std::string opcode_string_short (UINT32 opcode);
  static std::string category_string_short (UINT32 num);
  static std::string extension_string_short (UINT32 num);

  /// @{ Insert Pointers

  /// Pointer to INS_InsertCall
  static const Insert_Call_T <Ins>::funcptr_type __insert_call;

  /// @}

  /**
   * Initializing cosntructor
   *
   * @param[in]       ins       Instruction
   */
  Ins (INS & ins);

  /// Type conversion operator
  operator INS () const;

  /// {@ Comparison Operators
  bool operator == (const Ins & rhs) const;
  bool operator != (const Ins & rhs) const;
  /// @}

  /// Make an iterator to the current instruction.
  iterator_type make_iter (void) const;

  /// {@ Operand Methods

  Operand operand (int index) const;
  Operand operator [] (int index) const;
  UINT32 memory_operand_count (void) const;
  UINT32 operand_count (void) const;

  /// @}

  /// {@ Inspection Methods

  /// Get the instructions' category.
  INT32 category (void) const;

  INT32 extension (void) const;
  UINT32 effective_address_width (void) const;
  USIZE memory_write_size (void) const;
  USIZE memory_read_size (void) const;

  /// Get the address of the instruction.
  ADDRINT address (void) const;

  /// Get the size of the instruction
  USIZE size (void) const;

  SYSCALL_STANDARD syscall_std (void) const;

  /**
   * Disassemble the current instruction.
   */
  string disassemble (void) const;

  /// Get the mnemonic for the instruction.
  std::string mnemonic (void) const;

  BOOL is_valid (void) const;
  BOOL is_syscall (void) const;
  BOOL is_memory_read (void) const;
  BOOL is_memory_write (void) const;
  BOOL has_memory_read2 (void) const;
  BOOL has_fall_through (void) const;
  BOOL is_sysenter (void) const;
  BOOL is_lea (void) const;
  BOOL is_nop (void) const;
  BOOL is_branch (void) const;
  BOOL is_direct_branch (void) const;
  BOOL is_direct_call (void) const;
  BOOL is_branch_or_call (void) const;
  BOOL stutters (void) const;
  BOOL is_pc_materialization (void) const;
  BOOL is_call (void) const;
  BOOL is_far_call (void) const;
  BOOL is_far_jump (void) const;
  BOOL is_direct_far_jump (void) const;
  VOID get_far_pointer (UINT16 &segment_selector, UINT32 &displacement) const;
  BOOL is_procedure_call (void) const;
  BOOL is_interrupt (void) const;
  BOOL is_return (void) const;
  BOOL is_system_return (void) const;
  BOOL is_far_return (void) const;
  BOOL is_prefetch (void) const;
  BOOL is_atomic_update (void) const;
  BOOL is_indirect_branch_or_call (void) const;
  BOOL is_direct_branch_or_call (void) const;
  BOOL is_stack_read (void) const;
  BOOL is_stack_write (void) const;
  BOOL is_ip_relative_read (void) const;
  BOOL is_ip_relative_write (void) const;
  BOOL is_xbegin (void) const;
  BOOL is_xchg (void) const;
  BOOL is_xend (void) const;
  BOOL is_halt (void) const;
  BOOL is_vgather (void) const;

  BOOL is_sub (void) const;
  BOOL is_mov (void) const;
  // Returns true if instruction is a mov reg1, reg1 and reg1 is a full reg
  BOOL is_mov_reg_reg_same (void) const;
  BOOL is_rdtsc (void) const;
  BOOL is_mask_mov (void) const;
  BOOL is_string_op (void) const;
  BOOL is_iret (void) const;

#if (PIN_PRODUCT_VERSION_MAJOR > 2) || (PIN_PRODUCT_VERSION_MAJOR == 2 && PIN_PRODUCT_VERSION_MINOR >= 13)
  BOOL is_vscatter (void) const;
#endif


  BOOL has_real_rep (void) const;
  BOOL seg_prefix_is_memory_read (void) const;
  BOOL seg_prefix_is_memory_write (void) const;
  BOOL address_size_prefix (void) const;
  BOOL branch_not_taken_prefix (void) const;
  BOOL lock_prefix (void) const;
  BOOL operand_size_prefix (void) const;
  BOOL rep_prefix (void) const;
  BOOL repne_prefix (void) const;
  BOOL segment_prefix (void) const;

  REG reg_read (UINT32 k) const;
  REG reg_write (UINT32 k) const;
  REG rep_counter (void) const;
  REG segment_reg_prefix (void) const;

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

  /// Test if the current instruction is valid.
  BOOL valid (void) const;

  /// Remove the current instruction from the execution.
  void remove (void) const;

  /// Get the parent routine.
  Routine routine (void) const;

  ADDRINT direct_branch_or_call_target_address (void) const;
  ADDRINT next_address (void) const;
  ADDRDELTA memory_displacement (void) const;
  REG memory_base_reg (void) const;
  REG memory_index_reg (void) const;
  UINT32 memory_scale (void) const;
  BOOL change_reg (const REG old_reg, const REG new_reg, const BOOL as_read) const;
  VOID get_mem_accesses (int * num, int * size, int * indexSize) const;
  /// @}

  void insert_version_case (REG reg, INT32 case_value, ADDRINT new_version, CALL_ORDER order = CALL_ORDER_DEFAULT) const;

  void insert_indirect_jump (IPOINT location, REG reg) const;
  void insert_direct_jump (IPOINT location, ADDRINT tgt) const;

  /// {@ Code Cache methods
  ADDRINT code_cache_address (void) const;
  USIZE code_cache_size (void) const;
  /// @}

  /// {@ Disassembly syntax setters
  static void set_att_syntax (void);
  static void set_intel_syntax (void);
  static void set_xed_syntax (void);
  /// @}

private:
  INS & ins_;
};

} // namespace Pin
} // namespace OASIS

#include "Ins.inl"

#endif  // _OASIS_PIN_INS_H_
