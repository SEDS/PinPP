// -*- C++ -*-

//=============================================================================
/**
 * @file      Counter.h
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PINPP_CALLBACK_COUNTER_H_
#define _OASIS_PINPP_CALLBACK_COUNTER_H_

#include "pin++/Callback.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Counter
 *
 * Simple counter callback object. The Counter object is parameterize by
 * a type that implements pre-increment operator (i.e., operator ++). This
 * allows the counter to be used with basic integers, or abstract data types
 * that use operator overloading to implement pre-increment operator.
 *
 * T Requirements:
 *  - Initialization constructor with integer parameter
 *  - Pre-increment operator
 */
template <typename T = UINT64>
class Counter : public OASIS::Pin::Callback < Counter <T> (void) >
{
public:
  /// Type definition of the counter's type.
  typedef T type;

  /// Default constructor
  Counter (void);

  /// Handle the analysis callback
  void handle_analyze (void);

  /// Get the current count.
  const T & count (void) const;

private:
  /// Current count.
  T count_;
};

}
}

#include "Counter.inl"

#endif  // !defined _OASIS_PINPP_CALLBACK_COUNTER_H_
