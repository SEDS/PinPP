// -*- C++ -*-
// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace OASIS
{
namespace Pin
{

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (void)
: wrapper_ (T::invalid)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const T & t)
: wrapper_ (t)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const pin_type & t)
: wrapper_ (t)
{

}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT>::Iterator (const Iterator & t)
: wrapper_ (t.wrapper_)
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
  this->wrapper_ = rhs.wrapper_;
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
  this->wrapper_ = PREV (this->wrapper_);
  return *this;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
Iterator <T, PREV, NEXT> & Iterator <T, PREV, NEXT>::operator ++ (void)
{
  this->wrapper_ = NEXT (this->wrapper_);
  return *this;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
bool Iterator <T, PREV, NEXT>::operator == (const Iterator & rhs) const
{
  return this->wrapper_ == rhs.wrapper_;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
inline
bool Iterator <T, PREV, NEXT>::operator != (const Iterator & rhs) const
{
  return this->wrapper_ != rhs.wrapper_;
}
  
  /////////////////////////////////////////////////////////////////////////////////////////////
  // Iterator2
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT>::Iterator2 (void)
  : curr_ (T::invalid),
    wrapper_ (curr_)
  {
    
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT>::Iterator2 (const T & t)
  : curr_ (t),
    wrapper_ (curr_)
  {
    
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT>::Iterator2 (const pin_type & t)
  : curr_ (t),
    wrapper_ (curr_)
  {
    
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT>::Iterator2 (const Iterator2 & t)
  : curr_ (t.curr_),
    wrapper_ (curr_)
  {
    
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT>::~Iterator2 (void)
  {
    
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  const Iterator2 <T, PREV, NEXT> & Iterator2 <T, PREV, NEXT>::operator = (const Iterator2 & rhs)
  {
    this->curr_ = rhs.curr_;
    return *this;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  T & Iterator2 <T, PREV, NEXT>::operator * (void)
  {
    return this->wrapper_;
  }

  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  T * Iterator2 <T, PREV, NEXT>::operator -> (void)
  {
    return &this->wrapper_;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT> Iterator2 <T, PREV, NEXT>::make_end (void) const
  {
    return Iterator2 (T::invalid);
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT> & Iterator2 <T, PREV, NEXT>::operator -- (void)
  {
    this->curr_ = PREV (this->curr_);
    return *this;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  Iterator2 <T, PREV, NEXT> & Iterator2 <T, PREV, NEXT>::operator ++ (void)
  {
    this->curr_ = NEXT (this->curr_);
    return *this;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  bool Iterator2 <T, PREV, NEXT>::operator == (const Iterator2 & rhs) const
  {
    return this->wrapper_ == rhs.wrapper_;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  inline
  bool Iterator2 <T, PREV, NEXT>::operator != (const Iterator2 & rhs) const
  {
    return this->wrapper_ != rhs.wrapper_;
  }
  
} // namespace OASIS
} // namespace Pin
