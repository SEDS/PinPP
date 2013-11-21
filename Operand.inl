// -*- C++ -*-
// $Id: Operand.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Operand::Operand (const Ins & ins, int index)
: ins_ (ins),
  index_ (index)
{

}

inline
Operand::Operand (const Operand & rhs)
: ins_ (rhs.ins_),
  index_ (rhs.index_)
{

}

inline
Operand::~Operand (void)
{

}

inline
const Operand & Operand::operator = (const Operand & rhs)
{
//  this->ins_ = rhs.ins_;
  this->index_ = rhs.index_;
  return *this;
}

inline
BOOL Operand::is_memory_read (void) const
{
  return INS_MemoryOperandIsRead (this->ins_, this->index_);
}

inline
BOOL Operand::is_memory_written (void) const
{
  return INS_MemoryOperandIsWritten (this->ins_, this->index_);
}

inline
BOOL Operand::is_memory (void) const
{
  return INS_OperandIsMemory (this->ins_, this->index_);
}

inline
REG Operand::memory_base_reg (void) const
{
  return INS_OperandMemoryBaseReg (this->ins_, this->index_);
}

inline
REG Operand::memory_index_reg (void) const
{
  return INS_OperandMemoryIndexReg (this->ins_, this->index_);
}

inline
REG Operand::memory_segment_reg (void) const
{
  return INS_OperandMemorySegmentReg (this->ins_, this->index_);
}


inline
UINT32 Operand::memory_scale (void) const
{
  return INS_OperandMemoryScale (this->ins_, this->index_);
}

inline
INT64 Operand::memory_displacement (void) const
{
  return INS_OperandMemoryDisplacement (this->ins_, this->index_);
}

inline
BOOL Operand::is_fixed_memop (void) const
{
  return INS_OperandIsFixedMemop (this->ins_, this->index_);
}

inline
BOOL Operand::is_address_generator (void) const
{
  return INS_OperandIsAddressGenerator (this->ins_, this->index_);
}

inline
BOOL Operand::is_branch_displacememt (void) const
{
  return INS_OperandIsBranchDisplacement (this->ins_, this->index_);
}

inline
BOOL Operand::is_reg (void) const
{
  return INS_OperandIsReg (this->ins_, this->index_);
}

inline
REG Operand::reg (void) const
{
  return INS_OperandReg (this->ins_, this->index_);
}

inline
BOOL Operand::is_immediate (void) const
{
  return INS_OperandIsImmediate (this->ins_, this->index_);
}

inline
UINT64 Operand::immediate (void) const
{
  return INS_OperandImmediate (this->ins_, this->index_);
}

inline
BOOL Operand::is_implicit (void) const
{
  return INS_OperandIsImplicit (this->ins_, this->index_);
}

inline
UINT32 Operand::width (void) const
{
  return INS_OperandWidth (this->ins_, this->index_);
}

} // namespace OASIS
} // namespace Pin
