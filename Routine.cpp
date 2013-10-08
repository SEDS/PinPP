// $Id: Routine.cpp 2302 2013-10-05 05:54:21Z hillj $

#include "Routine.h"
#include "Section.h"

namespace OASIS
{
namespace Pin
{

const RTN Routine::invalid = RTN_Invalid ();

Section Routine::section (void) const
{
  return RTN_Sec (this->rtn_);
}

}
}
