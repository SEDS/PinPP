// -*- C++ -*-

//==============================================================================
/**
 *  @file        Inline_Thread_T.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_INLINE_THREAD_T_H_
#define _OASIS_PIN_INLINE_THREAD_T_H_

#include "Thread.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Inline_Thread_T
 *
 * Special implementation of the Thread class that allows clients to create 
 * Runnable objects for a thread using C++11 function objects. The advantage
 * of this approach is that you do not have to create a separate class to 
 * pass parameters to the Thread. Instead, you can bind to objects (or values)
 * from the parameters captured when the thread is created. The key, however,
 * is the capture objects have to live longer than the thread.
 *
 * The Inline_Thread_T class is extremely useful when creating one of more
 * type-specific threads in the constructor of the Tool.
 */
template <typename F>
class Inline_Thread_T : public Thread
{
public:
  /// Default constructor.
  Inline_Thread_T (F func)
  : func_ (func) { }

  /// Destructor.
  virtual ~Inline_Thread_T (void) { }
  
  /// Run the thread, but prevent subclass from override the behavior.
  void run (void)
  {
    this->func_ ();
  }
  
private:
  F func_;
};

/**
 * Factory function for creating a new inline thread.
 *
 * @param[in]       func      Function object for the Thread.
 */
template <typename F>
Inline_Thread_T <F> * make_inline_thread (F func)
{
  return new Inline_Thread_T <F> (func);
}
  
} // namespace OASIS
} // namespace Pin

#endif  // _OASIS_PIN_INLINE_THREAD_T_H_
