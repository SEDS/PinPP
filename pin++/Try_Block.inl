// -*- C++ -*-
// $Id: Try_Block.inl 2305 2013-10-07 03:23:23Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
inline
Try_Block <T>::Try_Block (THREADID thr_id)
: thr_id_ (thr_id)
{
  PIN_TryStart (this->thr_id_, &Try_Block::__internal_exception_handler, this);
}

template <typename T>
inline
Try_Block <T>::~Try_Block (void)
{
  PIN_TryEnd (this->thr_id_);
}

template <typename T>
inline
THREADID Try_Block <T>::thr_id (void) const
{
  return this->thr_id_;
}

} // namespace OASIS
} // namespace Pin
