// $Id: proccount.cpp 2281 2013-09-16 13:41:50Z dfeiock $

#include "pin++/Routine_Instrument.h"
#include "pin++/Counter.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <list>
#include <memory>

class routine_count : public OASIS::Pin::Callback <routine_count (void)>
{
public:
  routine_count (void)
    : rtnCount_ (0)
  {

  }

  void handle_analyze (void)
  {
    ++ this->rtnCount_;
  }

  /// Name of the routine
  std::string name_;

  /// Source image of the routine
  std::string image_;

  /// Address of the routine
  ADDRINT address_;

  /// The actual routine
  RTN rtn_;

  /// Number of times the routine executed
  UINT64 rtnCount_;

  /// Number of instructions in routine executed
  OASIS::Pin::Counter < > ins_count_;
};

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>
{
public:
  typedef std::list <routine_count *> list_type;

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;
    using OASIS::Pin::Ins;

    // Allocate a counter for this routine
    routine_count * rc = new routine_count ();

    // The RTN goes away when the image is unloaded, so save it now
    // because we need it in the fini
    rc->name_ = rtn.name ();

    const std::string & image_name = rtn.section ().image ().name ();
#if defined (TARGET_WINDOWS)
    rc->image_ = image_name.substr (image_name.find_last_of ('\\') + 1);
#else
    rc->image_ = image_name.substr (image_name.find_last_of ('/') + 1);
#endif
    rc->address_ = rtn.address ();

    // Add the counter to the listing.
    this->rtn_count_.push_back (rc);

    OASIS::Pin::Routine_Guard guard (rtn);
    rc->insert (IPOINT_BEFORE, rtn);

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
    for each (OASIS::Pin::Ins & ins in rtn)
#else
    for (OASIS::Pin::Ins & ins : rtn)
#endif
      rc->ins_count_.insert (IPOINT_BEFORE, ins);
  }

  const list_type & rtn_count (void) const
  {
    return this->rtn_count_;
  }

private:
  list_type rtn_count_;
};

class proccount : public OASIS::Pin::Tool <proccount>
{
public:
  proccount (void)
    : fout_ ("proccount.out")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->fout_
      << setw (23) << "Procedure" << " "
      << setw (15) << "Image" << " "
      << setw (18) << "Address" << " "
      << setw (12) << "Calls" << " "
      << setw (12) << "Instructions" << endl;

    Instrument::list_type::const_iterator
      iter = this->inst_.rtn_count ().begin (),
      iter_end = this->inst_.rtn_count ().end ();

    for (; iter != iter_end; ++ iter)
    {
      if ((*iter)->rtnCount_ == 0)
        continue;

      this->fout_
        << setw (23) << (*iter)->name_ << " "
        << setw (15) << (*iter)->image_ << " "
        << setw (18) << hex << (*iter)->address_ << dec << " "
        << setw (12) << (*iter)->rtnCount_ << " "
        << setw (12) << (*iter)->ins_count_.count () << endl;
    }

    this->fout_.close ();
  }

private:
  Instrument inst_;

  std::ofstream fout_;
};

DECLARE_PINTOOL (proccount);
