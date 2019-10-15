#include "sdmm_tool.h"
typedef OASIS::Pin::CORBA CORBA;
typedef OASIS::Pin::gRPC gRPC;

int main (int argc, char * argv []) {
    OASIS::Pin::Pintool <OASIS::Pin::SDMM_Tool<gRPC>>(argc, argv).start_program();
    return 0;
}
