#include "pin++/Image.h"
#include "pin++/Routine.h"
#include "writer.h"
#include <list>
#include <string>

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
    
}
}

#endif // !SDMM_MIDDLEWARE_H
