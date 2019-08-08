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

  std::string sign;
  std::string ret_val;
  std::string callee;
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
  void handle_instrument (const OASIS::Pin::Routine & rtn) {
    using OASIS::Pin::Section;
    using OASIS::Pin::Image;

	method_info * methinfo = new method_info ();
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
};

class stubcount : public OASIS::Pin::Tool <stubcount>
{
public:
  stubcount (void)
    :fout_ ("stubcount.json"),
    stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
    clientctx_regex_("(.*)(ClientContext::)(.*)")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32) {
    list_type & method_infos = inst_.get_list();

    for (auto &methinfo : method_infos) {
      if (methinfo->rtnCount_ == 0)
        continue;

      if (std::regex_match(methinfo->sign, stub_regex_)) {
        methinfo->callee = std::string("Stub");
        this->output_list_.push_back(methinfo);
        this->extract_args(methinfo->sign);
      }

      if (std::regex_match(methinfo->sign, clientctx_regex_)) {
        methinfo->callee = std::string("Client Context");
        this->output_list_.push_back(methinfo);
      }
    }

    //Form method_info for methods invoked from args.
     for (auto &methinfo : method_infos) {
       for (auto &pair : args_) {
         if (std::regex_match(methinfo->sign, pair.second)) {
           methinfo->callee = pair.first;
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
    this->fout_ << "{ \"data\": [" << std::endl;
    for (const auto &methinfo : output_list_) {
        this->fout_ << "{"
        << "\"Procedure\": \"" << methinfo->sign << "\","
        << "\"Callee\": \"" << methinfo->callee << "\"}," << std::endl;
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

DECLARE_PINTOOL (stubcount);
