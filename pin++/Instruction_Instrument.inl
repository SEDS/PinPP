// -*- C++ -*-
// $Id: Instruction_Instrument.inl 2285 2013-09-18 05:24:04Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Instruction_Instrument
//
template <typename T>
inline
Instruction_Instrument <T>::Instruction_Instrument (void)
{
  INS_AddInstrumentFunction (&Instruction_Instrument::__instrument, this);
}

//
// ~Instruction_Instrument
//
template <typename T>
inline
Instruction_Instrument <T>::~Instruction_Instrument (void)
{

}

} // namespace OASIS
} // namespace Pin
