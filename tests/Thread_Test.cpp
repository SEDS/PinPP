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
      already_started_test_passed_ (false),
      thread_wait_passed_ (false)
  {
    this->enable_fini_callback ();
    this->enable_fini_unlocked_callback ();

    // Create a new Thread and start it.
    cerr << "Starting the thread\n";
    this->thr_ = new OASIS::Pin::Thread (this);
    this->thr_->start ();
    
    try
    {
      // This should throw an exception
      this->thr_->start ();
    }
    catch (const OASIS::Pin::Thread::Already_Started &)
    {
      this->already_started_test_passed_ = true;
    }
  }

  ~Thread_Test (void)
  {

  }

  void handle_fini (INT32 code)
  {
    cerr << ">> Thread start passed: " << this->thread_start_passed_ << std::endl;
    cerr << ">> Already started passed: " << this->already_started_test_passed_ << std::endl;
    cerr << ">> Thread wait passed: " << this->thread_wait_passed_ << std::endl;
  }

  void handle_fini_unlocked (INT32 code)
  {
    std::cerr << "Waiting for thread to exit...\n";

    if (this->thr_->wait (5000))
      this->thread_wait_passed_ = true;
  }

  void run (void)
  {
    std::cerr << "Background thread is running..." << std::endl;
    this->thread_start_passed_ = true;
  }

private:
  OASIS::Pin::Thread * thr_;

  bool thread_start_passed_;
  bool already_started_test_passed_;
  bool thread_wait_passed_;
};

DECLARE_PINTOOL (Thread_Test);
