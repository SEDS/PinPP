/**
 * A pintool that performs reservoir sampling.
 *
 * File: reservoir_sampling.cpp
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

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <cmath>
#include <ctime>

#define TOTAL_TO_DISTINCT_RATIO 5      // the ratior total routines to distinct routines, for total estimation
#define CONSTANT_T 5                  // constant T in range [10, 40], optimal 22
#define DEBUG false



/*******************************
 * Callback
 *******************************/

/**
 * Conditonal guard. This is a conditional callback that controls when an analysis
 * routine will fire. This conditional callback fires by reservoir sampling.
 */
class rtn_sampling : public OASIS::Pin::Conditional_Callback < rtn_sampling (void) >
{
public:
  /*
   * Constructor.
   */
  rtn_sampling (std::ofstream & fout, double percentage)
    : fout_ (fout),
      percentage_ (percentage),
      
      distinct_rtn_count_ (0),
      est_sample_size_ (0),
      est_total_size_ (0),
      
      s1_counter_ (0),
      s1_rtn_total_ (0),
      s1_rtn_sampled_ (0),
      
      s2_counter_ (0),
      s2_threshold_ (0),
      s2_numer_ (0),
      s2_rtn_total_ (0),
      s2_rtn_sampled_ (0),
      
      s3_rand_ (0.0),
      s3_rtn_total_ (0),
      s3_rtn_sampled_ (0),
      
      skip_total_ (-1),
      skip_counter_ (0),
      index_ (-1)      
  {
  }

  /**
   * Update the number of distinct routine count.
   */
  void update_rtn_count (INT32 rtn_count)
  {
    distinct_rtn_count_ += rtn_count;
    update_initial_conditions ();

    // debugging output
    // output from the following code showed that the analysis routine was executed
    //   before all the distinct routines have been counted; therefore, the values
    //   for the initial conditions changes along the way, which may cause problems.
    if (DEBUG)
    {
      fout_ << "====routine count updated====" << std::endl;
      fout_ << "count:            " << distinct_rtn_count_ << std::endl;
      fout_ << "est_sample_size_: " << est_sample_size_ << std::endl;
      fout_ << "est_total_size_:  " << est_sample_size_ << std::endl;
      fout_ << "s2_threshold_:    " << s2_threshold_ << std::endl;
    }
  }

  /**
   * Get the number of distinct routine count recorded in the callback.
   *
   * @return      returns the number of distinct routine count
   */
  INT32 get_rtn_count (void)
  {
    return distinct_rtn_count_;
  }

  /**
   * Get the index of the next slot to store the information of the routine.
   *
   * @return      returns the index of the next slot in which the information
   *              of the sampled routine should be stored
   */
  INT32 get_next_index (void)
  {
    return index_;
  }

  /**
   * Get the estimated sample size.
   *
   * @return      returns est_sample_size_
   */
  INT32 get_sample_size (void)
  {
    return est_sample_size_;
  }

  /**
   * Output the number of routines processed and sampled through each stage.
   */
  void output_process_statistics (void)
  {
    std::cout << "Stage 1: " << s1_rtn_sampled_ << " / " << s1_rtn_total_ << std::endl;
    std::cout << "Stage 2: " << s2_rtn_sampled_ << " / " << s2_rtn_total_ << std::endl;
    std::cout << "Stage 3: " << s3_rtn_sampled_ << " / " << s3_rtn_total_ << std::endl;
    
    INT32 rtn_total = s1_rtn_total_ + s2_rtn_total_ + s3_rtn_total_;
    INT32 rtn_sampled = s1_rtn_sampled_ + s2_rtn_sampled_ + s3_rtn_sampled_;
    std::cout << "Total routines: " << rtn_total << std::endl;
    std::cout << "Expected samples: " << (int) rtn_total * percentage_ / 100.0 << std::endl;
    std::cout << "Sampled routines: " << rtn_sampled << std::endl;
  }
  
  /**
   * Get a standard double random number in range [0, 1)
   *
   * @return      returns a double in range [0, 1)
   */
  double std_rand (void)
  {
    return ((double) rand ()) / RAND_MAX;
  }

  /**
   * Update the initial conditions after the number of distinct routines has been updated.
   */
  void update_initial_conditions (void)
  {
    est_total_size_ = distinct_rtn_count_ * TOTAL_TO_DISTINCT_RATIO;
    est_sample_size_ = (int) (est_total_size_ * percentage_ / 100);
    s2_counter_ = est_sample_size_;
    s2_threshold_ = CONSTANT_T * est_sample_size_;
    s3_rand_ = pow (std_rand (), -1.0 / est_sample_size_);
  }

