// $Id: inscount0.cpp 2285 2013-09-18 05:24:04Z hillj $

#include "pin++/Callback.h"
#include "pin++/Instruction_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Inline_Thread_T.h"

#include <string>
#include <fstream>

class Inline_Thread_Test :
  public OASIS::Pin::Tool <Inline_Thread_Test>
{
public:
  Inline_Thread_Test (void)
  : thread_running_passed_ (false),
    msg_ ("Hello, World!")
  {
    this->enable_fini_callback ();
    this->enable_fini_unlocked_callback ();
    
    // Create an inline thread.
    cerr << "Creating an inline thread\n";
    this->thr_ = OASIS::Pin::make_inline_thread ([this] (void) -> void {
      using OASIS::Pin::Thread;
      
      std::cerr << this->msg_ << std::endl;
      this->thread_running_passed_ = true;
    });
    
    // Start the newly created thread.
    cerr << "Starting an inline thread\n";
    this->thr_->start ();
  }
  
  ~Inline_Thread_Test (void)
  {
    if (0 != this->thr_)
      delete this->thr_;
  }
  
  void handle_fini (INT32)
  {
    cerr << ">> Thread running passed: " << this->thread_running_passed_ << std::endl;
  }
  
  void handle_fini_unlocked (INT32)
  {
    std::cerr << "Waiting for thread to exit...\n";
    
    if (!this->thr_->wait (5000))
      std::cerr << "Failed to wait for thread to terminate\n";
  }
  
private:
  OASIS::Pin::Thread * thr_;
  bool thread_running_passed_;
  std::string msg_;
};

DECLARE_PINTOOL (Inline_Thread_Test);
