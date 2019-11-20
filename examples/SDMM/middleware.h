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
    
}
}

#endif // !SDMM_MIDDLEWARE_H
