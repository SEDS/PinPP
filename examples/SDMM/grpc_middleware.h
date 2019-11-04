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
    method_info (std::string signature, std::string call_object)
      : sign_(signature),
      obj_(call_object),
	count_(0)
    { }

    void handle_analyze (void) {
      ++this->count_;
    }

    virtual void write_to(std::ostream & out) {
      if (count_ > 0) {
        out << "{"
        << "\"Method\": \"" << this->sign_ << "\","
        << "\"Object\": \"" << this->obj_ << "\","
        << "\"Call Count\": \"" << this->count_ << "\"}";
      }
    }

    virtual bool has_info(void) {
      return count_;
    }
  private:
    std::string sign_;
    std::string obj_;
	  UINT64 count_;
  };

  class address_info : public OASIS::Pin::Callback <address_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    address_info (void)
	    :count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5) {
      server_address_ = (char const*)arg1;
      ++this->count_;
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Server Address\": \"" << this->server_address_ << "\""
      << "\"Call Count\": \"" << this->count_ << "\"}"; 
    }

    virtual bool has_info(void) {
      return count_;
    }

  private:
    std::string server_address_;
	  UINT64 count_;
  };

  class gRPC_Middleware : public Middleware {
  public:
    gRPC_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :stub_regex_("(.*)(Stub::)(.*)(ClientContext)(.*)"),
      clientctx_substr_("ClientContext::"),
      channel_create_substr_("grpc_channel_create(char const*")
    {  }

    virtual std::string name(void) {
      return "gRPC Middleware";
    }

    virtual void handle_helpers(const OASIS::Pin::Image & img) {
      //doesn't do anything
    }

    virtual void analyze_img(const OASIS::Pin::Image & img) {
      //doesn't do anything
    }

    virtual void analyze_rtn(const OASIS::Pin::Routine & rtn) {
      using OASIS::Pin::Section;
      using OASIS::Pin::Image;

      std::string signature(OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE));
      std::string calling_object("N/A");

      //check if the method is a RPC method on the Client Stub
      if (std::regex_match(signature, stub_regex_)) {
        calling_object = std::string("Stub");
      }

      //check if the method belongs to the Client Context
      if (signature.find(clientctx_substr_) != std::string::npos) {
        calling_object = std::string("ClientContext");
      }

      if (signature.find(channel_create_substr_) != std::string::npos) {
        address_info * a_info = new address_info();

        this->output_list_.push_back((Writer *) a_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        a_info->insert (IPOINT_BEFORE, rtn, 0, 1, 2, 3, 4);
        
      } else if (calling_object != "N/A") {
        method_info * m_info = new method_info (signature, calling_object);
        
        this->output_list_.push_back ((Writer *) m_info);
        OASIS::Pin::Routine_Guard guard (rtn);
        m_info->insert (IPOINT_BEFORE, rtn);
      }
    }

    virtual list_type & get_list(void) {
      return this->output_list_;
    }
  private:
    //output_list_ - the output list
    //stub_regex_ - regular expression for identifying Stub methods
    //clientctx_substr_ - substring for identifying ClientContext methods
    //channel_create_substr_ - substring for identifying the channel creation factory method
    list_type output_list_;
    std::regex stub_regex_;
    std::string clientctx_substr_;
    std::string channel_create_substr_;
  };
}
}

#endif // !GRPC_MIDDLEWARE_H
