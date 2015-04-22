/**
 * sampling_context.cpp
 */

#include <iostream>
#include "sampling_state.h"



template <class T>
Sampling_Context <T>::Sampling_Context (double percentage)
  : start_time_ (std::clock ()),
    all_states_ (),
    current_state_ (0),
    percentage_ (percentage),
    next_index_ (0)
{
}

template <class T>
Sampling_Context <T>::~Sampling_Context (void)
{
  for (auto state : all_states_)
  {
    if (state != 0)
    {
      delete state;
      state = 0;
    }
  }
}

template <class T>
bool Sampling_Context <T>::do_next (void)
{
  return all_states_[current_state_]->do_next ();
}

template <class T>
void Sampling_Context <T>::goto_next_state (void)
{
  ++ current_state_;
}

template <class T>
void Sampling_Context <T>::set_next_index (size_t next_index)
{
  next_index_ = next_index;
}

template <class T>
size_t Sampling_Context <T>::get_next_index (void)
{
  return next_index_;
}

template <class T>
double Sampling_Context <T>::get_percentage (void)
{
  return percentage_;
}

template <class T>
size_t Sampling_Context <T>::get_total_event_count (void)
{
  size_t total_event_count = 0;
  for (auto state : all_states_)
  {
    total_event_count = total_event_count + state->total_event_count ();
  }
  return total_event_count;
}

template <class T>
size_t Sampling_Context <T>::get_sampled_event_count (void)
{
  size_t sampled_event_count = 0;
  for (auto state : all_states_)
  {
    sampled_event_count = sampled_event_count + state->sampled_event_count ();
  }
  return sampled_event_count;
}

template <class T>
void Sampling_Context <T>::output_state_summary (void)
{
  std::cout << std::endl << "... State Summary ..." << std::endl;
  std::clock_t end_time = std::clock ();
  size_t actual_total_event_count = 0;
  size_t actual_sampled_event_count = 0;
  size_t state_no = 1;
  for (auto state : all_states_)
  {
    size_t sampled_event_in_current_state = state->sampled_event_count ();
    size_t total_event_in_current_state = state->total_event_count ();
    actual_sampled_event_count = actual_sampled_event_count + sampled_event_in_current_state;
    actual_total_event_count = actual_total_event_count + total_event_in_current_state;
    std::cout << "State " << state_no << ": " << sampled_event_in_current_state << " / " << total_event_in_current_state << std::endl;
    ++ state_no;
  }
}

template <class T>
void Sampling_Context <T>::output_sampling_summary (void)
{
  std::clock_t end_time = std::clock ();
  std::cout << std::endl << "... Sampling Summary ..." << std::endl;
  size_t actual_total_event_count = get_total_event_count ();
  size_t actual_sampled_event_count = get_sampled_event_count ();
  size_t expected_samples = size_t (actual_total_event_count * percentage_ / 100.0);
  std::cout << "Total events:     " << actual_total_event_count << std::endl;
  std::cout << "Expected samples: " << expected_samples << std::endl;
  std::cout << "Actual samples:   " << actual_sampled_event_count;
  if (expected_samples == actual_sampled_event_count)
  {
    std::cout << " (exact-sampling)" << std::endl;
  }
  else if (expected_samples > actual_sampled_event_count)
  {
    std::cout << " (under-sampling)" << std::endl;
  }
  else
  {
    std::cout << " (over-sampling)" << std::endl;
  }
  std::cout << "Time (sampling):  " << 1000.0 * (end_time - start_time_) / CLOCKS_PER_SEC << " (ms)" << std::endl;
  std::cout << std::flush;
}