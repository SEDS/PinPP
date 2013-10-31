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

inline
Symbol::iterator_type Symbol::make_iter (void) const
{
  return this->sym_;
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next>::Iterator (void)
: curr_ (Symbol::invalid),
  wrapper_ (curr_)
{

}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next>::Iterator (const Symbol & t)
: curr_ (t),
  wrapper_ (curr_)
{

}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next>::Iterator (const pin_type & t)
: curr_ (t),
  wrapper_ (curr_)
{

}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next>::Iterator (const Iterator & t)
: curr_ (t.curr_),
  wrapper_ (curr_)
{

}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next>::~Iterator (void)
{

}

inline
const Iterator<Symbol, &SYM_Prev, &SYM_Next> & Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator = (const Iterator & rhs)
{
  this->curr_ = rhs.curr_;
  return *this;
}
inline
Symbol & Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator * (void)
{
  return this->wrapper_;
}

inline
Symbol * Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator -> (void)
{
  return &this->wrapper_;
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next> Iterator <Symbol, &SYM_Prev, &SYM_Next>::make_end (void) const
{
  return Iterator (Symbol::invalid);
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next> & Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator -- (void)
{
  this->curr_ = SYM_Prev (this->curr_);
  return *this;
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next> & Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator ++ (void)
{
  this->curr_ = SYM_Next (this->curr_);
  return *this;
}

inline
bool Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator == (const Iterator & rhs) const
{
  return this->wrapper_ == rhs.wrapper_;
}

inline
bool Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator != (const Iterator & rhs) const
{
  return this->wrapper_ != rhs.wrapper_;
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next> Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator -- (int)
{
  Iterator tmp (this->wrapper_);
  this->curr_ = SYM_Prev (this->curr_);

  return tmp;
}

inline
Iterator <Symbol, &SYM_Prev, &SYM_Next> Iterator <Symbol, &SYM_Prev, &SYM_Next>::operator ++ (int)
{
  Iterator tmp (this->wrapper_);
  this->curr_ = SYM_Next (this->curr_);

  return tmp;
}

} // namespace OASIS
} // namespace Pin
