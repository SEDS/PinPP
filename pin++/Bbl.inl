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
Ins::iterator_type Bbl::begin (void) const
{
  return BBL_InsHead (this->bbl_);
}

inline
Ins::iterator_type Bbl::end (void) const
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

inline
ADDRINT Bbl::code_cache_address (void) const
{
  return BBL_CodeCacheAddress (this->bbl_);
}

inline
USIZE Bbl::code_cache_size (void) const
{
  return BBL_CodeCacheSize (this->bbl_);
}

} // namespace OASIS
} // namespace Pin
