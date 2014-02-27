// -*- C++ -*-
// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace OASIS
{
namespace Pin
{

inline
Symbol::Symbol (SYM & sym)
: sym_ (sym)
{

}

inline
Symbol::~Symbol (void)
{

}

inline
bool Symbol::operator == (const Symbol & rhs) const
{
  return this->sym_ == rhs.sym_;
}

inline
bool Symbol::operator != (const Symbol & rhs) const
{
  return this->sym_ != rhs.sym_;
}

inline
Symbol::operator SYM () const
{
  return this->sym_;
}

inline
std::string Symbol::undecorate (const std::string & name, UNDECORATION style)
{
  return PIN_UndecorateSymbolName (name, style);
}

inline
const string & Symbol::name (void) const
{
  return SYM_Name (this->sym_);
}

inline
BOOL Symbol::is_valid (void) const
{
  return SYM_Valid (this->sym_);
}

inline
BOOL Symbol::is_dynamic (void) const
{
  return SYM_Dynamic (this->sym_);
}

inline
BOOL Symbol::is_ifunc (void) const
{
  return SYM_IFunc (this->sym_);
}

inline
ADDRINT Symbol::value (void) const
{
  return SYM_Value (this->sym_);
}

inline
UINT32 Symbol::index (void) const
{
  return SYM_Index (this->sym_);
}

inline
ADDRINT Symbol::address (void) const
{
  return SYM_Address (this->sym_);
}

inline
std::string Symbol::undecorate (UNDECORATION style) const
{
  return undecorate (this->name (), style);
}

///////////////////////////////////////////////////////////////////////////////
// class Symbols

inline
Symbols::Symbols (const Image & img)
: img_ (img)
{
    
}

inline
Symbols::Symbols (const Symbols & symbols)
: img_ (symbols.img_)
{
    
}

inline
Symbol::iterator_type Symbols::end (void) const
{
  return SYM_Invalid ();
}
  
} // namespace OASIS
} // namespace Pin
