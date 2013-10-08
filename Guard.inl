// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

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

} // namespace OASIS
} // namespace Pin
