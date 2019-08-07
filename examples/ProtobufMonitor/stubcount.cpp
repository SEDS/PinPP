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
#include <vector>
#include <map>
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
    stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
    clientctx_regex_("(.*)(ClientContext::)(.*)")
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

      //extract the args from this RPC method
      extract_args(sign);
    }

    if (std::regex_match(sign, clientctx_regex_)) {
      method_info * methinfo = new method_info ();
      methinfo->sign_ = sign;
      methinfo->callee_ = std:string("Client Context");

      // Add the counter to the listing.
      this->out_.push_back (methinfo);

      OASIS::Pin::Routine_Guard guard (rtn);
      methinfo->insert (IPOINT_BEFORE, rtn);
    }

    for (const auto &pair : args_) {
      if (std::regex_match(sign, pair.second)) {
        method_info * methinfo = new method_info ();
        methinfo->sign_ = sign;
        methinfo->callee_ = std:string(pair.first);

        // Add the counter to the listing.
        this->out_.push_back (methinfo);

        OASIS::Pin::Routine_Guard guard (rtn);
        methinfo->insert (IPOINT_BEFORE, rtn);
      }
    }
  }

//extract_args - used to extract the arguments passed into a method and
//store in the args list.
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
        temp.replace(0, 2, "");
        temp.replace(temp.size()-1, 1, "");

        if (args_.count(temp) == 0) {
            std::string regex_lit("(.*)(::)(.*)");
            regex_lit.insert(5, temp);
            std::regex arg_regex(regex_lit);
            args_.insert(std::make_pair(temp, arg_regex));
        }
    }
}

private:
  list_type & out_;
  std::map<std::string, std::regex> args_;

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
