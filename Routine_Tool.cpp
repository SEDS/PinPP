// $Id: Routine_Tool.cpp 2288 2013-09-19 19:09:57Z hillj $

#if !defined (__inline__)
#include "Routine_Tool.inl"
#endif  // !defined __inline__

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
VOID Routine_Tool <T>::__instrument (RTN rtn, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Routine (rtn));
}

} // namespace OASIS
} // namespace Pin
