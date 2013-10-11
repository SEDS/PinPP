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
{
  PIN_InitLock (&this->lock_);
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
void Lock::acquire (int owner)
{
  PIN_GetLock (&this->lock_, owner);
}

//
// release
//
inline
void Lock::release (void)
{
  PIN_ReleaseLock (&this->lock_);
}

} // namespace OASIS
} // namespace Pin
