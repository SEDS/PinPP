// -*- C++ -*-

//==============================================================================
/**
 *  @file        Replacement_Routine.h
 *
 *  $Id: Replacement_Routine.h 2294 2013-10-01 20:09:09Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_REPLACEMENT_ROUTINE_H_
#define _OASIS_PIN_REPLACEMENT_ROUTINE_H_

#include "Prototype.h"

namespace OASIS
{
namespace Pin
{

template <typename T, typename F> class Replacement_Routine;

template <typename T, typename R>
class Replacement_Routine <T, R (void) >
{
public:
  typedef R (*funcptr_type)(void);
  static const int arg_count = 0;

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (void);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

template <typename T, typename R, typename P1>
class Replacement_Routine < T, R (P1) >
{
public:
  typedef R (*funcptr_type)(P1);
  static const int arg_count = 1;

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

}
}

#include "Replacement_Routine.inl"

#endif  // !defined _OASIS_PIN_PROTOTYPE_H_