  /**
   * Analysis routine executed for each routine as a guard for sampling.
   *
   * @return      returns true when the current routine should be sampled
   */
  bool do_next (void)
  {
    if (s1_counter_ < est_sample_size_)
    {
      return process_s1 ();
    }
    else if (s2_counter_ <= s2_threshold_)
    {
      return process_s2 ();
    }
    else
    {
      return process_s3 ();
    }
  }

  /**
   * Process the first stage of the sampling, when the first est_sample_size_ candidates
   * are to be put into the reservoir.
   *
   * @return      returns whether the current routine should be sampled
   */
  bool process_s1 (void)
  {
    index_ = s1_counter_;
    ++ s1_counter_;
    ++ s1_rtn_total_;
    ++ s1_rtn_sampled_;

    if (DEBUG)
    {
      fout_ << "stage two, (" << index_ << ")" << std::endl;
    }

    return true;
  }

  /**
   * Process the second stage of the sampling, when s2_counter_ <= s2_threshold_.
   *
   * @return      returns whether the current routine should be sampled
   */
  bool process_s2 (void)
  {
    ++ s2_rtn_total_;

    if (skip_counter_ > 0)             // skip totally skip_total_ number of routines
    {
      -- skip_counter_;

      if (DEBUG)
      {
        fout_ << "skipped" << std::endl;
      }

      return false;
    }    
    else if (skip_counter_ == 0)       // sample the current routine
    {
      ++ s2_rtn_sampled_;
      skip_counter_ = -1;
      index_ = rand () % est_sample_size_;

      if (DEBUG)
      {
        fout_ << "stage two, (" << index_ << ")" << std::endl;
      }

      return true;
    }
    else                               // re-calculate skip_total_
    {
      s2_counter_ = s2_counter_ + 1;
      s2_numer_ = s2_numer_ + 1;
      double distribution_v = std_rand ();
      skip_total_ = 0;
      double quotient = (double) s2_numer_ / s2_counter_;
      while (quotient > distribution_v)
      {
        skip_total_ = skip_total_ + 1;
        s2_counter_ = s2_counter_ + 1;
        s2_numer_ = s2_numer_ + 1;
        quotient = (quotient * s2_numer_) / s2_counter_;
      }
      skip_counter_ = skip_total_ - 1; // subtract skip_total_ by 1 because the current routine is skipped
      if (DEBUG)
      {
        fout_ << "skipped" << std::endl;
      }
      return false;
    }
  }

  /**
   * Process the rest routines with the rejection technique.
   *
   * @return      returns whether the current routine should be sampled
   */
  bool process_s3 (void)
  {
    ++ s3_rtn_total_;

    if (skip_counter_ > 0)             // skip totally skip_total_ number of routines
    {
      -- skip_counter_;

      if (DEBUG)
      {
        fout_ << "skipped" << std::endl;
      }

      return false;
    }    
    else if (skip_counter_ == 0)       // sample the current routine
    {
      ++s3_rtn_sampled_;
      skip_counter_ = -1;
      index_ = rand () % est_sample_size_;

      if (DEBUG)
      {
        fout_ << "stage three, (" << index_ << ")" << std::endl;
      }

      s2_counter_ = s2_counter_ + skip_total_ + 1;
      return true;
    }
    else                               // re-calculate skip_total_
    {
      do
      {
        double U = std_rand ();
        double dt = (double) s2_counter_;
        double dn = (double) est_sample_size_;
        double x = dt * (s3_rand_ - 1.0);
        skip_total_ = (int) floor (x);
        double term = dt - dn + 1.0;
        double lhs = U * pow ((dt + 1.0) / term, 2.0) * (term + skip_total_) / (dt + x);
        lhs = pow (lhs, 1.0 / dn);
        double rhs = term * (dt + x) / (term + skip_total_) / dt;

        if (lhs < rhs)                 // test if U <= h(S) / cg(X)
        {
          s3_rand_ = rhs / lhs;
          break;
        }
                                       // test if U <= f(S) / cg(X)
        double y = (((U * (dt + 1.0)) / term) * (dt + skip_total_ + 1.0)) / (dt + x);
        INT32 denominator = 0;
        INT32 numerator_min = 0;
        if (est_sample_size_ < skip_total_)                   
        {
          denominator = s2_counter_;
          numerator_min = s2_counter_ - est_sample_size_ + 1 + skip_total_;
        }
        else
        {
          denominator = s2_counter_ - est_sample_size_ + skip_total_;
          numerator_min = s2_counter_ + 1;
        }
        for (INT32 numerator = s2_counter_ + skip_total_; numerator >= numerator_min; -- numerator)
        {
          y = (y * numerator) / denominator;
          denominator = denominator - 1;
        }
        s3_rand_ = pow (std_rand (), -1.0 / est_sample_size_);
        if (pow (y, 1.0 / dn) < (dt + x) / dt)
        {
          break;
        }
      } while (true);

      skip_counter_ = skip_total_ - 1; // subtract skip_total_ by 1 because the current routine is skipped
      
      if (DEBUG)
      {
        fout_ << "skipped" << std::endl;
      }
      
      return false;
    }
  }

private:
  std::ofstream & fout_;               // file handler for output
  double percentage_;                  // percentage to be sampled
  
