/**
* Pintool that dynamically instrument the target method call.
* 2014.07
*
*/



/*******************************
* Dependencies
*******************************/
//#ifdef WIN32
   // #include <Windows.h>
//#else
    //#include <unistd.h>
//#endif

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Callback.h"
#include "pin++/Routine.h"
#include "pin++/Symbol.h"
#include "pin++/Buffer.h"
#include "pin++/Copy.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <time.h>

#include "data_type_cmd.h"
#include "data_type_cmd_factory.h"

#include <fstream>

/*******************************
* Type definitions
*******************************/

// map between name of the target method and the event type passed into it
typedef std::unordered_map <std::string, std::string> method_event_map_type;

// map between event type and its helper methods
typedef std::unordered_map <std::string, ADDRINT> helper_addr_map_type;
typedef std::unordered_multimap <std::string, helper_addr_map_type> event_helper_map_type;

// map between helper and return type.
typedef std::unordered_map <std::string, data_type_cmd *> helper_returntype_map_type;

/*******************************
* Analysis routine
*******************************/

/**
* Analysis routine that executes a helper method.
*/
class Event_Monitor : public OASIS::Pin::Callback <Event_Monitor (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)> //, OASIS::Pin::ARG_CONTEXT)>
{
public:
  Event_Monitor ()
    : fout_ (0),
    method_event_map_ (0),
    helper_return_type_map_ (0),
    eventtrace_ (0)
  {
  }
  /**
  * Analysis routine.
  */
  void handle_analyze (ADDRINT object_addr) //, OASIS::Pin::Context & ctx)
  {
    if (object_addr == 0)
    {
      if (logs_required_)
        *fout_ << "..Error: the object passed in is null." << std::endl;

      return;
    }
    // check the existence of the helper methods
    method_event_map_type::iterator push_event_iter = method_event_map_->find (target_name_);
    if (push_event_iter == method_event_map_->end ())
    {
      if (logs_required_)
        *fout_ << "..Error: push method '" << target_name_ << "' not registered." << std::endl;

      return;
    }

    std::string event_type = push_event_iter->second;

    if (logs_required_)
      *fout_ << "..Intercepted a push method call '" << target_name_ << "' with event type '" << event_type << "'" << std::endl;

    helper_methods_execution (event_type, object_addr);
  }

  /**
  * Execute all the helper methods for the target object
  *
  * @param[in]      addr_map         map of class name and helper method address
  * @param[in]      class_name       class name of the target object
  * @param[in]      object_addr      address of the target object
  */
  void helper_methods_execution (std::string event_type, ADDRINT object_addr) //, OASIS::Pin::Context & ctx)
  {
    // Find all the helper addr map for the event
    std::pair <std::unordered_multimap <std::string, helper_addr_map_type>::iterator,
      std::unordered_multimap <std::string, helper_addr_map_type>::iterator> it;

    it = event_helper_map_->equal_range (event_type);

    // Iterate through all the helpers found.
    std::unordered_multimap <std::string, helper_addr_map_type> ::iterator event_helper_it;
    for (event_helper_it = it.first; event_helper_it != it.second; ++ event_helper_it)
    {
      helper_addr_map_type helper_addr_map = event_helper_it->second;

      for (auto method : helper_addr_map)
      {
        ADDRINT helper_addr = method.second;
        ADDRINT result_addr = 0;

        // Create a command for the return type.
        data_type_cmd * cmd = (*helper_return_type_map_)[method.first];

        if (logs_required_)
          *fout_ << "  Method: " << method.first << std::endl;

        asm volatile(
          "mov %1, %%ecx\n"
          "call *%2\n"
          "mov %%eax, %0\n"
          : "=r" (result_addr)
          : "r" (object_addr), "r" (helper_addr)
          : "%eax", "%ecx"
        );

        /* Print to even trace the following:
         * Current date time
         * Severity
         * Host Name
         * Thread id
         * Message
         **/
        char machine_name [150];
        *eventtrace_ << "Date Time : " << current_date_time () 
                      << " Severity : 16854 " 
                      //<< get_machine_name (machine_name);
                      << " Thread id : " << PIN_GetTid ()
                      << " Component : " << get_component_name () 
                      << " Event : " << event_type
                      << " Element : " << method.first << std::endl; 

        if (cmd != 0)
        {
          cmd->execute (result_addr, *eventtrace_);

          if (logs_required_)
            cmd->execute (result_addr, *fout_);
        }          
      }
    }
    /*
    else
    {
    if (DEBUG)
    *fout_ << "..No helper method found." << std::endl;
    }*/
  }

