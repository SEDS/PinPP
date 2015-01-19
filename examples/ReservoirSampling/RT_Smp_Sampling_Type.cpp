/**
 * RT_Smp_Sampling_Type.cpp
 */


#include "RT_Smp_Sampling_Type.h"


RT_Smp_Sampling_Type::RT_Smp_Sampling_Type (double percentage)
  : generator_ (),
    percentage_ (percentage),
    skip_constant_ (size_t (100.0 / percentage_) - 1),
    distribution_ (0, skip_constant_),
    skip_counter_ (distribution_ (generator_)),
    actual_total_event_count_ (0),
    actual_sampled_event_count_ (0)
{
}

bool RT_Smp_Sampling_Type::do_next (void)
{
  return false;
}

size_t RT_Smp_Sampling_Type::actual_total_event_count (void)
{
  return actual_total_event_count_;
}

size_t RT_Smp_Sampling_Type::actual_sampled_event_count (void)
{
  return actual_sampled_event_count_;
}
