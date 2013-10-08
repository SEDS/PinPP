// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

// /////////////////////////////////////////////////////////
// Guard
// /////////////////////////////////////////////////////////

//
// Guard
//
template <typename T>
inline
Guard <T>::Guard (T & lock)
: lock_ (lock)
{

}

//
// Guard
//
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

//
// ~Guard
//
template <typename T>
inline
Guard <T>::~Guard (void)
{
  this->lock_.release ();
}

//
// acquire
//
template <typename T>
inline
void Guard <T>::acquire(void)
{
  this->lock_.acquire ();
}

//
// release
//
template <typename T>
inline
void Guard <T>::release(void)
{
  this->lock_.release ();
}

//
// locked
//
template <typename T>
inline
bool Guard <T>::locked (void)
{
  return this->lock_.locked ();
}

//
// try_acquire
//
template <typename T>
inline
bool Guard <T>::try_acquire (void)
{
  return this->lock_.try_acquire ();
}

// /////////////////////////////////////////////////////////
// Read_Guard
// /////////////////////////////////////////////////////////

//
// Read_Guard
//
inline
Read_Guard::Read_Guard (RWMutex & lock)
: lock_ (lock)
{

}

//
// Read_Guard
//
inline
Read_Guard::Read_Guard (RWMutex & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

//
// ~Guard
//
inline
Read_Guard::~Read_Guard (void)
{
  this->lock_.release ();
}

//
// acquire
//
inline
void Read_Guard::acquire(void)
{
  this->lock_.acquire_read ();
}

//
// release
//
inline
void Read_Guard::release(void)
{
  this->lock_.release ();
}

//
// locked
//
inline
bool Read_Guard::locked (void)
{
  return this->lock_.locked_read ();
}

//
// try_acquire
//
inline
bool Read_Guard::try_acquire (void)
{
  return this->lock_.try_acquire_read ();
}

// /////////////////////////////////////////////////////////
// Write_Guard
// /////////////////////////////////////////////////////////

//
// Write_Guard
//
inline
Write_Guard::Write_Guard (RWMutex & lock)
: lock_ (lock)
{

}

//
// Write_Guard
//
inline
Write_Guard::Write_Guard (RWMutex & lock, bool block)
: lock_ (lock)
{
  if (block)
    this->acquire ();
  else
    this->try_acquire ();
}

//
// ~Write_Guard
//
inline
Write_Guard::~Write_Guard (void)
{
  this->lock_.release ();
}

//
// acquire
//
inline
void Write_Guard::acquire (void)
{
  this->lock_.acquire_write ();
}

//
// release
//
inline
void Write_Guard::release(void)
{
  this->lock_.release ();
}

//
// locked
//
inline
bool Write_Guard::locked (void)
{
  return this->lock_.locked_write ();
}

//
// try_acquire
//
inline
bool Write_Guard::try_acquire (void)
{
  return this->lock_.try_acquire_write ();
}

} // namespace OASIS
} // namespace Pin
