// -*- C++ -*-
// $Id: Image_Tool.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Image_Tool
//
template <typename T>
inline
Image_Tool <T>::Image_Tool (void)
{

}

//
// ~Image_Tool
//
template <typename T>
inline
Image_Tool <T>::~Image_Tool (void)
{

}

//
// handle_init
//
template <typename T>
inline
void Image_Tool <T>::handle_init (int argc, char * argv [])
{
  IMG_AddInstrumentFunction (&Image_Tool::__instrument, this);
  IMG_AddUnloadFunction (&Image_Tool::__unload, this);
}

//
// handle_unload
//
template <typename T>
inline
void Image_Tool <T>::handle_unload (const Image & img)
{

}

} // namespace OASIS
} // namespace Pin
