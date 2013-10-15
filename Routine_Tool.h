// -*- C++ -*-

//==============================================================================
/**
 *  @file        Routine_Tool.h
 *
 *  $Id: Routine_Tool.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_ROUTINE_TOOL_H_
#define _OASIS_PIN_ROUTINE_TOOL_H_

#include "Tool.h"
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
class Routine_Tool : public Tool
{
public:
  /// Default constructor.
  Routine_Tool (void);

  /// Destructor.
  ~Routine_Tool (void);

  /// Initialize the tool.
  void handle_init (int argc, char * argv []);

private:
  // PIN Instrumentation hook
  static VOID __instrument (RTN ins, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#if defined (__inline__)
#include "Routine_Tool.inl"
#endif  // !defined __inline__

#include "Routine_Tool.cpp"

#endif  // _OASIS_PIN_ROUTINE_TOOL_H_
