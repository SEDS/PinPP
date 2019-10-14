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

class method_info {
  public:
    std::string sign;
    std::string obj;
    std::string target;
    RTN rtn_;
    UINT64 rtnCount_;
};

class count_info : public OASIS::Pin::Callback <count_info (void)>, public method_info
{
public:
  count_info (void)
    : rtnCount_ (0)
  {

  }

  void handle_analyze (void)
  {
    ++ this->rtnCount_;
  }
};

class channel_info : public OASIS::Pin::Callback <channel_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public method_info
{
  public:
  channel_info (void)
    : rtnCount_ (0)
  {

  }

  void handle_analyze (char const* str, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5)
  {
    ++ this->rtnCount_;
    std::cout << "Target address is --> " << str << std::endl;
  }
};

typedef std::list <method_info *> list_type;

class Instrument : public OASIS::Pin::Routine_Instrument <Instrument>
{
public:
  Instrument(void)
    :channel_create_substr_("grpc_channel_create(char const*")
  { }

  void handle_instrument (const OASIS::Pin::Routine & rtn) {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

    method_info * methinfo = nullptr;

    if (rtn_sign.find(channel_create_substr_) != std::string::npos) {
      methinfo = new channel_info ();
    } else {
      methinfo = new method_info ();
    }

    methinfo->sign = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);

    // Add the counter to the listing.
    this->out_.push_back (methinfo);

    OASIS::Pin::Routine_Guard guard (rtn);
    methinfo->insert (IPOINT_BEFORE, rtn);
  }

  list_type & get_list (void) {
    return this->out_;
  }

private:
  list_type out_;
  std::string channel_create_substr_;
};

class grpc_monitor : public OASIS::Pin::Tool <grpc_monitor>
{
public:
  grpc_monitor (void)
    :fout_ ("message_trace.json"),
    stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
    clientctx_regex_("(.*)(ClientContext::)(.*)")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32 code) {
    list_type & method_infos = inst_.get_list();

    for (auto &methinfo : method_infos) {
      if (methinfo->rtnCount_ == 0)
        continue;

      if (std::regex_match(methinfo->sign, stub_regex_)) {
        methinfo->obj = std::string("Stub");
        this->output_list_.push_back(methinfo);
        this->extract_args(methinfo->sign);
      }

      if (std::regex_match(methinfo->sign, clientctx_regex_)) {
        methinfo->obj = std::string("Client Context");
        this->output_list_.push_back(methinfo);
      }
    }

    //Form method_info for methods invoked from args.
    for (auto &methinfo : method_infos) {
      for (auto &pair : args_) {
        if (std::regex_match(methinfo->sign, pair.second)) {
          methinfo->obj = pair.first;
          this->output_list_.push_back(methinfo);
        }
      }
    }
    this->print_out();
  }

  //replace_all - replace all occurences of sub in str with rep.
  //modified from https://stackoverflow.com/questions/20406744/how-to-find-and-replace-all-occurrences-of-a-substring-in-a-string
  void replace_all(std::string & str, std::string sub, std::string rep) {
    std::string::size_type pos = 0;
    while ((pos = str.find(sub, pos)) != std::string::npos) {
      str.replace(pos, sub.size(), rep);
      pos += rep.size();
    }
  }

  void extract_args(std::string method) {
    std::vector<std::string::size_type> commas;
    std::vector<std::string::size_type> substr_lengths;

    //find all comma positions. We don't use string.find() because
    //we would need to know how many commas are in the string before hand and that requires a second loop through
    //the string.
    for (std::string::size_type i=0; i<method.length(); ++i) {
      if (method[i] == ',') {
        commas.push_back(i);
      }
    }

    for (std::string::size_type i=1; i<commas.size(); ++i) {
      substr_lengths.push_back(commas[i] - commas[i-1] + 1);

      //we use the location of last comma for the last arg's length
      if (i == commas.size()-1) {
        substr_lengths.push_back(commas[i]);
      }
    }

    for (std::string::size_type i=0; i<substr_lengths.size(); ++i) {
      std::string temp = method.substr(commas[i], substr_lengths[i]);

      //remove commas on either side of args
      temp.replace(0, 2, "");
      temp.replace(temp.size()-1, 1, "");

      //remove c++ keywords and symbols
      replace_all(temp, "const", "");
      replace_all(temp, "*", "");
      replace_all(temp, "&", "");

      //remove extra whitespace
      replace_all(temp, " ", "");

      if (args_.count(temp) == 0) {
        std::string regex_lit("(.*)(::)(.*)");
        regex_lit.insert(5, temp);
        std::regex arg_regex(regex_lit);
        args_.insert(std::make_pair(temp, arg_regex));
      }
    }
  }

void print_out(void) {
    list_type::const_iterator iter=output_list_.begin(), iter_end=output_list_.end();

    this->fout_ << "{ \"data\": [" << std::endl;
    for (; iter != iter_end; ++iter) {
      this->fout_ << "{"
      << "\"Procedure\": \"" << (*iter)->sign << "\","
      << "\"Object\": \"" << (*iter)->obj << "\"}";

      if (iter != std::prev(iter_end)){
        this->fout_ << "," << std::endl;
      }
    }

    this->fout_ << "]}" << std::endl;
    this->fout_.close ();
}

private:
  list_type output_list_;
  Instrument inst_;
  std::ofstream fout_;
  std::map<std::string, std::regex> args_;

  //regular expression for finding valid procedures
  //only want procedures that use a Stub followed by a ClientContext, this means
  //the client context is a parameter to the stub call.
  std::regex stub_regex_;
  std::regex clientctx_regex_;
};

DECLARE_PINTOOL (grpc_monitor);
