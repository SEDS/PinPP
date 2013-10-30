// -*- C++ -*-

//==============================================================================
/**
 *  @file        Callback.h
 *
 *  $Id: Callback.h 2302 2013-10-05 05:54:21Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_CALLBACK_H_
#define _OASIS_PIN_CALLBACK_H_

#include "pin.H"
#include "Arg_List.h"

namespace OASIS
{
namespace Pin
{
    
/**
 * @class Callback
 *
 * Base class for all callbacks. The callbacks are where the
 * analysis code resides.
 */
template <typename T, typename List>
class Callback_Base
{
public:
  typedef T type;

  /// @{ Argument List Definitions
  typedef List arglist_type;
  static const int arglist_length = Length <List>::RET;
  /// @}

private:
  /// Argument list for the callback.
  List arglist_;
};
  
template <typename T> class Callback;
    
/**
 * @class Callback0
 *
 * Callback for passing 0 arguments to the analysis routine.
 */
template <typename T>
class Callback <T (void)> : public Callback_Base <T, End>
{
public:
  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback);
  /// @}
};

template <typename T, typename A1>
class Callback <T (A1)> :
    public Callback_Base <T, Type_Node <A1> >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1);
  /// @}
};

template <typename T, typename A1, typename A2>
class Callback <T (A1, A2)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2> > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3>
class Callback <T (A1, A2, A3)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3> > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3, typename A4>
class Callback <T (A1, A2, A3, A4)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3, Type_Node <A4> > > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  static const IARG_TYPE arg_type4 = A4::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  typedef typename A4::param_type param_type4;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
class Callback <T (A1, A2, A3, A4, A5)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3, Type_Node <A4, Type_Node <A5> > > > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  static const IARG_TYPE arg_type4 = A4::arg_type;
  static const IARG_TYPE arg_type5 = A5::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  typedef typename A4::param_type param_type4;
  typedef typename A5::param_type param_type5;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class Callback <T (A1, A2, A3, A4, A5, A6)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3, Type_Node <A4, Type_Node <A5, Type_Node <A6> > > > > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  static const IARG_TYPE arg_type4 = A4::arg_type;
  static const IARG_TYPE arg_type5 = A5::arg_type;
  static const IARG_TYPE arg_type6 = A6::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  typedef typename A4::param_type param_type4;
  typedef typename A5::param_type param_type5;
  typedef typename A6::param_type param_type6;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class Callback <T (A1, A2, A3, A4, A5, A6, A7)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3, Type_Node <A4, Type_Node <A5, Type_Node <A6, Type_Node <A7> > > > > > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  static const IARG_TYPE arg_type4 = A4::arg_type;
  static const IARG_TYPE arg_type5 = A5::arg_type;
  static const IARG_TYPE arg_type6 = A6::arg_type;
  static const IARG_TYPE arg_type7 = A7::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  typedef typename A4::param_type param_type4;
  typedef typename A5::param_type param_type5;
  typedef typename A6::param_type param_type6;
  typedef typename A7::param_type param_type7;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7);
  /// @}
};

template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
class Callback <T (A1, A2, A3, A4, A5, A6, A7, A8)> :
  public Callback_Base <T, Type_Node < A1, Type_Node <A2, Type_Node <A3, Type_Node <A4, Type_Node <A5, Type_Node <A6, Type_Node <A7, Type_Node <A8> > > > > > > > >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  static const IARG_TYPE arg_type2 = A2::arg_type;
  static const IARG_TYPE arg_type3 = A3::arg_type;
  static const IARG_TYPE arg_type4 = A4::arg_type;
  static const IARG_TYPE arg_type5 = A5::arg_type;
  static const IARG_TYPE arg_type6 = A6::arg_type;
  static const IARG_TYPE arg_type7 = A7::arg_type;
  static const IARG_TYPE arg_type8 = A8::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  typedef typename A2::param_type param_type2;
  typedef typename A3::param_type param_type3;
  typedef typename A4::param_type param_type4;
  typedef typename A5::param_type param_type5;
  typedef typename A6::param_type param_type6;
  typedef typename A7::param_type param_type7;
  typedef typename A8::param_type param_type8;
  /// @}

  /// @{ Analysis Methods
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8);
  static ADDRINT PIN_FAST_ANALYSIS_CALL __analyze_if (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8);
  static void PIN_FAST_ANALYSIS_CALL __analyze_then (void * callback, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8);
  /// @}
};

} // namespace OASIS
} // namespace Pin

#include "Callback.inl"

#endif  // _OASIS_PIN_INSTRUCTION_CALLBACK_H_
