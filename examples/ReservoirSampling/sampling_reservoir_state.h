/**
 * sampling_reservoir_state.h
 */

#ifndef _SAMPLING_RESERVOIR_STATE_
#define _SAMPLING_RESERVOIR_STATE_



#include "sampling_context.h"
#include "sampling_state.h"

#define CONSTANT_T 22


class Sampling_Reservoir_Context;

/**
 * Reservoir sampling state.
 */
class Sampling_Reservoir_State : public Sampling_State <Sampling_Reservoir_Context>
{
public:
  Sampling_Reservoir_State (Sampling_Reservoir_Context * context);
  virtual bool do_next (void) = 0;
  virtual void update_state_parameters (void);
  size_t get_state_counter (void);
  void set_state_counter (size_t state_counter);

protected:
  size_t state_counter_;
  size_t skip_total_;
  int skip_counter_;
};

/**
 * Reservoir sampling state when the n slots are filled by the first n candidates.
 */
class Sampling_Reservoir_State_Initial : public Sampling_Reservoir_State
{
public:
  Sampling_Reservoir_State_Initial (Sampling_Reservoir_Context * context);
  virtual bool do_next (void);
};

/**
 * Reservoir sampling state that applies algorithm x.
 */
class Sampling_Reservoir_State_Algorithm_X : public Sampling_Reservoir_State
{
public:
  Sampling_Reservoir_State_Algorithm_X (Sampling_Reservoir_Context * context);
  virtual bool do_next (void);
  virtual void update_state_parameters (void);

private:
  size_t threshold_;
  size_t numerator_;
};

/**
 * Reservoir sampling state that applies rejection technique.
 */
class Sampling_Reservoir_State_Rejection : public Sampling_Reservoir_State
{
public:
  Sampling_Reservoir_State_Rejection (Sampling_Reservoir_Context * context);
  virtual bool do_next (void);
  virtual void update_state_parameters (void);

private:
  double distribution_w_;
};



#endif