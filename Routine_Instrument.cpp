// $Id: Routine_Instrument.cpp 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
VOID Routine_Instrument <T>::__instrument (RTN rtn, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Routine (rtn));
}

} // namespace OASIS
} // namespace Pin
