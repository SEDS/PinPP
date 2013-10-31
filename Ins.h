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

#include "Pin_export.h"

namespace OASIS
{
namespace Pin
{
// Forward decl.
class Routine;

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
  typedef Iterator <Ins, &INS_Prev, &INS_Next> iterator_type;

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
  Ins (INS & ins);

  /// Type conversion operator
  operator INS () const;

  /// {@ Comparison Operators
  bool operator == (const Ins & rhs) const;
  bool operator != (const Ins & rhs) const;
  /// @}

  /// Make an iterator to the current instruction.
  iterator_type make_iter (void) const;

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

  UINT32 memory_operand_count (void) const;
  BOOL is_memory_operand_read (UINT32 mem_op) const;
  BOOL is_memory_operand_written (UINT32 mem_op) const;

  /// Get the mnemonic for the instruction.
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

  /// Test if the current instruction is valid.
  BOOL valid (void) const;

  /// Remove the current instruction from the execution.
  void remove (void) const;

  /// Get the parent routine.
  Routine routine (void) const;

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

private:
  INS & ins_;
};

/**
 * @class Iterator <Ins, &INS_PREV, &INS_NEXT specalization
 */
template <>
class Iterator <Ins, &INS_Prev, &INS_Next>
{
public:
  typedef typename Ins::pin_type pin_type;

  /// Default constructor.
  Iterator (void);

  /// Initializing constructor.
  Iterator (const Ins & t);

  /// Initializing constructor.
  Iterator (const pin_type & t);

  /// Copy constructor.
  Iterator (const Iterator & iter);

  /// Destructor.
  ~Iterator (void);

  /// Assignment operator
  const Iterator & operator = (const Iterator & rhs);

  /// {@ Reference/Dereference Operators
  Ins & operator * (void);
  Ins * operator -> (void);
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
  Ins wrapper_;
};

} // namespace Pin
} // namespace OASIS

#include "Ins.inl"

#endif  // _OASIS_PIN_INS_H_
