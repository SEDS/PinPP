#include "Constant_Sampling.h"

namespace OASIS
{
  namespace Pin
  {
    bool Constant_Sampling::do_next (void)
    {
      // Increment the current iteration. Then, check if the current iteration
      // is greater than or equal to the number of expected iterations. If so,
      // then we need to fire the associated callback.
      ++ this->curr_iter_;
      bool result = this->curr_iter_ >= this->iters_;
      
      // Reset the iteration, if necessary.
      if (result)
        this->curr_iter_ = 0;
      
      return result;
    }
  }
}