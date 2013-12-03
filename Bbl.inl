// -*- C++ -*-
// $Id: Bbl.inl 2299 2013-10-05 05:32:11Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Bbl::Bbl (BBL & bbl)
: bbl_ (bbl)
{

}

inline
Bbl::~Bbl (void)
{

}

inline
bool Bbl::operator == (const Bbl & rhs) const
{
  return this->bbl_ == rhs.bbl_;
}

inline
bool Bbl::operator != (const Bbl & rhs) const
{
  return this->bbl_ != rhs.bbl_;
}

inline
UINT32 Bbl::ins_count (void) const
{
  return BBL_NumIns (this->bbl_);
}

inline
Ins::iterator_type Bbl::ins_head (void) const
{
  return BBL_InsHead (this->bbl_);
}

inline
Ins::iterator_type Bbl::ins_tail (void) const
{
  return BBL_InsTail (this->bbl_);
}

inline
bool Bbl::is_valid (void) const
{
  return BBL_Valid (this->bbl_);
}

inline
bool Bbl::original (void) const
{
  return BBL_Original (this->bbl_);
}

inline
ADDRINT Bbl::address (void) const
{
  return BBL_Address (this->bbl_);
}

inline
USIZE Bbl::size (void) const
{
  return BBL_Size (this->bbl_);
}

inline
bool Bbl::has_fall_through (void) const
{
  return BBL_HasFallThrough (this->bbl_);
}

inline
Bbl::operator BBL () const
{
  return this->bbl_;
}

inline
void Bbl::move_all_attributes (const Bbl & bbl)
{
  BBL_MoveAllAttributes (this->bbl_, bbl.bbl_);
}

inline
void Bbl::set_target_version (ADDRINT version)
{
  BBL_SetTargetVersion (this->bbl_, version);
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
