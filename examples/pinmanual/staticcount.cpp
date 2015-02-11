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

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
	for each (OASIS::Pin::Section & section in img)
#else
    for (OASIS::Pin::Section section : img)
#endif
    {
#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
	    for each (OASIS::Pin::Routine & rtn in section)
#else
      for (OASIS::Pin::Routine & rtn : section)
#endif
      {
        OASIS::Pin::Routine_Guard guard (rtn);

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
        for each (OASIS::Pin::Ins & ins in rtn)
#else
        for (OASIS::Pin::Ins & ins : rtn)
#endif
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
