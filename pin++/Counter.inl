// -*- C++ -*-

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Counter <T>::Counter (void)
: count_ (0)
{

}

template <typename T>
inline
void Counter <T>::handle_analyze (void)
{
  ++ this->count_;
}

template <typename T>
inline
const T & Counter <T>::count (void) const
{
  return this->count_;
}

}
}
