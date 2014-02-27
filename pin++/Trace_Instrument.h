// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Instrument.h
 *
 *  $Id: Trace_Instrument.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TRACE_TOOL_H_
#define _OASIS_PIN_TRACE_TOOL_H_

#include "Instrument.h"
#include "Trace.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Trace_Instrument
 *
 * Base class for trace-level instruments.
 */
template <typename T>
class Trace_Instrument : public Instrument
{
public:
  /// Type definition of the tool type.
  typedef T type;

  /// Default constructor.
  Trace_Instrument (void);

  /// Destructor.
  ~Trace_Instrument (void);

private:
  // PIN Instrumentation hook
  static VOID __instrument (TRACE trace, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Trace_Instrument.inl"
#include "Trace_Instrument.cpp"

#endif  // _OASIS_PIN_TRACE_TOOL_H_
