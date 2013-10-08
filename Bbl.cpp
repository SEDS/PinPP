// $Id$

#include "Bbl.h"

namespace OASIS
{
namespace Pin
{

const BBL Bbl::invalid = Bbl::BBL_Invalid ();

BBL Bbl::BBL_Invalid (void)
{
  BBL bbl;
  bbl.invalidate ();

  return bbl;
}

}
}
