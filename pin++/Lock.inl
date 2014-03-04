// -*- C++ -*-
// $Id: Lock.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Lock::Lock (void)
{
#if (PIN_BUILD_NUMBER < 61206)
  InitLock (&this->lock_);
#else
  PIN_InitLock (&this->lock_);
#endif
}

inline
Lock::Lock (const Lock & lock)
: lock_ (lock.lock_)
{

}

inline
Lock::~Lock (void)
{

}

inline
const Lock & Lock::operator = (const Lock & lock)
{
  this->lock_ = lock.lock_;
  return *this;
}

inline
void Lock::acquire (int owner)
{
#if (PIN_BUILD_NUMBER < 61206)
  GetLock (&this->lock_, owner);
#else
  PIN_GetLock (&this->lock_, owner);
#endif
}

inline
void Lock::release (void)
{
#if (PIN_BUILD_NUMBER < 61206)
  ReleaseLock (&this->lock_);
#else
  PIN_ReleaseLock (&this->lock_);
#endif
}

} // namespace OASIS
} // namespace Pin
