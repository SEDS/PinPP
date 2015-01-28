// -*- C++ -*-

//==============================================================================
/**
 *  @file        RW_Mutex.h
 *
 *  $Id: RW_Mutex.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_RW_MUTEX_H_
#define _OASIS_PIN_RW_MUTEX_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class RW_Mutex
 *
 * Wrapper class for PIN_RW_MUTEX.  Should be used with the GUARD class for
 * GetRW_Mutex and ReleaseRW_Mutex calls.
 */
class RW_Mutex
{
public:
  /// Default constructor.
  RW_Mutex (void);

  /// Destructor.
  ~RW_Mutex (void);

  /// Lock the mutex for reading (blocking).
  void acquire_read (void);

  /// Lock the mutex for writing (blocking).
  void acquire_write (void);

  /// Lock the mutex for reading (non-blocking).
  bool try_acquire_read (void);

  /// Lock the mutex for writing (non-blocking).
  bool try_acquire_write (void);

  /// Unlock the mutex.
  void release (void);

  /// Check if it is read locked
  bool is_locked_read (void);

  /// Check if it is write locked
  bool is_locked_write (void);

private:
  bool read_lock_;

  bool write_lock_;
  
  PIN_RWMUTEX mutex_;
};

} // namespace OASIS
} // namespace Pin

#include "RW_Mutex.inl"

#endif  // _OASIS_PIN_RW_MUTEX_H_
