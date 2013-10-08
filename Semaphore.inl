// -*- C++ -*-
// $Id: Semaphore.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Semaphore::Semaphore (void)
{
  PIN_SemaphoreInit (&this->semaphore_);
}

inline
Semaphore::~Semaphore (void)
{
  PIN_SemaphoreFini (&this->semaphore_);
}

inline
bool Semaphore::is_locked (void)
{
  return PIN_SemaphoreIsSet (&this->semaphore_);
}

inline
void Semaphore::set (void)
{
  PIN_SemaphoreSet (&this->semaphore_);
}

inline
void Semaphore::release (void)
{
  PIN_SemaphoreClear (&this->semaphore_);
}

inline
void Semaphore::acquire (void)
{
  PIN_SemaphoreWait (&this->semaphore_);
}

inline
bool Semaphore::try_acquire (void)
{
  // Semantically, this would be a wait with timeout
  // of 0, so just return the locked status.
  return this->locked ();
}

inline
void Semaphore::wait (unsigned timeout)
{
  PIN_SemaphoreTimedWait (&this->semaphore_, timeout);
}

} // namespace OASIS
} // namespace Pin
