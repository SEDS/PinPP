/**
 * sampling_state.h
 */

#ifndef _SAMPLING_STATE_
#define _SAMPLING_STATE_



#include <random>



template <class T>
class Sampling_State
{
public:
  Sampling_State (T * context);
  virtual bool do_next (void) = 0;
  size_t total_event_count (void);
  size_t sampled_event_count (void);

protected:
  T * context_;
  std::default_random_engine generator_;
  std::uniform_real_distribution<double> distribution_;
  size_t actual_total_event_count_;
  size_t actual_sampled_event_count_;
};



#include "sampling_state.cpp"



#endif