  /**
  * Get the current date time in string format
  */
  const std::string current_date_time ()
  {
    time_t now = time (0);
    struct tm tstruct;
    char buf[50];
    tstruct = *localtime(&now);
    strftime (buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
  }

  /**
  * Get the host name 
  */
  //void get_machine_name (char * machine_name)
  //{
  //  char name [150];

  //  #ifdef WIN32
  //    char info[150];
  //    unsigned long buf_char_count = 150;
  //    memset (name, 0, 150);
  //    if (GetComputerName (info, &buf_char_count));
  //    {
  //      for (int i = 0; i < 150; ++ i)
  //        name[i] = info[i];
  //    }
  //    else
  //    {
  //      strcpy (name, "Unknown_Host_Name");
  //    }
  //  #else
  //    memset (name, 0, 150)
  //    gethostname (name, 150);
  //  #endif

  //    strncpy (machine_name, name, 150);
  //}

  /**
  * Setter for the name of the push_ method to be instrumentated.
  */
  void set_target_name (std::string name)
  {
    target_name_.assign (name);
  }

  /**
  * Getter for the name of the target method to be instrumentated.
  *
  * @return      returns the name of the target method call.
  */
  std::string get_target_name (void)
  {
    return target_name_;
  }

  /**
  * Getter for the name of the target method to be instrumentated.
  *
  * @return      returns the name of the target method call.
  */
  std::string get_method_name (void)
  {
    size_t separator = target_name_.find ("::");
    return target_name_.substr (separator + 2, target_name_.length () - separator - 2);
  }

  /**
  * Getter for the name of the component of the target method to be instrumentated.
  *
  * @return      returns the name of the layer.
  */
  std::string get_component_name (void)
  {
    size_t separator1 = target_name_.find ("::");
    size_t separator2 = target_name_.rfind ("_", separator1);
    return target_name_.substr (0, separator2);
  }

   /**
  * Setter for ofstream pointer of log file
  */
  void set_logfile (std::ofstream & fout)
  {
    fout_ = &fout;
  }

  /**
  * Setter for ofstream pointer of event trace
  */
  void set_eventtrace (std::ofstream & eventtrace)
  {
    eventtrace_ = &eventtrace;
  }

  /**
  * Setter for method event map
  */
  void set_method_event_map (method_event_map_type & method_event_map)
  {
    method_event_map_ = & method_event_map;
  }

  /**
  * Setter for event helper map
  */
  void set_event_helper_map (event_helper_map_type & event_helper_map)
  {
    event_helper_map_ = & event_helper_map;
  }

  /**
  * Setter for helper and return type map
  */
  void set_helper_returntype_map (helper_returntype_map_type & helper_return_type_map)
  {
    helper_return_type_map_ = & helper_return_type_map;
  }

  /**
  * Setter for logs required
  */
  void set_logs_required (bool logs_required)
  {
    logs_required_ = logs_required;
  }

private:
  std::string target_name_;

  // File name to write output
  std::ofstream * fout_;

  // File to write event trace
  std::ofstream * eventtrace_;

  // Map between events and methods
  method_event_map_type * method_event_map_;

  // Map between event and helper
  event_helper_map_type * event_helper_map_;

  // Map between helper and its return type
  helper_returntype_map_type * helper_return_type_map_;

  // Logs required
  bool logs_required_;
};



/*******************************
* Instrument
*******************************/

/**
* Image level instrument.
*/
class Image_Inst : public OASIS::Pin::Image_Instrument <Image_Inst>
{
public:

  // Constructor
  Image_Inst (ofstream & fout, 
              std::ofstream & eventtrace,
              method_event_map_type & method_event_map,
              std::vector<string> & target_method_list,
              std::vector<string> & include_list,
              std::vector<string> & exclude_list,
              std::vector<string> & helper_list,
              std::string & obv,
              event_helper_map_type & event_helper_map,
              bool & logs_required)
    :fout_ (fout),
    eventtrace_ (eventtrace),
    method_event_map_ (method_event_map),
    target_method_list_ (target_method_list),
    include_list_ (include_list),
    exclude_list_ (exclude_list),
    helper_list_ (helper_list),
    obv_ (obv),
    helper_image_loaded_ (false),
    event_helper_map_ (event_helper_map),
    logs_required_ (logs_required)
  {
    
  }

private:
  enum RTN_TYPE {SIGNATURE, METHOD_CALL, INVALID};

public:
  /**
  * Instrument routine.
  *
  * @param[auto]      img      the image to be instrumented
  */
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    int push_method_count = 0;

