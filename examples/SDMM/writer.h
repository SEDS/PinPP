#include "pin.H"
#include <ostream>

#ifndef SDMM_WRITER_H
#define SDMM_WRITER_H

namespace OASIS {
namespace Pin {

    class Writer {
    public:
        virtual void write_to(std::ostream & out) = 0;
	virtual bool has_info(void) = 0;
    };

}
}

#endif // !SDMM_WRITER_H
