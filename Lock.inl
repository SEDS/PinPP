// -*- C++ -*-
// $Id: Lock.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Lock
//
inline
Lock::Lock (void)
: owner_ (0),
  locked_ (false)
{
  InitLock (&this->lock_);
}

//
// Lock
//
inline
Lock::Lock (int owner)
: owner_ (owner),
  locked_ (false)
{
  InitLock (&this->lock_);
}

//
// ~Lock
//
inline
Lock::~Lock (void)
{

}

//
// acquire
//
inline
void Lock::acquire (void)
{
  GetLock (&this->lock_, this->owner_);
  this->locked_ = true;
}

//
// try_acquire
//
inline
bool Lock::try_acquire (void)
{
  // There isn't a non-blocking way to acquire the lock
  this->acquire ();
  return true;
}

//
// release
//
inline
void Lock::release (void)
{
  ReleaseLock (&this->lock_);
  this->locked_ = false;
}

//
// locked
//
inline
bool Lock::locked (void)
{
  return this->locked_;
}

//
// owner
//
inline
void Lock::owner (int owner)
{
  this->owner_ = owner;
}

//
// owner
//
inline
int Lock::owner (void)
{
  return this->owner_;
}

} // namespace OASIS
} // namespace Pin
