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
  PIN_RWMutexFini (&this->mutex_);
}

//
// acquire_read
//
inline
void RWMutex::acquire_read (void)
{
  PIN_RWMutexReadLock (&this->mutex_);
  this->read_lock_ = true;
}

//
// acquire_write
//
inline
void RWMutex::acquire_write (void)
{
  PIN_RWMutexWriteLock (&this->mutex_);
  this->write_lock_ = true;
}


//
// try_acquire_read
//
inline
bool RWMutex::try_acquire_read (void)
{
  this->read_lock_ = PIN_RWMutexTryReadLock (&this->mutex_);
  return this->read_lock_;
}

//
// try_acquire_write
//
inline
bool RWMutex::try_acquire_write (void)
{
  this->write_lock_ = PIN_RWMutexTryWriteLock (&this->mutex_);
  return this->write_lock_;
}


//
// release
//
inline
void RWMutex::release (void)
{
  PIN_RWMutexUnlock (&this->mutex_);
  this->write_lock_ = false;
  this->read_lock_ = false;
}

//
// locked_read
//
inline
bool RWMutex::locked_read (void)
{
  return this->read_lock_;
}

//
// locked_write
//
inline
bool RWMutex::locked_write (void)
{
  return this->write_lock_;
}

} // namespace OASIS
} // namespace Pin
