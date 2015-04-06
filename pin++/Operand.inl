// -*- C++ -*-

namespace OASIS
{
namespace Pin
{

inline
Operand::Operand (INS ins, int index)
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
  if (this == &rhs)
    return *this;
  
  this->ins_ = rhs.ins_;
  this->index_ = rhs.index_;
  return *this;
}

inline
bool Operand::is_memory (void) const
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
bool Operand::is_fixed_memop (void) const
{
  return INS_OperandIsFixedMemop (this->ins_, this->index_);
}

inline
bool Operand::is_address_generator (void) const
{
  return INS_OperandIsAddressGenerator (this->ins_, this->index_);
}

inline
bool Operand::is_branch_displacememt (void) const
{
  return INS_OperandIsBranchDisplacement (this->ins_, this->index_);
}

inline
bool Operand::is_reg (void) const
{
  return INS_OperandIsReg (this->ins_, this->index_);
}

inline
REG Operand::reg (void) const
{
  return INS_OperandReg (this->ins_, this->index_);
}

inline
bool Operand::is_immediate (void) const
{
  return INS_OperandIsImmediate (this->ins_, this->index_);
}

inline
UINT64 Operand::immediate (void) const
{
  return INS_OperandImmediate (this->ins_, this->index_);
}

inline
bool Operand::is_implicit (void) const
{
  return INS_OperandIsImplicit (this->ins_, this->index_);
}

inline
UINT32 Operand::width (void) const
{
  return INS_OperandWidth (this->ins_, this->index_);
}

inline
UINT32 Operand::name_id (void) const
{
  return INS_OperandNameId (this->ins_, this->index_);
}

inline
bool Operand::is_read (void) const
{
  return INS_OperandRead (this->ins_, this->index_);
}

inline
bool Operand::is_read_only (void) const
{
  return INS_OperandReadOnly (this->ins_, this->index_);
}

inline
bool Operand::is_written (void) const
{
  return INS_OperandWritten (this->ins_, this->index_);
}

inline
bool Operand::is_written_only (void) const
{
  return INS_OperandWrittenOnly (this->ins_, this->index_);
}

inline
bool Operand::is_read_and_written (void) const
{
  return INS_OperandReadAndWritten (this->ins_, this->index_);
}

inline
Memory_Operand Operand::to_memory_operand (void) const
{
  return Memory_Operand (this->ins_, this->index_);
}
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Memory_Operand
  
  inline
  Memory_Operand::Memory_Operand (INS ins, int index)
  : Operand (ins, index)
  {
    
  }
  
  inline
  Memory_Operand::Memory_Operand (const Memory_Operand & copy)
  : Operand (copy)
  {
    
  }
  
  inline
  Memory_Operand::~Memory_Operand (void)
  {
    
  }
  
  inline
  const Memory_Operand & Memory_Operand::operator = (const Memory_Operand & rhs)
  {
    Operand::operator = (rhs);
    return *this;
  }
  
  inline
  bool Memory_Operand::is_read (void) const
  {
    return INS_MemoryOperandIsRead (this->ins_, this->index_);
  }
  
  inline
  bool Memory_Operand::is_written (void) const
  {
    return INS_MemoryOperandIsWritten (this->ins_, this->index_);
  }
  
  inline
  void Memory_Operand::rewrite (REG reg) const
  {
    INS_RewriteMemoryOperand (this->ins_, this->index_, reg);
  }
  
  inline
  USIZE Memory_Operand::size (void) const
  {
    return INS_MemoryOperandSize (this->ins_, this->index_);
  }

  
} // namespace OASIS
} // namespace Pin
