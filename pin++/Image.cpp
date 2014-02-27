// $Id$

#include "Image.h"

namespace OASIS
{
namespace Pin
{

const IMG Image::invalid = IMG_Invalid ();

Symbols Image::symbols (void) const
{
  return Symbols (*this);
}  

}
}
