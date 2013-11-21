// $Id$

#include "Ins.h"
#include "Routine.h"
#include "Operand.h"

namespace OASIS
{
namespace Pin
{

const INS Ins::invalid = INS_Invalid ();

Routine Ins::routine (void) const
{
  return INS_Rtn (this->ins_);
}

Operand Ins::operand (int index) const
{
  return Operand (*this, index);
}

Operand Ins::operator [] (int index) const
{
  return Operand (*this, index);
}

}
}
