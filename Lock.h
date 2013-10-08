// -*- C++ -*-

//==============================================================================
/**
 *  @file        Lock.h
 *
 *  $Id: Lock.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_LOCK_H_
#define _OASIS_PIN_LOCK_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Lock
 *
 * Wrapper class for PIN_LOCK.  Should be used with the GUARD class for
 * GetLock and ReleaseLock calls.
 */
class Lock
{
public:
  /// Default constructor.
  Lock (void);

  /// Initalizing constructor.
  Lock (int owner);

  /// Destructor.
  ~Lock (void);

  /// Acquire the lock.
  void acquire (void);

  /// Try to acquire the lock.
  bool try_acquire (void);

  /// Release ownership of the lock.
  void release (void);

  /// Check if it is locked
  bool locked (void);

  /// Owner setter
  void owner (int owner);

  /// Owner getter
  int owner (void);

private:
  bool locked_;
  int owner_;
  PIN_LOCK lock_;
};

} // namespace OASIS
} // namespace Pin

#include "Lock.inl"

#endif  // _OASIS_PIN_LOCK_H_
