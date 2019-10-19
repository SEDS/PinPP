#include "pin++/Callback.h"
#include "pin++/Image.h"
#include "pin++/Section.h"
#include "middleware.h"
#include "writer.h"

#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <regex>
#include <string.h>
#include <string>
#include <ctime>
#include <iostream>
#include <mutex>

#ifndef GRPC_MIDDLEWARE_H
#define GRPC_MIDDLEWARE_H

namespace OASIS {
namespace Pin {

  class time_accumulator {
  public:
    time_accumulator(void)
      :time_(0.0)
    { }

    void increase (double time) {
      std::unique_lock<std::mutex> lock(mutex_);
      time_ += time;
    }

    double get (void) {
      return time_;
    }
  private:
    std::mutex mutex_;
    double time_;
  };

  static time_accumulator accum_meth_info;

  class method_info : public OASIS::Pin::Callback <method_info (void)>, public Writer {
  public:
    method_info (void)
      : rtnCount_ (0)
    { }

    std::string sign;
    std::string obj;
    RTN rtn_;
    UINT64 rtnCount_;

    void handle_analyze (void)
    {
      std::clock_t start = std::clock ();
      ++ this->rtnCount_;
      std::clock_t end = std::clock ();
      double ET = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(ET);
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Method\": \"" << this->sign << "\","
      << "\"Object\": \"" << this->obj << "\"}";
    }
  };

  class gRPC_Middleware : public Middleware {
  public:
    gRPC_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
      clientctx_regex_("(.*)(ClientContext::)(.*)"),
      max_ET(0.0)
    {  }

    virtual void handle_helpers(const OASIS::Pin::Image & img) {
      //doesn't do anything
    }

    virtual void analyze_img(const OASIS::Pin::Image & img) {
      //doesn't do anything
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

    virtual void analyze_rtn(const OASIS::Pin::Routine & rtn) {
      std::clock_t start = std::clock ();
      using OASIS::Pin::Section;
      using OASIS::Pin::Image;

      std::string signature(OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE));
      std::string calling_object("N/A");

      //check if the method is a RPC method on the Client Stub
      if (std::regex_match(signature, stub_regex_)) {
        calling_object = std::string("Stub");
        this->extract_args(signature);
      }

      //check if the method belongs to the Client Context
      if (std::regex_match(signature, clientctx_regex_)) {
        calling_object = std::string("Client Context");
      }

      //check if the method belongs to one of the input RPC input arugments we've encountered thus far
      for (auto &pair : args_) {
        if (std::regex_match(signature, pair.second)) {
          calling_object = pair.first;
        }
      }

      if (calling_object != "N/A") {
        method_info * methinfo = new method_info ();
        methinfo->sign = signature;
        methinfo->obj = calling_object;
        
        // Add the counter to the listing.
        this->output_list_.push_back (methinfo);

        OASIS::Pin::Routine_Guard guard (rtn);
        methinfo->insert (IPOINT_BEFORE, rtn);
      }
      std::clock_t end = std::clock ();
      double ET = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      total_ET.increase(ET);
      if (ET > max_ET) {
        max_ET = ET;
        std::cout << "Analyze_rtn Time Consumption: " << max_ET << std::endl;
      }
    }

    virtual list_type & get_list(void) {
      std::cout << "Analyze_rtn total Time Consumption: " << total_ET.get() << std::endl;
      std::cout << "Method Info total Time Consumption: " << accum_meth_info.get() << std::endl;
      return this->output_list_;
    }
  private:
    //output_list_ - the output list
    //args_ - a map between RPC input arguments and the regular expression used to identify its methods
    //stub_regex_ - regular expression for identifying Stub methods
    //clientctx_regex_ - regulat expression for identifying ClientContext methods
    list_type output_list_;
    std::map<std::string, std::regex> args_;
    std::regex stub_regex_;
    std::regex clientctx_regex_;
    double max_ET;
    time_accumulator total_ET;
  };

}
}

#endif // !GRPC_MIDDLEWARE_H
