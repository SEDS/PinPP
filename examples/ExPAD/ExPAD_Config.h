#ifndef _EXPAD_CONFIG_H_
#define _EXPAD_CONFIG_H_

#include <string>
#include <set>
#include <map>

class ExPAD_Config
{
public:
  /// Constructor
  ExPAD_Config (void);

  /// Destructor
  ~ExPAD_Config (void);

  /// Read and parse the configuration file using boost
  bool read_config (const std::string & conf_file);

  /// Check whether the routine needs to be inckuded in the instrumentation
  bool ignore_routine (std::string & image_name, std::string & func_name);

  /// Add to the dll inlcudes
  void insert_to_dll_includes (std::string & dll_name);

  ///Add to the function includes
  void insert_to_function_includes (std::string & dll_name, std::string & func_name);

private:

  /// type definitions
  typedef std::set <std::string> STRING_SET;

  typedef std::map <std::string, STRING_SET> FUNCTIONS;
  
  STRING_SET dll_includes_;

  FUNCTIONS function_includes_;
};

#include "ExPAD_Config.inl"

#endif