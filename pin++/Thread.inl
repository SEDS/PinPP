// -*- C++ -*-

#include "Guard.h"

namespace OASIS
{
namespace Pin
{

inline
Thread::Thread (void)
: thr_id_ (INVALID_THREADID),
  os_thr_id_ (INVALID_OS_THREAD_ID),
  thr_uid_ (INVALID_PIN_THREAD_UID),
  parent_os_thr_id_ (INVALID_OS_THREAD_ID),
  runnable_ (0),
  state_ (NEW),
  auto_destroy_ (false)
{

}

inline
Thread::Thread (Runnable * runnable)
: thr_id_ (INVALID_THREADID),
  os_thr_id_ (INVALID_OS_THREAD_ID),
  thr_uid_ (INVALID_PIN_THREAD_UID),
  parent_os_thr_id_ (INVALID_OS_THREAD_ID),
  runnable_ (runnable),
  state_ (NEW),
  auto_destroy_ (false)
{

}

inline
Thread::Thread (THREADID thr_id,
                OS_THREAD_ID os_thr_id,
                PIN_THREAD_UID thr_uid,
                OS_THREAD_ID parent_os_thr_id)
: thr_id_ (thr_id),
  os_thr_id_ (os_thr_id),
  thr_uid_ (thr_uid),
  parent_os_thr_id_ (parent_os_thr_id),
  runnable_ (0),
  state_ (RUNNING),
  auto_destroy_ (true)
{

}
  
inline
Thread::~Thread (void)
{

}

inline
void Thread::sleep (UINT32 millis)
{
  PIN_Sleep (millis);
}

inline
void Thread::yield (void)
{
  PIN_Yield ();
}

inline
void Thread::terminate (INT32 exit_code)
{
  return PIN_ExitThread (exit_code);
}

inline
bool Thread::is_application_thread (void)
{
  return PIN_IsApplicationThread ();
}

inline
void Thread::run (void)
{

}

inline
Thread::State Thread::state (void) const
{
  return this->state_;
}
  
} // namespace OASIS
} // namespace Pin