    size_t separator = std::string::npos;

    // The first iteration looks for target method signatures, method calls and their associated event types
    // In the include list.
    for (auto include : include_list_)
    {
      separator = img.name ().find (include);
      if (separator != std::string::npos)
      {
        if (logs_required_)
          fout_ << "Finding push method in " << img.name () <<std::endl;

        for (auto sec : img) 
        {
          for (auto rtn : sec)
          {
            if (!rtn.valid ())
              continue;

            std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);        
            std::string rtn_name = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_NAME_ONLY);

            RTN_TYPE rtn_type = is_valid_push_method (rtn_signature);
            
            // the routine is merely a target method signature; map it with its event type
            if (rtn_type == SIGNATURE)
            {
              ++ push_method_count;
              std::string event_type = get_push_event_type (rtn_signature);
              method_event_map_[rtn_name] = event_type;
              event_list[event_type] = true;

              if (helper_image_loaded_)
                check_and_register_valid_helper_method ();

              if (logs_required_)
              {
                fout_ << "Signature found: " << std::endl;
                fout_ << "Image: " << img.name () << std::endl;
                fout_ << "Sign: " << rtn_signature << std::endl;
                fout_ << "Name: " << rtn_name << std::endl;
                fout_ << "Associated event type: " << event_type << std::endl;
                fout_ << std::endl;
              }
            }
            // the routine is an actual method call; insert the analysis routine
            else if (rtn_type == METHOD_CALL)
            {
              OASIS::Pin::Routine_Guard guard (rtn);
              // buffers must be used; otherwise the analysis routine cannot be preserved
              item_type helper_buffer (1);
              item_type::iterator helper = helper_buffer.begin ();
              helper->set_target_name (rtn_name);
              helper->set_logs_required (logs_required_);
              helper->set_logfile (fout_);
              helper->set_eventtrace (eventtrace_);
              helper->set_method_event_map (method_event_map_);
              helper->set_event_helper_map (event_helper_map_);
              helper->set_helper_returntype_map (helper_returntype_map_);
              helper->insert (IPOINT_BEFORE, rtn, 0);
              analysis_rtn_buffer_list_.push_back (helper_buffer);

              if (logs_required_)
              {
                fout_ << "Method call found: " << std::endl;
                fout_ << "Image: " << img.name () << std::endl;
                fout_ << "Sign: " << rtn_signature << std::endl;
                fout_ << "Name: " << rtn_name << std::endl;
                fout_ << std::endl;
              }
            }
          }
        }
      }
    }

    // Load methods from the helper class.
    size_t sep = std::string::npos;
    for (auto helper : helper_list_)
    {
      sep = img.name ().find (helper);
      if (sep != std::string::npos)
      {
        if (logs_required_)
          fout_ << "Finding helper method in " << img.name () <<std::endl;

        // Load the methods and address from helper image, so that we can process when we discover events laters.
        load_helper_image_methods (img);

        helper_image_loaded_ = true;
      }
    }
  }

  /**
  * Determine whether the passed in routine is a valid target method, and further
  * if it is an actual method call, or merely a signature.
  *
  * @param[in]      rtn_signature      a complete and undecorated routine name
  * @retval         INVALID            not a valid target method
  * @retval         SIGNATURE          a signature, not a real method call
  * @retval         METHOD_CALL        real method call
  */
  RTN_TYPE is_valid_push_method (std::string rtn_signature)
  {
    size_t separator = std::string::npos;
    for (auto method : target_method_list_)
    {
      separator = rtn_signature.find ("::" + method);
      if (separator != std::string::npos)
        break;
    }

    if (separator == std::string::npos)
      return INVALID;

    if (rtn_signature.find ("(", separator) != std::string::npos)
      return SIGNATURE;
    else
      return METHOD_CALL;
  }

  /**
  * Get the type of the object passed into the routine method with the signature rtn_signature.
  *
  * @param[in]      rtn_signature      complete routine name
  * @param[in]      rtn_name           concise routine name
  * @return         returns the type of the object passed into the routine method
  */
  std::string get_push_event_type (std::string rtn_signature)
  {
    size_t start = rtn_signature.find ("(class ") + 7;
    size_t end = rtn_signature.find (" ", start);
    return rtn_signature.substr (start, end - start);
  }

  /**
  * Check if the accessor method exists in the helper_methods_map and
  * register it with events that do not have helper methods registered.
  */
  void check_and_register_valid_helper_method ()
  {
    for (auto rtn : helper_methods_map)
    {
      std::string rtn_signature = rtn.first;
      ADDRINT rtn_addr = rtn.second;

      size_t separator = rtn_signature.rfind ("::");
      if (separator == std::string::npos)
        continue;

      std::string event_type = rtn_signature.substr (0, separator);

      // Find Object by value (obv) prefix in the event type. 
      // If it is not found, then default to OBV_, which is obv prefix for TAO middleware
      size_t obv_sep;

      if (!obv_.empty ())
        obv_sep = event_type.find (obv_);
      else
        obv_sep = event_type.find ("OBV_");

      if (obv_sep == std::string::npos)
        continue;

      // Taking out OBV_ from event type, becuase it is child class
      event_type = event_type.substr (4, event_type.length () - 4);

      // Get the classname to check for constructor, destructor.
      size_t sep2 = event_type.rfind ("::");
      std::string class_name = event_type.substr (0, sep2);

      //check if event is in event list.
      if ( (event_list.find (event_type) != event_list.end ()))   
      {
        std::string method_name = rtn_signature.substr (separator + 2, rtn_signature.length () - separator - 2);

        // exclude constructor, destructor, middleware specific or operator reloading routines
        if (method_name.find (class_name) != std::string::npos
          || event_type.find (method_name) != std::string::npos
          || method_name.find ("~") != std::string::npos
          || method_name.find ("operator") != std::string::npos 
          || method_name.find ("destructor") != std::string::npos
          || method_name.find ("_copy_value") != std::string::npos
          || method_name.find ("_tao") != std::string::npos
          || method_name.find ("truncation_") != std::string::npos)
          continue;

        helper_addr_map_type helper_addr_map;
        helper_addr_map[method_name] = rtn_addr;

        // Insert in event helper map, because one event can have multiple helpers.
        event_helper_map_.insert(std::pair <std::string, helper_addr_map_type>(event_type, helper_addr_map));

        if (logs_required_)
          fout_ << "Registered event " << event_type << " with accessor method " << method_name << std::endl;

        find_helper_return_type (event_type, method_name);
      }
    }
  }

  // Find the return type for the public accessor and store it for later processing
  void find_helper_return_type (std::string event_type, std::string method_name)
  {
    // Check the return signature to look for the helper signature.
    for (auto rtn : helper_methods_map)
    {
      std::string rtn_signature = rtn.first;

      // If rtn_signature has (, it is signature and not a method call. 
      // Method calls don't have return types and parameteres, so we ignore.
      if (rtn_signature.find("(") != std::string::npos)
      {
        // Look if the signature has event_type::method_name, i.e. the method we are looking for.
        if (rtn_signature.find(event_type + "::" + method_name) != std::string::npos)
        {
          size_t position1 = rtn_signature.find ("public: ");
          size_t position2 = rtn_signature.find (" __thiscall");

          std::string method_return_type = rtn_signature.substr (position1 + 8, position2 - (position1 + 8));         
          
          // If there is virtual, trim it
          if (method_return_type.find("virtual ") != std::string::npos)
            method_return_type = method_return_type.substr (8, method_return_type.length () - 8);
          
          // We don't need void return type.
          if (method_return_type.find ("void") == std::string::npos)
          {
	    fout_ << "Return signature of helper method is " << rtn_signature << std::endl;
	    fout_ << "Return type of method " << method_name << " is " << method_return_type << std::endl;
            data_type_cmd * cmd  = create_data_type_cmd (method_return_type);
            helper_returntype_map_[method_name] = cmd;
          }         
         }
       }
      else
        continue;
    }
  }

  /**
  * Create data type command for return type
  */
  data_type_cmd * create_data_type_cmd (std::string return_type)
  {
    data_type_cmd_factory factory;
  
    if (return_type.find("char const *") != std::string::npos)
      return factory.create_const_char_ptr_cmd ();
    else if (return_type.find("int") != std::string::npos)
      return factory.create_long_cmd ();
    else if (return_type.find("unsigned short") != std::string::npos)
      return factory.create_unsigned_short_cmd ();
    //else if (return_type.find("short") != std::string::npos)
      //return factory.create_short_cmd ();
    else
    {
      if (logs_required_)
        fout_ << "Return Data type is " << return_type << " Not supported" << std::endl;
      return 0;
    }

  }

  /**
  * Output the names of the methods that have been instrumented.
  */
  void output_helper_list (void)
  {
    for (auto helper_buffer : analysis_rtn_buffer_list_)
    {
      for (auto helper : helper_buffer)
      {
        if (logs_required_)
          fout_ << "  Analysis routine for:"
            << " method '" << helper.get_method_name () << "'"
            << " of component '" << helper.get_component_name () << "'"
            << std::endl;
      }
    }
  }

  /*
  * Load all the methods in the helper image methods and store them with their address
  */
  void load_helper_image_methods (const OASIS::Pin::Image & img)
  {
    // the second iteration looks for helper methods of the event
    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        if (!rtn.valid ())
          continue;

        std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
        helper_methods_map[rtn_signature] = rtn.address ();  // Store the method name and its return address.
      }
    }

    // If event list is not empty, i.e. it was loaded before the helper image was loaded,
    // then register helper methods immediately.
    if (! event_list.empty())
    {
      for (auto event : event_list)
        check_and_register_valid_helper_method ();
    }
  }

