#ifndef _EXPAD_CONFIG_H_
#define _EXPAD_CONFIG_H_

#include <string>
#include <set>
#include <map>

class ExPAD_Config
{
public:
  
  ExPAD_Config (void);

  ~ExPAD_Config (void);

  bool read_config (void);

  bool ignore_routine (std::string & image_name, std::string & func_name);

  void insert_to_dll_excludes (std::string & dll_name);

  void insert_to_function_excludes (std::string & dll_name, std::string & func_name);

private:

  typedef std::set <std::string> STRING_SET;

  typedef std::map <std::string, STRING_SET> FUNCTIONS;
  
  STRING_SET dll_excludes_;

  FUNCTIONS function_excludes_;
};

#endif