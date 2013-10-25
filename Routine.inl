// -*- C++ -*-
// $Id: Routine.inl 2299 2013-10-05 05:32:11Z hillj $

#include "Prototype.h"

namespace OASIS
{
namespace Pin
{

//
// Routine
//
inline
Routine::Routine (RTN rtn)
: rtn_ (rtn),
  symbol_ (sym_)
{

}

//
// Routine
//
inline
Routine::Routine (const Routine & rtn)
: rtn_ (rtn.rtn_),
  sym_ (rtn.sym_),
  symbol_ (sym_)
{

}

//
// ~Routine
//
inline
Routine::~Routine (void)
{

}

//
// operator RTN ()
//
inline
Routine::operator RTN () const
{
  return this->rtn_;
}

//
// operator =
//
inline
const Routine & Routine::operator = (const Routine & rtn)
{
  this->rtn_ = rtn.rtn_;
  this->sym_ = rtn.sym_;
  
  return *this;
}

inline
bool Routine::valid (void)
{
  return RTN_Valid (this->rtn_);
}

inline
const std::string & Routine::name (void) const
{
  return RTN_Name (this->rtn_);
}

inline
INT32 Routine::id (void) const
{
  return RTN_Id (this->rtn_);
}

inline
AFUNPTR Routine::function_ptr (void) const
{
  return RTN_Funptr (this->rtn_);
}

inline
USIZE Routine::size (void) const
{
  return RTN_Size (this->rtn_);
}

inline
string Routine::find_name (ADDRINT addr)
{
  return RTN_FindNameByAddress (addr);
}

inline
Routine Routine::find (ADDRINT addr)
{
  return RTN_FindByAddress (addr);
}

inline
void Routine::open (void)
{
  RTN_Open (this->rtn_);
}

inline
Routine Routine::create (ADDRINT addr, string name)
{
  return RTN_CreateAt (addr, name);
}

inline
void Routine::close (void)
{
  RTN_Close (this->rtn_);
}

inline
Ins::iterator_type Routine::instruction_head (void) const
{
  return RTN_InsHead (this->rtn_);
}

inline
Ins::iterator_type Routine::instruction_head_only (void) const
{
  return RTN_InsHeadOnly (this->rtn_);
}

inline
Ins::iterator_type Routine::instruction_tail (void) const
{
  return RTN_InsTail (this->rtn_);
}

inline
UINT32 Routine::instruction_count (void) const
{
  return RTN_NumIns (this->rtn_);
}

inline
ADDRINT Routine::address (void) const
{
  return RTN_Address (this->rtn_);
}

inline
bool Routine::is_safe_for_probed_insertion (void) const
{
  return RTN_IsSafeForProbedInsertion (this->rtn_);
}

inline
bool Routine::is_safe_for_probed_insertion_ex (PROBE_MODE mode) const
{
  return RTN_IsSafeForProbedInsertionEx (this->rtn_, mode);
}

inline
bool Routine::is_safe_for_probed_replacement (void) const
{
  return RTN_IsSafeForProbedReplacement (this->rtn_);
}

inline
bool Routine::is_safe_for_probed_replacement_ex (PROBE_MODE mode) const
{
  return RTN_IsSafeForProbedReplacementEx (this->rtn_, mode);
}

inline
INT32 Routine::code_ranges_probed (INT32 num, PIN_CODE_RANGE *buffer)
{
  return RTN_CodeRangesProbed (this->rtn_, num, buffer);
}

template <typename CALLBACK>
inline
void Routine::
insert_call (IPOINT location, CALLBACK * callback) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCall>::execute (this->rtn_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Routine::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCall>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Routine::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCall>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Routine::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCall>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Routine::
insert_call (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCall>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

template <typename CALLBACK>
inline
void Routine::
insert_call_probed (IPOINT location, CALLBACK * callback) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCallProbed>::execute (this->rtn_, location, callback, &CALLBACK::__analyze);
}

template <typename CALLBACK, typename XARG1>
inline
void Routine::
insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCallProbed>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1);
}

template <typename CALLBACK, typename XARG1, typename XARG2>
inline
void Routine::
insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCallProbed>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3>
inline
void Routine::
insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCallProbed>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3);
}

template <typename CALLBACK, typename XARG1, typename XARG2, typename XARG3, typename XARG4>
inline
void Routine::
insert_call_probed (IPOINT location, CALLBACK * callback, const XARG1 & xarg1, const XARG2 & xarg2, const XARG3 & xarg3, const XARG4 & xarg4) const
{
  Insert_T <RTN, CALLBACK, &RTN_InsertCallProbed>::execute (this->rtn_, location, callback, &CALLBACK::__analyze, xarg1, xarg2, xarg3, xarg4);
}

///////////////////////////////////////////////////////////////////////////////
// class Routine_Guard

//
// Routine_Guard
//
inline
Routine_Guard::Routine_Guard (Routine & rtn)
: rtn_ (rtn)
{
  this->rtn_.open ();
}

//
// ~Routine_Guard
//
inline
Routine_Guard::~Routine_Guard (void)
{
  this->rtn_.close ();
}

} // namespace OASIS
} // namespace Pin
