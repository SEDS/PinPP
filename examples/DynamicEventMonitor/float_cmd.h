/**
* Command class for const char * data types.
*
*/
#ifndef _FLOAT_CMD_H_
#define _FLOAT_CMD_H_

#include "data_type_cmd.h"

class float_cmd : public data_type_cmd
{
public:
  float_cmd (void);

  ~float_cmd (void);

  void execute (ADDRINT addr, std::ofstream & fout);
};

#endif
