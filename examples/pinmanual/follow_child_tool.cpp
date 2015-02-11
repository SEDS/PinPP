// $Id: follow_child_tool.cpp 2274 2013-09-11 18:39:11Z dfeiock $

#include "pin++/Tool.h"
#include "pin++/Pintool.h"

#include <iostream>

class follow_child_tool : public OASIS::Pin::Tool <follow_child_tool>
{
public:
  follow_child_tool (void)
  {
    this->enable_follow_child_process_callback ();
  }

  BOOL handle_follow_child_process (CHILD_PROCESS child)
  {
    std::cout << "before child: " << this->get_pid () << std::endl;
    return true;
  }
};

DECLARE_PINTOOL (follow_child_tool);
