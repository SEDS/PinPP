// $Id: isampling.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <stdio.h>
#include <cstdlib>

/**
 * @class countdown
 *
 * This is a conditional callback that controls when an analysis routine 
 * will fire. This conditional callback fires after N calls.
 */
class countdown : public OASIS::Pin::Conditional_Callback < countdown (void) >
{
public:
  countdown (void)
    : counter_ (1) { }

  void reset_counter (INT32 counter)
  {
    this->counter_ = counter;
  }

  bool do_next (void)
  {
    return (-- this->counter_ == 0);
  }

private:
  INT32 counter_;
};

/**
 * @class printip
 */
class printip : public OASIS::Pin::Callback <printip (OASIS::Pin::ARG_INST_PTR) >
{
public:
  static const INT32 N = 100000;
  static const INT32 M =  50000;

  printip (FILE * file, countdown & countdown)
    : file_ (file),
      countdown_ (countdown)
  {
    this->countdown_.reset_counter (N);
  }

  void handle_analyze (ADDRINT addr)
  {
    ::fprintf (this->file_, "0x%p\n", addr);
    this->countdown_.reset_counter (N + (rand () % M));
  }

private:
  FILE * file_;
  countdown & countdown_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : printip_ (file, countdown_)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    this->printip_[this->countdown_].insert (IPOINT_BEFORE, ins);
  }

private:
  /// The countdown guard protecting \a printip_.
  countdown countdown_;

  /// The analysis callback object
  printip printip_;
};

class isampling : public OASIS::Pin::Tool <isampling>
{
public:
  isampling (void)
    : file_ (fopen ("isampling.out", "w")),
      inst_ (file_)
  {
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
