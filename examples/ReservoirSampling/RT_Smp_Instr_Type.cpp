/**
 * RT_Smp_Instr_Type.cpp
 */


#include <iostream>

#include "RT_Smp_Instr_Type.h"
#include "RT_Smp_Sampling_Type.h"
#include "RT_Smp_Sampling_Constant.h"
#include "RT_Smp_Sampling_Naive.h"
#include "RT_Smp_Analysis_Universal.h"


RT_Smp_Instr_Type::RT_Smp_Instr_Type (double percentage, std::string algorithm)
  : algorithm_ (algorithm),
    percentage_ (percentage),
    sampling_ (0),
    analysis_ (new RT_Smp_Analysis_Universal (this))
{
  if (algorithm == "constant")
  {
    sampling_ = new RT_Smp_Sampling_Constant (percentage);
  }
  else
  {
    sampling_ = new RT_Smp_Sampling_Naive (percentage);
  }
}

RT_Smp_Instr_Type::~RT_Smp_Instr_Type (void)
{
  if (sampling_ != 0)
  {
    delete sampling_;
    sampling_ = 0;
  }

  if (analysis_ != 0)
  {
    delete analysis_;
    analysis_ = 0;
  }
}

bool RT_Smp_Instr_Type::do_next (void)
{
  return sampling_->do_next ();
}

double RT_Smp_Instr_Type::percentage (void)
{
  return percentage_;
}

void RT_Smp_Instr_Type::handle_instrument (const OASIS::Pin::Image & img)
{
  INT32 total_rtn_in_img = 0;
  for (auto sec : img)
  {
    for (auto rtn : sec)
    {
      OASIS::Pin::Routine_Guard guard (rtn);
      this->analysis_->insert (IPOINT_BEFORE, rtn);
      this->analysis_->insert (IPOINT_AFTER, rtn);
    }
  }
}

void RT_Smp_Instr_Type::output_sampled_result (std::ofstream & fout)
{
  this->analysis_->output_sampled_result (fout);
}

void RT_Smp_Instr_Type::output_process_statistics (void)
{
  size_t actual_total_event_count = this->sampling_->actual_total_event_count ();
  size_t actual_sampled_event_count = this->sampling_->actual_sampled_event_count ();
  size_t expected_samples = size_t (actual_total_event_count * percentage_ / 100.0);
  std::cout << "Algorithm:        " << algorithm_ << std::endl;
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
  std::cout << std::flush;
}
