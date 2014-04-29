// $Id: Trace.cpp 2302 2013-10-05 05:54:21Z hillj $

#include "Trace.h"
#include "Routine.h"

namespace OASIS
{
namespace Pin
{

const Insert_Call_T <Trace>::funcptr_type Trace::__insert_call = &TRACE_InsertCall;
const Insert_Call_T <Trace>::funcptr_type Trace::__insert_if_call = &TRACE_InsertIfCall;
const Insert_Call_T <Trace>::funcptr_type Trace::__insert_then_call = &TRACE_InsertThenCall;

Routine Trace::routine (void) const
{
  return TRACE_Rtn (this->trace_);
}
  
}
}
