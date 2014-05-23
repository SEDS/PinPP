#ifndef _OASIS_PIN_INSERT_T_H_
#define _OASIS_PIN_INSERT_T_H_

#include "Arg_List.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
struct Insert_Call_T
{
  /// Type definition of the Pin type.
  typedef typename T::pin_type pin_type;

  /// Type definition of the function pointer to *_InsertCall.
  typedef VOID (* funcptr_type) (pin_type, IPOINT, AFUNPTR, ...);
};

template <typename S, typename CALLBACK>
struct Insert_Base_T
{
  /// Type definition of the function pointer.
  typedef typename Insert_Call_T <S>::funcptr_type funcptr_type;

  /**
   * Initialization constructor
   *
   * @param[in]       insert        Pointer to insert function
   * @param[in]       callback      Target callback object to insert
   */
  Insert_Base_T (funcptr_type insert, CALLBACK & callback)
    : insert_ (insert),
      callback_ (callback) { }

protected:
  /// Pointer to the insert function
  funcptr_type insert_;

  /// Target callback object
  CALLBACK & callback_;
};

/**
 * @struct Insert_T
 *
 * Functor executing an InsertCall function. The \a S template parameter
 * is the scope of the insert (i.e., Ins, Bbl, Trace, or Routine). The
 * \a CALLBACK template parameter is the callback object we are inserting
 * into the binary. The \a CALLBACK object will recieve notifications when
 * it needs to perform analysis. The \a N template parameter is the number
 * of arguments need to perform the insert.
 * is the 
 */
template <typename S, typename CALLBACK, int N>
struct Insert_T
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    
};

// 0 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 0> : public Insert_Base_T <S, CALLBACK>
{ 
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    

  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (const S & scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, 
                   location, 
                   (AFUNPTR)analyze, 
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, 
                   &this->callback_,
                   IARG_END);
  }
};

// 1 argument

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 1> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    

  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback)
  {

  }

  template <typename A>
  void operator () (const S & scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, 
                   location, 
                   (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, 
                   &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   IARG_END);
  }
};

// 2 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 2> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback)
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   Arg_List <CALLBACK>::template get_arg <1> (),
                   IARG_END);
  }

  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                   IARG_END);
  }
};

// 3 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 3> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   Arg_List <CALLBACK>::template get_arg <1> (),
                   Arg_List <CALLBACK>::template get_arg <2> (),
                   IARG_END);
  }

  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                   IARG_END);
  }
};

// 4 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 4> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   Arg_List <CALLBACK>::template get_arg <1> (),
                   Arg_List <CALLBACK>::template get_arg <2> (),
                   Arg_List <CALLBACK>::template get_arg <3> (),
                   IARG_END);
  }

  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
       IARG_FAST_ANALYSIS_CALL,
       IARG_PTR, &this->callback_,
       Arg_List <CALLBACK>::template get_arg <0> (xarg1),
       Arg_List <CALLBACK>::template get_arg <1> (xarg1),
       Arg_List <CALLBACK>::template get_arg <2> (xarg1),
       Arg_List <CALLBACK>::template get_arg <3> (xarg1),
       IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                   IARG_END);
  }
};

// 5 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 5> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   Arg_List <CALLBACK>::template get_arg <1> (),
                   Arg_List <CALLBACK>::template get_arg <2> (),
                   Arg_List <CALLBACK>::template get_arg <3> (),
                   Arg_List <CALLBACK>::template get_arg <4> (),
                   IARG_END);
  }

  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                   IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                   IARG_END);
  }
};

// 6 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 6> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (),
                   Arg_List <CALLBACK>::template get_arg <1> (),
                   Arg_List <CALLBACK>::template get_arg <2> (),
                   Arg_List <CALLBACK>::template get_arg <3> (),
                   Arg_List <CALLBACK>::template get_arg <4> (),
                   Arg_List <CALLBACK>::template get_arg <5> (),
                   IARG_END);
  }

  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                   Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                   IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
                   Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                   Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                   IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 7> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 8> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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

// 9 arguments

template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 9> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                   IARG_FAST_ANALYSIS_CALL,
                   IARG_PTR, &this->callback_,
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

// 10 arguments
  
template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 10> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (),
                  Arg_List <CALLBACK>::template get_arg <1> (),
                  Arg_List <CALLBACK>::template get_arg <2> (),
                  Arg_List <CALLBACK>::template get_arg <3> (),
                  Arg_List <CALLBACK>::template get_arg <4> (),
                  Arg_List <CALLBACK>::template get_arg <5> (),
                  Arg_List <CALLBACK>::template get_arg <6> (),
                  Arg_List <CALLBACK>::template get_arg <7> (),
                  Arg_List <CALLBACK>::template get_arg <8> (),
                  Arg_List <CALLBACK>::template get_arg <9> (),
                  IARG_END);
  }
    
  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                    IARG_FAST_ANALYSIS_CALL,
                    IARG_PTR, &this->callback_,
                    Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <6> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <7> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <8> (xarg1),
                    Arg_List <CALLBACK>::template get_arg <9> (xarg1),
                    IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4),
                  IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  IARG_END);
  }
};

