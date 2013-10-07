// $Id: Image_Tool.cpp 2294 2013-10-01 20:09:09Z hillj $

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
VOID Image_Tool <T>::__instrument (IMG img, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Image (img));
}

//
// __unload
//
template <typename T>
VOID Image_Tool <T>::__unload (IMG img, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_unload (Image (img));
}

} // namespace OASIS
} // namespace Pin
