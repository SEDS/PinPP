/**
* Command class for various data types.
*
*/

#ifndef _DATA_TYPE_CMD_H_
#define _DATA_TYPE_CMD_H_

#include <string>
#include "pin++/Pintool.h"

class data_type_cmd
{
public:
  //Constructor
	data_type_cmd(void);

  virtual ~ data_type_cmd(void);

  virtual void execute (ADDRINT addr, std::string & str) = 0;
};

#endif