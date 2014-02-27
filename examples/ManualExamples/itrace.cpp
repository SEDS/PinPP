// $Id: itrace.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <stdio.h>
#include <cstdlib>

class printip : public OASIS::Pin::Callback <printip (OASIS::Pin::ARG_INST_PTR) >
{
public:
  printip (FILE * file)
    : file_ (file)
  {
  }

  void handle_analyze (ADDRINT addr)
  {
    ::fprintf (this->file_, "0x%p\n", addr);
  }

private:
  FILE * file_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : printip_ (file)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->printip_);
  }

private:
  printip printip_;
};

class itrace : public OASIS::Pin::Tool <itrace>
{
public:
  itrace (void)
    : file_ (fopen ("itrace.out", "w")),
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

DECLARE_PINTOOL (itrace);
