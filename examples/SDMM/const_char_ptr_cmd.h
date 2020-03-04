/**
* Command class for const char * data types.
*
*/
#ifndef _CONST_CHAR_PTR_CMD_H_
#define _CONST_CHAR_PTR_CMD_H_

#include "data_type_cmd.h"

class const_char_ptr_cmd : public data_type_cmd
{
public:
  const_char_ptr_cmd (void);

  ~const_char_ptr_cmd (void);

  void execute (ADDRINT addr, std::string & str);
};

#endif