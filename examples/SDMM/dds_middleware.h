#include "pin++/Callback.h"
#include "pin++/Image.h"
#include "pin++/Section.h"
#include "middleware.h"
#include "writer.h"

//Path to ADT definition
#include "/home/nyalia/OpenDDS-3.13.3/DevGuideExamples/DCPS/Messenger/MessengerC.h"

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

  class write_info : public OASIS::Pin::Callback <write_info (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
  OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>, public Writer {
  public:
    write_info (std::string signature, std::string call_object)
      :sign_(signature),
      obj_(call_object),
      count_(0)
    { }

    void handle_analyze (ADDRINT arg1, ADDRINT arg2) {
      std::clock_t start = std::clock ();
	std::cout << "here" << std::endl;
	const Messenger::Message* ptr = (const Messenger::Message*)arg1;
      Messenger::Message msg;
      msg = *ptr;
      values_.push_back(msg);
      ++this->count_;
      std::clock_t end = std::clock ();
      double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
      accum_meth_info.increase(time);
    }

    virtual void write_to(std::ostream & out) {
      out << "{"
      << "\"Values\": [";
	
      for (Messenger::Message &item : this->values_) {
        out << "{ \"Subject\": \"" << item.subject.in() << "\","
        << "\"SubjectId\": " << item.subject_id << ","
        << "\"From\": \"" << item.from.in() << "\","
        << "\"Count\": " << item.count << ","
        << "\"Text\": \"" << item.text.in() << "\"},";
      }

      out << "], \"Method\": \"" << this->sign_ << "\","
      << "\"Object\": \"" << this->obj_ << "\","
      << "\"CallCount\": " << this->count_ << "}"; 
    }

    virtual bool has_info(void) {
      return count_;
    }

  private:
    std::list<Messenger::Message> values_;
    std::string sign_;
    std::string obj_;
    UINT64 count_;
  };

  class DDS_Middleware : public Middleware {
  public:
    DDS_Middleware(std::vector<std::string> & method_list, std::string & obv)
      :datawriter_write_("write(Messenger::Message const&, int)")
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
      if (signature.find(datawriter_write_) != std::string::npos) {
        calling_object = std::string("OpenDDS::DCPS::DataWriterImpl_T<Messenger::Message>");

        write_info *w_info = new write_info(signature, calling_object);
        this->output_list_.push_back ((Writer *) w_info);

        OASIS::Pin::Routine_Guard guard (rtn);
        w_info->insert (IPOINT_BEFORE, rtn, 0, 1);
      }
    }

    virtual list_type & get_list(void) {
      return this->output_list_;
    }
  private:
    //output_list_ - the output list
    //datawriter_write_ - substring to identify the DataWriter.write() method used to publish data to a
    //Topics repository.
    list_type output_list_;
    std::string datawriter_write_;
  };
}
}

#endif // !DDS_MIDDLEWARE_H
