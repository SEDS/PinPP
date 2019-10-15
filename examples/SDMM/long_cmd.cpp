#include "long_cmd.h"

long_cmd::long_cmd (void)
{
}

long_cmd::~long_cmd (void)
{
}

void long_cmd::execute (ADDRINT addr, std::string & str)
{
  std::string temp = std::to_string((long)addr);
  str.assign(temp);
}