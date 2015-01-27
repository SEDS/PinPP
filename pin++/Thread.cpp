#include "Thread.h"
#include "Guard.h"

namespace OASIS
{
namespace Pin
{

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

void Thread::start (size_t stack_size)
{
  // Prevent multiple threads from calling this routine at the same
  // time and causing a race condition.
  Write_Guard <RW_Mutex> guard (this->rw_mutex_);

  // Make sure the thread is not already started.
  if (this->thr_id_ != INVALID_THREADID)
    throw Already_Started ();

  // We can start the thread.
  this->thr_id_ = PIN_SpawnInternalThread (&Thread::__thr_run, this, stack_size, &this->thr_uid_);

  if (this->thr_id_ == INVALID_THREADID)
    throw Cannot_Start ();
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

  do
  {
    Write_Guard <RW_Mutex> guard (thr->rw_mutex_);
    thr->os_thr_id_ = PIN_GetTid ();
    thr->parent_os_thr_id_ = PIN_GetParentTid ();
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
    // Reset the thread id since everything is complete. This allows the
    // client to call the start () method again on the thread. Make sure
    // we get a guard to the mutex since we are updating attributes that
    // are set in the start() method.
    Write_Guard <RW_Mutex> guard (thr->rw_mutex_);

    thr->thr_id_ = INVALID_THREADID;
    thr->thr_uid_ = INVALID_PIN_THREAD_UID;
    thr->os_thr_id_ = INVALID_OS_THREAD_ID;
    thr->parent_os_thr_id_ = INVALID_OS_THREAD_ID;
  } while (0);
}

const Thread & Thread::operator = (const Thread & rhs)
{
  this->thr_id_ = rhs.thr_id_;
  this->os_thr_id_ = rhs.os_thr_id_;
  this->thr_uid_ = rhs.thr_uid_;
  this->parent_os_thr_id_ = rhs.parent_os_thr_id_;
  this->runnable_ = rhs.runnable_;

  return *this;
}

}
}
