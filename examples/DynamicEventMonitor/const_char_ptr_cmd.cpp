#include "const_char_ptr_cmd.h"

const_char_ptr_cmd::const_char_ptr_cmd (void)
{
}

const_char_ptr_cmd::~const_char_ptr_cmd (void)
{
}

const char * const_char_ptr_cmd::execute (unsigned long addr)
{
  return (const char *) addr;
}