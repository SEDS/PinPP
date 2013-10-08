// -*- C++ -*-

//==============================================================================
/**
 *  @file        Mutex.h
 *
 *  $Id: Mutex.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_MUTEX_H_
#define _OASIS_PIN_MUTEX_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Mutex
 *
 * Wrapper class for PIN_MUTEX.  Should be used with the GUARD class for
 * GetMutex and ReleaseMutex calls.
 */
class Mutex
{
public:
  /// Default constructor.
  Mutex (void);

  /// Destructor.
  ~Mutex (void);

  /// Lock the mutex (blocking).
  void acquire (void);

  /// Lock the mutex (non-blocking).
  bool try_acquire (void);

  /// Unlock the mutex.
  void release (void);

  /// Check if it is locked
  bool is_locked (void); 

private:
  bool locked_;
  PIN_MUTEX mutex_;
};

} // namespace OASIS
} // namespace Pin

#include "Mutex.inl"

#endif  // _OASIS_PIN_MUTEX_H_
