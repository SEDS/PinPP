// $Id: inscount0.cpp 2285 2013-09-18 05:24:04Z hillj $

#include "pin++/Counter.h"
#include "pin++/Instruction_Instrument.h"
#include "pin++/Pintool.h"

#include <fstream>

class Instruction : public OASIS::Pin::Instruction_Instrument <Instruction>
{
public:
  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    this->counter_.insert (IPOINT_BEFORE, ins);
  }

  UINT64 count (void) const
  {
    return this->counter_.count ();
  }

private:
  OASIS::Pin::Counter <> counter_;
};

class inscount : public OASIS::Pin::Tool <inscount>
{
public:
  inscount (void)
  {
    this->enable_fini_callback ();
  }

  void handle_fini (INT32 code)
  {
    std::ofstream fout (outfile_.Value ().c_str ());
    fout.setf (ios::showbase);
    fout <<  "Count " << this->instruction_.count () << std::endl;

    fout.close ();
  }

private:
  Instruction instruction_;

  /// @{ KNOBS
  static KNOB <string> outfile_;
  /// @}
};

KNOB <string> inscount::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "inscount.out", "specify output file name");

DECLARE_PINTOOL (inscount);
