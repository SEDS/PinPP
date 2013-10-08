#ifndef _OASIS_PIN_INSERT_T_H_
#define _OASIS_PIN_INSERT_T_H_

#include "Arg_List.h"

namespace OASIS
{
namespace Pin
{

/**
 * @struct Insert_T
 *
 * Wrapper class for executing an InsertCall function.
 */
template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...), int N = Length <typename CALLBACK::arglist_type>::RET>
struct Insert_T;

// 0 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 0>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       IARG_END);
  }
};

// 1 argument

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 1>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       IARG_END);
  }
};

// 2 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 2>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       IARG_END);
  }
};

// 3 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 3>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       IARG_END);
  }
};

// 4 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 4>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       IARG_END);
  }
};

// 5 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 5>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       Arg_List <CALLBACK>::template get_arg <4> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
       IARG_END);
  }
};

// 6 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 6>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       Arg_List <CALLBACK>::template get_arg <4> (),
       Arg_List <CALLBACK>::template get_arg <5> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
       IARG_END);
  }
};

// 7 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 7>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       Arg_List <CALLBACK>::template get_arg <4> (),
       Arg_List <CALLBACK>::template get_arg <5> (),
       Arg_List <CALLBACK>::template get_arg <6> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
       IARG_END);
  }
};

// 8 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 8>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       Arg_List <CALLBACK>::template get_arg <4> (),
       Arg_List <CALLBACK>::template get_arg <5> (),
       Arg_List <CALLBACK>::template get_arg <6> (),
       Arg_List <CALLBACK>::template get_arg <7> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
       IARG_END);
  }
};

// 8 arguments

template <typename S, typename CALLBACK, void (*F) (S, IPOINT, AFUNPTR, ...)>
struct Insert_T <S, CALLBACK, F, 9>
{
  template <typename A>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (),
       Arg_List <CALLBACK>::template get_arg <1> (),
       Arg_List <CALLBACK>::template get_arg <2> (),
       Arg_List <CALLBACK>::template get_arg <3> (),
       Arg_List <CALLBACK>::template get_arg <4> (),
       Arg_List <CALLBACK>::template get_arg <5> (),
       Arg_List <CALLBACK>::template get_arg <6> (),
       Arg_List <CALLBACK>::template get_arg <7> (),
       Arg_List <CALLBACK>::template get_arg <8> (),
       IARG_END);
  }

  template <typename A, typename XARG1>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1),
       Arg_List <CALLBACK>::template get_arg <8> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
       Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
       Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static void execute (S scope, IPOINT location, CALLBACK * callback, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    F (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, callback,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
       Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
       IARG_END);
  }
};

}
}

#endif  // !defined _OASIS_PIN_INSERT_T_H_
