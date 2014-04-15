namespace OASIS
{
namespace Pin
{

template <typename T>
inline
THREADID Task <T>::run (PIN_THREAD_UID *threadUid)
{
	return PIN_SpawnInternalThread (&Task::__run_svc, this, 0, threadUid);
}

template <typename T>
void Task <T>::__run_svc (void * arg)
{
	// add the ID of this thread to the list
	do
	{
		Guard <RW_Mutex> guard (&lock_, WRITE);
		this->ids_.insert (get_uid);
	} while (false);

	reinterpret_cast <T *> (arg)->run_svc ();

	// remove the ID of this thread from the list
	do
	{
		Guard <RW_Mutex> guard (&lock_, WRITE);
		this->ids_.remove (get_uid);
	} while (false);
}

template <typename T>
bool Task <T>::wait (UINT32 timeout)
{
	while (! this->ids_.empty ())
	{

		do
		{
			Guard <RW_Mutex> guard (&lock_, READ);

			if (! this->ids_.empty ())
			{
				bool terminated = Thread::wait (this->ids_.front (), timeout, 0);

				// if the timeout time elapsed
				if (terminated == false && timeout != PIN_INFINITE_TIMEOUT)
					return false;

			}
		} while (false);

	}
	return true;
}

} // namespace OASIS
} // namespace Pin
