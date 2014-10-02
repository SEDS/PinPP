namespace OASIS
{
namespace Pin
{

template <typename T>
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
    Write_Guard <RW_Mutex> guard (Task::lock_);
    Task::ids_.push_back (Thread::uid ());
  } while (false);

  reinterpret_cast <T *> (arg)->run_svc ();

  // remove the ID of this thread from the list
  do
  {
    Write_Guard <RW_Mutex> guard (Task::lock_);
    Task::ids_.remove (Thread::uid ());
  } while (false);
}

template <typename T>
bool Task <T>::wait (UINT32 timeout)
{
  while (! Task::ids_.empty ())
  {

    do
    {
      Read_Guard <RW_Mutex> guard (Task::lock_);

      if (! Task::ids_.empty ())
      {
        bool terminated = Thread::wait (Task::ids_.front (), timeout, 0);

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
