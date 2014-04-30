// -*- C++ -*-

//==============================================================================
/**
 *  @file        Trace.h
 *
 *  $Id: Trace.h 2299 2013-10-05 05:32:11Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_TRACE_H_
#define _OASIS_PIN_TRACE_H_

#include "Bbl.h"

namespace OASIS
{
namespace Pin
{
// foraward decl
class Routine;

/**
 * @class Trace
 *
 * Wrapper class for the Pin TRACE object.
 */
class Trace
{
public:
  /// Type definition for Iterator support.
  typedef TRACE pin_type;

  /// Initializing constructor.
  Trace (TRACE & trace);

  /// Destructor.
  ~Trace (void);

  operator TRACE () const;

  // Get the parent Routine
  Routine routine () const;

  /// @{ Bbl Methods
  UINT32 num_ins (void) const;
  UINT32 num_bbl (void) const;
  
  Bbl::iterator_type begin (void) const;
  Bbl::iterator_type end (void) const;
  /// @}

  /// {@ Inspection Methods
  bool original (void) const;

  ADDRINT address (void) const;
  USIZE size (void) const;

  bool has_fall_through (void) const;
  USIZE stub_size (void) const;

  /// @}

  /// Version getter
  ADDRINT version (void) const;

  /// {@ Code Cache methods
  ADDRINT code_cache_address (void) const;
  USIZE code_cache_size (void) const;
  /// @}

  /// Pointer to INS_InsertCall
  static const Insert_Call_T <Trace>::funcptr_type __insert_call;
  static const Insert_Call_T <Trace>::funcptr_type __insert_if_call;
  static const Insert_Call_T <Trace>::funcptr_type __insert_then_call;
  /// @}

private:
  /// The target TRACE
  TRACE & trace_;
};

} // namespace Pin
} // namespace OASIS

#include "Trace.inl"

#endif  // _OASIS_PIN_TRACE_BUILDER_H_
