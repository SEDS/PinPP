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

#ifndef DDS_MIDDLEWARE_H
#define DDS_MIDDLEWARE_H

namespace OASIS {
namespace Pin {

  template<typename ARG2TYPE>
  class marshaller_info : public OASIS::Pin::Callback <marshaller_info<ARG2TYPE> (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    marshaller_info (std::string signature, std::string call_object)
	    :sign_(signature),
        obj_(call_object),
        count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2) {
      std::clock_t start = std::clock ();
      values_.push_back((ARG2TYPE)arg2);
      ++this->count_;
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Values\": [";
	
	for (ARG2TYPE &item : this->values_) {
		out << item << ", ";
	}

      out << "], \"Method\": \"" << this->sign_ << "\","
      << "\"Object\": \"" << this->obj_ << "\","
      << "\"Call Count\": " << this->count_ << "}"; 
    }

    virtual bool has_info(void) {
      return count_;
    }

  private:
    std::list<ARG2TYPE> values_;
    std::string sign_;
    std::string obj_;
	UINT64 count_;
  };

  template<>
  class marshaller_info <const char*> : public OASIS::Pin::Callback <marshaller_info<const char*> (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    marshaller_info (std::string signature, std::string call_object)
	    :sign_(signature),
        obj_(call_object),
        count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2) {
      std::clock_t start = std::clock ();
      values_.push_back(std::string((const char*)arg2));
      ++this->count_;
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Values\": [";

	for (std::string &item : this->values_) {
		out << "\"" << item << "\", ";
	}

      out << "], \"Method\": \"" << this->sign_ << "\","
      << "\"Object\": \"" << this->obj_ << "\","
      << "\"Call Count\": " << this->count_ << "}"; 
    }

    virtual bool has_info(void) {
      return count_;
    }

  private:
    std::list<std::string> values_;
    std::string sign_;
    std::string obj_;
	UINT64 count_;
  };

  class credentials_info : public OASIS::Pin::Callback <credentials_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    credentials_info (std::string signature, std::string call_object)
	    :port_(0),
	publisher_address_("sample.address.edu"),
	sign_(signature),
        obj_(call_object),
        count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4) {
      std::clock_t start = std::clock ();
      port_ = (unsigned short)arg1;
      //publisher_address_.assign((char const*)arg2);
      ++this->count_;
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Port\": " << this->port_ << ","
      << "\"Publisher Address\": \"" << this->publisher_address_ << "\","
      << "\"Method\": \"" << this->sign_ << "\","
      << "\"Object\": \"" << this->obj_ << "\","
      << "\"Call Count\": " << this->count_ << "}"; 
    }

    virtual bool has_info(void) {
      return count_;
    }

  private:
    unsigned short port_;
    std::string publisher_address_;
    std::string sign_;
    std::string obj_;
	UINT64 count_;
  };

  class DDS_Middleware : public Middleware {
  public:
    DDS_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :ace_inet_set_("ACE_INET_Addr::set(unsigned short, char const*, int, int)"),
      marshaller_string_("OpenDDS::DCPS::operator<<(OpenDDS::DCPS::Serializer&, char const*)"),
      marshaller_int_("OpenDDS::DCPS::operator<<(OpenDDS::DCPS::Serializer&, int)")
    {  }

    virtual std::string name(void) {
      return "DDS Middleware";
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

      //does the signature match one of the substrings we're looking for?
      if (signature.find(ace_inet_set_) != std::string::npos) {
        calling_object = std::string("ACE_INET_Addr");

        credentials_info *c_info = new credentials_info(signature, calling_object);
        this->output_list_.push_back((Writer *) c_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        c_info->insert (IPOINT_BEFORE, rtn, 0, 1, 2, 3);
      }

      if (signature.find(marshaller_string_) != std::string::npos) {
        calling_object = std::string("OpenDDS::DCPS");

        marshaller_info<const char*> *m_info = new marshaller_info<const char*> (signature, calling_object);
        this->output_list_.push_back ((Writer *) m_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        m_info->insert (IPOINT_BEFORE, rtn, 0, 1);
      }

      if (signature.find(marshaller_int_) != std::string::npos) {
        calling_object = std::string("OpenDDS::DCPS");

        marshaller_info<int> *m_info = new marshaller_info<int> (signature, calling_object);
        this->output_list_.push_back ((Writer *) m_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        m_info->insert (IPOINT_BEFORE, rtn, 0, 1);
      }
    }

    virtual list_type & get_list(void) {
      return this->output_list_;
    }
  private:
    //output_list_ - the output list
    //ace_inet_addre_ - substring to identify set method for the remote address and port number
    //marshaller_string_ - substring to identify the << method used to marshall C-strings
    //marshaller_int_ - substring to identify the << method use to marshall integers
    list_type output_list_;
    std::string ace_inet_set_;
    std::string marshaller_string_;
    std::string marshaller_int_;
  };
}
}

#endif // !DDS_MIDDLEWARE_H
