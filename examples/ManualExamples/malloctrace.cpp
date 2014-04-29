// $Id: malloctrace.cpp 2282 2013-09-17 13:38:10Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"

#include <fstream>

#if defined (TARGET_MAC)
  #define MALLOC "_malloc"
  #define FREE "_free"
#else
  #define MALLOC "malloc"
  #define FREE "free"
#endif

/**
 * @class Arg1_Before
 */
class Arg1_Before :
public OASIS::Pin::Callback <Arg1_Before (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>
{
public:
  Arg1_Before (std::ofstream & file, const char * name)
    : file_ (file),
      name_ (name)
  {

  }

  void handle_analyze (ADDRINT size)
  {
    this->file_ << this->name_ << "(" << size << ")" << std::endl;
  }

private:
  std::ofstream & file_;
  std::string name_;
};

/**
 * @class Malloc_After
 */
class Malloc_After :
public OASIS::Pin::Callback <Malloc_After (OASIS::Pin::ARG_FUNCRET_EXITPOINT_VALUE)>
{
public:
  Malloc_After (std::ofstream & file)
    : file_ (file)
  {
  }

  void handle_analyze (ADDRINT addr)
  {
    this->file_ << "  returns " << addr << std::endl;
  }

private:
  std::ofstream & file_;
};

/**
 * @class malloctrace
 */
class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  Instrument (std::ofstream & file)
    : file_ (file),
      free_before_ (file_, FREE),
      malloc_before_ (file_, MALLOC),
      malloc_after_ (file_)
  {
    this->file_ << std::hex;
    this->file_.setf (std::ios::showbase);
  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    // Instrument the malloc () and free () functions.  Print the input argument
    // of each malloc () or free (), and the return value of malloc ().
    //
    //  Find the malloc () function.
    OASIS::Pin::Routine rtn = img.find_routine (MALLOC);

    if (rtn.valid ())
    {
      OASIS::Pin::Routine_Guard guard (rtn);

      // Instrument malloc () to print the input argument value and the return value.
      this->malloc_before_.insert (IPOINT_BEFORE, rtn, 0);
      this->malloc_after_.insert (IPOINT_AFTER, rtn);
    }

    // Find the free () function.
    rtn = img.find_routine (FREE);

    if (rtn.valid ())
    {
      OASIS::Pin::Routine_Guard guard (rtn);
      this->free_before_.insert (IPOINT_BEFORE, rtn);
    }
  }

private:
  std::ofstream & file_;

  Arg1_Before free_before_;
  Arg1_Before malloc_before_;
  Malloc_After malloc_after_;
};

class malloctrace : public OASIS::Pin::Tool <malloctrace>
{
public:
  malloctrace (void)
    : file_ ("malloctrace.out"),
      inst_ (file_)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    this->file_.close ();
  }

private:
  std::ofstream file_;
  Instrument inst_;
};

DECLARE_PINTOOL (malloctrace);
