/**
 * RT_Smp_Sampling_Naive.cpp
 */


#include "RT_Smp_Sampling_Naive.h"


RT_Smp_Sampling_Naive::RT_Smp_Sampling_Naive (double percentage)
  : RT_Smp_Sampling_Type (percentage)
{
}

bool RT_Smp_Sampling_Naive::do_next (void)
{
  ++ actual_total_event_count_;
  bool should_sample = (distribution_ (generator_) * 100.0) < percentage_;
  if (should_sample)
  {
    ++ actual_sampled_event_count_;
  }
  return should_sample;
}
