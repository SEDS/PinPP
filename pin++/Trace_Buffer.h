// -*- C++ -*-

//=============================================================================
/**
 * @file      Trace_Buffer.h
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PINPP_TRACE_BUFFER_H_
#define _OASIS_PINPP_TRACE_BUFFER_H_

#include "Context.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Trace_Buffer
 *
 * Wrapper class for managing the state of trace buffers in Pin. The trace
 * buffer can be configured to support double buffering.
 */
template <typename T, typename ELEMENT_TYPE>
class Trace_Buffer
{
public:
  /// Type definition of subclass.
  typedef T type;

  /// Type definition of element type stored in buffer.
  typedef ELEMENT_TYPE element_type;

  /**
   * Initializing constructor. Flag that enables/disables double
   * buffering. By default, double buffering is not enabled.
   *
   * @param[in]       double_buffering      Enable double buffering
   */
  Trace_Buffer (UINT32 pages, bool double_buffering = false);

  /// Destructor.
  ~Trace_Buffer (void);

  /// Test if the trace buffer is valid
  bool is_valid (void) const;

  /// Get the buffer id for the trace buffer.
  BUFFER_ID buffer_id (void) const;

  /// Size of a record in the trace buffer.
  size_t record_size (void) const;

  /// Number of pages in the trace buffer.
  UINT32 pages (void) const;

private:
  /// Callback for handling trace buffer notification
  static VOID * __handle_trace_buffer (BUFFER_ID id, THREADID tid, const CONTEXT *ctx, VOID *buf, UINT64 elements  , VOID *v);

  /// The size of a record.
  size_t record_size_;

  /// Number of pages in the trace buffer.
  UINT32 pages_;

  /// Registered buffer id
  BUFFER_ID buf_id_;

  /// Double buffering state.
  bool double_buffering_;

  /// Pointer to the double buffer.
  element_type * xbuf_;
};

}
}

#include "Trace_Buffer.inl"
#include "Trace_Buffer.cpp"

#endif  // !defined _OASIS_PINPP_TRACE_BUFFER_H_
