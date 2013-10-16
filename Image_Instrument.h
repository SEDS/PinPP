// -*- C++ -*-

//==============================================================================
/**
 *  @file        Image_Instrument.h
 *
 *  $Id: Image_Instrument.h 2294 2013-10-01 20:09:09Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_IMAGE_INSTRUMENT_H_
#define _OASIS_PIN_IMAGE_INSTRUMENT_H_

#include "Instrument.h"
#include "Image.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Image_Instrument
 *
 * Base class for instruction-level instrumentation Pin tools.
 */
template <typename T>
class Image_Instrument : public Instrument
{
public:
  /// Default constructor.
  Image_Instrument (void);

  /// Destructor.
  ~Image_Instrument (void);

private:
  static VOID __instrument (IMG image, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Image_Instrument.inl"
#include "Image_Instrument.cpp"

#endif  // _OASIS_PIN_IMAGE_INSTRUMENT_H_
