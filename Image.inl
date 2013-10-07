// -*- C++ -*-
// $Id: Image.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

//
// Image
//
inline
Image::Image (IMG img)
: img_ (img)
{

}

//
// ~Image
//
inline
Image::~Image (void)
{

}

//
// operator IMG ()
//
inline
Image::operator IMG () const
{
  return this->img_;
}

//
// valid
//
inline
bool Image::valid (void) const
{
  return IMG_Valid (this->img_);
}

//
// entry
//
inline
ADDRINT Image::entry (void) const
{
  return IMG_Entry (this->img_);
}

//
// name
//
inline
const std::string & Image::name (void) const
{
  return IMG_Name (this->img_);
}

//
// gp
//
inline
ADDRINT Image::gp (void) const
{
  return IMG_Gp (this->img_);
}

//
// load_offset
//
inline
ADDRINT Image::load_offset (void) const
{
  return IMG_LoadOffset (this->img_);
}

//
// low_address
//
inline
ADDRINT Image::low_address (void) const
{
  return IMG_LowAddress (this->img_);
}

//
// high_address
//
inline
ADDRINT Image::high_address (void) const
{
  return IMG_HighAddress (this->img_);
}

//
// start_address
//
inline
ADDRINT Image::start_address (void) const
{
  return IMG_StartAddress (this->img_);
}

//
// size_mapped
//
inline
USIZE Image::size_mapped (void) const
{
  return IMG_SizeMapped (this->img_);
}

//
// type
//
inline
IMG_TYPE Image::type (void) const
{
  return IMG_Type (this->img_);
}

//
// is_main_executable
//
inline
bool Image::is_main_executable (void) const
{
  return IMG_IsMainExecutable (this->img_);
}

//
// is_static_executable
//
inline
bool Image::is_static_executable (void) const
{
  return IMG_IsStaticExecutable (this->img_);
}

//
// id
//
inline
UINT32 Image::id (void) const
{
  return IMG_Id (this->img_);
}

//
// close
//
inline
void Image::close (void)
{
  IMG_Close (this->img_);
}

//
// find_by_id
//
inline
Image Image::find_by_id (UINT32 id)
{
  return IMG_FindImgById (id);
}

//
// find_by_address
//
inline
Image Image::find_by_address (ADDRINT addr)
{
  return IMG_FindByAddress (addr);
}

//
// find_routine
//
inline
Routine Image::find_routine (const char * name) const
{
  return Routine (RTN_FindByName (this->img_, name));
}

//
// open
//
inline
Image Image::open (const std::string & filename)
{
  return IMG_Open (filename);
}

//
// section_head
//
inline
Section Image::section_head (void) const
{
  return IMG_SecHead (this->img_);
}

//
// section_tail
//
inline
Section Image::section_tail (void) const
{
  return IMG_SecTail (this->img_);
}

//
// next
//
inline
void Image::next (void)
{
  this->img_ = IMG_Next (this->img_);
}

//
// prev
//
inline
void Image::prev (void)
{
  this->img_ = IMG_Prev (this->img_);
}

} // namespace OASIS
} // namespace Pin
