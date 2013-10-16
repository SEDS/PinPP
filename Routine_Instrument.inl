// -*- C++ -*-
// $Id: Routine_Instrument.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Routine_Instrument
//
template <typename T>
inline
Routine_Instrument <T>::Routine_Instrument (void)
{
  RTN_AddInstrumentFunction (&Routine_Instrument::__instrument, this);
}

//
// ~Routine_Instrument
//
template <typename T>
inline
Routine_Instrument <T>::~Routine_Instrument (void)
{

}

} // namespace OASIS
} // namespace Pin
