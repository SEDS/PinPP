// -*- C++ -*-
// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace OASIS
{
namespace Pin
{

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (void)
: wrapper_ (curr_)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const T & t)
: curr_ (t),
  wrapper_ (curr_)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const pin_type & t)
: curr_ (t),
  wrapper_ (curr_)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const Iterator & t)
: curr_ (t.curr_),
  wrapper_ (curr_)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::~Iterator (void)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
const Iterator<T, PREV, NEXT> & Iterator <T, PREV, NEXT>::operator = (const Iterator & rhs)
{
  this->curr_ = rhs.curr_;
  return *this;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
T & Iterator <T, PREV, NEXT>::operator * (void)
{
  return this->wrapper_;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
T * Iterator <T, PREV, NEXT>::operator -> (void)
{
  return &this->wrapper_;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT> Iterator <T, PREV, NEXT>::make_end (void) const
{
  return Iterator (T::invalid);
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT> & Iterator <T, PREV, NEXT>::operator -- (void)
{
  this->curr_ = PREV (this->curr_);
  return *this;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT> & Iterator <T, PREV, NEXT>::operator ++ (void)
{
  this->curr_ = NEXT (this->curr_);
  return *this;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
bool Iterator <T, PREV, NEXT>::operator == (const Iterator & rhs) const
{
  return this->curr_ == rhs.curr_;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
bool Iterator <T, PREV, NEXT>::operator != (const Iterator & rhs) const
{
  return this->curr_ != rhs.curr_;
}

} // namespace OASIS
} // namespace Pin
