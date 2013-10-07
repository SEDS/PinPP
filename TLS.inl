// -*- C++ -*-
// $Id: TLS.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// TLS
//
template <typename T>
inline
TLS <T>::TLS (void)
{
  this->key_ = PIN_CreateThreadDataKey (0);
}

//
// ~TLS
//
template <typename T>
inline
TLS <T>::~TLS (void)
{
  PIN_DeleteThreadDataKey (this->key_);
}

//
// operator ->
//
template <typename T>
inline
T * TLS <T>::operator -> (void) const
{
  return reinterpret_cast <T *> (PIN_GetThreadData (this->key_));
}

//
// get
//
template <typename T>
inline
T * TLS <T>::get (THREADID thr_id) const
{
  return reinterpret_cast <T *> (PIN_GetThreadData (this->key_, thr_id));
}

//
// is_set
//
template <typename T>
inline
bool TLS <T>::is_set (void) const
{
  return 0 != PIN_GetThreadData (this->key_);
}

//
// set
//
template <typename T>
inline
void TLS <T>::set (T * data)
{
  PIN_SetThreadData (this->key_, data);
}

//
// set
//
template <typename T>
inline
void TLS <T>::set (THREADID thr_id, T * data)
{
  PIN_SetThreadData (this->key_, data, thr_id);
}

} // namespace OASIS
} // namespace Pin
