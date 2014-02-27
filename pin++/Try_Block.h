// -*- C++ -*-

//==============================================================================
/**
 *  @file        Try_Block.h
 *
 *  $Id: Try_Block.h 2305 2013-10-07 03:23:23Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_TRY_BLOCK_H_
#define _OASIS_PIN_TRY_BLOCK_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Try_Block
 */
template <typename T>
class Try_Block
{
protected:
  /// Default constructor.
  Try_Block (THREADID thr_id);

public:
  /// Destructor.
  ~Try_Block (void);

  /// Get the associated thread id
  THREADID thr_id (void) const;

private:
  static EXCEPT_HANDLING_RESULT __internal_exception_handler (THREADID, EXCEPTION_INFO *, PHYSICAL_CONTEXT *, VOID *);

  /// Thread associated with try block.
  THREADID thr_id_;
};

} // namespace OASIS
} // namespace Pin

#include "Try_Block.inl"
#include "Try_Block.cpp"

#endif  // _OASIS_PIN_TRY_BLOCK_H_
