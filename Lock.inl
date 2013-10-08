// -*- C++ -*-
// $Id: Lock.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Lock::Lock (void)
: owner_ (0),
  locked_ (false)
{
  InitLock (&this->lock_);
}

inline
Lock::Lock (int owner)
: owner_ (owner),
  locked_ (false)
{
  InitLock (&this->lock_);
}

inline
Lock::~Lock (void)
{

}

inline
void Lock::acquire (void)
{
  GetLock (&this->lock_, this->owner_);
  this->locked_ = true;
}

inline
bool Lock::try_acquire (void)
{
  // There isn't a non-blocking way to acquire the lock
  this->acquire ();
  return true;
}

inline
void Lock::release (void)
{
  ReleaseLock (&this->lock_);
  this->locked_ = false;
}

inline
bool Lock::locked (void)
{
  return this->locked_;
}

inline
void Lock::owner (int owner)
{
  this->owner_ = owner;
}

inline
int Lock::owner (void)
{
  return this->owner_;
}

} // namespace OASIS
} // namespace Pin
