/**
 * sampling_state.cpp
 */

#include "sampling_context.h"



template <class T>
Sampling_State <T>::Sampling_State (T * context)
  : context_ (context),
    generator_ (),
    distribution_ (0.0, 1.0),
    actual_total_event_count_ (0),
    actual_sampled_event_count_ (0)
{
}

template <class T>
size_t Sampling_State <T>::total_event_count (void)
{
  return actual_total_event_count_;
}

template <class T>
size_t Sampling_State <T>::sampled_event_count (void)
{
  return actual_sampled_event_count_;
}