/**
* Factory class for various data type commands.
*
*/
#ifndef _DATA_TYPE_CMD_FACTORY_H_
#define _DATA_TYPE_CMD_FACTORY_H_

#include "data_type_cmd.h"
#include "const_char_ptr_cmd.h"

class data_type_cmd_factory
{
  //friend class const_char_ptr_cmd;
public:
   data_type_cmd_factory(void);

   ~ data_type_cmd_factory (void);

   const_char_ptr_cmd * create_const_char_ptr_cmd ();
};

#endif