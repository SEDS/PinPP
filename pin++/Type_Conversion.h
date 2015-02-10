// -*- C++ -*-

#ifndef _OASIS_PINPP_TYPE_CONVERSION_H_
#define _OASIS_PINPP_TYPE_CONVERSION_H_

#include "pin.H"
#include "Context.h"

namespace OASIS
{
namespace Pin
{

template <typename T>
struct pinpp_type
{
  typedef T result_type;
};
  
template < >
struct pinpp_type <CONTEXT *>
{
  typedef Context result_type;
};
  
template < >
struct pinpp_type <const CONTEXT *>
{
  typedef const Context result_type;
};

}
}

#endif
