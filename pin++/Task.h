#ifndef _OASIS_PIN_TASK_H_
#define _OASIS_PIN_TASK_H_

#include "pin.H"
#include "Thread.h"
#include "Guard.h"
#include "RW_Mutex.h"
#include <list>

namespace OASIS
{
namespace Pin
{

template <typename T>
class Task
{
public:
	typedef T type;

	/// Default constructor.
	Task (void);

	/// Destructor.
	~Task (void);

	/**
	 * Create a new tool internal thread in the current process.
	 *
	 * @param[out]      thr_id        The id of the thread created.
	 */
	THREADID run (PIN_THREAD_UID *thr_id = 0);

	/**
	 * Wait until all threads created using a task have terminated.
	 * 
	 * @param[in]       timeout        The maximum amout of time, in milliseconds, to wait for any one thread to terminate.
	 * @return  TRUE if all threads terminated, FALSE if the timeout time elapsed.
	 */
	bool wait (UINT32 timeout = PIN_INFINITE_TIMEOUT);

	/// Get a list of the unique thread IDs of all currently running threads created using a task
	const std::list <PIN_THREAD_UID> & threads (void) const;

private:
	/// PIN thread hook
	static void __run_svc (void * arg);

	/// A list of the IDs of all currently running threads created using a task
	static std::list <PIN_THREAD_UID> ids_;

	/// Controls access to ids_
	static RW_Mutex lock_;
};

// definition of ids_
template <typename T>
std::list <PIN_THREAD_UID> Task <T>::ids_;

// definition of lock_
template <typename T>
RW_Mutex Task <T>::lock_;

} // namespace OASIS
} // namespace Pin

#include "Task.inl"
#include "Task.cpp"

#endif // _OASIS_PIN_TASK_H_
