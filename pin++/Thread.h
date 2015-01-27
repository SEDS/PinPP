// -*- C++ -*-

//==============================================================================
/**
 *  @file        Thread.h
 *
 *  $Id: Semaphore.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_THREAD_H_
#define _OASIS_PIN_THREAD_H_

#include "RW_Mutex.h"
#include "Runnable.h"

namespace OASIS
{
namespace Pin
{
/**
 * @class Thread
 *
 * Wrapper class that objectfies the Thread API in Pin. 
 *
 * Unlike the other classes in Pin++, the Thread class is allowed to use dynamic 
 * polymorphism instead of static polymorphism. This because we are not concerned
 * with the performance of dispatching indirect calls via the run() method since
 * it is not invoked frequently (only when a thread is started).
 *
 * The Thread class implements a copy constructor and assignment operator. This 
 * allows the Thread class to be used in STL container classes.
 */
class Thread : public Runnable
{
public:
  class Already_Started : public std::runtime_error  
  {
  public:
    Already_Started (void)
      : std::runtime_error ("Thread is already started") { }
  };

  class Cannot_Start : public std::runtime_error
  {
  public:
    Cannot_Start (void)
      : std::runtime_error ("Cannot start thread") { }
  };

  /// Default constructor.
  Thread (void);

  /**
   * Copy constuctor.
   *
   * @param[in]       thr       Source thread to copy.
   */
  Thread (const Thread & thr);

  /**
   * Initializing 
   */
  Thread (Runnable * runnable);

private:
  /**
   * Initializing constructor. This constructor can only be called by
   * the Thread class. It is mainly used by the current() method.
   */
  Thread (THREADID thr_id, 
          OS_THREAD_ID os_thr_id,
          PIN_THREAD_UID thr_uid,
          OS_THREAD_ID parent_os_thr_id);

public:
  /// Get the current thread.
  static Thread current (void);

  /// Destructor
  virtual ~Thread (void);

  /// Get identifier of the current thread in Pin. 
  THREADID id (void);

  /// Get unique identifier of the current thread in Pin. 
  PIN_THREAD_UID uid (void);

  /// Get the OS assigned thread id.
  OS_THREAD_ID os_id (void);

  /// Get system identifier of the parent thread, if known. 
  OS_THREAD_ID parent_id (void);

  /**
   * Delay execution of the current thread for the specified time 
   * interval. 
   *
   * @param[in]       millis      Number of milliseconds to sleep.
   */
  static void sleep (UINT32 millis);

  /// Yield the processor to another thread.
  static void yield (void);

  /// Check to see if the current thread is created by the application.
  static bool is_application_thread (void);

  /**
   * Start the thread. The caller can customize the size of the new thread's
   * stack. This, however, should be used only if you know what you are doing.
   * Otherwise, the thread has size of DEFAULT_THREAD_STACK_SIZE.
   *
   * If the thread is already started, then it throws the Already_Started 
   * exception. If the thread cannot be started, then it throws the Cannot_Start
   * exception.
   *
   *
   * @param[in]       stack_size        Size of the threads stack.
   */
  void start (size_t stack_size = DEFAULT_THREAD_STACK_SIZE);

  /**
   * Delay the current thread until the specified thread is terminated 
   * or the time-out interval elapses.
   */
  bool wait (UINT32 millis = PIN_INFINITE_TIMEOUT, INT32 * exit_code = 0);

  /**
   * The service method for the Thread. When a thread is started, this is
   * the main entry point for the spawned thread.
   */
  virtual void run (void);

  // Prevent the following operations
  const Thread & operator = (const Thread & rhs);

protected:
  /**
   * Terminate the current thread. This method can only be called by the original
   * thread that was created. For this reason, this method is declared in the 
   * protected section. Otherwise, clients can mistakenly call the terminate()
   * method on the incorrect thread.
   *
   * @param[in]     exit_code       Exit code for the thread
   */
  void terminate (INT32 exit_code = 0);

private:
  /**
   * The main entry point for the spawned thread that in turn calls the run()
   * method on the Thread class.
   *
   * @param[in]     arg         Argument passed to the spawned thread
   */
  static VOID __thr_run (VOID * arg);

  /// Thread ID assigned by PIN.
  THREADID thr_id_;

  /// Thread ID assigned by OS.
  OS_THREAD_ID os_thr_id_;

  /// Unique thread ID which, unlike THREADID identifier, is not reused by 
  /// Pin after the thread termination. The uniqueness of this identifier 
  /// allows to use it in the PIN_WaitForThreadTermination() function which 
  /// monitors the thread's state.
  PIN_THREAD_UID thr_uid_;

  /// The OS id of the parent thread.
  OS_THREAD_ID parent_os_thr_id_;

  /// Mutex to prevent race condition when updating thread information.
  RW_Mutex rw_mutex_;

  /// The optional runnable object for the thread.
  Runnable * runnable_;
};

} // namespace OASIS
} // namespace Pin

#include "Thread.inl"

#endif  // _OASIS_PIN_THREAD_H_
