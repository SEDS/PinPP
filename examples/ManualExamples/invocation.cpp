// $Id: invocation.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Callback.h"
#include "pin++/Context.h"

#include <fstream>
#include <iostream>

class taken : public OASIS::Pin::Callback <taken (OASIS::Pin::ARG_CONTEXT) >
{
public:
  taken (ofstream & fout)
    : fout_ (fout)
  {

  }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "Taken: IP = 0x" << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class before : public OASIS::Pin::Callback <before (OASIS::Pin::ARG_CONTEXT) >
{
public:
  before (ofstream & fout)
    : fout_ (fout) { }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "Before: IP = 0x" << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class after : public OASIS::Pin::Callback <after (OASIS::Pin::ARG_CONTEXT) >
{
public:
  after (ofstream & fout)
    : fout_ (fout) { }

  void handle_analyze (const OASIS::Pin::Context & ctx)
  {
    this->fout_ << "After: IP = 0x" << hex << ctx.get_reg (REG_INST_PTR) << dec << endl;
  }

private:
  std::ofstream & fout_;
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  Instrument (std::ofstream & fout)
    : before_ (fout),
      after_ (fout),
      taken_ (fout)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    using OASIS::Pin::Section;

    for (OASIS::Pin::Section section : img)
    {
      using OASIS::Pin::Routine;

      // RTN_InsertCall () and INS_InsertCall () are executed in order of
      // appearance.  In the code sequence below, the IPOINT_AFTER is
      // executed before the IPOINT_BEFORE.

      for (OASIS::Pin::Routine rtn : section)
      {
        OASIS::Pin::Routine_Guard guard (rtn);

        // IPOINT_AFTER is implemented by instrumenting each return
        // instruction in a routine.  Pin tries to find all return
        // instructions, but success is not guaranteed.
        rtn.insert_call (IPOINT_AFTER, &this->after_);

        // Examine each instruction in the routine.
        for (OASIS::Pin::Ins ins : rtn)
        {
          if (ins.is_return ())
          {
            ins.insert_call (IPOINT_BEFORE, &this->before_);
            ins.insert_call (IPOINT_TAKEN_BRANCH, &this->taken_);
          }
        }
      }
    }

  }

private:
  before before_;
  after after_;
  taken taken_;
};

class invocation : public OASIS::Pin::Tool <invocation>
{
public:
  invocation (void)
    : fout_ ("invocation.out"),
      inst_ (fout_)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->fout_.close ();
  }

private:
  std::ofstream fout_;
  Instrument inst_;
};

DECLARE_PINTOOL (invocation);
