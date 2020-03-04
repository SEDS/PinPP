#include "data_type_cmd_factory.h"

data_type_cmd_factory::data_type_cmd_factory (void)
{
}

data_type_cmd_factory::~data_type_cmd_factory (void)
{
}

const_char_ptr_cmd * data_type_cmd_factory::create_const_char_ptr_cmd ()
{
  return new const_char_ptr_cmd ();
}

long_cmd * data_type_cmd_factory::create_long_cmd ()
{
  return new long_cmd ();
}

unsigned_short_cmd * data_type_cmd_factory::create_unsigned_short_cmd ()
{
  return new unsigned_short_cmd ();
}