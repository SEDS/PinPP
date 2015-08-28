/**
 * RT_Smp_Analysis_Type.cpp
 */

#include <iostream>
#include "RT_Smp_Analysis_Type.h"
#include "RT_Smp_Instr_Type.h"


RT_Smp_Analysis_Type::RT_Smp_Analysis_Type (RT_Smp_Instr_Type * instrument)
  : instrument_ (instrument),
    analysis_state_ (ANALYSIS_BEFORE),
    should_sample_ (false),
    start_time_ (),
    end_time_ (),
    event_runtime_info_ ()
{
}

void RT_Smp_Analysis_Type::handle_analyze (void)
{
  if (analysis_state_ == ANALYSIS_BEFORE)
  {
    analysis_state_ = ANALYSIS_AFTER;
    should_sample_ = instrument_->do_next ();
    start_time_ = std::chrono::system_clock::now();
  }
  else
  {
    analysis_state_ = ANALYSIS_BEFORE;
    if (should_sample_)
    {
      end_time_ = std::chrono::system_clock::now();
      event_runtime_info_.push_back (std::make_pair (start_time_, end_time_));
    }
  }
}

void RT_Smp_Analysis_Type::output_sampled_result (std::ofstream & fout)
{
  for (auto pair : event_runtime_info_)
  {
    fout << std::chrono::duration_cast<std::chrono::microseconds>(pair.second - pair.first).count() << " us "
          << "(" << pair.first.time_since_epoch ().count() << " ~ " << pair.second.time_since_epoch ().count() << ")" << std::endl;
  }
}
