
namespace OASIS
{
namespace Pin
{

template <typename T, typename ELEMENT_TYPE>
inline
VOID * Trace_Buffer <T, ELEMENT_TYPE>::
__handle_trace_buffer (BUFFER_ID id,  THREADID tid, const CONTEXT *ctx, VOID *buf, UINT64 elements  , VOID *v)
{
  return reinterpret_cast <T *> (v)->handle_trace_buffer (id,
                                                          tid,
                                                          Const_Context (ctx),
                                                          reinterpret_cast <element_type *> (buf),
                                                          elements);
}

}
}
