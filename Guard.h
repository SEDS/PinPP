// -*- C++ -*-

//==============================================================================
/**
 *  @file        Guard.h
 *
 *  $Id: Guard.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_GUARD_H_
#define _OASIS_PIN_GUARD_H_

#include "RW_Mutex.h"
#include "Lock.h"
#include "Mutex.h"
#include "Semaphore.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Guard
 *
 * Guard for restricting lock ownership to a scope.
 */
template <typename T>
class Guard;

/**
 * Template specalization for Lock.
 * Unique features are:
 *  Locks do not have a non-blocking acquire, removing try_acquire and is_locked.
 *  Can provide owner identifier upon acquisition.
 *
 */
template <>
class Guard <Lock>
{
public:
  /**
   * Locking constructor.
   *
   * @param[in]     owner       Owner of the lock
   */
  Guard (Lock & lock, int owner);

  /// Destructor.
  ~Guard (void);

private:
  Lock & lock_;
};

/**
 * Template specalization for Mutex.
 */
template <>
class Guard <Mutex>
{
public:
  /// Locking constructor.
  Guard (Mutex & lock);

  /// Destructor.
  ~Guard (void);

private:
  Mutex & lock_;
};

/**
 * Template specalization for RW_Mutex
 * Unique features are:
 *  Similar to Mutex but has two locks (Read/Write)
 *  Release removes both locks
 */
template <>
class Guard <RW_Mutex>
{
public:
  enum Lock_Type {READ, WRITE};

  /**
   * Locking constructor
   *
   * @param[in]     type      The type of lock to acquire
   */
  Guard (RW_Mutex & lock, Lock_Type type);

  /// Destructor.
  ~Guard (void);

private:
  RW_Mutex & lock_;
};

/**
 * @class Client_Guard
 *
 * Special implementation of a guard type for the Pin client. When the
 * guard is instantiated, it will lock the client. When the guard is 
 * destroyed, it will unlock the client. This helps simply code since the
 * client will automatically be unlockd regardless of how the control returns
 * to the caller.
 */
class Client_Guard
{
public:
  /// Default constructor.
  Client_Guard (void);
  
  /// Destructor.
  ~Client_Guard (void);
};
  
} // namespace OASIS
} // namespace Pin

#include "Guard.inl"

#endif  // _OASIS_PIN_GUARD_H_
