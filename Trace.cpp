// $Id: Trace.cpp 2302 2013-10-05 05:54:21Z hillj $

#include "Trace.h"
#include "Routine.h"

namespace OASIS
{
namespace Pin
{

Routine Trace::routine (void) const
{
  return TRACE_Rtn (this->trace_);
}
  
}
}
