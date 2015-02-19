// -*- C++ -*-
// $Id: Section.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Section::Section (SEC sec)
: sec_ (sec)
{

}

inline
Section::Section (const Section & sec)
: sec_ (sec.sec_)
{

}

inline
Section::~Section (void)
{

}

inline
const Section & Section::operator = (const Section & sec)
{
  this->sec_ = sec.sec_;
  return *this;
}

inline
const Section & Section::operator = (const SEC & sec)
{
  this->sec_ = sec;
  return *this;
}

inline
bool Section::operator == (const Section & rhs) const
{
  return this->sec_ == rhs.sec_;
}

inline
bool Section::operator != (const Section & rhs) const
{
  return this->sec_ != rhs.sec_;
}

inline
Section::operator SEC () const
{
  return this->sec_;
}

inline
BOOL Section::valid (void) const
{
  return SEC_Valid (this->sec_);
}

inline
Routine::iterator_type Section::begin (void) const
{
  return SEC_RtnHead (this->sec_);
}

inline
Routine::iterator_type Section::end (void) const
{
  return Routine::invalid;
}

inline
const string & Section::name (void) const
{
  return SEC_Name (this->sec_);
}

inline
SEC_TYPE Section::type (void) const
{
  return SEC_Type (this->sec_);
}

inline
BOOL Section::mapped (void) const
{
  return SEC_Mapped (this->sec_);
}

inline
const VOID * Section::data (void) const
{
  return SEC_Data (this->sec_);
}

inline
ADDRINT Section::address (void) const
{
  return SEC_Address (this->sec_);
}

inline
BOOL Section::is_readable (void) const
{
  return SEC_IsReadable (this->sec_);
}

inline
BOOL Section::is_writeable (void) const
{
  return SEC_IsWriteable (this->sec_);
}

inline
BOOL Section::is_executable (void) const
{
  return SEC_IsExecutable (this->sec_);
}

inline
USIZE Section::size (void) const
{
  return SEC_Size (this->sec_);
}

inline
Section::iterator_type Section::make_iter (void) const
{
  return iterator_type (this->sec_);
}

} // namespace OASIS
} // namespace Pin
