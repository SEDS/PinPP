/**
 * sampling_context.h
 */

#ifndef _SAMPLING_CONTEXT_
#define _SAMPLING_CONTEXT_



#include <vector>
#include <ctime>



template <class T>
class Sampling_Context
{
public:
  Sampling_Context (double percentage);
  ~Sampling_Context (void);

  bool do_next (void);
  virtual void goto_next_state (void);

  size_t get_next_index (void);
  void set_next_index (size_t index);

  double get_percentage (void);

  size_t get_total_event_count (void);
  size_t get_sampled_event_count (void);

  void output_state_summary (void);
  void output_sampling_summary (void);

protected:
  std::clock_t start_time_;
  std::vector<T *> all_states_;
  size_t current_state_;
  double percentage_;
  size_t next_index_;
};



#include "sampling_context.cpp"



#endif