// -*- C++ -*-

//=============================================================================
/**
 * @file      Batch_Counter.h
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PINPP_CALLBACK_BATCH_COUNTER_H_
#define _OASIS_PINPP_CALLBACK_BATCH_COUNTER_H_

#include "pin++/Callback.h"

namespace OASIS
{
namespace Pin
{

template <typename T = UINT64, typename INCREMENT = T>
class Batch_Counter : public OASIS::Pin::Callback < Batch_Counter <T, INCREMENT> (void) >
{
public:
  /// Type definition for the counter type.
  typedef T type;

  /// Type definition of the increment type.
  typedef INCREMENT increment_type;

  /// Default constructor
  Batch_Counter (void);
  Batch_Counter (const INCREMENT & inc);

  /// Set the increment value for the batch counter.
  void increment (const INCREMENT & inc);

  /// Get the current increment value.
  const INCREMENT & increment (void) const;

  /// Handle the analysis callback from Pin.
  void handle_analyze (void);

  /// The the current count.
  const T & count (void) const;

private:
  /// Current count value
  T count_;

  /// Increment value
  INCREMENT increment_;
};

}
}

#include "Batch_Counter.inl"

#endif  // !defined _OASIS_PINPP_CALLBACK_BATCH_COUNTER_H_
