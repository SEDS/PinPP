/**
* Command class for short data types.
*
*/
#ifndef _SHORT_CMD_H_
#define _SHORt_CMD_H_

#include "data_type_cmd.h"

class short_cmd : public data_type_cmd
{
public:
  short_cmd (void);

  ~short_cmd (void);

  void execute (ADDRINT addr, std::ofstream & fout);
};

#endif
