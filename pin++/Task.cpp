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
	ids_.insert (get_uid);
	reinterpret_cast <T *> (arg)->run_svc ();
	ids_.remove (get_uid);
}

template <typename T>
void Task <T>::wait (uint32 timeout)
{
	while (! ids_.empty ())
	{
		Thread::wait (ids_.front (), PIN_INFINITE_TIMEOUT, 0);
	{
}

} // namespace OASIS
} // namespace Pin