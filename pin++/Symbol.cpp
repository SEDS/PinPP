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

Symbol::reverse_iterator_type Symbols::rbegin (void) const
{
  // Pin does not provide a method for directly accessing the last symbol
  // in the image. So, we have to emulate accessing the last symbol by iterating
  // over all the symbols until we reach the last one.
  Symbol::iterator_type last_sym = Symbol::invalid;
  Symbol::iterator_type iter = this->begin (), iter_end = this->end ();
  
  for (; iter != iter_end; ++ iter)
    last_sym = iter;

  return *last_sym;
}

} // namespace OASIS
} // namespace Pin
