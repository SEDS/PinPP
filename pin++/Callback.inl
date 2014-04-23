// -*- C++ -*-
// $Id: Callback.inl 2294 2013-10-01 20:09:09Z hillj $

#include "Context.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (void)>::__analyze (void * callback)
{
  reinterpret_cast <T *> (callback)->handle_analyze ();
}

template <typename T, typename A1>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1)>::__analyze (void * callback, param_type1 p1)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1);
}

template <typename T, typename A1>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1)>::__analyze_if (void * callback, param_type1 p1)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1);
}

template <typename T, typename A1>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1)>::__analyze_then (void * callback, param_type1 p1)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1);
}

template <typename T, typename A1, typename A2>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2)>::
__analyze (void * callback, param_type1 p1, param_type2 p2)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2);
}

template <typename T, typename A1, typename A2>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2);
}

template <typename T, typename A1, typename A2>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2);
}

template <typename T, typename A1, typename A2, typename A3>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3);
}

template <typename T, typename A1, typename A2, typename A3>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3);
}

template <typename T, typename A1, typename A2, typename A3>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3);
}

template <typename T, typename A1, typename A2, typename A3, typename A4>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4);
}

template <typename T, typename A1, typename A2, typename A3, typename A4>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4);
}

template <typename T, typename A1, typename A2, typename A3, typename A4>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6, p7);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6, p7);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6, p7);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7, A8)>::
__analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  reinterpret_cast <T *> (callback)->handle_analyze (p1, p2, p3, p4, p5, p6, p7, p8);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
inline
ADDRINT PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7, A8)>::
__analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  return reinterpret_cast <T *> (callback)->handle_analyze_if (p1, p2, p3, p4, p5, p6, p7, p8);
}

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
inline
void PIN_FAST_ANALYSIS_CALL Callback <T (A1, A2, A3, A4, A5, A6, A7, A8)>::
__analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
{
  reinterpret_cast <T *> (callback)->handle_analyze_then (p1, p2, p3, p4, p5, p6, p7, p8);
}

} // namespace OASIS
} // namespace Pin
