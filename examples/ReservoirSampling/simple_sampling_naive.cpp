/**
 * A pintool that performs constant sampling.
 *
 * File: runtime_sampling_naive.cpp
 *
 */



/*******************************
 * Dependencies / Constants
 *******************************/

#include "pin++/Image_Instrument.h"
#include "pin++/Instruction_Instrument.h"
#include "pin++/Routine.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>



/*******************************
 * Callback
 *******************************/

/**
 * Conditonal guard. This is a conditional callback that controls when an analysis
 * routine will fire.
 */
class Rtn_Sampling : public OASIS::Pin::Conditional_Callback < Rtn_Sampling (void) >
{
public:
  /*
   * Constructor.
   */
  Rtn_Sampling (double percentage)
    : generator_ (),
      distribution_ (0.0, 1.0),
      percentage_ (percentage),
      actual_total_event_count_ (0),
      actual_sampled_event_count_ (0)
  {
  }

  /**
   * Analysis routine executed for each routine as a guard for sampling.
   *
   * @return      returns true when the current routine should be sampled
   */
  bool do_next (void)
  {
    ++ actual_total_event_count_;
    bool should_sample = (distribution_ (generator_) * 100.0) < percentage_;
    if (should_sample)
    {
      ++ actual_sampled_event_count_;
    }
    return should_sample;
  }
  
  /**
   * Getter for actual_total_event_count_.
   *
   * @return      returns total number of processed events
   */
  size_t actual_total_event_count (void)
  {
    return actual_total_event_count_;
  }

  /**
   * Getter for actual_sampled_event_count_.
   *
   * @return      returns the number of sampled events
   */
  size_t actual_sampled_event_count (void)
  {
    return actual_sampled_event_count_;
  }

private:  
  std::default_random_engine generator_;
  std::uniform_real_distribution<double> distribution_;
  double percentage_;
  size_t actual_total_event_count_;
  size_t actual_sampled_event_count_;
};

/**
 * Analysis routine executed only when chosen by the guard.
 */
class Rtn_Analysis : public OASIS::Pin::Callback < Rtn_Analysis (void) >
{
public:
  /**
   * Constructor.
   */
  Rtn_Analysis (Rtn_Sampling & rtn_sampling)
    : rtn_sampling_ (rtn_sampling),
      analysis_state_ (ANALYSIS_BEFORE),
      should_sample_ (false),
      start_time_ (),
      end_time_ (),
      event_runtime_info_ ()
  {
  }

  /**
   * Analysis routine.
   */
  void handle_analyze (void)
  {
    if (analysis_state_ == ANALYSIS_BEFORE)
    {
      analysis_state_ = ANALYSIS_AFTER;
      should_sample_ = rtn_sampling_.do_next ();
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

  /**
   * Write the sampled result from the vector to the file.
   */
  void output_sampled_result (std::ofstream & fout)
  {
    for (auto pair : event_runtime_info_)
    {
      fout << std::chrono::duration_cast<std::chrono::microseconds>(pair.second - pair.first).count() << " us "
           << "(" << pair.first.time_since_epoch ().count() << " ~ " << pair.second.time_since_epoch ().count() << ")" << std::endl;
    }
  }

private:
  typedef std::vector <std::pair <std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> time_pair_vec_type;
  enum analysis_state_type {ANALYSIS_BEFORE, ANALYSIS_AFTER};
  
  Rtn_Sampling & rtn_sampling_;
  analysis_state_type analysis_state_;
  size_t should_sample_;
  std::chrono::system_clock::time_point start_time_;
  std::chrono::system_clock::time_point end_time_;
  time_pair_vec_type event_runtime_info_;
};



/*******************************
 * Instrument
 *******************************/

/**
 * Image level instrument.
 */
class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  /**
   * Constructor.
   */
  Instrument (std::ofstream & fout, double percentage)
    : percentage_ (percentage > 100.0 ? 100.0 : percentage < 0.0 ? 0.0 : percentage),
      sampling_ (percentage_),
      analysis_ (sampling_)
  {
  }

  /**
   * Instrument routine.
   */
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    INT32 total_rtn_in_img = 0;
    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        OASIS::Pin::Routine_Guard guard (rtn);
        this->analysis_.insert (IPOINT_BEFORE, rtn);
        this->analysis_.insert (IPOINT_AFTER, rtn);
      }
    }
  }

  /**
   * Get the sampled result from the analysis routine.
   */
  void output_sampled_result (std::ofstream & fout)
  {
    analysis_.output_sampled_result (fout);
  }

  /**
   * Output the number of routines processed and sampled through each stage.
   */
  void output_process_statistics (void)
  {
    size_t actual_total_event_count = sampling_.actual_total_event_count ();
    size_t actual_sampled_event_count = sampling_.actual_sampled_event_count ();
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
    std::cout << std::flush;
  }

private:
  double percentage_;                            // sampling percentage
  Rtn_Sampling sampling_;                        // conditional guard for routine sampling
  Rtn_Analysis analysis_;                        // analysis routine  
};



/*******************************
 * Tool
 *******************************/

/**
 * Pintool for naive sampling.
 */
class runtime_sampling_naive : public OASIS::Pin::Tool <runtime_sampling_naive>
{
public:
  /**
   * Constructor.
   */
  runtime_sampling_naive (void)
    : fout_ (outfile_.ValueString ()),
      image_instrument_ (new Instrument (fout_, percentage_.Value ())),
      start_time_ (std::chrono::system_clock::now ()),
      end_time_ ()
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  /**
   * Procedure to be executed after the program execution has finished.
   */
  void handle_fini (INT32)
  {
    end_time_ = std::chrono::system_clock::now ();
    std::cout << std::endl << ".....Sampling Summary....." << std::endl;
    std::cout << "Output filename:  " << outfile_.ValueString () << std::endl;
    std::cout << "Percentage:       " << percentage_.Value () << std::endl;
    std::cout << "Time (sampling):  " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_).count() << " ms" << std::endl;

    start_time_ = std::chrono::system_clock::now ();
    image_instrument_->output_sampled_result (fout_);
    end_time_ = std::chrono::system_clock::now ();
    std::cout << "Time (I/O):       " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_).count() << " ms" << std::endl;

    image_instrument_->output_process_statistics ();
  }

private:
  std::ofstream fout_;                                     // output file handler
  Instrument * image_instrument_;                          // image level instrument
  std::chrono::system_clock::time_point start_time_;       // start time
  std::chrono::system_clock::time_point end_time_;         // end time
  static KNOB <double> percentage_;                        // desired percentage for sampling
  static KNOB <string> outfile_;                           // output file handler
};



/*******************************
 * KNOB declaration
 *******************************/

// $PIN_ROOT/pin -t $PINPP_ROOT/lib/simple_sampling_naive.dll -p <percentage> -f <output_filename> -- <program>
KNOB <double> runtime_sampling_naive::percentage_ (KNOB_MODE_WRITEONCE, "pintool", "p", "20.0", "sampling percentage");
KNOB <string> runtime_sampling_naive::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "f", "simple_sampling_naive.out", "output file name");


/*******************************
 * Tool declaration
 *******************************/

DECLARE_PINTOOL (runtime_sampling_naive);
