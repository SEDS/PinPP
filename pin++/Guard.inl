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

inline 
Guard <Lock>::~Guard (void)
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
Guard <RW_Mutex>::Guard (RW_Mutex & lock)
: lock_ (lock)
{

}

inline
Read_Guard <RW_Mutex>::Read_Guard (RW_Mutex & lock)
: Guard (lock)
{
  this->lock_.acquire_read ();
}

inline
Read_Guard <RW_Mutex>::~Read_Guard (void)
{

}

inline
Write_Guard <RW_Mutex>::Write_Guard (RW_Mutex & lock)
: Guard (lock)
{
  this->lock_.acquire_write ();
}

inline
Write_Guard <RW_Mutex>::~Write_Guard (void)
{

}

inline
Guard <RW_Mutex>::~Guard (void)
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
 
