// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
namespace OASIS
{
namespace Pin
{

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
Iterator <T, PREV, NEXT> Iterator <T, PREV, NEXT>::operator -- (int)
{
  Iterator tmp (this->wrapper_);
  this->wrapper_ = PREV (this->wrapper_);

  return tmp;
}

template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
Iterator <T, PREV, NEXT> Iterator <T, PREV, NEXT>::operator ++ (int)
{
  Iterator tmp (this->wrapper_);
  this->wrapper_ = NEXT (this->wrapper_);

  return tmp;
}
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  Iterator2 <T, PREV, NEXT> Iterator2 <T, PREV, NEXT>::operator -- (int)
  {
    Iterator2 tmp (this->wrapper_);
    this->curr_ = PREV (this->curr_);
    
    return tmp;
  }
  
  template <typename T, typename T::pin_type (*PREV) (typename T::pin_type), typename T::pin_type (*NEXT) (typename T::pin_type)>
  Iterator2 <T, PREV, NEXT> Iterator2 <T, PREV, NEXT>::operator ++ (int)
  {
    Iterator2 tmp (this->wrapper_);
    this->curr_ = NEXT (this->curr_);
    
    return tmp;
  }
   

} // namespace OASIS
} // namespace Pin
