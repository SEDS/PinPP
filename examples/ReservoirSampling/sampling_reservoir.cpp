/**
 * A pintool that performs reservoir sampling.
 *
 * File: sampling_reservoir.cpp
 *
 */



/*******************************
 * Dependencies / Constants
 *******************************/

#include "pin++/Image_Instrument.h"
#include "pin++/Routine.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include "sampling_reservoir_context.h"
#include "sampling_reservoir_state.h"

#include <iostream>
#include <fstream>
#include <ctime>

#define TOTAL_TO_DISTINCT_RATIO 1      // the ratior total routines to distinct routines, for total estimation
#define DEBUG 1


/*******************************
 * Callback
 *******************************/

/**
 * Conditonal guard. This is a conditional callback that controls when an analysis
 * routine will fire. This conditional callback fires by reservoir sampling.
 */
class Rtn_Sampling : public OASIS::Pin::Conditional_Callback < Rtn_Sampling (void) >
{
public:
  Rtn_Sampling (std::ofstream & fout, double percentage)
    : context_ (percentage),
      distinct_rtn_count_ (0)
  {
  }

  bool do_next (void)
  {
    return context_.do_next ();
  }

  void update_rtn_count (INT32 rtn_count)
  {
    distinct_rtn_count_ = distinct_rtn_count_ + rtn_count;
    size_t estimated_total_size = distinct_rtn_count_ * TOTAL_TO_DISTINCT_RATIO;
    size_t estimated_sample_size = int (estimated_total_size * context_.get_percentage () / 100.0);
    context_.update_estimated_total_and_sample_size (estimated_total_size, estimated_sample_size);
  }
  
  size_t get_next_index (void)
  {
    return context_.get_next_index ();
  }
  
  size_t get_est_sample_size (void)
  {
    return context_.get_estimated_sample_size ();
  }

  void output_process_statistics (void)
  {
    context_.output_state_summary ();
    context_.output_sampling_summary ();
  }

private:
  Sampling_Reservoir_Context context_;
  size_t distinct_rtn_count_;
};

/**
 * Analysis routine executed only when chosen by the guard.
 */
class Rtn_Analysis : public OASIS::Pin::Callback < Rtn_Analysis (OASIS::Pin::ARG_RETURN_IP) >
{
public:
  /**
   * Constructor.
   */
  Rtn_Analysis (std::ofstream & fout, Rtn_Sampling & sampling)
    : rtn_info_ (),
      fout_ (fout),
      sampling_ (sampling)
  {
  }

  /**
   * Analysis routine.
   */
  void handle_analyze (param_type1 addr)
  {
    if (sampling_.do_next ())
    {
      size_t sample_size = sampling_.get_est_sample_size ();
      if (sample_size > rtn_info_.capacity ())
      {
        rtn_info_.resize (sample_size * 2);
      }
      rtn_info_[ sampling_.get_next_index ()] = addr;
    }
  }

  /**
   * Write the sampled result from the vector to the file.
   */
  void output_sampled_result (void)
  {
    fout_ << std::hex;
    for (size_t i = 0; i < sampling_.get_est_sample_size (); ++i)
    {
      fout_ << "0x" << rtn_info_[i] << std::endl;
    }
    fout_ << std::dec;
  }

private:
  typedef std::vector <ADDRINT> vec_type;
  vec_type rtn_info_;
  std::ofstream & fout_;
  Rtn_Sampling & sampling_;
};



/*******************************
 * Instrument
 *******************************/

/**
 * Image level instrument
 */
class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  /**
   * Constructor.
   */
  Instrument (std::ofstream & fout, double percentage)
    : sampling_ (fout, percentage),
      analysis_ (fout, sampling_)
  {
  }

  /**
   * Instrument routine.
   */
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    // keep track of the total number of distinct routines
    // as an estimation of total number of routine calls
    INT32 total_rtn_in_img = 0;

    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        if (rtn.valid ())
        {
          OASIS::Pin::Routine_Guard guard (rtn);
          // this->sampling_ will be inlined and executed for each routin
          // this->analysis_ will be executed only if this->sampling_ returns true
          this->analysis_.insert (IPOINT_BEFORE, rtn);        
          ++total_rtn_in_img;
        }
      }
    }

    sampling_.update_rtn_count (total_rtn_in_img);
  }

  /**
   * Get the sampled result from the analysis routine.
   */
  void output_sampled_result (void)
  {
    analysis_.output_sampled_result ();
  }

  /**
   * Output the number of routines processed and sampled through each stage.
   */
  void output_process_statistics (void)
  {
    sampling_.output_process_statistics ();
  }

private:
  Rtn_Sampling sampling_;              // the conditional guard for sampling
  Rtn_Analysis analysis_;              // the analysis callback object
};



/*******************************
 * Tool
 *******************************/

/**
 * Pintool for reservoir sampling.
 */
class sampling_reservoir : public OASIS::Pin::Tool <sampling_reservoir>
{
public:
  /**
   * Constructor.
   */
  sampling_reservoir (void)
    : fout_ (outfile_.ValueString ()),
      image_ (fout_, percentage_.Value ()),
      start_ (std::clock ()),
      end_ (0)
  {
    std::srand (time (0));
    this->enable_fini_callback ();
  }

  /**
   * Procedure to be executed after the program execution has finished.
   */
  void handle_fini (INT32)
  {
    start_ = std::clock ();
    image_.output_sampled_result ();
    fout_ << "#EOF" << std::endl;
    end_ = std::clock ();   
    
    image_.output_process_statistics ();
    std::cout << "Time (I/O):       " << 1000.0 * (end_ - start_) / CLOCKS_PER_SEC << " (ms)" << std::endl;
  }

private:
  std::ofstream fout_;                 // output file handler
  Instrument image_;                   // image level instrument
  std::clock_t start_;                 // starting time of the instrument
  std::clock_t end_;                   // ending time of the instrument
  static KNOB <double> percentage_;    // desired percentage for sampling
  static KNOB <string> outfile_;       // output file handler
};



/*******************************
 * KNOB declaration
 *******************************/

// $PIN_ROOT/pin -t $PINPP_ROOT/lib/sampling_reservoir.dll -p <percentage> -f <output_filename> -- <program>
KNOB <double> sampling_reservoir::percentage_ (KNOB_MODE_WRITEONCE, "pintool", "p", "20.0", "specify the sampling percentage");
KNOB <string> sampling_reservoir::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "f", "sampling_reservoir.out", "specify output file name");



/*******************************
 * Tool declaration
 *******************************/

DECLARE_PINTOOL (sampling_reservoir);
