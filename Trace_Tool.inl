// -*- C++ -*-
// $Id: Trace_Tool.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Trace_Tool
//
template <typename T>
inline
Trace_Tool <T>::Trace_Tool (void)
{

}

//
// ~Trace_Tool
//
template <typename T>
inline
Trace_Tool <T>::~Trace_Tool (void)
{

}

//
// handle_init
//
template <typename T>
inline
void Trace_Tool <T>::handle_init (int, char * [])
{
  TRACE_AddInstrumentFunction (&Trace_Tool::__instrument, this);
}

} // namespace Pin
} // namespace OASIS
