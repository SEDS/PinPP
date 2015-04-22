/**
 * sampling_reservoir_state.cpp
 */

#include "sampling_reservoir_context.h"
#include "sampling_reservoir_state.h"
#include <iostream>



Sampling_Reservoir_State::Sampling_Reservoir_State (Sampling_Reservoir_Context * context)
  : Sampling_State (context),
    state_counter_ (0),
    skip_total_ (0),
    skip_counter_ (-1)
{
}

void Sampling_Reservoir_State::update_state_parameters (void)
{
}

size_t Sampling_Reservoir_State::get_state_counter (void)
{
  return state_counter_;
}

void Sampling_Reservoir_State::set_state_counter (size_t state_counter)
{
  state_counter_ = state_counter;
}

Sampling_Reservoir_State_Initial::Sampling_Reservoir_State_Initial (Sampling_Reservoir_Context * context)
  : Sampling_Reservoir_State (context)
{
}

bool Sampling_Reservoir_State_Initial::do_next (void)
{
  ++ actual_total_event_count_;
  context_->set_next_index (state_counter_);  
  if (state_counter_ == context_->get_estimated_sample_size () - 1)
  {
    context_->goto_next_state ();
  }
  ++ state_counter_;
  ++ actual_sampled_event_count_;
  return true;
}

Sampling_Reservoir_State_Algorithm_X::Sampling_Reservoir_State_Algorithm_X (Sampling_Reservoir_Context * context)
  : Sampling_Reservoir_State (context),
    threshold_ (context_->get_estimated_sample_size () * CONSTANT_T),
    numerator_ (0)
{
}

bool Sampling_Reservoir_State_Algorithm_X::do_next (void)
{
  ++ actual_total_event_count_;
  while (true)
  {
    if (skip_counter_ > 0)               // skip totally skip_counter_ number of routines
    {
      -- skip_counter_;
      return false;
    }
    else if (skip_counter_ == 0)         // sample the current routine
    {
      ++ actual_sampled_event_count_;

      if (state_counter_ > threshold_)
      {
        context_->goto_next_state ();
      }

      skip_counter_ = -1;
      context_->set_next_index (int (distribution_ (generator_) * context_->get_estimated_sample_size ()));      
      return true;
    }
    else                                 // re-calculate skip_counter_
    {
      double distribution_v = distribution_ (generator_);
      skip_total_ = 0;
      ++ state_counter_;
      ++ numerator_;
      double quotient = double (numerator_) / state_counter_;
      
      while (quotient > distribution_v)
      {
        ++ skip_total_;
        ++ state_counter_;
        ++ numerator_;
        quotient = (quotient * numerator_) / state_counter_;
      }
      skip_counter_ = skip_total_;
    }
  }
}

void Sampling_Reservoir_State_Algorithm_X::update_state_parameters (void)
{
  threshold_ = context_->get_estimated_sample_size () * CONSTANT_T;
}

Sampling_Reservoir_State_Rejection::Sampling_Reservoir_State_Rejection (Sampling_Reservoir_Context * context)
  : Sampling_Reservoir_State (context),
    distribution_w_ (0.0)
{
  distribution_w_ = pow (distribution_ (generator_), -1.0 / context_->get_estimated_sample_size ());
}

bool Sampling_Reservoir_State_Rejection::do_next (void)
{
  ++ actual_total_event_count_;

  size_t estimated_sample_size = context_->get_estimated_sample_size ();

  while (true)
  {
    if (skip_counter_ > 0)               // skip totally skip_total_ number of routines
    {
      -- skip_counter_;
      return false;
    }
    else if (skip_counter_ == 0)         // sample the current routine
    {
      ++ actual_sampled_event_count_;

      skip_counter_ = -1;
      context_->set_next_index (int (distribution_ (generator_) * context_->get_estimated_sample_size ()));
      state_counter_ = state_counter_ + skip_total_ + 1;
      return true;
    }
    else                                 // re-calculate skip_total_
    {
      do
      {      
        double U = distribution_ (generator_);
        double state_counter_double = double (state_counter_);
        double sample_size_double = double (estimated_sample_size);
        double x = state_counter_double * (distribution_w_ - 1.0);
        skip_total_ = int (floor (x));
        double term = state_counter_double - sample_size_double + 1.0;
        double lhs = U * pow ((state_counter_double + 1.0) / term, 2.0) * (term + skip_total_) / (state_counter_double + x);
        lhs = pow (lhs, 1.0 / sample_size_double);
        double rhs = term * (state_counter_double + x) / (term + skip_total_) / state_counter_double;

        if (lhs < rhs)                   // test if U <= h(S) / cg(X)
        {
          distribution_w_ = rhs / lhs;
          break;
        }
                                         // test if U <= f(S) / cg(X)
        double y = (((U * (state_counter_double + 1.0)) / term) * (state_counter_double + skip_total_ + 1.0)) / (state_counter_double + x);
        size_t denominator = 0;
        size_t numerator_min = 0;
        if (estimated_sample_size < skip_total_)                   
        {
          denominator = state_counter_;
          numerator_min = state_counter_ - estimated_sample_size + 1 + skip_total_;
        }
        else
        {
          denominator = state_counter_ - estimated_sample_size + skip_total_;
          numerator_min = state_counter_ + 1;
        }
        for (size_t numerator = state_counter_ + skip_total_; numerator >= numerator_min; -- numerator)
        {
          y = (y * numerator) / denominator;
          denominator = denominator - 1;
        }
        distribution_w_ = pow (distribution_ (generator_), -1.0 / estimated_sample_size);
        if (pow (y, 1.0 / sample_size_double) < (state_counter_double + x) / state_counter_double)
        {
          break;
        }
      } while (true);

      skip_counter_ = skip_total_;
    }
  }
}

void Sampling_Reservoir_State_Rejection::update_state_parameters (void)
{
  distribution_w_ = pow (distribution_ (generator_), -1.0 / context_->get_estimated_sample_size ());
}