// -*- C++ -*-
// $Id: Image_Instrument.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Image_Instrument
//
template <typename T>
inline
Image_Instrument <T>::Image_Instrument (void)
{
  IMG_AddInstrumentFunction (&Image_Instrument::__instrument, this);
}

//
// ~Image_Instrument
//
template <typename T>
inline
Image_Instrument <T>::~Image_Instrument (void)
{

}

} // namespace OASIS
} // namespace Pin
