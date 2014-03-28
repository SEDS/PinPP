namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Copy <T>::Copy (void)
{

}

template <typename T>
inline
Copy <T>::Copy (const VOID * src)
{
  this->perform_copy (src);
}

template <typename T>
inline
void Copy <T>::operator = (const VOID * src)
{

}
  
template <typename T>
inline
Copy <T>::operator const T & () const
{
  return this->value_;
}

template <typename T>
inline
void Copy <T>::perform_copy (const VOID * src)
{
  PIN_SafeCopy (&this->value_, static_cast <T *> (src), sizeof (T));
}

}
}
