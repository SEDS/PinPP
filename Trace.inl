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
Bbl::iterator_type Trace::bbl_head (void) const
{
  return TRACE_BblHead (this->trace_);
}

//
// bbl_tail
//
inline
Bbl::iterator_type Trace::bbl_tail (void) const
{
  return TRACE_BblTail (this->trace_);
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

template <typename CALLBACK>
inline
void Trace::insert_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Trace::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Trace::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Trace::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Trace::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Trace::insert_if_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertIfCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_if);
}

template <typename CALLBACK, typename XARG1>
inline
void Trace::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertIfCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Trace::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertIfCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Trace::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertIfCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Trace::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertIfCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Trace::insert_then_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertThenCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_then);
}

template <typename CALLBACK, typename XARG1>
inline
void Trace::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertThenCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Trace::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertThenCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Trace::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertThenCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Trace::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <TRACE, CALLBACK, &TRACE_InsertThenCall>::execute (this->trace_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

} // namespace Pin
} // namespace OASIS
