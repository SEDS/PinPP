// $Id$

#include "Section.h"
#include "Image.h"

namespace OASIS
{
namespace Pin
{

const SEC Section::invalid = SEC_Invalid ();

Image Section::image (void) const
{
  return SEC_Img (this->sec_);
}


}
}
