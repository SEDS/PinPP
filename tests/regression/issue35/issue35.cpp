#include "pin++/Image_Instrument.h"
#include "pin++/Tool.h"
#include "pin++/Pintool.h"

#include <iostream>

#define TEST_RESULT(condition, message) \
  std::cerr << message << ": " << (condition ? "PASSED" : "FAILED") << std::endl;

class instrument : public OASIS::Pin::Image_Instrument <instrument>
{
public:
  instrument (void)
    : count_ (0) { }
  
  void handle_instrument (const OASIS::Pin::Image & img)
  {
#if defined TARGET_WINDOWS
    static const std::string ending = "program.exe";
#else
    static const std::string ending = "program";
#endif
    
    if (std::equal (ending.rbegin (), ending.rend (), img.name ().rbegin ()))
    {
      for (OASIS::Pin::Section sec : img)
        for (OASIS::Pin::Routine rtn : sec)
        {
          cerr << rtn.name () << std::endl;
          ++ this->count_;
        }
    }
  }
  
  size_t count (void) const
  {
    return this->count_;
  }
  
private:
  size_t count_;
};

class issue35 : public OASIS::Pin::Tool <issue35>
{
public:
  issue35 (void)
  {
    this->enable_fini_callback ();
  }
  
  void handle_fini (INT32 retcode)
  {
#if defined TARGET_MAC
    this->assert_equals (static_cast <size_t> (5), this->instrument_.count (), "Counting number of routines");
#endif
  }
  
private:
  template <typename T>
  void assert_equals (T expected, T actual, const std::string & msg)
  {
    std::cerr << msg << ": ";
    
    if (expected == actual)
      std::cerr << "passed" << std::endl;
    else
      std::cerr << "failed; expected <" << expected << "> but got <" << actual << ">" << std::endl;
  }
  
  instrument instrument_;
  
};

DECLARE_PINTOOL (issue35)
