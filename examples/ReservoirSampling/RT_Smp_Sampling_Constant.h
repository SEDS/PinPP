/**
 * RT_Smp_Sampling_Constant.h
 */


#ifndef _RT_SMP_SAMPLING_CONSTANT_H_
#define _RT_SMP_SAMPLING_CONSTANT_H_


#include "RT_Smp_Sampling_Type.h"


class RT_Smp_Sampling_Constant : public RT_Smp_Sampling_Type
{
public:
  RT_Smp_Sampling_Constant (double percentage);
  virtual bool do_next (void);
};


#endif
