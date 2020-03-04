#include "short_cmd.h"

short_cmd::short_cmd (void)
{
}

short_cmd::~short_cmd (void)
{
}

void short_cmd::execute (ADDRINT addr, std::ofstream & fout)
{
  fout << "  Return value: " << (short) addr << std::endl;
}