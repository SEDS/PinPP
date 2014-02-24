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
bool Ins::operator == (const Ins & rhs) const
{
  return this->ins_ == rhs.ins_;
}

inline
bool Ins::operator != (const Ins & rhs) const
{
  return this->ins_ != rhs.ins_;
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
BOOL Ins::is_system_return (void) const
{
  return INS_IsSysret (this->ins_);
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
BOOL Ins::is_lea (void) const
{
  return INS_IsLea (this->ins_);
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
BOOL Ins::is_direct_branch (void) const
{
  return INS_IsDirectBranch (this->ins_);
}

inline
BOOL Ins::is_direct_call (void) const
{
  return INS_IsDirectCall (this->ins_);
}

inline
BOOL Ins::is_branch_or_call (void) const
{
  return INS_IsBranchOrCall (this->ins_);
}

inline
BOOL Ins::stutters (void) const
{
  return INS_Stutters (this->ins_);
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
ADDRDELTA Ins::memory_displacement (void) const
{
  return INS_MemoryDisplacement (this->ins_);
}

inline
REG Ins::memory_base_reg (void) const
{
  return INS_MemoryBaseReg (this->ins_);
}

inline
REG Ins::memory_index_reg (void) const
{
  return INS_MemoryIndexReg (this->ins_);
}

inline
UINT32 Ins::memory_scale (void) const
{
  return INS_MemoryScale (this->ins_);
}

inline
BOOL Ins::change_reg (const REG old_reg, const REG new_reg, const BOOL as_read) const
{
  return INS_ChangeReg (this->ins_, old_reg, new_reg, as_read);
}

inline
VOID Ins::get_mem_accesses (int * num, int * size, int * indexSize) const
{
  return GetNumberAndSizeOfMemAccesses (this->ins_, num, size, indexSize);
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
REG Ins::rep_counter (void) const
{
  return INS_RepCountRegister (this->ins_);
}

inline
REG Ins::segment_reg_prefix (void) const
{
  return INS_SegmentRegPrefix (this->ins_);
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
BOOL Ins::is_xbegin (void) const
{
  return INS_IsXbegin (this->ins_);
}

inline
BOOL Ins::is_xchg (void) const
{
  return INS_IsXchg (this->ins_);
}

inline
BOOL Ins::is_xend (void) const
{
  return INS_IsXend (this->ins_);
}

inline
BOOL Ins::is_halt (void) const
{
  return INS_IsHalt (this->ins_);
}

inline
BOOL Ins::is_vgather (void) const
{
  return INS_IsVgather (this->ins_);
}

#if (PIN_PRODUCT_VERSION_MAJOR > 2) || (PIN_PRODUCT_VERSION_MAJOR == 2 && PIN_PRODUCT_VERSION_MINOR >= 13)
inline
BOOL Ins::is_vscatter (void) const
{
  return INS_IsVscatter (this->ins_);
}
#endif

inline
BOOL Ins::is_sub (void) const
{
  return INS_IsSub (this->ins_);
}

inline
BOOL Ins::is_mov (void) const
{
  return INS_IsMov (this->ins_);
}

inline
BOOL Ins::is_mov_reg_reg_same (void) const
{
  return INS_IsMovFullRegRegSame (this->ins_);
}

inline
BOOL Ins::is_rdtsc (void) const
{
  return INS_IsRDTSC (this->ins_);
}

inline
BOOL Ins::is_mask_mov (void) const
{
  return INS_IsMaskMov (this->ins_);
}

inline
BOOL Ins::is_string_op (void) const
{
  return INS_IsStringop (this->ins_);
}

inline
BOOL Ins::is_iret (void) const
{
  return INS_IsIRet (this->ins_);
}

inline
BOOL Ins::has_real_rep (void) const
{
  return INS_HasRealRep (this->ins_);
}

inline
BOOL Ins::seg_prefix_is_memory_read (void) const
{
  return INS_SegPrefixIsMemoryRead (this->ins_);
}

inline
BOOL Ins::seg_prefix_is_memory_write (void) const
{
  return INS_SegPrefixIsMemoryWrite (this->ins_);
}

inline
BOOL Ins::address_size_prefix (void) const
{
  return INS_AddressSizePrefix (this->ins_);
}

inline
BOOL Ins::branch_not_taken_prefix (void) const
{
  return INS_BranchNotTakenPrefix (this->ins_);
}

inline
BOOL Ins::lock_prefix (void) const
{
  return INS_LockPrefix (this->ins_);
}

inline
BOOL Ins::operand_size_prefix (void) const
{
  return INS_OperandSizePrefix (this->ins_);
}

inline
BOOL Ins::rep_prefix (void) const
{
  return INS_RepPrefix (this->ins_);
}

inline
BOOL Ins::repne_prefix (void) const
{
  return INS_RepnePrefix (this->ins_);
}

inline
BOOL Ins::segment_prefix (void) const
{
  return INS_SegmentPrefix (this->ins_);
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
ADDRINT Ins::code_cache_address (void) const
{
  return INS_CodeCacheAddress (this->ins_);
}

inline
USIZE Ins::code_cache_size (void) const
{
  return INS_CodeCacheSize (this->ins_);
}

inline
void Ins::set_att_syntax (void)
{
  PIN_SetSyntaxATT ();
}

inline
void Ins::set_intel_syntax (void)
{
  PIN_SetSyntaxIntel ();
}

inline
void Ins::set_xed_syntax (void)
{
  PIN_SetSyntaxXED ();
}

inline
void Ins::insert_version_case (REG reg, INT32 case_value, ADDRINT new_version, CALL_ORDER order) const
{
  INS_InsertVersionCase (this->ins_, reg, case_value, new_version,
                         IARG_CALL_ORDER, order, IARG_END);
}

inline
void Ins::insert_indirect_jump (IPOINT location, REG reg) const
{
  INS_InsertIndirectJump (this->ins_, location, reg);
}

inline
void Ins::insert_direct_jump (IPOINT location, ADDRINT tgt) const
{
  INS_InsertDirectJump (this->ins_, location, tgt);
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
