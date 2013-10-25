// $Id: Trace_Instrument.cpp 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
void Trace_Instrument <T>::__instrument (TRACE trace, void * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Trace (trace));
}

} // namespace OASIS
} // namespace Pin
