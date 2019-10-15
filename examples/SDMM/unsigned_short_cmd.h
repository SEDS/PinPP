/**
* Command class for unsigned short data types.
*
*/
#ifndef _UNSIGNED_SHORT_CMD_H_
#define _UNSIGNED_SHORT_CMD_H_

#include "data_type_cmd.h"

class unsigned_short_cmd : public data_type_cmd
{
public:
  unsigned_short_cmd (void);

  ~unsigned_short_cmd (void);

  void execute (ADDRINT addr, std::string & str);
};

#endif