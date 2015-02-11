// $Id: statica.cpp 2308 2013-10-07 15:23:19Z dfeiock $

#include "pin++/Image.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

typedef struct
{
  ADDRINT start;
  ADDRINT end;
} RTN_INTERNAL_RANGE;

vector <RTN_INTERNAL_RANGE> rtn_internal_range_list;

class statica : OASIS::Pin::Tool <statica>
{
public:
  int execute (void)
  {
    using OASIS::Pin::Image;
    using OASIS::Pin::Routine;
    using OASIS::Pin::Section;
    using OASIS::Pin::Tool;

    Image img = Image::open (inputfile_.Value ().c_str ());

    if (!img.valid ())
    {
      std::cout << "Could not open " << inputfile_.Value() << endl;
      exit (1);
    }

    std::cout << hex;
    rtn_internal_range_list.clear ();

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
   for each (OASIS::Pin::Section & section in img)
#else
   for (OASIS::Pin::Section & section : img)
#endif
    {
      std::cout << "Section: " << std::setw (8) << section.address () << " " << section.name () << std::endl;

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
      for each (OASIS::Pin::Routine & rtn in section)
#else
      for (OASIS::Pin::Routine rtn : section)
#endif
      {
        std::cout << "  Rtn: " << std::setw (8) << hex << rtn.address () << " " << rtn.name () << endl;

        std::string path;
        INT32 line;

        this->get_source_location (rtn.address (), 0, &line, &path);

        if (path != "")
          std::cout << "File " << path << " Line " << line << std::endl;

        using OASIS::Pin::Ins;
        OASIS::Pin::Routine_Guard guard (rtn);

        Ins::iterator_type ins_iter = rtn.begin ();

        if (!ins_iter->is_valid ())
          continue;

        RTN_INTERNAL_RANGE rtn_internal_range;
        rtn_internal_range.start = ins_iter->address ();
        rtn_internal_range.end = rtn_internal_range.start + ins_iter->size ();

        Ins::iterator_type last_ins (Ins::invalid);

        for (Ins::iterator_type ins_iter_end = ins_iter.make_end ();
             ins_iter != ins_iter_end;
             ++ ins_iter)
        {
          std::cout << "    " << std::setw(8) << hex << ins_iter->address () << " " << ins_iter->disassemble () << endl;

          if (last_ins->valid ())
          {
            ADDRINT last_addr = last_ins->address ();
            ADDRINT curr_addr = ins_iter->address ();

            USIZE last_size = last_ins->size ();
            USIZE curr_size = ins_iter->size ();

            if (last_addr + last_size == curr_addr)
            {
              rtn_internal_range.end = curr_addr + curr_size;
            }
            else
            {
              rtn_internal_range_list.push_back (rtn_internal_range);
              std::cout
                << "  rtn_internal_range_list.push_back "
                << std::setw(8) << std::hex << rtn_internal_range.start << " "
                << std::setw(8) << std::hex << rtn_internal_range.end << std::endl;

              // make sure this ins has not already appeared in this RTN
              for (vector <RTN_INTERNAL_RANGE>::iterator ri = rtn_internal_range_list.begin ();
                   ri != rtn_internal_range_list.end ();
                   ++ ri)
              {
                if ((curr_addr >= ri->start) && (curr_addr < ri->end))
                {
                  std::cout << "***Error - above instruction already appeared in this RTN\n";

                  std::cout
                    << "  in rtn_internal_range_list "
                    << std::setw(8) << std::hex << ri->start << " "
                    << std::setw(8) << std::hex << ri->end << std::endl;

                  exit (1);
                }
              }

              rtn_internal_range.start = curr_addr;
              rtn_internal_range.end = curr_addr + curr_size;
            }
          }

          last_ins = ins_iter;
        }

        rtn_internal_range_list.clear();
      }
    }

    img.close ();
    return 0;
  }

private:
  static KNOB <string> inputfile_;
};

KNOB <string> statica::inputfile_ (KNOB_MODE_WRITEONCE, "pintool", "i", "<imagename>", "specify an image to read");

int main (INT32 argc, CHAR ** argv)
{
  return OASIS::Pin::Pintool <statica> (argc, argv)->execute ();
}
