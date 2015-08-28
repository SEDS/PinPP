/**
 * RT_Smp_Sampling_Type.h
 */


#ifndef _RT_SMP_SAMPLING_TYPE_H_
#define _RT_SMP_SAMPLING_TYPE_H_


#include "pin++/Callback.h"

#include <random>
#include <chrono>


class RT_Smp_Sampling_Type : public OASIS::Pin::Conditional_Callback <RT_Smp_Sampling_Type (void)>
{
public:
  RT_Smp_Sampling_Type (double percentage);
  virtual bool do_next (void);
  size_t actual_total_event_count (void);
  size_t actual_sampled_event_count (void);

protected:
  std::default_random_engine generator_;
  double percentage_;
  size_t skip_constant_;
  std::uniform_int_distribution<int> distribution_;  
  size_t skip_counter_;
  size_t actual_total_event_count_;
  size_t actual_sampled_event_count_;
};


#endif
