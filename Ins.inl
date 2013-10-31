// -*- C++ -*-
// $Id: Ins.inl 2305 2013-10-07 03:23:23Z hillj $

#include "Insert_T.h"

namespace OASIS
{
namespace Pin
{

inline
std::string Ins::opcode_string_short (UINT32 opcode)
{
  return OPCODE_StringShort (opcode);
}

inline
std::string Ins::category_string_short (UINT32 num)
{
  return CATEGORY_StringShort (num);
}

inline
std::string Ins::extension_string_short (UINT32 num)
{
  return EXTENSION_StringShort (num);
}

inline
Ins::Ins (INS & ins)
: ins_ (ins)
{

}

inline
Ins::operator INS () const
{
  return this->ins_;
}

inline
Ins::iterator_type Ins::make_iter (void) const
{
  return iterator_type (this->ins_);
}

inline
bool Ins::valid (void) const
{
  return INS_Valid (this->ins_);
}

inline
INT32 Ins::category (void) const
{
  return INS_Category (this->ins_);
}

inline
void Ins::remove (void) const
{
  return INS_Delete (this->ins_);
}

inline
INT32 Ins::extension (void) const
{
  return INS_Extension (this->ins_);
}

inline
UINT32 Ins::effective_address_width (void) const
{
  return INS_EffectiveAddressWidth (this->ins_);
}

inline
BOOL Ins::is_valid (void) const
{
  return INS_Valid (this->ins_);
}

inline
USIZE Ins::memory_write_size (void) const
{
  return INS_MemoryWriteSize (this->ins_);
}

inline
USIZE Ins::memory_read_size (void) const
{
  return INS_MemoryReadSize (this->ins_);
}

inline
BOOL Ins::is_return (void) const
{
  return INS_IsRet (this->ins_);
}

inline
BOOL Ins::is_memory_read (void) const
{
  return INS_IsMemoryRead (this->ins_);
}

inline
BOOL Ins::is_memory_write (void) const
{
  return INS_IsMemoryWrite (this->ins_);
}

inline
BOOL Ins::has_memory_read2 (void) const
{
  return INS_HasMemoryRead2 (this->ins_);
}

inline
BOOL Ins::has_fall_through (void) const
{
  return INS_HasFallThrough (this->ins_);
}

inline
BOOL Ins::is_sysenter (void) const
{
  return INS_IsSysenter (this->ins_);
}

inline
BOOL Ins::is_nop (void) const
{
  return INS_IsNop (this->ins_);
}

inline
BOOL Ins::is_syscall (void) const
{
  return INS_IsSyscall (this->ins_);
}

inline
SYSCALL_STANDARD Ins::syscall_std (void) const
{
  return INS_SyscallStd (this->ins_);
}

inline
ADDRINT Ins::address (void) const
{
  return INS_Address (this->ins_);
}

inline
USIZE Ins::size (void) const
{
  return INS_Size (this->ins_);
}

inline
string Ins::disassemble (void) const
{
  return INS_Disassemble (this->ins_);
}

inline
UINT32 Ins::memory_operand_count (void) const
{
  return INS_MemoryOperandCount (this->ins_);
}

inline
BOOL Ins::is_memory_operand_read (UINT32 mem_op) const
{
  return INS_MemoryOperandIsRead (this->ins_, mem_op);
}

inline
BOOL Ins::is_memory_operand_written (UINT32 mem_op) const
{
  return INS_MemoryOperandIsWritten (this->ins_, mem_op);
}

inline
std::string Ins::mnemonic (void) const
{
  return INS_Mnemonic (this->ins_);
}

inline
BOOL Ins::is_branch (void) const
{
  return INS_IsBranch (this->ins_);
}

inline
BOOL Ins::is_branch_or_call (void) const
{
  return INS_IsBranchOrCall (this->ins_);
}

inline
BOOL Ins::is_pc_materialization (void) const
{
  return INS_IsPcMaterialization (this->ins_);
}

inline
BOOL Ins::is_call (void) const
{
  return INS_IsCall (this->ins_);
}

inline
BOOL Ins::is_far_call (void) const
{
  return INS_IsFarCall (this->ins_);
}

inline
BOOL Ins::is_far_jump (void) const
{
  return INS_IsFarJump (this->ins_);
}

inline
BOOL Ins::is_direct_far_jump (void) const
{
  return INS_IsDirectFarJump (this->ins_);
}

inline
VOID Ins::get_far_pointer (UINT16 &selector, UINT32 &displacement) const
{
  return INS_GetFarPointer (this->ins_, selector, displacement);
}

inline
BOOL Ins::is_procedure_call (void) const
{
  return INS_IsProcedureCall (this->ins_);
}

inline
BOOL Ins::is_interrupt (void) const
{
  return INS_IsInterrupt (this->ins_);
}

inline
BOOL Ins::is_far_return (void) const
{
  return INS_IsFarRet (this->ins_);
}

inline
BOOL Ins::is_prefetch (void) const
{
  return INS_IsPrefetch (this->ins_);
}

inline
BOOL Ins::is_atomic_update (void) const
{
  return INS_IsAtomicUpdate (this->ins_);
}

inline
BOOL Ins::is_indirect_branch_or_call (void) const
{
  return INS_IsIndirectBranchOrCall (this->ins_);
}

inline
BOOL Ins::is_direct_branch_or_call (void) const
{
  return INS_IsDirectBranchOrCall (this->ins_);
}

inline
ADDRINT Ins::direct_branch_or_call_target_address (void) const
{
  return INS_DirectBranchOrCallTargetAddress (this->ins_);
}

inline
ADDRINT Ins::next_address (void) const
{
  return INS_NextAddress (this->ins_);
}

inline
REG Ins::reg_read (UINT32 k) const
{
  return INS_RegR (this->ins_, k);
}

inline
REG Ins::reg_write (UINT32 k) const
{
  return INS_RegW (this->ins_, k);
}

inline
OPCODE Ins::opcode (void) const
{
  return INS_Opcode (this->ins_);
}

inline
UINT32 Ins::max_number_rregs (void) const
{
  return INS_MaxNumRRegs (this->ins_);
}

inline
UINT32 Ins::max_number_wregs (void) const
{
  return INS_MaxNumWRegs (this->ins_);
}

inline
BOOL Ins::reg_read_contain (const REG reg) const
{
  return INS_RegRContain (this->ins_, reg);
}

inline
BOOL Ins::reg_write_contain (const REG reg) const
{
  return INS_RegWContain (this->ins_, reg);
}

inline
BOOL Ins::full_reg_read_contain (const REG reg) const
{
  return INS_FullRegRContain (this->ins_, reg);
}

inline
BOOL Ins::full_reg_write_contain (const REG reg) const
{
  return INS_FullRegWContain (this->ins_, reg);
}

inline
BOOL Ins::is_stack_read (void) const
{
  return INS_IsStackRead (this->ins_);
}

inline
BOOL Ins::is_stack_write (void) const
{
  return INS_IsStackWrite (this->ins_);
}

inline
BOOL Ins::is_ip_relative_read (void) const
{
  return INS_IsIpRelRead (this->ins_);
}

inline
BOOL Ins::is_ip_relative_write (void) const
{
  return INS_IsIpRelWrite (this->ins_);
}

inline
PREDICATE Ins::get_predicate (void) const
{
  return INS_GetPredicate (this->ins_);
}

inline
BOOL Ins::is_predicated (void) const
{
  return INS_IsPredicated (this->ins_);
}

inline
BOOL Ins::is_original (void) const
{
  return INS_IsOriginal (this->ins_);
}

inline
UINT32 Ins::operand_count (void) const
{
  return INS_OperandCount (this->ins_);
}

inline
BOOL Ins::operand_is_memory (UINT32 n) const
{
  return INS_OperandIsMemory (this->ins_, n);
}

inline
REG Ins::operand_memory_base_reg (UINT32 n) const
{
  return INS_OperandMemoryBaseReg (this->ins_, n);
}

inline
REG Ins::operand_memory_index_reg (UINT32 n) const
{
  return INS_OperandMemoryIndexReg (this->ins_, n);
}

inline
REG Ins::operand_memory_segment_reg (UINT32 n) const
{
  return INS_OperandMemorySegmentReg (this->ins_, n);
}


inline
UINT32 Ins::operand_memory_scale (UINT32 n) const
{
  return INS_OperandMemoryScale (this->ins_, n);
}

inline
INT64 Ins::operand_memory_displacement (UINT32 n) const
{
  return INS_OperandMemoryDisplacement (this->ins_, n);
}

inline
BOOL Ins::operand_is_fixed_memop (UINT32 n) const
{
  return INS_OperandIsFixedMemop (this->ins_, n);
}

inline
BOOL Ins::operand_is_address_generator (UINT32 n) const
{
  return INS_OperandIsAddressGenerator (this->ins_, n);
}

inline
BOOL Ins::operand_is_branch_displacememt (UINT32 n) const
{
  return INS_OperandIsBranchDisplacement (this->ins_, n);
}

inline
BOOL Ins::operand_is_reg (UINT32 n) const
{
  return INS_OperandIsReg (this->ins_, n);
}

inline
REG Ins::operand_reg (UINT32 n) const
{
  return INS_OperandReg (this->ins_, n);
}

inline
BOOL Ins::operand_is_immediate (UINT32 n) const
{
  return INS_OperandIsImmediate (this->ins_, n);
}

inline
UINT64 Ins::operand_immediate (UINT32 n) const
{
  return INS_OperandImmediate (this->ins_, n);
}

inline
BOOL Ins::operand_is_implicit (UINT32 n) const
{
  return INS_OperandIsImplicit (this->ins_, n);
}

inline
UINT32 Ins::operand_width (UINT32 n) const
{
  return INS_OperandWidth (this->ins_, n);
}

template <typename CALLBACK>
inline
void Ins::
insert_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline
  void Ins::
  insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5) const
  {
    Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline
  void Ins::
  insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6) const
  {
    Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }

template <typename CALLBACK>
inline
void Ins::
insert_if_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Ins::
insert_then_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Ins::
insert_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Ins::
insert_if_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Ins::
insert_then_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then);
}

template <typename CALLBACK, typename XARG1>
inline
void Ins::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

} // namespace OASIS
} // namespace Pin
