#ifndef _OASIS_PIN_TASK_H_
#define _OASIS_PIN_TASK_H_

#include "pin.H"
#include "Thread.h"
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

	/// Default constructor
	Task (void);

	/// Destructor
	~Task (void);

	/**
	 * Create a new tool internal thread in the current process.
	 *
	 * @param[out]      thr_id        The id of the thread created
	 */
	THREADID run (PIN_THREAD_UID *thr_id = 0);

	/// Wait until all threads created by this task have terminated
	void wait (void);

	/// Get a list of the unique thread IDs of all currently running threads created by this task
	std::list<PIN_THREAD_UID> threads (void) const;

private:

	static void __run_svc (void * arg);

	std::list <PIN_THREAD_UID> ids_;
};

#include "Task.cpp"
#include "Task.inl"

} // namespace OASIS
} // namespace Pin


#endif // _OASIS_PIN_TASK_H_