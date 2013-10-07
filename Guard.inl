// -*- C++ -*-
// $Id: Guard.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Guard
//
inline
Guard::Guard (Lock & lock, int owner)
: lock_ (lock)
{
  this->lock_.acquire (owner);
}

//
// ~Guard
//
inline
Guard::~Guard (void)
{
  this->lock_.release ();
}

} // namespace OASIS
} // namespace Pin
