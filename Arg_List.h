// -*- C++ -*-

//==============================================================================
/**
 *  @file        Arg_List.h
 *
 *  $Id: Arg_List.h 2305 2013-10-07 03:23:23Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_ARG_LIST_H_
#define _OASIS_PIN_ARG_LIST_H_

#include "Arg_Traits.h"
#include "If.h"
#include "Xarg_Select.h"

namespace OASIS
{
namespace Pin
{

/**
 * @struct End
 *
 * This structure marks the end of an argument list. The nodes in the list
 * should be either a Type_Node or a Value_Node.
 */
struct End
{
  typedef End Tail;
  typedef void value_type;
  typedef void arg_value_type;
};

/**
 * @struct Type_Node
 *
 * An IARG_TYPE node in the argument list.
 */
template <IARG_TYPE T, typename NEXT = End>
struct Type_Node
{
  /// Type definition of the arg value type.
  typedef IARG_TYPE arg_value_type;

  /// Type definition of the parameter type
  typedef typename Arg_T <T>::param_type param_type;

  /// Type definition of the next node.
  typedef NEXT Tail;

  static const IARG_TYPE value = T;
};

/**
 * @struct Value_Node
 *
 * The value associated with a Type_Node. If the Type_Node has an extra
 * argument, then the next node will in the list will be of this type.
 */
template <typename ARG_VALUE_TYPE, typename PARAM_TYPE, typename NEXT = End>
struct Value_Node
{
  /// Type definition of the arg value type.
  typedef ARG_VALUE_TYPE arg_value_type;

  /// Type definition of the value type.
  typedef PARAM_TYPE param_type;

  /// Type definition of the next node. It should be of type Type_Node.
  typedef NEXT Tail;
};

// template specializations

#define DEFINE_TYPE_NODE_WITH_EXTRA_ARGUMENT(IARG, ARG_VALUE_TYPE, PARAM_TYPE) \
  template <typename NEXT> \
  struct Type_Node <IARG, NEXT> { \
    typedef IARG_TYPE arg_value_type; \
    typedef typename Arg_T <IARG>::param_type param_type; \
    static const IARG_TYPE value = IARG; \
    typedef Value_Node <ARG_VALUE_TYPE, PARAM_TYPE, NEXT> Tail; \
  }

DEFINE_TYPE_NODE_WITH_EXTRA_ARGUMENT (IARG_MEMORYOP_EA, int, ADDRINT);
DEFINE_TYPE_NODE_WITH_EXTRA_ARGUMENT (IARG_FUNCARG_ENTRYPOINT_VALUE, int, ADDRINT);
DEFINE_TYPE_NODE_WITH_EXTRA_ARGUMENT (IARG_REG_REFERENCE, REG, PIN_REGISTER *);
DEFINE_TYPE_NODE_WITH_EXTRA_ARGUMENT (IARG_REG_VALUE, REG, ADDRINT);

/**
 * @struct Length
 *
 * Calculate the length of the list at compile-time.
 */
template <typename List>
struct Length
{
  static const int RET = Length < typename List::Tail >::RET + 1;
};

template < >
struct Length <End>
{
  static const int RET = 0;
};

template < >
struct Length < Type_Node <IARG_LAST> >
{
  static const int RET = 0;
};

/**
 * @struct Is_Value_Node
 *
 * Test if the current node has a value node next.
 */
template <typename List, int N = 0>
struct Is_Value_Node
{
  static const bool RET = Is_Value_Node <typename List::Tail, N - 1>::RET;
};

template <typename ARG_VALUE_TYPE, typename PARAM_TYPE, typename NEXT>
struct Is_Value_Node < Value_Node <ARG_VALUE_TYPE, PARAM_TYPE, NEXT>, 0>
{
  static const bool RET = true;
};

template <typename List>
struct Is_Value_Node <List, 0>
{
  static const bool RET = false;
};

/**
 * @struct Is_Type_Node
 *
 * Test if a node in the list is a Type_Node.
 */
template <typename List, int N = 0>
struct Is_Type_Node
{
  static const bool RET = Is_Type_Node <typename List::Tail, N - 1>::RET;
};

template <typename List>
struct Is_Type_Node <List, 0>
{
  static const bool RET = true;
};

template <typename ARG_VALUE_TYPE, typename PARAM_TYPE, typename NEXT>
struct Is_Type_Node < Value_Node <ARG_VALUE_TYPE, PARAM_TYPE, NEXT> , 0>
{
  static const bool RET = false;
};

