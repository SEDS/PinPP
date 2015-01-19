/**
 * sampling_reservoir_context.h
 */

#ifndef _SAMPLING_RESERVOIR_CONTEXT_
#define _SAMPLING_RESERVOIR_CONTEXT_



#include "sampling_context.h"



class Sampling_Reservoir_State;

/**
 * Reservoir sampling context.
 */
class Sampling_Reservoir_Context : public Sampling_Context <Sampling_Reservoir_State>
{
public:
  Sampling_Reservoir_Context (double percentage);
  virtual void goto_next_state (void);

  void update_estimated_total_and_sample_size (size_t estimated_total_size, size_t estimated_sample_size);
  size_t get_estimated_total_size (void);
  size_t get_estimated_sample_size (void);

protected:
  size_t estimated_total_size_;
  size_t estimated_sample_size_;
};



#endif