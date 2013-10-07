// -*- C++ -*-
// $Id: Bbl.inl 2299 2013-10-05 05:32:11Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Bbl
//
inline
Bbl::Bbl (const BBL & bbl)
: bbl_ (bbl)
{

}

//
// ~Bbl
//
inline
Bbl::~Bbl (void)
{

}

//
// ins_count
//
inline
UINT32 Bbl::ins_count (void) const
{
  return BBL_NumIns (this->bbl_);
}

//
// ins_head
//
inline
Ins Bbl::ins_head (void) const
{
  return BBL_InsHead (this->bbl_);
}

//
// ins_tail
//
inline
Ins Bbl::ins_tail (void) const
{
  return BBL_InsTail (this->bbl_);
}

//
// next
//
inline
Bbl & Bbl::next (void)
{
  this->bbl_ = BBL_Next (this->bbl_);
  return *this;
}

//
// prev
//
inline
Bbl & Bbl::prev (void)
{
  this->bbl_ = BBL_Prev (this->bbl_);
  return *this;
}

//
// is_valid
//
inline
bool Bbl::is_valid (void) const
{
  return BBL_Valid (this->bbl_);
}

//
// original
//
inline
bool Bbl::original (void) const
{
  return BBL_Original (this->bbl_);
}

//
// address
//
inline
ADDRINT Bbl::address (void) const
{
  return BBL_Address (this->bbl_);
}

//
// size
//
inline
USIZE Bbl::size (void) const
{
  return BBL_Size (this->bbl_);
}

//
// has_fall_through
//
inline
bool Bbl::has_fall_through (void) const
{
  return BBL_HasFallThrough (this->bbl_);
}

//
// operator INS ()
//
inline
Bbl::operator BBL () const
{
  return this->bbl_;
}

template <typename CALLBACK>
inline
void Bbl::insert_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Bbl::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Bbl::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Bbl::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Bbl::insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Bbl::insert_if_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertIfCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_if);
}

template <typename CALLBACK, typename XARG1>
inline
void Bbl::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertIfCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_if, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Bbl::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertIfCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Bbl::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertIfCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Bbl::insert_if_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertIfCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_if, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Bbl::insert_then_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertThenCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_then);
}

template <typename CALLBACK, typename XARG1>
inline
void Bbl::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertThenCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_then, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Bbl::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertThenCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Bbl::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertThenCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Bbl::insert_then_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <BBL, CALLBACK, &BBL_InsertThenCall>::execute (this->bbl_, location, callback, &CALLBACK::__analyze_then, xarg1, xarg2, xarg3, xarg4);
}

} // namespace OASIS
} // namespace Pin
