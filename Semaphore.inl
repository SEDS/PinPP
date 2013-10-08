// -*- C++ -*-
// $Id: Semaphore.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Semaphore
//
inline
Semaphore::Semaphore (void)
{
  PIN_SemaphoreInit (&this->semaphore_);
}

//
// ~Semaphore
//
inline
Semaphore::~Semaphore (void)
{
  PIN_SemaphoreFini (&this->semaphore_);
}

//
// locked
//
inline
bool Semaphore::locked (void)
{
  return PIN_SemaphoreIsSet (&this->semaphore_);
}

//
// acquire
//
inline
void Semaphore::acquire (void)
{
  PIN_SemaphoreSet (&this->semaphore_);
}

//
// release
//
inline
void Semaphore::release (void)
{
  PIN_SemaphoreClear (&this->semaphore_);
}

//
// wait
//
inline
void Semaphore::wait (void)
{
  PIN_SemaphoreWait (&this->semaphore_);
}

//
// wait
//
inline
void Semaphore::wait (unsigned timeout)
{
  PIN_SemaphoreTimedWait (&this->semaphore_, timeout);
}

} // namespace OASIS
} // namespace Pin
