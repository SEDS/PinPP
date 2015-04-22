// -*- C++ -*-
// $Id: Trace.inl 2299 2013-10-05 05:32:11Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Trace
//
inline
Trace::Trace (TRACE & trace)
: trace_ (trace)
{

}

//
// ~Trace
//
inline
Trace::~Trace (void)
{

}

//
// operator TRACE ()
//
inline
Trace::operator TRACE () const
{
  return this->trace_;
}

//
// bbl_head
//
inline
Bbl::iterator_type Trace::begin (void) const
{
  return TRACE_BblHead (this->trace_);
}

//
// bbl_tail
//
inline
Bbl::iterator_type Trace::end (void) const
{
  return Bbl::invalid;
}

//
// original
//
inline
bool Trace::original (void) const
{
  return TRACE_Original (this->trace_);
}

//
// address
//
inline
ADDRINT Trace::address (void) const
{
  return TRACE_Address (this->trace_);
}

//
// size
//
inline
USIZE Trace::size (void) const
{
  return TRACE_Size (this->trace_);
}

/*
inline
RTN Trace::rtn (void) const
{

}*/

//
// has_fall_through
//
inline
bool Trace::has_fall_through (void) const
{
  return TRACE_HasFallThrough (this->trace_);
}

//
// num_bbl
//
inline
UINT32 Trace::num_bbl (void) const
{
  return TRACE_NumBbl (this->trace_);
}

//
// num_ins
//
inline
UINT32 Trace::num_ins (void) const
{
  return TRACE_NumIns (this->trace_);
}

//
// stub_size
//
inline
USIZE Trace::stub_size (void) const
{
  return TRACE_StubSize (this->trace_);
}

inline
ADDRINT Trace::version (void) const
{
  return TRACE_Version (this->trace_);
}

inline
ADDRINT Trace::code_cache_address (void) const
{
  return TRACE_CodeCacheAddress (this->trace_);
}

inline
USIZE Trace::code_cache_size (void) const
{
  return TRACE_CodeCacheSize (this->trace_);
}

} // namespace Pin
} // namespace OASIS
