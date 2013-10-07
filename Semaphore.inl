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
// is_set
//
inline
bool Semaphore::is_set (void)
{
  return PIN_SemaphoreIsSet (&this->semaphore_);
}

//
// set
//
inline
void Semaphore::set (void)
{
  PIN_SemaphoreSet (&this->semaphore_);
}

//
// clear
//
inline
void Semaphore::clear (void)
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
