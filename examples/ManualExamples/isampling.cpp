// $Id: isampling.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <stdio.h>
#include <cstdlib>

/**
 * @class countdown
 */
class countdown : public OASIS::Pin::Conditional_Callback < countdown (void) >
{
public:
  countdown (INT32 & counter)
    : counter_ (counter)  { }

  ADDRINT do_next (void)
  {
    std::cerr << "current count: " << this->counter_ << std::endl;
    return -- this->counter_;
  }

  static ADDRINT __do_next (VOID * arg)
  {
    return reinterpret_cast <countdown *> (arg)->do_next ();
  }

private:
  INT32 & counter_;
};

/**
 * @class printip
 */
class printip : public OASIS::Pin::Callback <printip (OASIS::Pin::ARG_INST_PTR) >
{
public:
  static const INT32 N = 100000;
  static const INT32 M =  50000;

  printip (FILE * file, INT32 & counter)
    : file_ (file),
      counter_ (counter)
  {
    this->counter_ = N;
  }

  void handle_analyze (ADDRINT addr)
  {
    //::fprintf (this->file_, "0x%p\n", addr);

    // Reset the counter.
    this->counter_ = N + (rand () % M);
  }

private:
  FILE * file_;
  INT32 & counter_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : counter_ (50000),
      countdown_ (counter_),
      printip_ (file, counter_)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    //std::cerr << "instrumenting the instruction" << std::endl;
    //this->printip_[this->countdown_].insert (IPOINT_BEFORE, ins);
  }

private:
  /// Number of instruction to count.
  INT32 counter_;
  
  /// The countdown guard protecting \a printip_.
  countdown countdown_;

  /// The analysis callback object
  printip printip_;
};

class isampling : public OASIS::Pin::Tool <isampling>
{
public:
  isampling (void)
    : file_ (0),
      inst_ (file_)
  {
    std::cout << "creating isampling" << std::endl;
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  Instrument inst_;
};

DECLARE_PINTOOL (isampling);
