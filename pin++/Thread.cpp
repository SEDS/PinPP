#include "Thread.h"
#include "Guard.h"

#include <iostream>

namespace OASIS
{
namespace Pin
{

TLS <Thread> Thread::current_ (&Thread::__tls_cleanup);
  
VOID Thread::__tls_cleanup (VOID * arg)
{
  Thread * thr = reinterpret_cast <Thread *> (arg);
  
  // TODO If we start experiencing runtime error where, we may have to
  // implement a destroy () method on the Thread to call delete.
  if (0 != thr && thr->auto_destroy_)
    delete thr;
}
  
THREADID Thread::id (void)
{
  Read_Guard <RW_Mutex> guard (this->rw_mutex_);
  return this->thr_id_;
}

PIN_THREAD_UID Thread::uid (void)
{
  Read_Guard <RW_Mutex> guard (this->rw_mutex_);
  return this->thr_uid_;
}

OS_THREAD_ID Thread::os_id (void)
{
  Read_Guard <RW_Mutex> guard (this->rw_mutex_);
  return this->os_thr_id_;
}

OS_THREAD_ID Thread::parent_id (void)
{
  Read_Guard <RW_Mutex> guard (this->rw_mutex_);
  return this->parent_os_thr_id_;
}
  
Thread * Thread::current (void)
{
  // Get the current thread in TLS, and return if exists.
  THREADID thr_id = PIN_ThreadId ();
  Thread * thr = Thread::current_.get (thr_id);
  
  if (0 != thr)
    return thr;
  
  // This could be the main thread, which does not have an Thread object
  // in the TLS. So, create a new thread, and store it.
  thr = new Thread (thr_id,
                    PIN_GetTid (),
                    PIN_ThreadUid (),
                    PIN_GetParentTid ());
  
  Thread::current_.set (thr_id, thr);
  return thr;
}

Thread::State Thread::start (size_t stack_size)
{
  // Prevent multiple threads from calling this routine at the same
  // time and causing a race condition.
  Write_Guard <RW_Mutex> guard (this->rw_mutex_);

  // Make sure the thread is not already started.
  if (this->state_ == STARTED || this->state_ == RUNNING)
    return this->state_;
  
  // We can start the thread.
  this->thr_id_ = PIN_SpawnInternalThread (&Thread::__thr_run, this, stack_size, &this->thr_uid_);
  this->state_ = this->thr_id_ != INVALID_THREADID ? STARTED : ERROR;
  
  return this->state_;
}

bool Thread::wait (UINT32 millis, INT32 * exit_code)
{
  // Ideally, we would like to put a read guard here while we are "reading"
  // the thread uid. Unfortunately, using a read guard here results in the
  // program hanging if the wait() method is called in fini unlocked by a
  // tool (the most logical place to call this method).
  Read_Guard <RW_Mutex> guard (this->rw_mutex_);

  if (this->thr_uid_ == INVALID_PIN_THREAD_UID)
    return true;

  return PIN_WaitForThreadTermination (this->thr_uid_, millis, exit_code);
}

VOID Thread::__thr_run (VOID * arg)
{
  // Get the thread object, and update its remaining attributes.
  Thread * thr = reinterpret_cast <Thread *> (arg);
  
  // Set the current thread to the Thread object. This allows the
  // client to access the Thread object via the current () method.
  Thread::current_.set (thr->thr_id_, thr);
  
  do
  {
    Write_Guard <RW_Mutex> guard (thr->rw_mutex_);
    thr->os_thr_id_ = PIN_GetTid ();
    thr->parent_os_thr_id_ = PIN_GetParentTid ();
    
    // Set the state to running.
    thr->state_ = RUNNING;
  } while (0);

  // Determine what run method we should invoke. Either we invoke the run()
  // method on the runnable_ object contained in the thread, or we invoke
  // the run() method on the thread. The runnable_ variable takes precedence
  // over the run() method on the Thread.
  Runnable * runnable = thr->runnable_;

  if (0 == runnable)
    runnable = thr;

  runnable->run ();

  do
  {
    // Reset the thread state.
    Write_Guard <RW_Mutex> guard (thr->rw_mutex_);
    thr->state_ = TERMINATED;
  } while (0);
}

}
}
