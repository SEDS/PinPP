// $Id: inscount0.cpp 2285 2013-09-18 05:24:04Z hillj $

#include "pin++/Callback.h"
#include "pin++/Instruction_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Thread.h"

#include <fstream>
#include <memory>

class Thread_Test :
  public OASIS::Pin::Tool <Thread_Test>,
  public OASIS::Pin::Runnable
{
public:
  Thread_Test (void)
    : thread_start_passed_ (false),
      thread_running_passed_ (false),
      already_started_test_passed_ (false),
      thread_wait_passed_ (false),
      thread_current_passed_ (false)
  {
    using OASIS::Pin::Thread;
    
    this->enable_fini_callback ();
    this->enable_fini_unlocked_callback ();

    std::cerr << "Main Thread: " << Thread::current ()->id () << std::endl;
    
    // Create a new thread and start it.
    cerr << "Starting the thread\n";
    this->thr_ = new Thread (this);
    this->thread_start_passed_ = this->thr_->start () == Thread::STARTED;
    
    // Should return that the thread is running.
    this->already_started_test_passed_ = this->thr_->start () != Thread::NEW;
  }

  ~Thread_Test (void)
  {
    if (0 != this->thr_)
      delete this->thr_;
  }

  void handle_fini (INT32)
  {
    cerr << ">> Thread start passed: " << this->thread_start_passed_ << std::endl;
    cerr << ">> Already started passed: " << this->already_started_test_passed_ << std::endl;
    cerr << ">> Thread running passed: " << this->thread_running_passed_ << std::endl;
    cerr << ">> Thread wait passed: " << this->thread_wait_passed_ << std::endl;
    cerr << ">> Thread current passed: " << this->thread_current_passed_ << std::endl;
  }

  void handle_fini_unlocked (INT32)
  {
    using OASIS::Pin::Thread;
    
    std::cerr << "Waiting for thread to exit...\n";

    if (this->thr_->wait (5000))
      this->thread_wait_passed_ = (this->thr_->state () == Thread::TERMINATED);
  }

  void run (void)
  {
    using OASIS::Pin::Thread;
    
    std::cerr << "Background thread is running..." << std::endl;
    this->thread_running_passed_ = (this->thr_->state () == Thread::RUNNING);
    this->thread_current_passed_ = (this->thr_ == Thread::current ());
  }

private:
  OASIS::Pin::Thread * thr_;

  bool thread_start_passed_;
  bool thread_running_passed_;
  bool already_started_test_passed_;
  bool thread_wait_passed_;
  bool thread_current_passed_;
};

DECLARE_PINTOOL (Thread_Test);
