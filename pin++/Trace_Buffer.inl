// -*- C++ -*-

namespace OASIS
{
namespace Pin
{

template <typename T, typename ELEMENT_TYPE>
inline
Trace_Buffer <T, ELEMENT_TYPE>::Trace_Buffer (UINT32 pages, bool double_buffering)
: record_size_ (sizeof (ELEMENT_TYPE)),
  pages_ (pages),
  buf_id_ (BUFFER_ID_INVALID),
  double_buffering_ (double_buffering),
  xbuf_ (0)
{
  this->buf_id_ = PIN_DefineTraceBuffer (this->record_size_, this->pages_, &Trace_Buffer::__handle_trace_buffer, this);

  if (double_buffering && this->buf_id_ != BUFFER_ID_INVALID)
    this->xbuf_ = reinterpret_cast <element_type *> (PIN_AllocateBuffer (this->buf_id_));
}

template <typename T, typename ELEMENT_TYPE>
inline
Trace_Buffer <T, ELEMENT_TYPE>::~Trace_Buffer (void)
{
  if (0 != this->xbuf_)
    PIN_DeallocateBuffer (this->buf_id_, this->xbuf_);
}

template <typename T, typename ELEMENT_TYPE>
inline
bool Trace_Buffer <T, ELEMENT_TYPE>::is_valid (void) const
{
  return this->buf_id_ != BUFFER_ID_INVALID;
}

template <typename T, typename ELEMENT_TYPE>
inline
BUFFER_ID Trace_Buffer <T, ELEMENT_TYPE>::buffer_id (void) const
{
  return this->buf_id_;
}

template <typename T, typename ELEMENT_TYPE>
inline
size_t Trace_Buffer <T, ELEMENT_TYPE>::record_size (void) const
{
  return this->record_size_;
}

template <typename T, typename ELEMENT_TYPE>
inline
UINT32 Trace_Buffer <T, ELEMENT_TYPE>::pages (void) const
{
  return this->pages_;
}

}
}
