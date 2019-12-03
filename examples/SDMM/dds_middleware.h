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

  class dds_method_info : public OASIS::Pin::Callback <dds_method_info (void)>, public Writer {
  public:
    dds_method_info (std::string signature, std::string call_object)
      : sign_(signature),
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

  class DDS_Middleware : public Middleware {
  public:
    DDS_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :datawriter_write_("::write("),
      datareader_takenextsample_("::take_next_sample(")
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
      if (signature.find(datawriter_write_) != std::string::npos && signature.find("DataWriterImpl_T") != std::string::npos) {
        calling_object = std::string("OpenDDS::DCPS::DataWriterImpl_T<Messenger::Message>");
      }

      if (signature.find(datareader_takenextsample_) != std::string::npos) {
        calling_object = std::string("OpenDDS::DCPS::DataReaderImpl_T<Messenger::Message>");
      }

        dds_method_info * dds_info = new dds_method_info(signature, calling_object);
        this->output_list_.push_back((Writer *) dds_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        dds_info->insert (IPOINT_BEFORE, rtn);
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
  };
}
}

#endif // !DDS_MIDDLEWARE_H
