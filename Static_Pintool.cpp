// $Id: Static_Pintool.cpp 2304 2013-10-05 18:54:01Z hillj $

#include "Static_Pintool.h"

namespace OASIS
{
namespace Pin
{

void Static_Pintool::init (INT32 argc, CHAR ** argv, bool init_symbols)
{
  // Initialize Pin, and our finalize method.
  if (init_symbols)
    PIN_InitSymbols ();

  PIN_Init (argc, argv);
}

} // namespace OASIS
} // namespace Pin
