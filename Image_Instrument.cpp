// $Id: Image_Instrument.cpp 2294 2013-10-01 20:09:09Z hillj $

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
VOID Image_Instrument <T>::__instrument (IMG img, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Image (img));
}

} // namespace OASIS
} // namespace Pin
