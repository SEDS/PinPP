// $Id: Trace_Tool.cpp 2288 2013-09-19 19:09:57Z hillj $

#if !defined (__inline__)
#include "Trace_Tool.inl"
#endif  // !defined __inline__

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
void Trace_Tool <T>::__instrument (TRACE trace, void * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Trace (trace));
}

} // namespace OASIS
} // namespace Pin
