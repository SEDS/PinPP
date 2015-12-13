// -*- C++ -*-
// $Id: TLS.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
TLS <T>::TLS (DESTRUCTFUN destructor)
: key_ (PIN_CreateThreadDataKey (destructor))
{

}

template <typename T>
inline
TLS <T>::~TLS (void)
{
  PIN_DeleteThreadDataKey (this->key_);
}

template <typename T>
inline
T * TLS <T>::operator -> (void) const
{
  return this->get ();
}

template <typename T>
inline
T * TLS <T>::get (void) const
{
  return this->get (PIN_ThreadId ());
}


template <typename T>
inline
T * TLS <T>::get (THREADID thr_id) const
{
  return reinterpret_cast <T *> (PIN_GetThreadData (this->key_, thr_id));
}
  
template <typename T>
template <typename FACTORY>
inline
T * TLS <T>::get_with_create (FACTORY factory)
{
  return this->get (PIN_ThreadId (), factory);
}

template <typename T>
template <typename FACTORY>
inline
T * TLS <T>::get_with_create (THREADID thr_id, FACTORY factory)
{
  T * data = this->get (thr_id);
    
  if (0 != data)
    return data;
    
  // Create a new data object using the provided factory. Then, store
  // the data object for access later.
  data = factory ();
  this->set (thr_id, data);
    
  return data;
}

template <typename T>
inline
bool TLS <T>::is_set (void) const
{
  return this->is_set (PIN_ThreadId ());
}

template <typename T>
inline
bool TLS <T>::is_set (THREADID thr_id) const
{
  return 0 != PIN_GetThreadData (this->key_, thr_id);
}

template <typename T>
inline
void TLS <T>::set (T * data)
{
  this->set (PIN_ThreadId (), data);
}

template <typename T>
inline
void TLS <T>::set (THREADID thr_id, T * data)
{
  PIN_SetThreadData (this->key_, data, thr_id);
}

} // namespace OASIS
} // namespace Pin
