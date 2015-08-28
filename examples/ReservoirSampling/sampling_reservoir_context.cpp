/**
 * sampling_reservoir_context.cpp
 */

#include "sampling_reservoir_context.h"
#include "sampling_reservoir_state.h"
#include <iostream>



Sampling_Reservoir_Context::Sampling_Reservoir_Context (double percentage)
  : Sampling_Context (percentage),
    estimated_total_size_ (0),
    estimated_sample_size_ (0)
{
  Sampling_Reservoir_State * state_initial = new Sampling_Reservoir_State_Initial (this);
  Sampling_Reservoir_State * state_algorithm_x = new Sampling_Reservoir_State_Algorithm_X (this);
  Sampling_Reservoir_State * state_rejection = new Sampling_Reservoir_State_Rejection (this);
  all_states_.push_back (state_initial);
  all_states_.push_back (state_algorithm_x);
  all_states_.push_back (state_rejection);
}

void Sampling_Reservoir_Context::goto_next_state (void)
{
  ++ current_state_;
  all_states_[current_state_]->set_state_counter (estimated_sample_size_);
  all_states_[current_state_]->update_state_parameters ();
}

void Sampling_Reservoir_Context::update_estimated_total_and_sample_size (size_t estimated_total_size, size_t estimated_sample_size)
{
  estimated_total_size_ = estimated_total_size;
  estimated_sample_size_ = estimated_sample_size;
  all_states_[current_state_]->update_state_parameters ();
}

size_t Sampling_Reservoir_Context::get_estimated_total_size (void)
{
  return estimated_total_size_;
}

size_t Sampling_Reservoir_Context::get_estimated_sample_size (void)
{
  return estimated_sample_size_;
}