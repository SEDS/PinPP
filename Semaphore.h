// -*- C++ -*-

//==============================================================================
/**
 *  @file        Semaphore.h
 *
 *  $Id: Semaphore.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_SEMAPHORE_H_
#define _OASIS_PIN_SEMAPHORE_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Semaphore
 *
 * Wrapper class for PIN_SEMAPHORE.  Should be used with the GUARD class for
 * GetSemaphore and ReleaseSemaphore calls.
 */
class Semaphore
{
public:
  /// Default constructor.
  Semaphore (void);

  /// Destructor.
  ~Semaphore (void);

  /// Signal the lock
  void acquire (void);

  /// Test if the semaphore is set
  bool locked (void);

  /// Clear the lock
  void release (void);

  /// Block until the semaphore is set
  void wait (void);

  /*
   * Block until the semaphore is set or timeout is reached
   *
   * @param[in]       timeout       Timeout in ms
   */
  void wait (unsigned timeout);

private:
  PIN_SEMAPHORE semaphore_;
};

} // namespace OASIS
} // namespace Pin

#include "Semaphore.inl"

#endif  // _OASIS_PIN_SEMAPHORE_H_
