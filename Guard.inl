// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Guard <Lock>::Guard (Lock & lock, int owner)
: lock_ (lock)
{
  this->lock_.acquire (owner);
}

inline Guard <Lock>::~Guard (void)
{
  this->lock_.release ();
}

inline
Guard <Mutex>::Guard (Mutex & lock)
: lock_ (lock)
{
  this->lock_.acquire ();
}

inline
Guard <Mutex>::~Guard (void)
{
  this->lock_.release ();
}

inline
Guard <RW_Mutex>::Guard (RW_Mutex & lock, Lock_Type type)
: lock_ (lock)
{
  if (type == READ)
    this->lock_.acquire_read ();
  else
    this->lock_.acquire_write ();
}

inline
Guard <RW_Mutex>::~Guard (void)
{
  this->lock_.release ();
}

} // namespace OASIS
} // namespace Pin
