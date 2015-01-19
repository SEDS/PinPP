/**
 * RT_Smp_Analysis_Type.h
 */


#ifndef _RT_SMP_ANALYSIS_TYPE_H_
#define _RT_SMP_ANALYSIS_TYPE_H_


#include <chrono>

#include "pin++/Callback.h"


class RT_Smp_Instr_Type;

class RT_Smp_Analysis_Type : public OASIS::Pin::Callback <RT_Smp_Analysis_Type (void)>
{
public:
  RT_Smp_Analysis_Type (RT_Smp_Instr_Type * instrument);
  virtual void handle_analyze (void);
  virtual void output_sampled_result (std::ofstream & fout);

protected:
  typedef std::vector <std::pair <std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> time_pair_vec_type;
  enum analysis_state_type {ANALYSIS_BEFORE, ANALYSIS_AFTER};

  RT_Smp_Instr_Type * instrument_;
  analysis_state_type analysis_state_;
  bool should_sample_;
  std::chrono::system_clock::time_point start_time_;
  std::chrono::system_clock::time_point end_time_;
  time_pair_vec_type event_runtime_info_;
};


#endif
