/**
* Command class for various data types.
*
*/

#ifndef _DATA_TYPE_CMD_H_
#define _DATA_TYPE_CMD_H_

#include <fstream>

class data_type_cmd
{
public:
  //Constructor
	data_type_cmd(void);

  virtual ~ data_type_cmd(void);

  virtual void execute (unsigned long addr, std::ofstream & fout) = 0;
};

#endif