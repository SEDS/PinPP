// -*- C++ -*-
// $Id: RWMutex.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// RWMutex
//
inline
RWMutex::RWMutex (void)
{
  PIN_RWMutexInit (&this->mutex_);
}

//
// ~RWMutex
//
inline
RWMutex::~RWMutex (void)
{
  PIN_RWMutexFini (&this->mutex);
}

//
// read_lock
//
inline
void RWMutex::read_lock (void)
{
  PIN_RWMutexReadLock (&this->mutex_);
}

//
// write_lock
//
inline
void RWMutex::write_lock (void)
{
  PIN_RWMutexWriteLock (&this->mutex_);
}


//
// try_read_lock
//
inline
void RWMutex::try_read_lock (void)
{
  return PIN_RWMutexTryReadLock (&this->mutex_);
}

//
// try_write_lock
//
inline
void RWMutex::try_write_lock (void)
{
  return PIN_RWMutexTryWriteLock (&this->mutex_);
}


//
// unlock
//
inline
void RWMutex::unlock (void)
{
  PIN_RWMutexUnlock (&this->mutex_);
}

} // namespace OASIS
} // namespace Pin
