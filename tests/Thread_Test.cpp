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
    : thread_test_1_ (0)
  {
    this->enable_fini_callback ();
    this->enable_fini_unlocked_callback ();

    cerr << "Starting the thread\n";
    this->thr_ = new OASIS::Pin::Thread (this);
    this->thr_->start ();
  }

  ~Thread_Test (void)
  {
    cerr << "~Thread_Test\n";
  }

  void handle_fini (INT32 code)
  {
  }

  void handle_fini_unlocked (INT32 code)
  {
    cerr << ">> Thread Test 1: " << this->thread_test_1_ << std::endl;

    if (!this->thr_->wait (5000))
      std::cerr << "Time has elapsed" << std::endl;

    cerr << ">>> Thread Test 1: " << this->thread_test_1_ << std::endl;
  }

  void run (void)
  {
    std::cerr << "Background thread is running..." << std::endl;
    this->thread_test_1_ = 1;
  }

private:
  OASIS::Pin::Thread * thr_;

  int thread_test_1_;
};

DECLARE_PINTOOL (Thread_Test);
