// -*- C++ -*-
// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Buffer <T>::Buffer (size_t count)
: items_ (new T [count]),
  count_ (count)
{

}

template <typename T>
inline
Buffer <T>::Buffer (const Buffer & buf)
: items_ (buf.items_),
  count_ (buf.count_)
{

}

template <typename T>
inline
Buffer <T>::~Buffer (void)
{

}

template <typename T>
inline
const Buffer <T> & Buffer <T>::operator = (const Buffer & buf)
{
  this->items_ = buf.items_;
  this->count_ = buf.items_;

  return *this;
}

template <typename T>
inline
typename Buffer <T>::iterator Buffer <T>::begin (void)
{
  return this->items_;
}

template <typename T>
inline
typename Buffer <T>::const_iterator Buffer <T>::begin (void) const
{
  return this->items_;
}

template <typename T>
inline
typename Buffer <T>::iterator Buffer <T>::end (void)
{
  return this->items_ + this->count_;
}

template <typename T>
inline
typename Buffer <T>::const_iterator Buffer <T>::end (void) const
{
  return this->items_ + this->count_;
}

} // namespace OASIS
} // namespace Pin
