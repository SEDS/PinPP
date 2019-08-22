// $Id: grpc_monitor.cpp 11:28 AM 7/22/2019 nlui $

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
#include <vector>
#include <map>
#include <memory>
#include <regex>

class method_info : public OASIS::Pin::Callback <method_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE, OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE, OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>
{
public:
  method_info (void)
    : rtnCount_ (0)
  {

  }

  std::string sign;
  std::string obj;
  ADDRINT address;
  ADDRINT result;
  RTN rtn_;
  UINT64 rtnCount_;

  void handle_analyze (ADDRINT input1, ADDRINT input2, ADDRINT input3) {
    if (input1 == 0 || input2 == 0 || input3 == 0) {
      return;
    }

    ++ this->rtnCount_;
  }
};

typedef std::list <method_info *> list_type;

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>  {
public:
  Instrument (void)
    :stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
    clientctx_regex_("(.*)(ClientContext::)(.*)")
  { }

  void handle_instrument (const OASIS::Pin::Routine & rtn) {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

   std::string signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);

    if (std::regex_match(signature, stub_regex_)) {
      method_info * methinfo = new method_info ();
      methinfo->sign = signature;
      methinfo->obj = std::string("Stub");
      methinfo->address = rtn.address();
      methinfo->rtn_ = rtn;
      this->out_.push_back(methinfo);

      OASIS::Pin::Routine_Guard guard (rtn);
      methinfo->insert (IPOINT_BEFORE, rtn, 0, 1, 2);
    }
  }

  list_type & get_list (void) {
    return this->out_;
  }

private:
  list_type out_;
  std::regex stub_regex_;
  std::regex clientctx_regex_;
};

class grpc_monitor : public OASIS::Pin::Tool <grpc_monitor>
{
public:
  grpc_monitor (void)
    :fout_ ("message_trace.json")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32) {
    list_type & method_infos = inst_.get_list();
    this->output_list_ = method_infos;
    this->print_out();
  }

void print_out(void) {
    list_type::const_iterator iter=output_list_.begin(), iter_end=output_list_.end();

    this->fout_ << "{ \"data\": [" << std::endl;
    for (; iter != iter_end; ++iter) {

	if ((*iter)->rtnCount_ > 0) {
		this->fout_ << "{"
		<< "\"Result\": \"" << std::hex << (*iter)->result << "\","
		<< "\"Procedure\": \"" << (*iter)->sign << "\","
		<< "\"Object\": \"" << (*iter)->obj << "\"}";

		if (iter != std::prev(iter_end)){
			this->fout_ << "," << std::endl;
		}
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

DECLARE_PINTOOL (grpc_monitor);
