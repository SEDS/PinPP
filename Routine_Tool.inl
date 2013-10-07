// -*- C++ -*-
// $Id: Routine_Tool.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Routine_Tool
//
template <typename T>
inline
Routine_Tool <T>::Routine_Tool (void)
{

}

//
// ~Routine_Tool
//
template <typename T>
inline
Routine_Tool <T>::~Routine_Tool (void)
{

}

//
// handle_init
//
template <typename T>
inline
void Routine_Tool <T>::handle_init (int argc, char * argv [])
{
  RTN_AddInstrumentFunction (&Routine_Tool::__instrument, this);
}

} // namespace OASIS
} // namespace Pin
