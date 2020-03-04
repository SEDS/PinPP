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
#include <typeinfo>

#ifndef GRPC_MIDDLEWARE_H
#define GRPC_MIDDLEWARE_H

namespace OASIS {
namespace Pin {
	
	template<typename T>
	class grpc_data : public OASIS::Pin::Callback <grpc_data<T> (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
	public:
		grpc_data (std::string method, std::string in_types, std::string call_object)
      :method_(method),
      in_types_(in_types),
      obj_(call_object),
      count_(0)
    { }

    void handle_analyze (T arg) {
      std::clock_t start = std::clock ();
      ++this->count_;
			std::cout << arg << std::endl;
			data_.push_back(arg);
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      if (count_ > 0) {
        out << "Method: " << this->method_ << std::endl
        << "Input Types: " << this->in_types_ << std::endl
        << "Calling Object: " << this->obj_ << std::endl
        << "Call Count: " << this->count_ << std::endl;

				out << "Data: [";
				for (auto &item: data_) {
					out << item << ",";
				}
				out << "]" << std::endl;
      }
    }

    virtual bool has_info(void) {
      return count_;
    }
  private:
    std::string method_;
    std::string in_types_;
    std::string obj_;
		std::list<T> data_;
	  UINT64 count_;
	};

  class grpc_general : public OASIS::Pin::Callback <grpc_general (void)>, public Writer {
  public:
    grpc_general (std::string method, std::string in_types, std::string call_object)
      :method_(method),
      in_types_(in_types),
      obj_(call_object),
      count_(0)
    { }

    void handle_analyze (void) {
      std::clock_t start = std::clock ();
      ++this->count_;
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      if (count_ > 0) {
        out << "Method: " << this->method_ << std::endl
        << "Input Types: " << this->in_types_ << std::endl
        << "Calling Object: " << this->obj_ << std::endl
        << "Call Count: " << this->count_ << std::endl;
      }
    }

    virtual bool has_info(void) {
      return count_;
    }
  private:
    std::string method_;
    std::string in_types_;
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
      std::clock_t start = std::clock ();
      if (arg1) {
        server_address_ = (char const*)arg1;
        ++this->count_;
      }
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      out << "Server Address: " << this->server_address_ << std::endl
      << "Call Count: " << this->count_ << std::endl;
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
      channel_create_substr_("grpc_channel_create(char const*"),
			value_substr_("set_value(double)"),
			timestamp_substr_("set_timestamp(long long)")
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
      std::string method;
      std::string in_types;

      //check if the method is a RPC method on the Client Stub
      if (std::regex_match(signature, stub_regex_)) {
        std::list<std::string> sign_info(parse_signature(signature));
        calling_object = sign_info.front(); sign_info.pop_front();
        method = sign_info.front(); sign_info.pop_front();
        in_types = sign_info.front(); sign_info.pop_front();

        grpc_general * m_info = new grpc_general (method, in_types, calling_object);
        
        this->output_list_.push_back ((Writer *) m_info);
        OASIS::Pin::Routine_Guard guard (rtn);
        m_info->insert (IPOINT_BEFORE, rtn);
      }

      //check if the method belongs to the Client Context
      if (signature.find(clientctx_substr_) != std::string::npos) {
        std::list<std::string> sign_info(parse_signature(signature));
        calling_object = sign_info.front(); sign_info.pop_front();
        method = sign_info.front(); sign_info.pop_front();
        in_types = sign_info.front(); sign_info.pop_front();

        grpc_general * m_info = new grpc_general (method, in_types, calling_object);
        
        this->output_list_.push_back ((Writer *) m_info);
        OASIS::Pin::Routine_Guard guard (rtn);
        m_info->insert (IPOINT_BEFORE, rtn);
      }

      if (signature.find(channel_create_substr_) != std::string::npos) {
        address_info * a_info = new address_info();

        this->output_list_.push_back((Writer *) a_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        a_info->insert (IPOINT_BEFORE, rtn, 0, 1, 2, 3, 4);
      }
			//else if (signature.find(value_substr_) != std::string::npos) {
			//	std::list<std::string> sign_info(parse_signature(signature));
      //  calling_object = sign_info.front(); sign_info.pop_front();
      //  method = sign_info.front(); sign_info.pop_front();
      //  in_types = sign_info.front(); sign_info.pop_front();

			//	grpc_data<double> * data_info = new grpc_data<double> (method, in_types, calling_object);

			//	this->output_list_.push_back ((Writer *) data_info);
			//	OASIS::Pin::Routine_Guard guard (rtn);
			//	data_info->insert (IPOINT_AFTER, rtn, 0);

			//}
			//if (signature.find(timestamp_substr_) != std::string::npos) {
			//	std::list<std::string> sign_info(parse_signature(signature));
      //  calling_object = sign_info.front(); sign_info.pop_front();
      //  method = sign_info.front(); sign_info.pop_front();
      //  in_types = sign_info.front(); sign_info.pop_front();

			//	grpc_data<long long> * data_info = new grpc_data<long long> (method, in_types, calling_object);

			//	this->output_list_.push_back ((Writer *) data_info);
			//	OASIS::Pin::Routine_Guard guard (rtn);
			//	data_info->insert (IPOINT_AFTER, rtn, 0);
			//}
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
		std::string value_substr_;
		std::string timestamp_substr_;
  };
}
}

#endif // !GRPC_MIDDLEWARE_H
