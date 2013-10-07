// -*- C++ -*-
// $Id: Ins.inl 2305 2013-10-07 03:23:23Z hillj $

#include "Insert_T.h"

namespace OASIS
{
namespace Pin
{

template <typename INS_TYPE>
const INS Ins_Base <INS_TYPE>::invalid = INS_Invalid ();

template <typename INS_TYPE>
inline
std::string Ins_Base <INS_TYPE>::opcode_string_short (UINT32 opcode)
{
  return OPCODE_StringShort (opcode);
}

template <typename INS_TYPE>
inline
std::string Ins_Base <INS_TYPE>::category_string_short (UINT32 num)
{
  return CATEGORY_StringShort (num);
}

template <typename INS_TYPE>
inline
std::string Ins_Base <INS_TYPE>::extension_string_short (UINT32 num)
{
  return EXTENSION_StringShort (num);
}

template <typename INS_TYPE>
inline
Ins_Base <INS_TYPE>::Ins_Base (const INS & ins)
  : ins_ (ins)
{

}

template <typename INS_TYPE>
inline
Ins_Base <INS_TYPE>::operator INS () const
{
  return this->ins_;
}

template <typename INS_TYPE>
inline
bool Ins_Base <INS_TYPE>::valid (void) const
{
  return INS_Valid (this->ins_);
}

template <typename INS_TYPE>
inline
INT32 Ins_Base <INS_TYPE>::category (void) const
{
  return INS_Category (this->ins_);
}

template <typename INS_TYPE>
inline
void Ins_Base <INS_TYPE>::remove (void) const
{
  return INS_Delete (this->ins_);
}

template <typename INS_TYPE>
inline
INT32 Ins_Base <INS_TYPE>::extension (void) const
{
  return INS_Extension (this->ins_);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::effective_address_width (void) const
{
  return INS_EffectiveAddressWidth (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_valid (void) const
{
  return INS_Valid (this->ins_);
}

template <typename INS_TYPE>
inline
USIZE Ins_Base <INS_TYPE>::memory_write_size (void) const
{
  return INS_MemoryWriteSize (this->ins_);
}

template <typename INS_TYPE>
inline
USIZE Ins_Base <INS_TYPE>::memory_read_size (void) const
{
  return INS_MemoryReadSize (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_return (void) const
{
  return INS_IsRet (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_memory_read (void) const
{
  return INS_IsMemoryRead (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_memory_write (void) const
{
  return INS_IsMemoryWrite (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::has_memory_read2 (void) const
{
  return INS_HasMemoryRead2 (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::has_fall_through (void) const
{
  return INS_HasFallThrough (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_sysenter (void) const
{
  return INS_IsSysenter (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_nop (void) const
{
  return INS_IsNop (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_syscall (void) const
{
  return INS_IsSyscall (this->ins_);
}

template <typename INS_TYPE>
inline
SYSCALL_STANDARD Ins_Base <INS_TYPE>::syscall_std (void) const
{
  return INS_SyscallStd (this->ins_);
}

template <typename INS_TYPE>
inline
ADDRINT Ins_Base <INS_TYPE>::address (void) const
{
  return INS_Address (this->ins_);
}

template <typename INS_TYPE>
inline
USIZE Ins_Base <INS_TYPE>::size (void) const
{
  return INS_Size (this->ins_);
}

template <typename INS_TYPE>
inline
string Ins_Base <INS_TYPE>::disassemble (void) const
{
  return INS_Disassemble (this->ins_);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::memory_operand_count (void) const
{
  return INS_MemoryOperandCount (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_memory_operand_read (UINT32 mem_op) const
{
  return INS_MemoryOperandIsRead (this->ins_, mem_op);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_memory_operand_written (UINT32 mem_op) const
{
  return INS_MemoryOperandIsWritten (this->ins_, mem_op);
}

template <typename INS_TYPE>
inline
std::string Ins_Base <INS_TYPE>::mnemonic (void) const
{
  return INS_Mnemonic (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_branch (void) const
{
  return INS_IsBranch (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_branch_or_call (void) const
{
  return INS_IsBranchOrCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_pc_materialization (void) const
{
  return INS_IsPcMaterialization (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_call (void) const
{
  return INS_IsCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_far_call (void) const
{
  return INS_IsFarCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_far_jump (void) const
{
  return INS_IsFarJump (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_direct_far_jump (void) const
{
  return INS_IsDirectFarJump (this->ins_);
}

template <typename INS_TYPE>
inline
VOID Ins_Base <INS_TYPE>::get_far_pointer (UINT16 &selector, UINT32 &displacement) const
{
  return INS_GetFarPointer (this->ins_, selector, displacement);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_procedure_call (void) const
{
  return INS_IsProcedureCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_interrupt (void) const
{
  return INS_IsInterrupt (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_far_return (void) const
{
  return INS_IsFarRet (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_prefetch (void) const
{
  return INS_IsPrefetch (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_atomic_update (void) const
{
  return INS_IsAtomicUpdate (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_indirect_branch_or_call (void) const
{
  return INS_IsIndirectBranchOrCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_direct_branch_or_call (void) const
{
  return INS_IsDirectBranchOrCall (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_rewritable_mem_op_base (MEMORY_TYPE mtype, REG &base) const
{
  return INS_IsRewritableMemOpBase (this->ins_, mtype, base);
}

template <typename INS_TYPE>
inline
ADDRINT Ins_Base <INS_TYPE>::direct_branch_or_call_target_address (void) const
{
  return INS_DirectBranchOrCallTargetAddress (this->ins_);
}

template <typename INS_TYPE>
inline
ADDRINT Ins_Base <INS_TYPE>::next_address (void) const
{
  return INS_NextAddress (this->ins_);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::reg_read (UINT32 k) const
{
  return INS_RegR (this->ins_, k);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::reg_write (UINT32 k) const
{
  return INS_RegW (this->ins_, k);
}

template <typename INS_TYPE>
inline
OPCODE Ins_Base <INS_TYPE>::opcode (void) const
{
  return INS_Opcode (this->ins_);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::max_number_rregs (void) const
{
  return INS_MaxNumRRegs (this->ins_);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::max_number_wregs (void) const
{
  return INS_MaxNumWRegs (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::reg_read_contain (const REG reg) const
{
  return INS_RegRContain (this->ins_, reg);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::reg_write_contain (const REG reg) const
{
  return INS_RegWContain (this->ins_, reg);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::full_reg_read_contain (const REG reg) const
{
  return INS_FullRegRContain (this->ins_, reg);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::full_reg_write_contain (const REG reg) const
{
  return INS_FullRegWContain (this->ins_, reg);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_stack_read (void) const
{
  return INS_IsStackRead (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_stack_write (void) const
{
  return INS_IsStackWrite (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_ip_relative_read (void) const
{
  return INS_IsIpRelRead (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_ip_relative_write (void) const
{
  return INS_IsIpRelWrite (this->ins_);
}

template <typename INS_TYPE>
inline
PREDICATE Ins_Base <INS_TYPE>::get_predicate (void) const
{
  return INS_GetPredicate (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_predicated (void) const
{
  return INS_IsPredicated (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::is_original (void) const
{
  return INS_IsOriginal (this->ins_);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::operand_count (void) const
{
  return INS_OperandCount (this->ins_);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_memory (UINT32 n) const
{
  return INS_OperandIsMemory (this->ins_, n);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::operand_memory_base_reg (UINT32 n) const
{
  return INS_OperandMemoryBaseReg (this->ins_, n);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::operand_memory_index_reg (UINT32 n) const
{
  return INS_OperandMemoryIndexReg (this->ins_, n);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::operand_memory_segment_reg (UINT32 n) const
{
  return INS_OperandMemorySegmentReg (this->ins_, n);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::operand_memory_scale (UINT32 n) const
{
  return INS_OperandMemoryScale (this->ins_, n);
}

template <typename INS_TYPE>
inline
INT64 Ins_Base <INS_TYPE>::operand_memory_displacement (UINT32 n) const
{
  return INS_OperandMemoryDisplacement (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_fixed_memop (UINT32 n) const
{
  return INS_OperandIsFixedMemop (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_address_generator (UINT32 n) const
{
  return INS_OperandIsAddressGenerator (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_branch_displacememt (UINT32 n) const
{
  return INS_OperandIsBranchDisplacement (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_reg (UINT32 n) const
{
  return INS_OperandIsReg (this->ins_, n);
}

template <typename INS_TYPE>
inline
REG Ins_Base <INS_TYPE>::operand_reg (UINT32 n) const
{
  return INS_OperandReg (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_immediate (UINT32 n) const
{
  return INS_OperandIsImmediate (this->ins_, n);
}

template <typename INS_TYPE>
inline
UINT64 Ins_Base <INS_TYPE>::operand_immediate (UINT32 n) const
{
  return INS_OperandImmediate (this->ins_, n);
}

template <typename INS_TYPE>
inline
BOOL Ins_Base <INS_TYPE>::operand_is_implicit (UINT32 n) const
{
  return INS_OperandIsImplicit (this->ins_, n);
}

template <typename INS_TYPE>
inline
UINT32 Ins_Base <INS_TYPE>::operand_width (UINT32 n) const
{
  return INS_OperandWidth (this->ins_, n);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_if_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_then_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_if_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_if_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertIfPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename INS_TYPE>
template <typename CALLBACK>
inline
void Ins_Base <INS_TYPE>::
insert_then_predicated_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1>
inline
void Ins_Base <INS_TYPE>::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Ins_Base <INS_TYPE>::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Ins_Base <INS_TYPE>::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename INS_TYPE>
template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Ins_Base <INS_TYPE>::
insert_then_predicated_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <INS, CALLBACK, &INS_InsertThenPredicatedCall>::execute (this->ins_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

////////////////////////////////////////////////////////////////////////////////
// Ins_Ref

//
// Ins_Ref
//
inline
Ins_Ref::Ins_Ref (const INS & ins)
: Ins_Base (ins)
{

}

////////////////////////////////////////////////////////////////////////////////
// Ins

//
// Ins
//
inline
Ins::Ins (const INS & ins)
: Ins_Base (ins)
{

}

//
// Ins
//
inline
Ins::Ins (const Ins & ins)
: Ins_Base (ins.ins_)
{

}

//
// operator =
//
inline
const Ins & Ins::operator = (const Ins & ins)
{
  this->ins_ = ins;
  return *this;
}

//
// prev
//
inline
Ins & Ins::prev (void)
{
  this->ins_ = INS_Prev (this->ins_);
  return *this;
}

//
// next
//
inline
Ins & Ins::next (void)
{
  this->ins_ = INS_Next (this->ins_);
  return *this;
}

} // namespace OASIS
} // namespace Pin
