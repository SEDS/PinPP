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
  this->ins_ = rhs.ins_;
  this->index_ = rhs.index_;
  return *this;
}

} // namespace OASIS
} // namespace Pin
