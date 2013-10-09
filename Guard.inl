// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Guard <T>::Guard (T & lock)
: lock_ (lock)
{

}

template <typename T>
inline
Guard <T>::Guard (T & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

template <typename T>
inline
Guard <T>::~Guard (void)
{
  this->lock_.release ();
}

template <typename T>
inline
void Guard <T>::acquire(void)
{
  this->lock_.acquire ();
}

template <typename T>
inline
void Guard <T>::release(void)
{
  this->lock_.release ();
}

template <typename T>
inline
bool Guard <T>::is_locked (void)
{
  return this->lock_.is_locked ();
}

template <typename T>
inline
bool Guard <T>::try_acquire (void)
{
  return this->lock_.try_acquire ();
}

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
Read_Guard::Read_Guard (RW_Mutex & lock)
: lock_ (lock)
{

}

inline
Read_Guard::Read_Guard (RW_Mutex & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

inline
Read_Guard::~Read_Guard (void)
{
  this->lock_.release ();
}

inline
void Read_Guard::acquire(void)
{
  this->lock_.acquire_read ();
}

inline
void Read_Guard::release(void)
{
  this->lock_.release ();
}

inline
bool Read_Guard::is_locked (void)
{
  return this->lock_.locked_read ();
}

inline
bool Read_Guard::try_acquire (void)
{
  return this->lock_.try_acquire_read ();
}

inline
Write_Guard::Write_Guard (RW_Mutex & lock)
: lock_ (lock)
{

}

inline
Write_Guard::Write_Guard (RW_Mutex & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

inline
Write_Guard::~Write_Guard (void)
{
  this->lock_.release ();
}

inline
void Write_Guard::acquire (void)
{
  this->lock_.acquire_write ();
}

inline
void Write_Guard::release(void)
{
  this->lock_.release ();
}

inline
bool Write_Guard::is_locked (void)
{
  return this->lock_.locked_write ();
}

inline
bool Write_Guard::try_acquire (void)
{
  return this->lock_.try_acquire_write ();
}

} // namespace OASIS
} // namespace Pin
