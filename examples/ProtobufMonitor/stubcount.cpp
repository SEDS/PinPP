// $Id: stubcount.cpp 11:28 AM 7/22/2019 nlui $

#include "pin++/Image_Instrument.h"
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

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  typedef std::list <std::string> list_type;

  void handle_instrument (const OASIS::Pin::Image & img) {
    for (auto sec : img) {
        for (auto rtn : sec) {
            if (!rtn.valid ())
              continue;

            std::string rtn_sign = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
            // Add the signature to the listing.
            this->rtn_signatures_.push_back(rtn_sign);
        }
    }

  const list_type & rtn_signature (void) const
  {
    return this->rtn_signatures_;
  }

private:
  list_type rtn_signatures_;
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

  void handle_fini (INT32) {
    this->fout_ << "{ \"data\": [" << std::endl;

    //regular expression for finding valid procedures
    //only want procedures that use a Stub followed by a ClientContext, this means
    //the client context is a parameter to the stub call.
    std::regex stub_regex("(.*)(Stub)(.*)(ClientContext)(.*)");

    Instrument::list_type inst_list = inst_.rtn_signature();

    for (std::string sign : inst_list) {
        this->fout_ << "{" << sign << "},";
    //   //only print info if the procedure has "Stub" and "ClientContext" in the string
    //   if (std::regex_match(sign, stub_regex)) {
    //     this->fout_ << "{"
    //     << "\"Procedure\": \"" << (*iter)->sign << "\","
    //     << "\"ReturnType\": \"" << (*iter)->return_type << "\","
    //     << "\"Image\": \"" << (*iter)->image << "\","
    //   }
    }

    this->fout_ << "]}" << std::endl;

    this->fout_.close ();
  }

private:
  Instrument inst_;

  std::ofstream fout_;
};

DECLARE_PINTOOL (stubcount);
