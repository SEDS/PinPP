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

  /// Copy constructor.
  Lock (const Lock & lock);

  /// Destructor.
  ~Lock (void);

  /// Assignment operator.
  const Lock & operator = (const Lock & lock);

  /**
   * Acquire the lock
   *
   * @param[in]     owner     The owner of the lock.
   */
  void acquire (int owner);

  /// Release ownership of the lock.
  void release (void);

private:
  PIN_LOCK lock_;
};

} // namespace OASIS
} // namespace Pin

#include "Lock.inl"

#endif  // _OASIS_PIN_LOCK_H_
