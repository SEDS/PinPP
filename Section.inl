// -*- C++ -*-
// $Id: Section.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Section
//
inline
Section::Section (SEC sec)
: sec_ (sec)
{

}

//
// Section
//
inline
Section::Section (const Section & sec)
: sec_ (sec.sec_)
{

}

//
// ~Section
//
inline
Section::~Section (void)
{

}


//
// operator SEC
//
inline
Section::operator SEC () const
{
  return this->sec_;
}

//
// image
//
inline
IMG Section::image (void) const
{
  return SEC_Img (this->sec_);
}

//
// next
//
inline
void Section::next (void)
{
  this->sec_ = SEC_Next (this->sec_);
}

//
// prev
//
inline
void Section::prev (void)
{
  this->sec_ = SEC_Prev (this->sec_);
}

//
// valid
//
inline
bool Section::valid (void) const
{
  return SEC_Valid (this->sec_);
}

//
// routine_head
//
inline
Routine Section::routine_head (void) const
{
  return SEC_RtnHead (this->sec_);
}

//
// routine_tail
//
inline
Routine Section::routine_tail (void) const
{
  return SEC_RtnTail (this->sec_);
}

//
// name
//
inline
const string & Section::name (void) const
{
  return SEC_Name (this->sec_);
}

//
// type
//
inline
SEC_TYPE Section::type (void) const
{
  return SEC_Type (this->sec_);
}

//
// mapped
//
inline
bool Section::mapped (void) const
{
  return SEC_Mapped (this->sec_);
}

//
// data
//
inline
const VOID * Section::data (void) const
{
  return SEC_Data (this->sec_);
}

//
// address
//
inline
ADDRINT Section::address (void) const
{
  return SEC_Address (this->sec_);
}

//
// is_readable
//
inline
bool Section::is_readable (void) const
{
  return SEC_IsReadable (this->sec_);
}

//
// is_writeable
//
inline
bool Section::is_writeable (void) const
{
  return SEC_IsWriteable (this->sec_);
}

//
// is_executable
//
inline
bool Section::is_executable (void) const
{
  return SEC_IsExecutable (this->sec_);
}

//
// size
//
inline
USIZE Section::size (void) const
{
  return SEC_Size (this->sec_);
}

} // namespace OASIS
} // namespace Pin