public:
  // File for writing the logs
  std::ofstream & fout_;

  // File to write event trace
  std::ofstream & eventtrace_;

private:
  typedef OASIS::Pin::Buffer <Event_Monitor> item_type;              // a buffer for a routine
  typedef std::list <item_type> list_type;                           // a list of buffers for routines
  list_type analysis_rtn_buffer_list_;                               // the list that carries all the buffers for routines

  // map for registered event types
  std::unordered_map <std::string, bool> event_list;

  // map that loads and stores all the methods in the helper image, to be registered later with events
  typedef std::unordered_map <std::string, ADDRINT> helper_method_map_type;
  helper_method_map_type helper_methods_map;

  // map between name of the target method and the event type passed into it
  method_event_map_type & method_event_map_;
  
  // list of the target method call to be instrumented
  std::vector<string> & target_method_list_;

  // list of the dlls to be included in instrumentation
  std::vector<string> & include_list_;

  // list of the dlls to be excluded in instrumentation
  std::vector<string> & exclude_list_;
  
  // list of the dlls to be instrumetned to find helper methods.
  std::vector<string> & helper_list_;

  // Object by value prefix.
  std::string & obv_;

  // Check if helper image loaded.
  bool helper_image_loaded_;

  // Map between event and helper
  event_helper_map_type & event_helper_map_;

  // map between helper and its return types
  helper_returntype_map_type helper_returntype_map_;

  // Logs required
  bool & logs_required_;
};

