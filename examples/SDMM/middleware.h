#include "pin++/Image.h"
#include "pin++/Routine.h"

#ifndef SDMM_MIDDLEWARE_H
#define SDMM_MIDDLEWARE_H

namespace OASIS {
namespace Pin {
    
    class Middleware {
    public:
        virtual void handle_helpers(const OASIS::Pin::Image & img) = 0;
        virtual void analyze_img(const OASIS::Pin::Image & img) = 0;
        virtual void analyze_rtn(const OASIS::Pin::Routine & rtn) = 0;
    };
    
}
}

#endif // !SDMM_MIDDLEWARE_H
