// -*- C++ -*-

//=================================================================================
/**
 * @file        Constant_Sampling.h
 *
 * @author      LiRen Tu
 */
//=================================================================================

#ifndef __OASIS_PINPP_CALLBACK_CONSTANT_SAMPLING_H__
#define __OASIS_PINPP_CALLBACK_CONSTANT_SAMPLING_H__

#include "Callback.h"

#include "Pin_export.h"

namespace OASIS
{
  namespace Pin
  {
    /**
     * @class Constant_Sampling
     *
     * Implementation of a Conditional_Callback that performs constant sampling. In
     * constant sampling, the associated callback is fired after N iterations has
     * surpassed.
     *
     * For example, if you want to sample each 5 instructions, then you would use this
     * implementation of the Conditional_Callback, and set the number of iterations to
     * 5.
     */
    class OASIS_PIN_Export Constant_Sampling :
      public OASIS::Pin::Conditional_Callback < Constant_Sampling (void) >
    {
    public:
      /**
       * Initializing constructor
       *
       * @param[in]       iters       Number of iteration between samples.
       */
      Constant_Sampling (size_t iters);
      
      /// Destructor.
      ~Constant_Sampling (void);
      
      /**
       * Analysis routine executed for each routine as a guard for sampling.
       *
       * @return      returns true when the current routine should be sampled
       */
      bool do_next (void);
      
      /// Get the number of iterations between firing the associated callback.
      size_t iterations (void) const;
      
      /// Number of iterations between firing the associated callback.
      void iterations (size_t iters);

      /// Current iterations of the sampling callback.
      size_t current_iteration (void) const;
      
    private:
      /// The number of iterations to execute before firing the associated callback.
      size_t iters_;
      
      /// The current number of iterations executed.
      size_t curr_iter_;
    };
  }
}

#include "Constant_Sampling.inl"

#endif  // !defined __OASIS_PINPP_CALLBACK_CONSTANT_SAMPLING_H__
