#include "sdmm_tool.h"

int main (int argc, char * argv []) {
    OASIS::Pin::Pintool <OASIS::Pin::SDMM_Tool>(argc, argv).start_program();
    return 0;
}
