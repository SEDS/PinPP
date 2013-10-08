// $Id: Instruction_Tool.cpp 2285 2013-09-18 05:24:04Z hillj $

namespace OASIS
{
namespace Pin
{

//
// __instrument
//
template <typename T>
VOID Instruction_Tool <T>::__instrument (INS ins, VOID * v)
{
  reinterpret_cast <T *> (v)->handle_instrument (Ins (ins));
}

} // namespace OASIS
} // namespace Pin
