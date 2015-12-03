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

//float_cmd * data_type_cmd_factory::create_float_cmd ()
//{
//  return new float_cmd ();
//}
//
//short_cmd * data_type_cmd_factory::create_short_cmd ()
//{
//  return new short_cmd ();
//}