// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

#include "Thread.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Guard <T>::Guard (T & lock)
: lock_ (lock)
{
  this->lock_.acquire ();
}

template <typename T>
inline
Guard <T>::~Guard (void)
{
  this->lock_.release ();
}

inline
Guard <Lock>::Guard (Lock & lock)
: lock_ (lock)
{
  this->lock_.acquire (Thread::current ()->id ());
}

inline 
Guard <Lock>::~Guard (void)
{
  this->lock_.release ();
}

template <typename T>
inline
Read_Guard <T>::Read_Guard (T & lock)
: lock_ (lock)
{
  this->lock_.acquire_read ();
}

template <typename T>
inline
Read_Guard <T>::~Read_Guard (void)
{
  this->lock_.release ();
}

template <typename T>
inline
Write_Guard <T>::Write_Guard (T & lock)
: lock_ (lock)
{
  this->lock_.acquire_write ();
}

template <typename T>
inline
Write_Guard <T>::~Write_Guard (void)
{
  this->lock_.release ();
}

inline
Client_Guard::Client_Guard (void)
{
  PIN_LockClient ();
}

inline
Client_Guard::~Client_Guard (void)
{
  PIN_UnlockClient ();
}

} // namespace OASIS
} // namespace Pin
 
