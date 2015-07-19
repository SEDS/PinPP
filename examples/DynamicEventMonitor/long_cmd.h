/**
* Command class for const char * data types.
*
*/
#ifndef _LONG_CMD_H_
#define _LONG_CMD_H_

#include "data_type_cmd.h"

class long_cmd : public data_type_cmd
{
public:
  long_cmd (void);

  ~long_cmd (void);

  void execute (unsigned long addr, std::ofstream & fout);
};

#endif