#ifndef _OASIS_PIN_THREAD_H_
#define _OASIS_PIN_THREAD_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Thread
 *
 * Wrapper class for Pin Thread functions
 */
class Thread
{
public:

	/// Destructor
	~Thread (void);

	/// Get identifier of the current thread in Pin. 
	static THREADID id (void);

	/// Get unique identifier of the current thread in Pin. 
	static PIN_THREAD_UID uid (void);

	/// Get system identifier of the parent thread, if known. 
	static OS_THREAD_ID parent_id (void);

	/// Delay execution of the current thread for the specified time interval. 
	static void sleep (UINT32 milliseconds);

	/// Yield the processor to another thread.
	static void yield (void);

	/// Terminate the current thread.
  static void terminate (INT32 exitCode);

	/// Check to see if the current thread is created by the application.
	static bool is_application_thread (void);

	/// Delay the current thread until the specified thread is terminated or the time-out interval elapses.
	static bool wait (const PIN_THREAD_UID &threadUid, UINT32 milliseconds, INT32 *pExitCode);

private:

	/// Private default constructor
	Thread (void);

};

} // namespace OASIS
} // namespace Pin

#include "Thread.inl"

#endif  // _OASIS_PIN_THREAD_H_
