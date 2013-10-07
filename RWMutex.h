// -*- C++ -*-

//==============================================================================
/**
 *  @file        RWMutex.h
 *
 *  $Id: RWMutex.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_RWMUTEX_H_
#define _OASIS_PIN_RWMUTEX_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class RWMutex
 *
 * Wrapper class for PIN_RWMUTEX.  Should be used with the GUARD class for
 * GetRWMutex and ReleaseRWMutex calls.
 */
class RWMutex
{
public:
  /// Default constructor.
  RWMutex (void);

  /// Destructor.
  ~RWMutex (void);

  /// Lock the mutex for reading (blocking).
  void read_lock (void);

  /// Lock the mutex for writing (blocking).
  void write_lock (void);

  /// Lock the mutex for reading (non-blocking).
  bool try_read_lock (void);

  /// Lock the mutex for writing (non-blocking).
  bool try_write_lock (void);

  /// Unlock the mutex.
  void unlock (void);

private:
  PIN_RWMUTEX mutex_;
};

} // namespace OASIS
} // namespace Pin

#include "RWMutex.inl"

#endif  // _OASIS_PIN_RWMUTEX_H_