/*******************************
* Tool
*******************************/

/**
* Pintool that instruments the target method by replacement.
*/
class dynamic_event_monitor : public OASIS::Pin::Tool <dynamic_event_monitor>
{
public:
  /**
  * Constructor.
  */
  dynamic_event_monitor (void)
    : instrument_ (fout_, 
    eventtrace_file_,
    method_event_map_,
    target_method_list_,
    include_list_,
    exclude_list_,
    helper_list_,
    obv,
    event_helper_map_,
    logs_required_)
  { 
    std::stringstream methods_string (target_methods_);              // parse the target method argument
    std::string method;
    while (std::getline (methods_string, method, ','))
      target_method_list_.push_back(method);

    std::stringstream include_string (include_);              // parse the include dll argument
    std::string include;
    while (std::getline (include_string, include, ','))
      include_list_.push_back(include);

    std::stringstream exclude_string (exclude_);              // parse the include dll argument
    std::string exclude;
    while (std::getline (exclude_string, exclude, ','))
      exclude_list_.push_back(exclude);

    std::stringstream helper_string (helper_);              // parse the include dll argument
    std::string helper;
    while (std::getline (helper_string, helper, ','))
      helper_list_.push_back(helper);

    logs_required_ = logs_.Value ();
    
    if (logs_required_)
      fout_.open (logfile_.Value ().c_str (), ios_base::app);

    eventtrace_file_.open (eventtrace_.Value ().c_str (), ios_base::app);

    // Object by value prefix
    obv = obv_.Value ().c_str ();   

    this->init_symbols ();

    if (logs_required_)
      this->enable_fini_callback ();
  }

