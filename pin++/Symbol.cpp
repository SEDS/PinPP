// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

#include "Symbol.h"
#include "Image.h"

namespace OASIS
{
namespace Pin
{

const SYM Symbol::invalid = SYM_Invalid ();
  
Symbol::iterator_type Symbols::begin (void) const
{
  return IMG_RegsymHead (this->img_);
}

} // namespace OASIS
} // namespace Pin