// 11 arguments
  
template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 11> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (),
                  Arg_List <CALLBACK>::template get_arg <1> (),
                  Arg_List <CALLBACK>::template get_arg <2> (),
                  Arg_List <CALLBACK>::template get_arg <3> (),
                  Arg_List <CALLBACK>::template get_arg <4> (),
                  Arg_List <CALLBACK>::template get_arg <5> (),
                  Arg_List <CALLBACK>::template get_arg <6> (),
                  Arg_List <CALLBACK>::template get_arg <7> (),
                  Arg_List <CALLBACK>::template get_arg <8> (),
                  Arg_List <CALLBACK>::template get_arg <9> (),
                  Arg_List <CALLBACK>::template get_arg <10> (),
                  IARG_END);
  }
    
  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  IARG_END);
  }
};
  
// 12 arguments
  
template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 12> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (),
                  Arg_List <CALLBACK>::template get_arg <1> (),
                  Arg_List <CALLBACK>::template get_arg <2> (),
                  Arg_List <CALLBACK>::template get_arg <3> (),
                  Arg_List <CALLBACK>::template get_arg <4> (),
                  Arg_List <CALLBACK>::template get_arg <5> (),
                  Arg_List <CALLBACK>::template get_arg <6> (),
                  Arg_List <CALLBACK>::template get_arg <7> (),
                  Arg_List <CALLBACK>::template get_arg <8> (),
                  Arg_List <CALLBACK>::template get_arg <9> (),
                  Arg_List <CALLBACK>::template get_arg <10> (),
                  Arg_List <CALLBACK>::template get_arg <11> (),
                  IARG_END);
  }
    
  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  IARG_END);
  }
};

// 13 arguments
  
template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 13> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (),
                  Arg_List <CALLBACK>::template get_arg <1> (),
                  Arg_List <CALLBACK>::template get_arg <2> (),
                  Arg_List <CALLBACK>::template get_arg <3> (),
                  Arg_List <CALLBACK>::template get_arg <4> (),
                  Arg_List <CALLBACK>::template get_arg <5> (),
                  Arg_List <CALLBACK>::template get_arg <6> (),
                  Arg_List <CALLBACK>::template get_arg <7> (),
                  Arg_List <CALLBACK>::template get_arg <8> (),
                  Arg_List <CALLBACK>::template get_arg <9> (),
                  Arg_List <CALLBACK>::template get_arg <10> (),
                  Arg_List <CALLBACK>::template get_arg <11> (),
                  Arg_List <CALLBACK>::template get_arg <12> (),
                  IARG_END);
  }
    
  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  IARG_END);
  }
};
  
// 14 arguments
  
template <typename S, typename CALLBACK>
struct Insert_T <S, CALLBACK, 14> : public Insert_Base_T <S, CALLBACK>
{
  /// Type definition of the base type
  typedef Insert_Base_T <S, CALLBACK> base_type;

  /// Type definition of the function pointer type
  typedef typename base_type::funcptr_type funcptr_type;    


  Insert_T (funcptr_type insert, CALLBACK & callback)
    : base_type (insert, callback) 
  {

  }

  template <typename A>
  void operator () (S scope, IPOINT location, A analyze)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (),
                  Arg_List <CALLBACK>::template get_arg <1> (),
                  Arg_List <CALLBACK>::template get_arg <2> (),
                  Arg_List <CALLBACK>::template get_arg <3> (),
                  Arg_List <CALLBACK>::template get_arg <4> (),
                  Arg_List <CALLBACK>::template get_arg <5> (),
                  Arg_List <CALLBACK>::template get_arg <6> (),
                  Arg_List <CALLBACK>::template get_arg <7> (),
                  Arg_List <CALLBACK>::template get_arg <8> (),
                  Arg_List <CALLBACK>::template get_arg <9> (),
                  Arg_List <CALLBACK>::template get_arg <10> (),
                  Arg_List <CALLBACK>::template get_arg <11> (),
                  Arg_List <CALLBACK>::template get_arg <12> (),
                  Arg_List <CALLBACK>::template get_arg <13> (),
                  IARG_END);
  }
    
  template <typename A, typename XARG1>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2, xarg3),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2, xarg3, xarg4),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <11> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2, xarg3, xarg4, xarg5),
                  IARG_END);
  }
    
  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6),
                  IARG_END);
  }

  template <typename A, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6, typename XARG7>
  void operator () (S scope, IPOINT location, A analyze, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6, const XARG7 & xarg7)
  {
    this->insert_ (scope, location, (AFUNPTR)analyze,
                  IARG_FAST_ANALYSIS_CALL,
                  IARG_PTR, &this->callback_,
                  Arg_List <CALLBACK>::template get_arg <0> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <1> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <2> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <3> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <4> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <5> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <6> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <7> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <8> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <9> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <10> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <12> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  Arg_List <CALLBACK>::template get_arg <13> (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6, xarg7),
                  IARG_END);
  }
};

}
}

#endif  // !defined _OASIS_PIN_INSERT_T_H_
