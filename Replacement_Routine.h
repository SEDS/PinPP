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
  static const int arg_count = 0;

  /// @{ Prototype Type Definitions
  typedef R return_type;
  typedef R (*funcptr_type)(void);
  /// @}

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
  static const int arg_count = 1;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1);
  typedef R return_type;
  typedef P1 param1_type;
  /// @}

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

template <typename T, typename R, typename P1, typename P2>
class Replacement_Routine < T, R (P1, P2) >
{
public:
  static const int arg_count = 2;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1, P2);
  typedef R return_type;
  typedef P1 param1_type;
  typedef P2 param2_type;
  /// @}

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1, P2 p2);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

template <typename T, typename R, typename P1, typename P2, typename P3>
class Replacement_Routine < T, R (P1, P2, P3) >
{
public:
  static const int arg_count = 3;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1, P2, P3);
  typedef R return_type;
  typedef P1 param1_type;
  typedef P2 param2_type;
  typedef P3 param3_type;
  /// @}

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1, P2 p2, P3 p3);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
class Replacement_Routine < T, R (P1, P2, P3, P4) >
{
public:
  static const int arg_count = 4;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1, P2, P3, P4);
  typedef R return_type;
  typedef P1 param1_type;
  typedef P2 param2_type;
  typedef P3 param3_type;
  typedef P4 param4_type;
  /// @}

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1, P2 p2, P3 p3, P4 p4);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class Replacement_Routine < T, R (P1, P2, P3, P4, P5) >
{
public:
  static const int arg_count = 5;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1, P2, P3, P4, P5);
  typedef R return_type;
  typedef P1 param1_type;
  typedef P2 param2_type;
  typedef P3 param3_type;
  typedef P4 param4_type;
  typedef P5 param5_type;
  /// @}

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1, P2 p2, P3 p3, P4 p4, P5 p5);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Replacement_Routine < T, R (P1, P2, P3, P4, P5, P6) >
{
public:
  static const int arg_count = 6;

  /// @{ Prototype Type Definitions
  typedef R (*funcptr_type)(P1, P2, P3, P4, P5, P6);
  typedef R return_type;
  typedef P1 param1_type;
  typedef P2 param2_type;
  typedef P3 param3_type;
  typedef P4 param4_type;
  typedef P5 param5_type;
  typedef P6 param6_type;
  /// @}

  static Prototype make_prototype (const char * name, CALLINGSTD_TYPE callstd_type = CALLINGSTD_DEFAULT);

  /// @{ Original Function Pointer Methods
  static void original_funcptr (funcptr_type funcptr);
  static funcptr_type original_funcptr (void);
  static R call_original (P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6);
  /// @}

private:
  /// Pointer to the original function pointer
  static funcptr_type orig_funcptr_;
};

}
}

#include "Replacement_Routine.inl"

#endif  // !defined _OASIS_PIN_PROTOTYPE_H_
