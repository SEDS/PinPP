// -*- C++ -*-

namespace OASIS
{
namespace Pin
{

template <typename T, typename INCREMENT>
inline
Batch_Counter <T, INCREMENT>::Batch_Counter (void)
: count_ (0)
{

}

template <typename T, typename INCREMENT>
inline
Batch_Counter <T, INCREMENT>::Batch_Counter (const INCREMENT & incr)
: count_ (0),
  increment_ (incr)
{

}

template <typename T, typename INCREMENT>
inline
void Batch_Counter <T, INCREMENT>::increment (const INCREMENT & incr)
{
  this->increment_ = incr;
}

template <typename T, typename INCREMENT>
inline
const INCREMENT & Batch_Counter <T, INCREMENT>::increment (void) const
{
  return this->increment_;
}

template <typename T, typename INCREMENT>
inline
void Batch_Counter <T, INCREMENT>::handle_analyze (void)
{
  this->count_ += this->increment_;
}

template <typename T, typename INCREMENT>
inline
const T & Batch_Counter <T, INCREMENT>::count (void) const
{
  return this->count_;
}

}
}
