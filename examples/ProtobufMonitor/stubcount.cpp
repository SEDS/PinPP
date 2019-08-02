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

class func_info : public OASIS::Pin::Callback <func_info (void)> {
public:
	func_info(void)
	  : used(0)
	{ }

	std::string sign;
	std::string returntype;
	std::string image;
	UINT64 used;

  void handle_analyze (void) {
    ++ this->used;
  }
};

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument> {
public:
  typedef std::list <func_info*> list_type;

  Instrument(void) { }

  void handle_instrument (const OASIS::Pin::Routine & rtn) {
	    func_info* info = new func_info;
	    info->sign = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
	    info->returntype = "Status";

    	    const std::string & image_name = rtn.section ().image ().name ();
#if defined (TARGET_WINDOWS)
	    info->image = image_name.substr (image_name.find_last_of ('\\') + 1);
#else
	    info->image = image_name.substr (image_name.find_last_of ('/') + 1);
#endif

            // Add the signature to the listing.
            this->rtn_signatures_.push_back(info);
  }

  const list_type & rtn_signatures (void) const {
    return this->rtn_signatures_;
  }

private:
  list_type rtn_signatures_;
};

class stubcount : public OASIS::Pin::Tool <stubcount> {
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

    Instrument::list_type::const_iterator
      iter = this->inst_.rtn_signatures().begin(),
      iter_end = this->inst_.rtn_signatures().end();

    for (; iter != iter_end; ++ iter) {

      if ((*iter)->used == 0)
        continue;


       //only print info if the procedure has "Stub" and "ClientContext" in the string
       if (std::regex_match((*iter)->sign, stub_regex)) {
         this->fout_ << "{"
         << "\"Procedure\": \"" << (*iter)->sign << "\","
         << "\"ReturnType\": \"" << (*iter)->returntype << "\","
         << "\"Image\": \"" << (*iter)->image << "\"}," << std::endl;
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
