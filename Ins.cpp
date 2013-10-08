// $Id$

#include "Ins.h"
#include "Routine.h"

namespace OASIS
{
namespace Pin
{

const INS Ins::invalid = INS_Invalid ();

Routine Ins::routine (void) const
{
  return INS_Rtn (this->ins_);
}

}
}
