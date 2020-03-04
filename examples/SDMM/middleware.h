#include "pin++/Image.h"
#include "pin++/Routine.h"
#include "writer.h"
#include <list>
#include <string>
#include <mutex>

#ifndef SDMM_MIDDLEWARE_H
#define SDMM_MIDDLEWARE_H

namespace OASIS {
namespace Pin {
    
class Middleware {
public:
	typedef std::list <Writer *> list_type;

	virtual ~Middleware(void) {}
	virtual std::string name(void) = 0;
	virtual void handle_helpers(const OASIS::Pin::Image & img) = 0;
	virtual void analyze_img(const OASIS::Pin::Image & img) = 0;
	virtual void analyze_rtn(const OASIS::Pin::Routine & rtn) = 0;
	virtual list_type & get_list(void) = 0;
};

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
  static time_accumulator accum_data_coll;

  //parse_signature - parses a Pin method signature and return
  //a list of strings with the calling object, the invoked method, and
  //the list of input types.
  std::list<std::string> parse_signature(std::string & sign) {
    std::list<std::string> parsed_list;
    std::string object("");
    std::string method("");
    std::string in_types("");
    size_t i = 0;

    //parse up to "(" for the object + method name
    for (; sign[i] != '('; ++i) {
      object += sign[i];
    }

    //skip the '('
    ++i;

    //extract input types
    for (; sign[i] != ')'; ++i) {
      in_types += sign[i];
    }

    //remove method name from object
    std::string temp("");
    for (i=object.length(); object[i] != ':'; --i) {
      temp += object[i];
      object[i] = ' ';
    }

    //remove last "::" from object
    object[i] = ' ';
    object[i-1] = ' ';

    //reverse method name to correct order
    for (i=temp.length(); i > 0; --i) {
      method += temp[i];
    }

    //add into list
    parsed_list.push_back(object);
    parsed_list.push_back(method);
    parsed_list.push_back(in_types);

    return parsed_list;
  }
    
}
}

#endif // !SDMM_MIDDLEWARE_H
