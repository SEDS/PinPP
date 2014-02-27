// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instrument.h
 *
 *  $Id: Image.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_INSTRUMENT_H_
#define _OASIS_PIN_INSTRUMENT_H_

namespace OASIS
{
namespace Pin
{

/**
 * @class Instrument
 *
 * Base class for the different instrument types in Pin. The subclasses
 * are responsible for calling the correct AddInstrument function in Pin.
 */
class Instrument
{

};

} // namespace Pin
} // namespace OASIS

#endif  // _OASIS_PIN_INSTRUMENT_H_
