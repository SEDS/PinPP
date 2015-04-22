/**
 * runtime_sampling.cpp
 */


#include <iostream>
#include <fstream>
#include <chrono>

#include "pin++/Pintool.h"

#include "RT_Smp_Instr_Type.h"


class runtime_sampling : public OASIS::Pin::Tool <runtime_sampling>
{
public:
  runtime_sampling (void)
    : fout_ (outfile_.ValueString ()),
      image_instrument_ (percentage_.Value (), algorithm_.ValueString ()),
      start_time_ (std::chrono::system_clock::now ()),
      end_time_ ()
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    end_time_ = std::chrono::system_clock::now ();
    std::cout << std::endl << ".....Sampling Summary....." << std::endl;
    std::cout << "Output filename:  " << outfile_.ValueString () << std::endl;
    std::cout << "Percentage:       " << percentage_.Value () << std::endl;
    std::cout << "Time (sampling):  " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_).count() << " ms" << std::endl;

    start_time_ = std::chrono::system_clock::now ();
    image_instrument_.output_sampled_result (fout_);
    end_time_ = std::chrono::system_clock::now ();
    std::cout << "Time (I/O):       " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_).count() << " ms" << std::endl;

    image_instrument_.output_process_statistics ();
  }

private:
  std::ofstream fout_;
  RT_Smp_Instr_Type image_instrument_;
  std::chrono::system_clock::time_point start_time_;
  std::chrono::system_clock::time_point end_time_;
  static KNOB <double> percentage_;
  static KNOB <string> outfile_;
  static KNOB <string> algorithm_;
};


// $PIN_ROOT/pin -t $PINPP_ROOT/lib/runtime_sampling.dll -p <percentage> -f <output_filename> -a <algorithm> -- <program>
KNOB <double> runtime_sampling::percentage_ (KNOB_MODE_WRITEONCE, "pintool", "p", "50.0", "sampling percentage");

KNOB <string> runtime_sampling::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "f", "runtime_sampling.out", "output file name");

KNOB <string> runtime_sampling::algorithm_ (KNOB_MODE_WRITEONCE, "pintool", "a", "constant", "sampling algorithm");

DECLARE_PINTOOL (runtime_sampling);
