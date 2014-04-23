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
#include "Insert_T.h"

namespace OASIS
{
namespace Pin
{

// Forward decl.
class Ins;

// Forward decl.
class Bbl;

// Forward decl.
class Routine;

///////////////////////////////////////////////////////////////////////////////
// class Callback_Guard

/**
 * @class Callback_Guard
 *
 * Wrapper class that handles executing _InsertIfCall and _InsertThenCall
 * for the sampling callback and the analysis callback. The wrapper ensures
 * that the same object and location is applied to either callback object. 
 * This is necessary per the Pin specification.
 */
template <typename GUARD, typename CALLBACK>
class Callback_Guard
{
public:
  /// Type definition of the guard type.
  typedef GUARD guard_type;

  /// Type definition of the callback type.
  typedef CALLBACK callback_type;

  Callback_Guard (GUARD & guard, CALLBACK & callback)
    : guard_ (guard),
      callback_ (callback)
  {

  }

  Callback_Guard (const Callback_Guard & src)
    : guard_ (src.guard_),
      callback_ (src.callback_)
  {

  }

  const Callback_Guard & operator = (const Callback_Guard & rhs)
  {
    this->guard_ = rhs.guard_;
    this->callback_ = rhs.callback_;

    return *this;
  }

  template <typename S>
  void insert (IPOINT location, const S & obj)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze);
  }

private:
  /// Guard object that determine when the callback is called.
  GUARD & guard_;

  /// Target callback object.
  CALLBACK & callback_;
};

///////////////////////////////////////////////////////////////////////////////
// class Callback_Base

/**
 * @class Callback_Base
 *
 * Base class for all callbacks. The callbacks are where the analysis code 
 * resides.
 */
template <typename T, typename List>
class Callback_Base
{
public:
  /// Type definition of the callback.
  typedef T type;

  /// Type definition of the callback argument list.
  typedef List arglist_type;

  /// The number of arguments expected by the insert method.
  static const int arglist_length = Length <arglist_type>::RET;

  /// @{ InsertCall

  /**
   * Instrument the object with this analysis routine. The analysis routine
   * is inserted at \a location in relation to the object being instrumented.
   * Valid locations are:
   * 
   * = \a IPOINT_BEFORE
   * = \a IPOINT_AFTER
   * = \a IPOINT_ANYWHERE
   *
   * The \a obj is the object being instrumented. Based on Pin, the following
   * are acceptable objects types (or scopes):
   *
   *  = Ins
   *  = Bbl
   *  = Trace
   *  = Routine
   *
   * If the callback has parameters that require additional arguments, then the
   * additional arguments must come after the object being instrumented. The 
   * framework will take care of forming the correct argument list for you.
   *
   * @param[in]       location      Location to insert instrument
   * @param[in]       obj           Object to instrument
   */
  template <typename S>
  void insert (IPOINT location, const S & obj)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T *)this);
    insert (obj, location, &T::__analyze);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1>
  void insert (IPOINT location, const S & obj, XARG1 xarg1) 
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1, xarg2);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1, xarg2, xarg3);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1, xarg2, xarg3, xarg4);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5, XARG6 xarg6)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call);
    insert (obj, location, (T *) this, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }

  ///
  template <typename GUARD>
  Callback_Guard <GUARD, T> operator [] (GUARD & guard)
  {
    return Callback_Guard <GUARD, T> (guard, (T &)*this);
  }
};
  
///////////////////////////////////////////////////////////////////////////////
// Callback

// Forward decl.
template <typename T> class Callback;

/**
 * @class Callback
 *
 * Callback for passing 0 arguments to the analysis routine.
 */
template <typename T>
class Callback <T (void)> : public Callback_Base <T, End>
{
public:
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * callback);
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

///////////////////////////////////////////////////////////////////////////////
// Conditional_Callback

template <typename T> class Conditional_Callback;

template <typename T>
class Conditional_Callback <T (void)>
{
public:
  typedef T type;

  typedef End arglist_type;

  /// The number of arguments expected by the insert method.
  static const int arglist_length = Length <arglist_type>::RET;

  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * callback)
  {
    return reinterpret_cast <T *> (callback)->do_next ();
  }
};
 

} // namespace OASIS
} // namespace Pin

#include "Callback.inl"

#endif  // _OASIS_PIN_INSTRUCTION_CALLBACK_H_
