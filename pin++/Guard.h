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
class Guard
{
public:
  /**
   * Initializing constructor. The lock is acquired by the Guard during
   * the construction process.
   *
   * @param[in]     lock      Target lock
   */
  Guard (T & lock);
  
  /**
   * Destructor. The lock is released when the Guard is destroyed.
   */
  ~Guard (void);

private:
  /// The lock managed by the guard.
  T & lock_;
};

/**
 * @class Guard <Lock>
 * 
 * Template specialization of the Guard for a Lock. This version of the 
 * Guard behaves the same as the generic Guard class. The main difference
 * with this version is that it passes the current thread id to the acquire()
 * method on the Lock. This helps with debugging.
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
  Guard (Lock & lock);

  /// Destructor.
  ~Guard (void);

private:
  Lock & lock_;
};

/** 
 * @class Read_Guard
 * 
 * A guard that acquires a read lock from the locking object. The Read_Guard
 * expects the locking object to define the following methods:
 *
 *  # acquire_read (void);
 *  # release (void);
 */
template <typename T>
class Read_Guard
{
public:
  /**
   * Locking constructor
   *
   * @param[in]     type      The read lock to acquire
   */
  Read_Guard (T & lock);

  /// Destructor
  ~Read_Guard (void);

private:
  /// Reference to the lock managed by the guard.
  T & lock_;
};

/** 
 * @class Write_Guard
 * 
 * A guard that acquires a write lock from the locking object. The Write_Guard
 * expects the locking object to define the following methods:
 *
 *  # acquire_write (void);
 *  # release (void);
 */
template <typename T>
class Write_Guard
{
public:
  /**
   * Locking constructor
   *
   * @param[in]     type      The write lock to acquire
   */
  Write_Guard (T & lock);

  /// Destructor
  ~Write_Guard (void);

private:
  /// Reference to the lock managed by the guard.
  T & lock_;
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
