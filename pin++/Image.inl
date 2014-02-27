// -*- C++ -*-
// $Id: Image.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Image::Image (const IMG & img)
: img_ (img)
{

}

inline
Image::Image (const Image & img)
: img_ (img.img_)
{

}

inline
Image::~Image (void)
{

}

inline
Image::operator IMG () const
{
  return this->img_;
}

inline
const Image & Image::operator = (const Image & img)
{
  this->img_ = img.img_;
  return *this;
}

inline
const Image & Image::operator = (const IMG & img)
{
  this->img_ = img;
  return *this;
}

inline
bool Image::operator == (const Image & rhs) const
{
  return this->img_ == rhs.img_;
}

inline
bool Image::operator != (const Image & rhs) const
{
  return this->img_ != rhs.img_;
}

inline
bool Image::valid (void) const
{
  return IMG_Valid (this->img_);
}

inline
ADDRINT Image::entry (void) const
{
  return IMG_Entry (this->img_);
}

inline
const std::string & Image::name (void) const
{
  return IMG_Name (this->img_);
}

inline
ADDRINT Image::gp (void) const
{
  return IMG_Gp (this->img_);
}

inline
ADDRINT Image::load_offset (void) const
{
  return IMG_LoadOffset (this->img_);
}

inline
ADDRINT Image::low_address (void) const
{
  return IMG_LowAddress (this->img_);
}

inline
ADDRINT Image::high_address (void) const
{
  return IMG_HighAddress (this->img_);
}

inline
ADDRINT Image::start_address (void) const
{
  return IMG_StartAddress (this->img_);
}

inline
USIZE Image::size_mapped (void) const
{
  return IMG_SizeMapped (this->img_);
}

inline
IMG_TYPE Image::type (void) const
{
  return IMG_Type (this->img_);
}

inline
bool Image::is_main_executable (void) const
{
  return IMG_IsMainExecutable (this->img_);
}

inline
bool Image::is_static_executable (void) const
{
  return IMG_IsStaticExecutable (this->img_);
}

inline
UINT32 Image::id (void) const
{
  return IMG_Id (this->img_);
}

inline
void Image::close (void)
{
  IMG_Close (this->img_);
}

inline
Image Image::find_by_id (UINT32 id)
{
  return IMG_FindImgById (id);
}

inline
Image Image::find_by_address (ADDRINT addr)
{
  return IMG_FindByAddress (addr);
}

inline
Routine Image::find_routine (const std::string & name) const
{
  return this->find_routine (name.c_str ());
}

inline
Routine Image::find_routine (const char * name) const
{
  return Routine (RTN_FindByName (this->img_, name));
}

inline
Image Image::open (const std::string & filename)
{
  return IMG_Open (filename);
}

inline
Image Image::head (void)
{
  return APP_ImgHead ();
}

inline
Image Image::tail (void)
{
  return APP_ImgTail ();
}

inline
Section::iterator_type Image::begin (void) const
{
  return IMG_SecHead (this->img_);
}

inline
Section::iterator_type Image::end (void) const
{
  return IMG_SecTail (this->img_);
}

inline
Image::iterator_type Image::make_iter (void) const
{
  return iterator_type (this->img_);
}

} // namespace OASIS
} // namespace Pin
