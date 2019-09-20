#include "unsigned_short_cmd.h"

unsigned_short_cmd::unsigned_short_cmd (void)
{
}

unsigned_short_cmd::~unsigned_short_cmd (void)
{
}

void unsigned_short_cmd::execute (ADDRINT addr, std::ofstream & fout)
{
  fout << "  Return value: " << (unsigned short) addr << std::endl;
}