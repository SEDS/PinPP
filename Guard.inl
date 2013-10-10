// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Guard <Lock>::Guard (Lock & lock)
: lock_ (lock)
{

}

inline
Guard <Lock>::Guard (Lock & lock, int owner)
: lock_ (lock)
{
  this->acquire (owner);
}

inline
void Guard <Lock>::acquire (int owner)
{
  this->lock_.acquire (owner);
}

inline
void Guard <Lock>::release (void)
{
  this->lock_.release ();
}

inline
Guard <Mutex>::Guard (Mutex & lock)
: lock_ (lock)
{

}

inline
Guard <Mutex>::Guard (Mutex & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

inline
Guard <Mutex>::~Guard (void)
{
  this->lock_.release ();
}

inline
void Guard <Mutex>::acquire (void)
{
  this->lock_.acquire ();
}

inline
bool Guard <Mutex>::try_acquire (void)
{
  return this->lock_.try_acquire ();
}

inline
void Guard <Mutex>::release(void)
{
  this->lock_.release ();
}

inline
bool Guard <Mutex>::is_locked (void)
{
  return this->lock_.is_locked ();
}

inline
Guard <RW_Mutex>::Guard (RW_Mutex & lock)
: lock_ (lock)
{

}

inline
Guard <RW_Mutex>::Guard (RW_Mutex & lock, Lock_Type type, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire (type);
  else
    this->try_acquire (type);
}

inline
Guard <RW_Mutex>::~Guard (void)
{
  this->lock_.release ();
}

inline
void Guard <RW_Mutex>::acquire (Lock_Type type)
{
  if (type == READ)
    this->lock_.acquire_read ();
  else
    this->lock_.acquire_write ();
}

inline
bool Guard <RW_Mutex>::try_acquire (Lock_Type type)
{
  if (type == READ)
    return this->lock_.try_acquire_read ();
  else
    return this->lock_.try_acquire_write ();
}

inline
void Guard <RW_Mutex>::release(void)
{
  this->lock_.release ();
}

inline
bool Guard <RW_Mutex>::is_locked (Lock_Type type)
{
  if (type == READ)
    return this->lock_.is_locked_read ();
  else
    return this->lock_.is_locked_write ();
}

} // namespace OASIS
} // namespace Pin
