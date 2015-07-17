/**
* Command class for various data types.
*
*/

#ifndef _DATA_TYPE_CMD_H_
#define _DATA_TYPE_CMD_H_

class data_type_cmd
{
  //friend class data_type_cmd_factory;
public:
  //Constructor
	data_type_cmd(void);

  virtual ~ data_type_cmd(void);

  virtual const char * execute (unsigned long addr) = 0;
};

#endif