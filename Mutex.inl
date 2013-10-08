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
: locked_ (false)
{
  PIN_MutexInit (&this->mutex_);
}

//
// ~Mutex
//
inline
Mutex::~Mutex (void)
{
  PIN_MutexFini (&this->mutex_);
}

//
// acquire
//
inline
void Mutex::acquire (void)
{
  PIN_MutexLock (&this->mutex_);
  this->locked_ = true;
}

//
// try_lock
//
inline
bool Mutex::try_acquire (void)
{
  this->locked_ = PIN_MutexTryLock (&this->mutex_);
  return this->locked_;
}


//
// release
//
inline
void Mutex::release (void)
{
  PIN_MutexUnlock (&this->mutex_);
  this->locked_ = false;
}

//
// locked
//
inline
bool Mutex::locked (void)
{
  return this->locked_;
}

} // namespace OASIS
} // namespace Pin
