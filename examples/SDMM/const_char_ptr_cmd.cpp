#include "const_char_ptr_cmd.h"

const_char_ptr_cmd::const_char_ptr_cmd (void)
{
}

const_char_ptr_cmd::~const_char_ptr_cmd (void)
{
}

void const_char_ptr_cmd::execute (ADDRINT addr, std::string & str)
{
  str.assign((const char*)addr);
}