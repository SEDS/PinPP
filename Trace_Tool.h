// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Tool.h
 *
 *  $Id: Trace_Tool.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TRACE_TOOL_H_
#define _OASIS_PIN_TRACE_TOOL_H_

#include "Tool.h"
#include "Trace.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Trace_Tool
 *
 * Base class for trace-level instrumentation Pin tools.
 */
template <typename T>
class Trace_Tool : public Tool
{
public:
  /// Type definition of the tool type.
  typedef T type;

  /// Default constructor.
  Trace_Tool (void);

  /// Destructor.
  ~Trace_Tool (void);

  /// Initialize the tool.
  void handle_init (int argc, char * argv []);

private:
  // PIN Instrumentation hook
  static VOID __instrument (TRACE trace, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#if defined (__inline__)
#include "Trace_Tool.inl"
#endif  // !defined __inline__

#include "Trace_Tool.cpp"

#endif  // _OASIS_PIN_TRACE_TOOL_H_
