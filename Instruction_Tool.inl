// -*- C++ -*-
// $Id: Instruction_Tool.inl 2285 2013-09-18 05:24:04Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Instruction_Tool
//
template <typename T>
inline
Instruction_Tool <T>::Instruction_Tool (void)
{

}

//
// ~Instruction_Tool
//
template <typename T>
inline
Instruction_Tool <T>::~Instruction_Tool (void)
{

}

//
// handle_init
//
template <typename T>
inline
void Instruction_Tool <T>::handle_init (int argc, char * argv [])
{
  INS_AddInstrumentFunction (&Instruction_Tool::__instrument, this);
}

} // namespace OASIS
} // namespace Pin
