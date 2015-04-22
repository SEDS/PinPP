/**
 * RT_Smp_Instr_Type.h
 */


#ifndef _RT_SMP_INSTR_TYPE_H_
#define _RT_SMP_INSTR_TYPE_H_


#include <fstream>

#include "pin++/Image_Instrument.h"


class RT_Smp_Sampling_Type;
class RT_Smp_Analysis_Type;

class RT_Smp_Instr_Type : public OASIS::Pin::Image_Instrument <RT_Smp_Instr_Type>
{
public:
  RT_Smp_Instr_Type (double percentage, std::string algorithm);
  ~RT_Smp_Instr_Type (void);
  bool do_next (void);
  double percentage (void);

  // the following three methods cannot be "virtual"; otherwise, the pintool won't run
  void handle_instrument (const OASIS::Pin::Image & img);
  void output_sampled_result (std::ofstream & fout);
  void output_process_statistics (void);

protected:
  std::string algorithm_;
  double percentage_;
  RT_Smp_Sampling_Type * sampling_;
  RT_Smp_Analysis_Type * analysis_;
};


#endif
