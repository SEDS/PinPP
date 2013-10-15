// -*- C++ -*-
// $Id: Lock.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Lock::Lock (void)
{
  PIN_InitLock (&this->lock_);
}

inline
Lock::~Lock (void)
{

}

inline
void Lock::acquire (int owner)
{
  PIN_GetLock (&this->lock_, owner);
}

inline
void Lock::release (void)
{
  PIN_ReleaseLock (&this->lock_);
}

} // namespace OASIS
} // namespace Pin
