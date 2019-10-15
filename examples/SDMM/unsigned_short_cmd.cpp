#include "unsigned_short_cmd.h"

unsigned_short_cmd::unsigned_short_cmd (void)
{
}

unsigned_short_cmd::~unsigned_short_cmd (void)
{
}

void unsigned_short_cmd::execute (ADDRINT addr, std::string & str)
{
  std::string temp = std::to_string((unsigned short)addr);
  str.assign(temp);
}