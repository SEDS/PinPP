// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace OASIS
{
namespace Pin
{

template <typename T>
void Buffer <T>::release (void)
{
  if (0 != this->items_)
  {
    delete [] this->items_;
    this->items_ = 0;
  }
}


} // namespace OASIS
} // namespace Pin
