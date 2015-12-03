#include "const_char_ptr_cmd.h"

const_char_ptr_cmd::const_char_ptr_cmd (void)
{
}

const_char_ptr_cmd::~const_char_ptr_cmd (void)
{
}

void const_char_ptr_cmd::execute (ADDRINT addr, std::ofstream & fout)
{
  fout << "  Return value: " << (const char *) addr << std::endl;
}