  /**
  * Process posterior to program execution.
  */
  void handle_fini (INT32 code)
  {
    if (logs_required_)
    {
      fout_ << std::endl << "Pintool information:" << std::endl;

      fout_ << "..Target method:" << std::endl;
      for (auto method : target_method_list_)
        fout_ << "  " << method << std::endl;

      fout_ << std::endl;

      fout_ << "..Helper methods list:" << std::endl;
      instrument_.output_helper_list ();
      fout_ << std::endl;

      fout_ << "..Mapping between push method and event type:" << std::endl;
      for (auto pair : method_event_map_)
        fout_ << "  " << pair.first << " <-> " << pair.second << std::endl;      

      fout_ << std::endl;

      fout_ << "..Helper methods:" << std::endl;
      for (auto event : event_helper_map_)
      {
        fout_ << "  Event: " << event.first << std::endl;
        for (auto method : event.second)
          fout_ << "    Method: " << method.first << " <-> " << method.second << std::endl;
      }

      fout_ << std::endl;
      fout_.close ();
    }

    eventtrace_file_.close ();
  }
private:
  // file to write logs 
  std::ofstream fout_;

  // File to write event trace
  std::ofstream eventtrace_file_;

  // map between name of the target method and the event type passed into it
  method_event_map_type method_event_map_; 
  
  // list of the target method call to be instrumented
  std::vector<string> target_method_list_;

  // list of the dlls to be included in instrumentation
  std::vector<string> include_list_;

  // list of the dlls to be excluded in instrumentation
  std::vector<string> exclude_list_;
  
  // list of the dlls to be instrumetned to find helper methods.
  std::vector<string> helper_list_;

  // Object by value prefix.
  std::string obv;

  // Map between event and helper
  event_helper_map_type event_helper_map_;

  // Logs required
  bool logs_required_;

  // Instrumentation
  Image_Inst instrument_;

  // Knobs
  static KNOB <string> target_methods_;
  static KNOB <string> include_;
  static KNOB <string> exclude_;
  static KNOB <string> logfile_;
  static KNOB <string> eventtrace_;
  static KNOB <string> helper_;
  static KNOB <string> obv_;
  static KNOB <bool> logs_;
};

/*******************************
* KNOB declaration
*******************************/

// syntax:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -l <layer1>,<layer2>,... -m <method> -- <program>

// example:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -l Context,Servant -m push -- <program>

KNOB <string> dynamic_event_monitor::target_methods_ (KNOB_MODE_WRITEONCE, "pintool", "m", "push_",
                                                      "(case sensitive) name of the method call to be instrumented");

KNOB <string> dynamic_event_monitor::include_ (KNOB_MODE_WRITEONCE, "pintool", "i", "",
                                               "(case sensitive) name of the dll to be included to find push method");

KNOB <string> dynamic_event_monitor::helper_ (KNOB_MODE_WRITEONCE, "pintool", "ih", "",
                                              "(case sensitive) name of the dll to be included to find helper method");

KNOB <string> dynamic_event_monitor::exclude_ (KNOB_MODE_WRITEONCE, "pintool", "e", "ACEd_",
                                               "(case sensitive) name of the dlls to be excluded");

KNOB <string> dynamic_event_monitor::logfile_ (KNOB_MODE_WRITEONCE, "pintool", "lf", "Log_File.out", 
                                               "specify log file name");

KNOB <string> dynamic_event_monitor::eventtrace_ (KNOB_MODE_WRITEONCE, "pintool", "et", "Trace.out", 
                                               "specify file name for event trace");

KNOB <string> dynamic_event_monitor::obv_ (KNOB_MODE_WRITEONCE, "pintool", "obv", "OBV_", 
                                               "Object by value prefix");

KNOB <bool> dynamic_event_monitor::logs_ (KNOB_MODE_WRITEONCE, "pintool", "l", "1", 
                                               "logs required?");
/*******************************
* Pintool declaration
*******************************/

DECLARE_PINTOOL (dynamic_event_monitor);
