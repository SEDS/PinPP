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

class method_info : public OASIS::Pin::Callback <method_info (void)>
{
public:
  method_info (void)
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

typedef std::list <method_info *> list_type;

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>
{
public:
  Instrument (list_type & out)
    :out_(out),
    stub_regex("(.*)(Stub::)(.*)(ClientContext)(.*)"),
    clientctx_regex("(.*)(ClientContext::)(.*)")
  { }

  void handle_instrument (const OASIS::Pin::Routine & rtn)
  {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

    std::string sign = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);

    if (std::regex_match(sign, stub_regex_)) {
      method_info * methinfo = new method_info ();
      methinfo->sign_ = sign;
      methinfo->callee_ = std:string("Stub");

      // Add the counter to the listing.
      this->out_.push_back (methinfo);

      OASIS::Pin::Routine_Guard guard (rtn);
      methinfo->insert (IPOINT_BEFORE, rtn);
    }

    if (std::regex_match((*iter)->sign_, clientctx_regex)) {
      method_info * methinfo = new method_info ();
      methinfo->sign_ = sign;
      methinfo->callee_ = std:string("Client Context");

      // Add the counter to the listing.
      this->out_.push_back (methinfo);

      OASIS::Pin::Routine_Guard guard (rtn);
      methinfo->insert (IPOINT_BEFORE, rtn);
    }
  }

private:
  list_type & out_;

  //regular expression for finding valid procedures
  //only want procedures that use a Stub followed by a ClientContext, this means
  //the client context is a parameter to the stub call.
  std::regex stub_regex_;
  std::regex clientctx_regex_;
};

class stubcount : public OASIS::Pin::Tool <stubcount>
{
public:
  stubcount (void)
    :inst_(output_list_),
    fout_ ("stubcount.json")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->fout_ << "{ \"data\": [" << std::endl;

    list_type::const_iterator
      iter = this->output_list_.begin (),
      iter_end = this->output_list_.end ();

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
  list_type output_list_;
  Instrument inst_;
  std::ofstream fout_;
};

DECLARE_PINTOOL (stubcount);
