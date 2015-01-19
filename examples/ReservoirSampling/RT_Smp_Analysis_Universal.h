/**
 * RT_Smp_Analysis_Universal.h
 */


#ifndef _RT_SMP_ANALYSIS_UNIVERSAL_H_
#define _RT_SMP_ANALYSIS_UNIVERSAL_H_


#include "RT_Smp_Analysis_Type.h"


class RT_Smp_Instr_Type;

class RT_Smp_Analysis_Universal : public RT_Smp_Analysis_Type
{
public:
  RT_Smp_Analysis_Universal (RT_Smp_Instr_Type * instrument);
};


#endif
