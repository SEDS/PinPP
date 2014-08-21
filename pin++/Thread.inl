namespace OASIS
{
namespace Pin
{

inline
Thread::Thread (void)
{

}

inline
Thread::~Thread (void)
{

}

inline
THREADID Thread::id (void)
{
  return PIN_ThreadId ();
}

inline
PIN_THREAD_UID Thread::uid (void)
{
  return PIN_ThreadUid ();
}

inline
OS_THREAD_ID Thread::parent_id (void)
{
  return PIN_GetParentTid ();
}

inline
void Thread::sleep (UINT32 milliseconds)
{
  PIN_Sleep (milliseconds);
}

inline
void Thread::yield (void)
{
  PIN_Yield ();
}

inline
void Thread::terminate (INT32 exitCode)
{
  return PIN_ExitThread (exitCode);
}

inline
bool Thread::is_application_thread (void)
{
  return PIN_IsApplicationThread ();
}

inline
bool Thread::wait (const PIN_THREAD_UID &threadUid, UINT32 milliseconds, INT32 *pExitCode)
{
  return PIN_WaitForThreadTermination (threadUid, milliseconds, pExitCode);
}

} // namespace OASIS
} // namespace Pin
