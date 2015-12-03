#include "long_cmd.h"

long_cmd::long_cmd (void)
{
}

long_cmd::~long_cmd (void)
{
}

void long_cmd::execute (ADDRINT addr, std::ofstream & fout)
{
  fout << "  Return value: " << (long) addr << std::endl;
}