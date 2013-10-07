// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Tool.h
 *
 *  $Id: Instruction_Tool.h 2285 2013-09-18 05:24:04Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_INSTRUCTION_PROBE_H_
#define _OASIS_PIN_INSTRUCTION_PROBE_H_

#include "Tool.h"
#include "Ins.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Instruction_Tool
 *
 * Base class for instruction-level instrumentation Pin tools.
 */
template <typename T>
class Instruction_Tool : public Tool
{
public:
  /// Default constructor.
  Instruction_Tool (void);

  /// Destructor.
  ~Instruction_Tool (void);

  /// Initialize the tool.
  void handle_init (int argc, char * argv []);

private:
  // PIN Instrumentation hook
  static VOID __instrument (INS ins, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Instruction_Tool.inl"
#include "Instruction_Tool.cpp"

#endif  // _OASIS_PIN_INSTRUCTION_PROBE_H_
