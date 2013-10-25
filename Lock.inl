// -*- C++ -*-
// $Id: Lock.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Lock::Lock (void)
{
  #if (PIN_PRODUCT_VERSION_MAJOR == 2) and (PIN_PRODUCT_VERSION_MINOR < 13)
    InitLock (&this->lock_);
  #else
    PIN_InitLock (&this->lock_);
  #endif
}

inline
Lock::~Lock (void)
{

}

inline
void Lock::acquire (int owner)
{
  #if (PIN_PRODUCT_VERSION_MAJOR == 2) and (PIN_PRODUCT_VERSION_MINOR < 13)
    GetLock (&this->lock_, owner);
  #else
    PIN_GetLock (&this->lock_, owner);
  #endif
}

inline
void Lock::release (void)
{
  #if (PIN_PRODUCT_VERSION_MAJOR == 2) and (PIN_PRODUCT_VERSION_MINOR < 13)
    ReleaseLock (&this->lock_);
  #else
    PIN_ReleaseLock (&this->lock_);
  #endif
}

} // namespace OASIS
} // namespace Pin
