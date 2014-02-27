// -*- C++ -*-

//==============================================================================
/**
 *  @file        Routine_Instrument.h
 *
 *  $Id: Routine_Instrument.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_ROUTINE_INSTRUMENT_H_
#define _OASIS_PIN_ROUTINE_INSTRUMENT_H_

#include "Instrument.h"
#include "Routine.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Instruction_Instrument
 *
 * Base class for instruction-level instrumentation Pin tools.
 */
template <typename T>
class Routine_Instrument : public Instrument
{
public:
  /// Default constructor.
  Routine_Instrument (void);

  /// Destructor.
  ~Routine_Instrument (void);

private:
  // PIN Instrumentation hook
  static VOID __instrument (RTN ins, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Routine_Instrument.inl"
#include "Routine_Instrument.cpp"

#endif  // _OASIS_PIN_ROUTINE_INSTRUMENT_H_
