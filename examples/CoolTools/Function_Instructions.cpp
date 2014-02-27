// $Id: Function_Instructions.cpp 2308 2013-10-07 15:23:19Z dfeiock $

#include "pin++/Image.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

class Function_Instructions : OASIS::Pin::Tool <Function_Instructions>
{
public:
  Function_Instructions (void)
  {
    this->init_symbols ();
  }

  int execute (void)
  {
    using OASIS::Pin::Image;
    using OASIS::Pin::Routine;
    using OASIS::Pin::Section;

    Image img = Image::open (inputfile_.Value ().c_str ());

    if (!img.valid ())
    {
      std::cout << "Could not open " << inputfile_.Value() << endl;
      exit (1);
    }

    std::cout <<
      std::setw (60) << "Routine" << std::setw (80) << "Instructions" << std::endl <<
      std::setw (60) << "------------------------------------------------------------" <<
      std::setw (80) << "--------------------" << std::endl;


    for (OASIS::Pin::Section section : img)
    {
      for (OASIS::Pin::Routine rtn : section)
      {
        int count = 0;

        OASIS::Pin::Routine_Guard guard (rtn);

        for (OASIS::Pin::Ins ins : rtn)
        {
          ++ count;
        }

        std::cout << std::setw (60) << rtn.name () << std::setw (80) << count << std::endl;
      }
    }

    img.close ();
    return 0;
  }

private:
  static KNOB <string> inputfile_;
};

KNOB <string> Function_Instructions::inputfile_ (KNOB_MODE_WRITEONCE, "pintool", "i", "<imagename>", "specify an image to read");

int main (int argc, char * argv [])
{
  return OASIS::Pin::Pintool <Function_Instructions> (argc, argv)->execute ();
}
