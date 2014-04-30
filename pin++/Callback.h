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
 * for the sampling _this and the analysis _this. The wrapper ensures
 * that the same object and location is applied to either _this object. 
 * This is necessary per the Pin specification.
 */
template <typename GUARD, typename CALLBACK>
class Callback_Guard
{
public:
  /// Type definition of the guard type.
  typedef GUARD guard_type;

  /// Type definition of the _this type.
  typedef CALLBACK callback_type;

  /**
   * Initializing constructor
   *
   * @param[in]       guard         Reference to conditional callback object
   * @param[in]       callback      Callback object being guareded 
   */
  Callback_Guard (GUARD & guard, CALLBACK & callback)
    : guard_ (guard),
      callback_ (callback) { }

  /**
   * Copy constructor.
   */
  Callback_Guard (const Callback_Guard & src)
    : guard_ (src.guard_),
      callback_ (src.callback_) { }

  /**
   * Assignment operator
   */
  const Callback_Guard & operator = (const Callback_Guard & rhs)
  {
    this->guard_ = rhs.guard_;
    this->callback_ = rhs.callback_;

    return *this;
  }

  /**
   * Insert the conditional callback and the regular callback into the 
   * \a obj at the specification \a location.
   *
   * @param[in]       location        Location to perform insert
   * @param[in]       obj             Target object for insert
   */
  template <typename S>
  void insert (IPOINT location, const S & obj)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1>
  void insert (IPOINT location, const S & obj, XARG1 xarg1)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1, typename XARG2>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1, xarg2);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  /**
   * @overloaded
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5, XARG6 xarg6)
  {
    Insert_T <S, GUARD, GUARD::arglist_length> __if (S::__insert_if_call, this->guard_);
    __if (obj, location, &GUARD::__do_next);

    Insert_T <S, CALLBACK, CALLBACK::arglist_length> __then (S::__insert_then_call, this->callback_);
    __then (obj, location, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }

private:
  /// Guard object that determine when the _this is called.
  GUARD & guard_;

  /// Target _this object.
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
  /// Type definition of the _this.
  typedef T type;

  /// Type definition of the _this argument list.
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
   * If the _this has parameters that require additional arguments, then the
   * additional arguments must come after the object being instrumented. The 
   * framework will take care of forming the correct argument list for you.
   *
   * @param[in]       location      Location to insert instrument
   * @param[in]       obj           Object to instrument
   */
  template <typename S>
  void insert (IPOINT location, const S & obj)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1>
  void insert (IPOINT location, const S & obj, XARG1 xarg1) 
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void insert (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5, XARG6 xarg6)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }

  /// @}

  /// @{ InsertPredicatedCall

  /**
   * Instrument the object with this predicated analysis routine. The analysis 
   * routine is inserted at \a location in relation to the object being instrumented.
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
   * If the _this has parameters that require additional arguments, then the
   * additional arguments must come after the object being instrumented. The 
   * framework will take care of forming the correct argument list for you.
   *
   * @param[in]       location      Location to insert instrument
   * @param[in]       obj           Object to instrument
   */
  template <typename S>
  void insert_predicated (IPOINT location, const S & obj)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1) 
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  /**
   * @overload
   */
  template <typename S, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void insert_predicated (IPOINT location, const S & obj, XARG1 xarg1, XARG2 xarg2, XARG3 xarg3, XARG4 xarg4, XARG5 xarg5, XARG6 xarg6)
  {
    Insert_T <S, T, arglist_length> insert (S::__insert_predicated_call, (T &)*this);
    insert (obj, location, &T::__analyze, xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }
  /// @}

  /**
   * Create a callback guard for the callback object. The purpose of the
   * callback guard is to insert a conditional guard into the target object.
   * The conditionl guard controls when the Callback object is invoked.
   */
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
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze ();
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1);
  }
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
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2);
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3);
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3, p4);
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3, p4, p5);
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3, p4, p5, p6);
  }
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

  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3, p4, p5, p6, p7);
  }
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
  static void PIN_FAST_ANALYSIS_CALL __analyze (void * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4, param_type5 p5, param_type6 p6, param_type7 p7, param_type8 p8)
  {  
    reinterpret_cast <T *> (_this)->handle_analyze (p1, p2, p3, p4, p5, p6, p7, p8);
  }
  /// @}
};

