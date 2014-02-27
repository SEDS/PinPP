// -*- C++ -*-
// $Id: Trace_Instrument.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Trace_Instrument
//
template <typename T>
inline
Trace_Instrument <T>::Trace_Instrument (void)
{
  TRACE_AddInstrumentFunction (&Trace_Instrument::__instrument, this);
}

//
// ~Trace_Instrument
//
template <typename T>
inline
Trace_Instrument <T>::~Trace_Instrument (void)
{

}

} // namespace Pin
} // namespace OASIS
