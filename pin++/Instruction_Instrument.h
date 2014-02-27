// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Instrument.h
 *
 *  $Id: Instruction_Instrument.h 2285 2013-09-18 05:24:04Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_INSTRUCTION_INSTRUMENT_H_
#define _OASIS_PIN_INSTRUCTION_INSTRUMENT_H_

#include "Instrument.h"
#include "Ins.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Instruction_Instrument
 *
 * Base class for instruction-level instruments in Pin.
 */
template <typename T>
class Instruction_Instrument : public Instrument
{
public:
  /// Default constructor.
  Instruction_Instrument (void);

  /// Destructor.
  ~Instruction_Instrument (void);

private:
  // PIN Instrumentation hook
  static VOID __instrument (INS ins, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Instruction_Instrument.inl"
#include "Instruction_Instrument.cpp"

#endif  // _OASIS_PIN_INSTRUCTION_PROBE_H_
