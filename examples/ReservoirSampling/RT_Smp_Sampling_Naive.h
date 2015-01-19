/**
 * RT_Smp_Sampling_Naive.h
 */


#ifndef _RT_SMP_SAMPLING_NAIVE_H_
#define _RT_SMP_SAMPLING_NAIVE_H_


#include "RT_Smp_Sampling_Type.h"


class RT_Smp_Sampling_Naive : public RT_Smp_Sampling_Type
{
public:
  RT_Smp_Sampling_Naive (double percentage);
  virtual bool do_next (void);
};


#endif
