#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include <iostream>

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  { }
};

class empty : public OASIS::Pin::Tool <empty>
{
public:
  empty (void)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  { }

private:
  Instrument inst_;
};

DECLARE_PINTOOL (empty);
