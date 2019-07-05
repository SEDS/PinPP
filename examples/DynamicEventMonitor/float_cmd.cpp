#include "float_cmd.h"

float_cmd::float_cmd (void)
{
}

float_cmd::~float_cmd (void)
{
}

void float_cmd::execute (ADDRINT addr, std::ofstream & fout)
{
  fout << "  Return value: "<< LEVEL_BASE::StringFlt (* (float *) addr, 2, 4) << std::endl;
}
