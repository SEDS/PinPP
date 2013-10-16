// -*- C++ -*-
// $Id: Pintool.inl 2305 2013-10-07 03:23:23Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Pintool <T>::~Pintool (void)
{

}

template <typename T>
inline
void Pintool <T>::start_program (void)
{
  PIN_StartProgram ();
}

template <typename T>
inline
void Pintool <T>::start_program_probed (void)
{
  PIN_StartProgramProbed ();
}

} // namespace OASIS
} // namespace Pin
