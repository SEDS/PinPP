// $Id: Prototype.inl 2294 2013-10-01 20:09:09Z hillj $

namespace OASIS
{
namespace Pin
{

inline
Prototype::Prototype (PROTO proto)
: proto_ (proto)
{

}

inline
Prototype::Prototype (const Prototype & proto)
: proto_ (proto.proto_)
{

}

inline
Prototype::~Prototype (void)
{

}

inline
const Prototype & Prototype::operator = (const Prototype & rhs)
{
  this->proto_ = rhs.proto_;
  return *this;
}

inline
Prototype::operator PROTO (void) const
{
  return this->proto_;
}

inline
void Prototype::close (void)
{
  PROTO_Free (this->proto_);
}

}
}
