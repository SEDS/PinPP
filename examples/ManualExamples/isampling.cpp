// $Id: isampling.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <stdio.h>
#include <cstdlib>

/**
 * @class countdown
 */
class countdown : public OASIS::Pin::Callback <countdown (void)>
{
public:
  countdown (INT32 & count)
    : count_ (count)
  {

  }

  ADDRINT handle_analyze_if (void)
  {
     return (-- this->count_ == 0);
  }

private:
  INT32 & count_;
};

/**
 * @class printip
 */
class printip : public OASIS::Pin::Callback <printip (OASIS::Pin::ARG_INST_PTR) >
{
public:
  static const INT32 N = 100000;
  static const INT32 M =  50000;

  printip (FILE * file, INT32 & count)
    : file_ (file),
      count_ (count)
  {
    this->count_ = N;
  }

  void handle_analyze_then (ADDRINT addr)
  {
    ::fprintf (this->file_, "0x%p\n", addr);

    // random number from N to N + M
    this->count_ = N + rand () % M;
  }

private:
  FILE * file_;
  INT32 & count_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : count_ (0),
      countdown_ (count_),
      printip_ (file, count_)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_if_call (IPOINT_BEFORE, &this->countdown_);
    ins.insert_then_call (IPOINT_BEFORE, &this->printip_);
  }

private:
  INT32 count_;

  countdown countdown_;
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
