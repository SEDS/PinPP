// $Id: detach.cpp 2297 2013-10-01 20:31:06Z hillj $

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <iostream>

class docount : public OASIS::Pin::Callback <docount (void)>
{
public:
  inline docount (void)
    : count_ (0) { }

  void handle_analyze (void)
  {
    ++ this->count_;

    if ((this->count_ % 10000) == 0)
      PIN_Detach ();
  }

  inline UINT64 count (void) const
  {
    return this->count_;
  }

private:
  UINT64 count_;
};

class Instruction : public OASIS::Pin::Instruction_Instrument <Instruction>
{
public:
  inline void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    ins.insert_call (IPOINT_BEFORE, &this->callback_);
  }

  inline UINT64 count (void) const
  {
    return this->callback_.count ();
  }

private:
  docount callback_;
};

class detach : public OASIS::Pin::Tool <detach>
{
public:
  inline detach (void)
  {
    this->enable_detach_callback ();
  }

  inline void handle_detach (void)
  {
    std::cerr << "Detached at icount = " << this->inst_.count () << std::endl;
  }

private:
  Instruction inst_;
};

DECLARE_PINTOOL (detach);
