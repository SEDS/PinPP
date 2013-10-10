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
  /// Default constructor, do not acquire the lock.
  Guard (Lock & lock);

  /**
   * Locking constructor.
   *
   * @param[in]     owner       Owner of the lock
   */
  Guard (Lock & lock, int owner);

  /// Destructor.
  ~Guard (void);

  /**
   * Acquire the lock (blocking)
   *
   * @param[in]     owner       Owner of the lock
   */
  void acquire (int owner);

  /// Release the lock
  void release (void);

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
  /// Default constructor, do not acquire the lock.
  Guard (Mutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]     block     Block when acquiring the lock
   */
  Guard (Mutex & lock, bool block);

  /// Destructor.
  ~Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Is the mutex locked?
  bool is_locked (void);

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

  /// Default constructor, do not acquire the lock.
  Guard (RW_Mutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]     type      The type of lock to acquire
   * @param[in]     block     Block when acquiring the lock
   */
  Guard (RW_Mutex & lock, Lock_Type type, bool block);

  /// Destructor.
  ~Guard (void);

  /**  
   * Acquire the lock (blocking)
   *
   * @param[in]     type      The type of lock to acquire
   */
  void acquire (Lock_Type type);

  /**
   * Try to acquire the lock (non-blocking)
   *
   * @param[in]     type      The type of lock to acquire
   */
  bool try_acquire (Lock_Type type);

  /// Release the lock.  This releases both read and write locks
  void release (void);

  /**
   * Is the mutex locked?
   *
   * @param[in]     type      The type of lock to check
   */
  bool is_locked (Lock_Type type);

private:
  RW_Mutex & lock_;
};


/**
 * @class Read_Guard
 *
 * Guard for getting read locks from a RW_Mutex
 */
class Read_Guard
{
public:
  /// Default constructor, do not acquire the lock
  Read_Guard (RW_Mutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]   block     Block when acquiring the lock
   */
  Read_Guard (RW_Mutex & lock, bool block);

  /// Destructor.
  ~Read_Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Test if it is locked
  bool is_locked (void);

private:
  RW_Mutex & lock_;
};

/**
 * @class Write_Guard
 *
 * Guard for getting write locks from a RW_Mutex
 */
class Write_Guard 
{
public:
  /// Default constructor, do not acquire the lock
  Write_Guard (RW_Mutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]   block     Block when acquiring the lock
   */
  Write_Guard (RW_Mutex & lock, bool block);

  /// Destructor.
  ~Write_Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Test if it is locked
  bool is_locked (void);

private:
  RW_Mutex & lock_;
};

} // namespace OASIS
} // namespace Pin

#include "Guard.inl"

#endif  // _OASIS_PIN_GUARD_H_
