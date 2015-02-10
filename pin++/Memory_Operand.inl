// -*- C++ -*-

namespace OASIS
{
namespace Pin
{
       
inline
Memory_Operand::Memory_Operand (INS ins, int index)
: ins_ (ins),
  index_ (index)
{

}

inline
Memory_Operand::Memory_Operand (const Memory_Operand & copy)
: ins_ (copy.ins_),
  index_ (copy.index_)
{
  
}

inline
Memory_Operand::~Memory_Operand (void)
{

}
  
inline
const Memory_Operand & Memory_Operand::operator = (const Memory_Operand & rhs)
{
  this->ins_ = rhs.ins_;
  this->index_ = rhs.index_;
  
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
  INS_MemoryOperandSize (this->ins_, this->index_);
}

} // namespace OASIS
} // namespace Pin
