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

  class dds_readwrite_info : public OASIS::Pin::Callback <dds_readwrite_info (void)>, public Writer {
  public:
    dds_readwrite_info (std::string method, std::string in_types, std::string call_object)
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

  class dds_topic_info : public OASIS::Pin::Callback <dds_topic_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    dds_topic_info (std::string method, std::string in_types, std::string call_object)
      :method_(method),
      in_types_(in_types),
      obj_(call_object),
      count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5) {
      std::clock_t start = std::clock ();
      ++this->count_;
      this->topics_.push_back(std::string((const char*)arg2));
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

        out << "Topics: [";
        for (std::string &topic : topics_) {
          out << topic << ",";
        }
	      out << "]" << std::endl;
      }
    }

    virtual bool has_info(void) {
      return count_;
    }
  private:
    std::list<std::string> topics_;
    std::string method_;
    std::string in_types_;
    std::string obj_;
	  UINT64 count_;
  };

  class DDS_Middleware : public Middleware {
  public:
    DDS_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :datawriter_write_("::write("),
      datareader_takenextsample_("::take_next_sample("),
      create_topic_("::create_topic(")
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
      std::string method;
      std::string in_types;

      //does the signature match one of the substrings we're looking for?
      if (signature.find(datawriter_write_) != std::string::npos) {
        std::list<std::string> sign_info(parse_signature(signature));
        calling_object = sign_info.front(); sign_info.pop_front();
        method = sign_info.front(); sign_info.pop_front();
        in_types = sign_info.front(); sign_info.pop_front();

        dds_readwrite_info * dds_info = new dds_readwrite_info(method, in_types, calling_object);
        this->output_list_.push_back((Writer *) dds_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        dds_info->insert (IPOINT_BEFORE, rtn);
      }

      if (signature.find(datareader_takenextsample_) != std::string::npos) {
        std::list<std::string> sign_info(parse_signature(signature));
        calling_object = sign_info.front(); sign_info.pop_front();
        method = sign_info.front(); sign_info.pop_front();
        in_types = sign_info.front(); sign_info.pop_front();

        dds_readwrite_info * dds_info = new dds_readwrite_info(method, in_types, calling_object);
        this->output_list_.push_back((Writer *) dds_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        dds_info->insert (IPOINT_BEFORE, rtn);
      }

      if (signature.find(create_topic_) != std::string::npos) {
				std::list<std::string> sign_info(parse_signature(signature));
        calling_object = sign_info.front(); sign_info.pop_front();
        method = sign_info.front(); sign_info.pop_front();
        in_types = sign_info.front(); sign_info.pop_front();

        dds_topic_info * topic_info = new dds_topic_info(method, in_types, calling_object);
        this->output_list_.push_back((Writer *) topic_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        topic_info->insert (IPOINT_BEFORE, rtn, 0, 1, 2, 3, 4);
      }
    }

    virtual list_type & get_list(void) {
      return this->output_list_;
    }
  private:
    //output_list_ - the output list
    //datawriter_write_ - substring to identify the write method on publisher end
    //datareader_takenextsample_ - substring to identify take_next_sample method on subscriber end
    list_type output_list_;
    std::string datawriter_write_;
    std::string datareader_takenextsample_;
    std::string create_topic_;
  };
}
}

#endif // !DDS_MIDDLEWARE_H
