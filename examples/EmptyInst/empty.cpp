#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include <iostream>

class empty : public OASIS::Pin::Tool <empty>
{
public:
  empty (void)
  {
    //this->init_symbols ();
    //this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  { }

};

DECLARE_PINTOOL (empty);
