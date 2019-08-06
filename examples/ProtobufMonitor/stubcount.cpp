// $Id: stubcount.cpp 11:28 AM 7/22/2019 nlui $

#include "pin++/Routine_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <memory>
#include <regex>

class routine_count : public OASIS::Pin::Callback <routine_count (void)>
{
public:
  routine_count (void)
    : rtnCount_ (0)
  {

  }

  std::string sign_;
  std::string ret_val_;
  std::string callee_;
  RTN rtn_;
  UINT64 rtnCount_;

  void handle_analyze (void)
  {
    ++ this->rtnCount_;
  }
};

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>
{
public:
  typedef std::list <routine_count *> list_type;

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

    // Allocate a counter for this routine
    routine_count * rc = new routine_count ();

    // The RTN goes away when the image is unloaded, so save it now
    // because we need it in the fini
    rc->sign_ = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
    rc->callee_ = rtn.section().name();

    // Add the counter to the listing.
    this->rtn_count_.push_back (rc);

    OASIS::Pin::Routine_Guard guard (rtn);
    rc->insert (IPOINT_BEFORE, rtn);
  }

  const list_type & rtn_count (void) const
  {
    return this->rtn_count_;
  }

private:
  list_type rtn_count_;
};

class stubcount : public OASIS::Pin::Tool <stubcount>
{
public:
  stubcount (void)
    : fout_ ("stubcount.json")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->fout_ << "{ \"data\": [" << std::endl;

    Instrument::list_type::const_iterator
      iter = this->inst_.rtn_count ().begin (),
      iter_end = this->inst_.rtn_count ().end ();

    //regular expression for finding valid procedures
    //only want procedures that use a Stub followed by a ClientContext, this means
    //the client context is a parameter to the stub call.
    std::regex stub_regex("(.*)(Stub)(.*)(ClientContext)(.*)");
    std::regex clientctx_regex("(.*)(ClientContext::)(.*)");

    for (; iter != iter_end; ++ iter)
    {
      if ((*iter)->rtnCount_ == 0)
        continue;

      //print info that has "Stub" and "ClientContext" in the string
      if (std::regex_match((*iter)->sign_, stub_regex)) {
        this->fout_ << "{"
        << "\"Procedure\": \"" << (*iter)->sign_ << "\","
        << "\"Callee\": \"" << (*iter)->callee_ << "\"}," << std::endl;
      }

      //print info for all invoked ClientContext methods
      if (std::regex_match((*iter)->sign_, clientctx_regex)) {
        this->fout_ << "{"
        << "\"Procedure\": \"" << (*iter)->sign_ << "\","
        << "\"Callee\": \"" << (*iter)->callee_ << "\"}," << std::endl;
      }
    }

    this->fout_ << "]}" << std::endl;

    this->fout_.close ();
  }

private:
  Instrument inst_;

  std::ofstream fout_;
};

DECLARE_PINTOOL (stubcount);
