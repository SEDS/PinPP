// $Id$

#include "Ins.h"
#include "Routine.h"

namespace OASIS
{
namespace Pin
{

const Insert_Call_T <Ins>::funcptr_type Ins::__insert_call = &INS_InsertCall;
const Insert_Call_T <Ins>::funcptr_type Ins::__insert_predicated_call = &INS_InsertPredicatedCall;
const Insert_Call_T <Ins>::funcptr_type Ins::__insert_if_call = &INS_InsertIfCall;
const Insert_Call_T <Ins>::funcptr_type Ins::__insert_then_call = &INS_InsertThenCall;

const INS Ins::invalid = INS_Invalid ();

Routine Ins::routine (void) const
{
  return INS_Rtn (this->ins_);
}

}
}