template < >
struct Is_Type_Node <End, 0>
{
  static const bool RET = false;
};

/**
 * @struct Arg_Type
 *
 * Get the type information of an argument in the arg list.
 */
template <typename List, int N>
struct Arg_Type
{
  typedef typename Arg_Type <typename List::Tail, N - 1>::result_type result_type;
};

template <typename List>
struct Arg_Type <List, 0>
{
  typedef typename List::arg_value_type result_type;
};

/**
 * @struct Type_Node_Value
 *
 * Get the value of a type node in the list. It is assume that
 * node N is the list is a Type_Node.
 */
template <typename List, int N>
struct Type_Node_Value
{
  static const IARG_TYPE value = Type_Node_Value <typename List::Tail, N - 1>::value;
};

template <typename List>
struct Type_Node_Value <List, 0>
{
  static const IARG_TYPE value = List::value;
};

/**
 * @struct Increment
 *
 * Statically increment a value of the parameter type is true.
 */
template <bool result>
struct Increment
{
  static const int RET = 1;
};

template < >
struct Increment <false>
{
  static const int RET = 0;
};

/**
 * @struct Xarg_Ordinal
 *
 * Get the 1-based ordinal for the extra argument. This is not the same
 * as the extra arguments index. The ordinal is based on that of the other
 * extra arguments in the argument list, and therefore will be less than
 * or equal to the actual index value.
 */
template <typename List, int N>
struct Xarg_Ordinal
{
  static const int RET = Increment < Is_Value_Node <List>::RET >::RET + Xarg_Ordinal < typename List::Tail, N - 1 >::RET;
};

template <typename List>
struct Xarg_Ordinal <List, 0>
{
  static const int RET = Increment < Is_Value_Node <List>::RET >::RET;
};

/**
 * @class Type_Select
 *
 * Selete the IARG_* value for the specified node.
 */
template <typename List, int N>
struct Type_Select
{
  template <typename XARG1>
  inline static IARG_TYPE execute (const XARG1 &)
  {
    return Type_Node_Value <List, N>::value;
  }

  template <typename XARG1, typename XARG2>
  inline static IARG_TYPE execute (const XARG1 &, const XARG2 &)
  {
    return Type_Node_Value <List, N>::value;
  }

  template <typename XARG1, typename XARG2, typename XARG3>
  inline static IARG_TYPE execute (const XARG1 &, const XARG2 &, const XARG3 &)
  {
    return Type_Node_Value <List, N>::value;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static IARG_TYPE execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &)
  {
    return Type_Node_Value <List, N>::value;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static IARG_TYPE execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 &)
  {
    return Type_Node_Value <List, N>::value;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static IARG_TYPE execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 &, const XARG6 &)
  {
    return Type_Node_Value <List, N>::value;
  }
};

/**
 * @class Arg_List
 *
 * Compile-time selection of a value from the argument list. Right now,
 * we support up argument list that take up to 6 extra arguments. If you
 * need to support more than 6 extra arguments, then you need to extend
 * the inner classes accordingly.
 */
template <typename CALLBACK>
struct Arg_List
{
  /// Type definition of the argument list type for the callback.
  typedef typename CALLBACK::arglist_type type;

public:
  template <int N>
  inline static IARG_TYPE get_arg (void)
  {
    return Type_Node_Value <type, N>::value;
  }

  template <int N, typename XARG1>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1);
  }

  template <int N, typename XARG1, typename XARG2>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1, const XARG2 & xarg2)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1, xarg2);
  }

  template <int N, typename XARG1, typename XARG2, typename XARG3>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1, xarg2, xarg3);
  }

  template <int N, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1, xarg2, xarg3, xarg4);
  }

  template <int N, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1, xarg2, xarg3, xarg4, xarg5);
  }

  template <int N, typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static typename Arg_Type <type, N>::result_type
  get_arg (const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4, const XARG5 & xarg5, const XARG6 & xarg6)
  {
    typedef typename
      If < Is_Type_Node <type, N>::RET,
           Type_Select <type, N>,
           Xarg_Select < Xarg_Ordinal <type, N>::RET > >::result_type result_type;

    return result_type::execute (xarg1, xarg2, xarg3, xarg4, xarg5, xarg6);
  }
};

}
}

#endif