  INT32 distinct_rtn_count_;           // total number of distinct routines
  INT32 est_sample_size_;              // n, estimated sample size
  INT32 est_total_size_;               // N, estimated population size
  
  INT32 s1_counter_;                   // j, counter for stage one
  INT32 s1_rtn_total_;                 // number of routines passed through stage one
  INT32 s1_rtn_sampled_;               // number of routines sampled in stage one
  
  INT32 s2_counter_;                   // t, counter for stage two and three
  INT32 s2_threshold_;                 // thresh, threshold for stage two and three
  INT32 s2_numer_;                     // num, numerator for stage two
  INT32 s2_rtn_total_;                 // number of routines passed through stage two
  INT32 s2_rtn_sampled_;               // number of routines sampled in stage two
  
  double s3_rand_;                     // W, random variable for stage three
  INT32 s3_rtn_total_;                 // number of routines passed through stage three
  INT32 s3_rtn_sampled_;               // number of routines sampled in stage three
  
  INT32 skip_total_;                   // S, total number of routines to be skipped
  INT32 skip_counter_;                 // S, counter for skip_total  
  INT32 index_;                        // M, next index for the information to be stored  
};

/**
 * Analysis routine executed only when chosen by the guard.
 */
class rtn_analysis : public OASIS::Pin::Callback < rtn_analysis (OASIS::Pin::ARG_RETURN_IP) >
{
public:
  /**
   * Constructor.
   */
  rtn_analysis (std::ofstream & fout, rtn_sampling & sampling)
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
      size_t sample_size = sampling_.get_sample_size ();
      if (sample_size > rtn_info_.size ())
      {
        std::cout << "resize from " << rtn_info_.size () << " to " << sample_size << std::endl;
        rtn_info_.resize (sample_size);
      }
      int idx = sampling_.get_next_index ();
      rtn_info_[idx] = addr;
    }
  }

  /**
   * Write the sampled result from the vector to the file.
   */
  void output_sampled_result (void)
  {
    fout_ << std::hex;
    for (auto addr : rtn_info_)
    {
      if (addr != 0)
      {
        fout_ << "0x" << addr << std::endl;
      }
    }
    fout_ << std::dec;
  }

private:
  typedef std::vector <ADDRINT> vec_type;
  vec_type rtn_info_;
  std::ofstream & fout_;
  rtn_sampling & sampling_;
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
        OASIS::Pin::Routine_Guard guard (rtn);
        // this->sampling_ will be inlined and executed for each routin
        // this->analysis_ will be executed only if this->sampling_ returns true
        this->analysis_.insert (IPOINT_BEFORE, rtn);        
        ++total_rtn_in_img;
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
  rtn_sampling sampling_;              // the conditional guard for sampling
  rtn_analysis analysis_;              // the analysis callback object
};



/*******************************
 * Tool
 *******************************/

/**
 * Pintool for reservoir sampling.
 */
class reservoir_sampling_native : public OASIS::Pin::Tool <reservoir_sampling_native>
{
public:
  /**
   * Constructor.
   */
  reservoir_sampling_native (void)
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
    end_ = std::clock ();
    std::cout << "==== Sampling (algorithm z) ====" << std::endl;
    std::cout << "Time (sampling):  " << 1000.0 * (end_ - start_) / CLOCKS_PER_SEC << " (ms)" << std::endl;

    start_ = std::clock ();

    image_.output_sampled_result ();
    fout_ << "#EOF" << std::endl;

    end_ = std::clock ();
    std::cout << "Time (output):    " << 1000.0 * (end_ - start_) / CLOCKS_PER_SEC << " (ms)" << std::endl;
    
    image_.output_process_statistics ();
    std::cout << flush;
  }

private:
  std::ofstream fout_;                 // output file handler
  Instrument image_;                   // image level instrument
  std::clock_t start_;
  std::clock_t end_;
  static KNOB <double> percentage_;    // desired percentage for sampling
  static KNOB <string> outfile_;       // output file handler
};



/*******************************
 * KNOB declaration
 *******************************/

// $PIN_ROOT/pin -t $PINPP_ROOT/lib/reservoir_sampling.dll -p <percentage> -f -- <program>
KNOB <double> reservoir_sampling_native::percentage_ (KNOB_MODE_WRITEONCE, "pintool", "p", "20.0", "specify the sampling percentage");
KNOB <string> reservoir_sampling_native::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "f", "reservoir_sampling_native.out", "specify output file name");



/*******************************
 * Tool declaration
 *******************************/

DECLARE_PINTOOL (reservoir_sampling_native);
