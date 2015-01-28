// -*- C++ -*-

//==============================================================================
/**
 *  @file        Runnable.h
 *
 *  $Id: Semaphore.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PINPP_RUNNABLE_H_
#define _OASIS_PINPP_RUNNABLE_H_

namespace OASIS
{
namespace Pin
{
/**
 * @class Runnable
 *
 * Interface for any object that is Runnable. This interface is based
 * on the Runnable interface in Java.
 */
class Runnable
{
public:
  virtual void run (void) = 0;
};

}
}

#endif  // !defined _OASIS_PINPP_RUNNABLE_H_
