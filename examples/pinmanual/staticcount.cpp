// $Id: staticcount.cpp 2278 2013-09-15 20:12:52Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"

#include <iostream>

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    int count = 0;

    for (OASIS::Pin::Section section : img)
    {
      for (OASIS::Pin::Routine & rtn : section)
      {
        OASIS::Pin::Routine_Guard guard (rtn);

        for (OASIS::Pin::Ins & ins : rtn)
          ++ count;
      }
    }

    std::cerr << "Image " << img.name () << " has " << count << " instructions" << std::endl;
  }
};

class staticcount : public OASIS::Pin::Tool <staticcount>
{
public:
  staticcount (void) { }
  
private:
  Instrument inst_;
};

DECLARE_PINTOOL (staticcount);
