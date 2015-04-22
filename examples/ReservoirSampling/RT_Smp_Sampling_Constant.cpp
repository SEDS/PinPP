/**
 * RT_Smp_Sampling_Constant.cpp
 */


#include "RT_Smp_Sampling_Constant.h"


RT_Smp_Sampling_Constant::RT_Smp_Sampling_Constant (double percentage)
  : RT_Smp_Sampling_Type (percentage)
{
}

bool RT_Smp_Sampling_Constant::do_next (void)
{
  ++ actual_total_event_count_;
  if (skip_counter_ > 0)
  {
    -- skip_counter_;
    return false;
  }
  else
  {
    skip_counter_ = skip_constant_;
    ++ actual_sampled_event_count_;
    return true;
  }
}
