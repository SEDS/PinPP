// -*- C++ -*-
// $Id: Callback.inl 2294 2013-10-01 20:09:09Z hillj $

#include "Context.h"

namespace OASIS
{
namespace Pin
{

///////////////////////////////////////////////////////////////////////////////
// class Callback

//
// __analyze_fork
//
template <typename T, typename List>
inline
void Callback <T, List>::__analyze_fork (THREADID index, const CONTEXT *ctx, VOID * obj)
{
  reinterpret_cast <T *> (obj)->handle_analyze_fork (index, ctx);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback0

//
// __analyze
//
template <typename T>
inline
void PIN_FAST_ANALYSIS_CALL Callback0 <T>::__analyze (void * callback)
{
  reinterpret_cast <T *> (callback)->handle_analyze ();
}

//
// __analyze_if
//
template <typename T>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback0 <T>::__analyze_if (void * callback)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if ();
}

//
// __analyze_then
//
template <typename T>
inline
void PIN_FAST_ANALYSIS_CALL Callback0 <T>::__analyze_then (void * callback)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then ();
}

///////////////////////////////////////////////////////////////////////////////
// class Callback1

//
// __analyze
//
template <typename T, IARG_TYPE P1>
inline
void PIN_FAST_ANALYSIS_CALL Callback1 <T, P1>::__analyze (void * callback, param_type1 p1)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE P1>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback1 <T, P1>::__analyze_if (void * callback, param_type1 p1)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE P1>
inline
void PIN_FAST_ANALYSIS_CALL Callback1 <T, P1>::__analyze_then (void * callback, param_type1 p1)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback2

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2>
inline
void PIN_FAST_ANALYSIS_CALL Callback2 <T, A1, A2>::
__analyze (void * callback, param_type1 p1, param_type2 p2)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback2 <T, A1, A2>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2>
inline
void PIN_FAST_ANALYSIS_CALL Callback2 <T, A1, A2>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback3

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3>
inline
void PIN_FAST_ANALYSIS_CALL Callback3 <T, A1, A2, A3>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback3 <T, A1, A2, A3>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3>
inline
void PIN_FAST_ANALYSIS_CALL Callback3 <T, A1, A2, A3>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback4

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4>
inline
void PIN_FAST_ANALYSIS_CALL Callback4 <T, A1, A2, A3, A4>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback4 <T, A1, A2, A3, A4>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4>
inline
void PIN_FAST_ANALYSIS_CALL Callback4 <T, A1, A2, A3, A4>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback5

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5>
inline
void PIN_FAST_ANALYSIS_CALL Callback5 <T, A1, A2, A3, A4, A5>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback5 <T, A1, A2, A3, A4, A5>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5>
inline
void PIN_FAST_ANALYSIS_CALL Callback5 <T, A1, A2, A3, A4, A5>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback6

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6>
inline
void PIN_FAST_ANALYSIS_CALL Callback6 <T, A1, A2, A3, A4, A5, A6>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback6 <T, A1, A2, A3, A4, A5, A6>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6>
inline
void PIN_FAST_ANALYSIS_CALL Callback6 <T, A1, A2, A3, A4, A5, A6>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback7

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7>
inline
void PIN_FAST_ANALYSIS_CALL Callback7 <T, A1, A2, A3, A4, A5, A6, A7>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6, p7);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback7 <T, A1, A2, A3, A4, A5, A6, A7>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6, p7);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7>
inline
void PIN_FAST_ANALYSIS_CALL Callback7 <T, A1, A2, A3, A4, A5, A6, A7>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6, p7);
}

///////////////////////////////////////////////////////////////////////////////
// class Callback8

//
// __analyze
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7, IARG_TYPE A8>
inline
void PIN_FAST_ANALYSIS_CALL Callback8 <T, A1, A2, A3, A4, A5, A6, A7, A8>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6, p7, p8);
}

//
// __analyze_if
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7, IARG_TYPE A8>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback8 <T, A1, A2, A3, A4, A5, A6, A7, A8>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6, p7, p8);
}

//
// __analyze_then
//
template <typename T, IARG_TYPE A1, IARG_TYPE A2, IARG_TYPE A3, IARG_TYPE A4, IARG_TYPE A5, IARG_TYPE A6, IARG_TYPE A7, IARG_TYPE A8>
inline
void PIN_FAST_ANALYSIS_CALL Callback8 <T, A1, A2, A3, A4, A5, A6, A7, A8>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6, p7, p8);
}

} // namespace OASIS
} // namespace Pin