///////////////////////////////////////////////////////////////////////////////
// Conditional_Callback


/**
 * @class Callback_Base
 *
 * Base class for all callbacks. The callbacks are where the analysis code 
 * resides.
 */
template <typename T, typename List>
class Conditional_Callback_Base
{
public:
  /// Type definition of the _this.
  typedef T type;

  /// Type definition of the _this argument list.
  typedef List arglist_type;

  /// The number of arguments expected by the insert method.
  static const int arglist_length = Length <arglist_type>::RET;
};

/**
 * @class Conditional_Callback
 *
 * Conditional callback are callback back objects that determine when a 
 * regular \a Callback object should fire. It therefore acts like a guard
 * to the callback it is associated with.
 *
 * Each conditional callback object is required to implemented do_next ()
 * method. This is similar to the handle_analyze () method on regular
 * \a Callback objects. The return type of the method must be bool. If
 * the return value is \a true, then the traditional callback object will
 * fire. If it is \a false, then nothing happens. This allows the conditional
 * callback to have different logic that determines when the traditional
 * callbakc object should fire.

 * Similar to regular \a Callack objects, the do_next () method can take 
 * multiple parameters. You just need to define the parameters when defining
 * the \a T template parameter as done with \a Callback objects.
 */
template <typename T> class Conditional_Callback;

/**
 * @class Conditional_Callback <T (void)>
 *
 * Conditional callback with no arguments.
 */
template <typename T>
class Conditional_Callback <T (void)> : 
  public Conditional_Callback_Base <T, End>
{
public:
  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * _this) 
  {
    return static_cast <ADDRINT> (reinterpret_cast <T *> (_this)->do_next ());
  }
};

/**
 * @class Conditional_Callback <T (A1)>
 *
 * Conditional callback with 1 argument.
 */
template <typename T, typename A1>
class Conditional_Callback <T (A1)> :
  public Conditional_Callback_Base <T, Type_Node <A1> >
{
public:
  /// @{ Argument Type Definitions
  static const IARG_TYPE arg_type1 = A1::arg_type;
  /// @}

  /// @{ Parameter Type Definitions
  typedef typename A1::param_type param_type1;
  /// @}

  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * _this, param_type1 p1)
  {  
    return static_cast <ADDRINT> (reinterpret_cast <T *> (_this)->do_next (p1));
  }
};

/**
 * @class Conditional_Callback <T (A1, A2)>
 *
 * Conditional callback with 2 arguments.
 */
template <typename T, typename A1, typename A2>
class Conditional_Callback <T (A1, A2)> :
  public Conditional_Callback_Base <T, Type_Node <A1, Type_Node <A2> > >
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

  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * _this, param_type1 p1, param_type2 p2)
  {  
    return static_cast <ADDRINT> (reinterpret_cast <T *> (_this)->do_next (p1, p2));
  }
};
 
/**
 * @class Conditional_Callback <T (A1, A2, A3)>
 *
 * Conditional callback with 3 arguments.
 */
template <typename T, typename A1, typename A2, typename A3>
class Conditional_Callback <T (A1, A2, A3)> :
  public Conditional_Callback_Base <T, Type_Node <A1, Type_Node <A2, Type_Node <A3> > > >
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

  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * _this, param_type1 p1, param_type2 p2, param_type3 p3)
  {  
    return static_cast <ADDRINT> (reinterpret_cast <T *> (_this)->do_next (p1, p2, p3));
  }
};

/**
 * @class Conditional_Callback <T (A1, A2, A3, A4)>
 *
 * Conditional callback with 4 arguments.
 */
template <typename T, typename A1, typename A2, typename A3, typename A4>
class Conditional_Callback <T (A1, A2, A3, A4)> :
  public Conditional_Callback_Base <T, Type_Node <A1, Type_Node <A2, Type_Node <A3, Type_Node <A4> > > > >
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

  static ADDRINT PIN_FAST_ANALYSIS_CALL __do_next (VOID * _this, param_type1 p1, param_type2 p2, param_type3 p3, param_type4 p4)
  {  
    return static_cast <ADDRINT> (reinterpret_cast <T *> (_this)->do_next (p1, p2, p3, p4));
  }
};

} // namespace OASIS
} // namespace Pin

#endif  // _OASIS_PIN_INSTRUCTION_CALLBACK_H_
