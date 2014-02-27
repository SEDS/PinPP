// $Id: inscount1.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/callback/Batch_Counter.h"
#include "pin++/Pintool.h"
#include "pin++/Buffer.h"
#include "pin++/Trace_Instrument.h"

#include <fstream>
#include <list>

class Trace : public OASIS::Pin::Trace_Instrument <Trace>
{
public:
  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // Allocate a callback for each BBL.
    item_type item (trace.num_bbl ());
    item_type::iterator callback = item.begin ();

    for (OASIS::Pin::Bbl bbl : trace)
    {
      callback->increment (bbl.ins_count ());
      bbl.insert_call (IPOINT_BEFORE, callback ++);
    }

    this->traces_.push_back (item);
  }

  UINT64 count (void) const
  {
    list_type::const_iterator
      iter = this->traces_.begin (),
      iter_end = this->traces_.end ();

    UINT64 count = 0;

    for (auto trace : this->traces_)
      for (auto buffer : trace)
        count += buffer.count ();

    return count;
  }

private:
  typedef OASIS::Pin::Buffer < OASIS::Pin::Batch_Counter <> > item_type;
  typedef std::list <item_type> list_type;

  list_type traces_;
};

class inscount : public OASIS::Pin::Tool <inscount>
{
public:
  inscount (void)
  {
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    std::ofstream fout (outfile_.Value ().c_str ());
    fout <<  "Count " << this->trace_.count () << std::endl;
    fout.close ();
  }

private:
  Trace trace_;

  /// @{ KNOBS
  static KNOB <string> outfile_;
  /// @}
};

KNOB <string> inscount::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "inscount.out", "specify output file name");

DECLARE_PINTOOL (inscount);
