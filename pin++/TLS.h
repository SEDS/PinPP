// -*- C++ -*-

//==============================================================================
/**
 *  @file        TLS.h
 *
 *  $Id: TLS.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TLS_H_
#define _OASIS_PIN_TLS_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class TLS
 *
 * Wrapper class for Thread local storage, also known as Thread-specific
 * storage on most systems.
 */
template <typename T>
class TLS
{
public:
  /// Default constructor.
  TLS (DESTRUCTFUN destructor = 0);

  /// Copy constructor.
  TLS (const TLS & rhs);

  /// Destructor.
  ~TLS (void);

  /// Get the object in thread-local storage.
  T * operator -> (void) const;
  T * operator [] (THREADID thr_id) const;

  T * get (void) const;
  T * get (THREADID thr_id) const;

  /// Set the data for the local storage.
  void set (T * data);
  void set (THREADID thr_id, T * data);

  /// Test if the value is set.
  bool is_set (void) const;

  /// Assignment operator. This will copy the stored key.
  const TLS & operator = (const TLS & rhs);

private:
  TLS_KEY key_;
};

} // namespace OASIS
} // namespace Pin

#include "TLS.inl"

#endif  // _OASIS_PIN_TLS_H_
