// $Id: Pintool.cpp 2306 2013-10-07 05:03:46Z hillj $

#include <iostream>

namespace OASIS
{
namespace Pin
{

template <typename T>
Pintool <T>::Pintool (int argc, char * argv [])
: tool_ (0),
  cmdline_error_ (false)
{
  PIN_InitSymbols ();
  this->cmdline_error_ = PIN_Init (argc, argv);
  
  if (this->cmdline_error_)
    std::cerr
      << "*** error parsing command line arguments" << std::endl
      << KNOB_BASE::StringKnobSummary () << std::endl;
  else
    this->tool_ = new T ();
}

} // namespace OASIS
} // namespace Pin
