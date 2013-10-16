// $Id: Pintool.cpp 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
Pintool <T>::Pintool (int argc, char * argv [])
: tool_ (0)
{
  // Initialize first, the allocate the tool.
  PIN_Init (argc, argv);
  this->tool_ = new T ();
}

} // namespace OASIS
} // namespace Pin
