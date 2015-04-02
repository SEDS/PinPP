#include "pin++/Image_Instrument.h"
#include "pin++/Tool.h"
#include "pin++/Pintool.h"

#include <iostream>
#include <algorithm>

#define TEST_RESULT(condition, message) \
std::cerr << message << ": " << (condition ? "PASSED" : "FAILED") << std::endl;

class instrument : public OASIS::Pin::Image_Instrument <instrument>
{
public:
  instrument (void)
  : forward_count_ (0),
    reverse_count_ (0)
  {
  
  }
  
  void handle_instrument (const OASIS::Pin::Image & img)
  {
#if defined (TARGET_WINDOWS)
    static const std::string ending = "program.exe";
#else
    static const std::string ending = "program";
#endif
    
    if (std::equal (ending.rbegin (), ending.rend (), img.name ().rbegin ()))
    {
      // Count the number of instructions forward.
      
      std::for_each (img.begin (), img.end (), [&] (OASIS::Pin::Section sec) {
        std::for_each (sec.begin (), sec.end (), [&] (OASIS::Pin::Routine rtn) {
          OASIS::Pin::Routine_Guard guard (rtn);
          
          std::for_each (rtn.begin (), rtn.end (), [&] (OASIS::Pin::Ins ins) {
            ++ this->forward_count_;
          });
        });
      });
      
      // Count the number of instructions backwards.
                     
      std::for_each (img.rbegin (), img.rend (), [&] (OASIS::Pin::Section sec) {
        std::for_each (sec.rbegin (), sec.rend (), [&] (OASIS::Pin::Routine rtn) {
          OASIS::Pin::Routine_Guard guard (rtn);
          
          std::for_each (rtn.rbegin (), rtn.rend (), [&] (OASIS::Pin::Ins ins) {
            ++ this->reverse_count_;
          });
        });
      });
    }
  }
  
  size_t forward_count (void) const
  {
    return this->forward_count_;
  }
  
  size_t reverse_count (void) const
  {
    return this->reverse_count_;
  }
  
private:
  size_t forward_count_;
  size_t reverse_count_;
};

class issue38 : public OASIS::Pin::Tool <issue38>
{
public:
  issue38 (void)
  {
    this->enable_fini_callback ();
  }
  
  void handle_fini (INT32 retcode)
  {
    this->assert_equals (this->instrument_.forward_count (),
                         this->instrument_.reverse_count (),
                         "Counting number of instructions forward and reverse");
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

DECLARE_PINTOOL (issue38)
