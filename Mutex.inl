// -*- C++ -*-
// $Id: Mutex.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Mutex
//
inline
Mutex::Mutex (void)
{
  PIN_MutexInit (&this->mutex_);
}

//
// ~Mutex
//
inline
Mutex::~Mutex (void)
{
  PIN_MutexFini (&this->mutex);
}

//
// lock
//
inline
void Mutex::lock (void)
{
  PIN_MutexLock (&this->mutex_);
}

//
// try_lock
//
inline
void Mutex::try_lock (void)
{
  return PIN_MutexTryLock (&this->mutex_);
}


//
// unlock
//
inline
void Mutex::unlock (void)
{
  PIN_MutexUnlock (&this->mutex_);
}

} // namespace OASIS
} // namespace Pin
