// $Id$

#include "Bbl.h"

namespace OASIS
{
namespace Pin
{

const Insert_Call_T <Bbl>::funcptr_type Bbl::__insert_call = &BBL_InsertCall;

const BBL Bbl::invalid = Bbl::BBL_Invalid ();

BBL Bbl::BBL_Invalid (void)
{
  BBL bbl;
  bbl.invalidate ();

  return bbl;
}

}
}
