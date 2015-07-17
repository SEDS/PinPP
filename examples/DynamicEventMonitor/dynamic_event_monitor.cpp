/**
* Pintool that dynamically instrument the target method call at the specified layer.
* 2014.07
*
*/



/*******************************
* Dependencies
*******************************/

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Callback.h"
#include "pin++/Routine.h"
#include "pin++/Symbol.h"
#include "pin++/Buffer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "data_type_cmd.h"
#include "data_type_cmd_factory.h"

#define DEBUG 1

#include <fstream>

class dynamic_event_monitor_utility
{
public:
  // map between name of the target method and the event type passed into it
  typedef std::unordered_map <std::string, std::string> method_event_map_type;
  static method_event_map_type method_event_map;                              

  static bool helper_image_loaded;

  // map between event type and its helper methods
  typedef std::unordered_map <std::string, ADDRINT> helper_addr_map_type;
  typedef std::unordered_map <std::string, helper_addr_map_type> event_helper_map_type;
  static event_helper_map_type event_helper_map;

  // map between helper and its return types
  static std::unordered_map <std::string, data_type_cmd *> helper_return_type_map;

  //std::vector<string> target_layer_list;                               // list of the target layers to be instrumented
  static std::vector<string> target_method_list;                         // list of the target method call to be instrumented
  static std::vector<string> include_list;                              // list of the dlls to be included in instrumentation
  static std::vector<string> exclude_list;                              // list of the dlls to be excluded in instrumentation
  static std::vector<string> helper_list;                              // list of the dlls to be instrumetned to find helper methods.
  static std::ofstream fout;                                           // file to write output 
  static std::string obv;
};

// Defining static members of dynamic_event_monitor
bool dynamic_event_monitor_utility::helper_image_loaded;
std::vector<string> dynamic_event_monitor_utility::target_method_list;                         // list of the target method call to be instrumented
std::vector<string> dynamic_event_monitor_utility::include_list;                              // list of the dlls to be included in instrumentation
std::vector<string> dynamic_event_monitor_utility::exclude_list;                              // list of the dlls to be excluded in instrumentation
std::vector<string> dynamic_event_monitor_utility::helper_list;                              // list of the dlls to be instrumetned to find helper methods.
std::ofstream dynamic_event_monitor_utility::fout;                                           // file to write output 
std::string dynamic_event_monitor_utility::obv;
dynamic_event_monitor_utility::method_event_map_type dynamic_event_monitor_utility::method_event_map;
dynamic_event_monitor_utility::event_helper_map_type dynamic_event_monitor_utility::event_helper_map;
std::unordered_map <std::string, data_type_cmd *> dynamic_event_monitor_utility::helper_return_type_map;


/*******************************
* Analysis routine
*******************************/

/**
* Analysis routine that executes a helper method.
*/
class Event_Monitor : public OASIS::Pin::Callback <Event_Monitor (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>
{
public:
  /**
  * Analysis routine.
  */
  void handle_analyze (ADDRINT object_addr)
  {
    if (object_addr == 0)
    {
      if (DEBUG)
        dynamic_event_monitor_utility::fout << "..Error: the object passed in is null." << std::endl;

      return;
    }
    // check the existence of the helper methods
    dynamic_event_monitor_utility::method_event_map_type::iterator push_event_iter = dynamic_event_monitor_utility::method_event_map.find (target_name_);
    if (push_event_iter == dynamic_event_monitor_utility::method_event_map.end ())
    {
      if (DEBUG)        
        dynamic_event_monitor_utility::fout << "..Error: push method '" << target_name_ << "' not registered." << std::endl;

      return;
    }

    std::string event_type = push_event_iter->second;

    if (DEBUG)
      dynamic_event_monitor_utility::fout << "..Intercepted a push method call '" << target_name_ << "' with event type '" << event_type << "'" << std::endl;

    helper_methods_execution (event_type, object_addr);
  }

  /**
  * Execute all the helper methods for the target object
  *
  * @param[in]      addr_map         map of class name and helper method address
  * @param[in]      class_name       class name of the target object
  * @param[in]      object_addr      address of the target object
  */
  void helper_methods_execution (std::string event_type, ADDRINT object_addr)
  {
    if (dynamic_event_monitor_utility::event_helper_map.find (event_type) != dynamic_event_monitor_utility::event_helper_map.end ())
    {
      dynamic_event_monitor_utility::helper_addr_map_type helper_addr_map = dynamic_event_monitor_utility::event_helper_map[event_type];

      for (auto method : helper_addr_map)
      {
        ADDRINT helper_addr = method.second;
        ADDRINT result_addr = 0;

        // Create a command for the return type.
        data_type_cmd * cmd = dynamic_event_monitor_utility::helper_return_type_map[method.first];

        if (DEBUG)
          dynamic_event_monitor_utility::fout << "  Method: " << method.first << std::endl;

        __asm
        {
          mov ecx, object_addr
          call helper_addr
          mov result_addr, eax
        }

        if (DEBUG)
          dynamic_event_monitor_utility::fout << "  Return value: " << cmd->execute (result_addr) << std::endl;
      }
    }
    else
    {
      if (DEBUG)
        dynamic_event_monitor_utility::fout << "..No helper method found." << std::endl;
    }
  }

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
  * Getter for the layer of the component of the target method to be instrumentated.
  *
  * @return      returns the name of the layer of the component.
  */
  std::string get_component_layer (void)
  {
    size_t separator1 = target_name_.find ("::");
    size_t separator2 = target_name_.rfind ("_", separator1);
    return target_name_.substr (separator2 + 1, separator1 - separator2 - 1);
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

private:
  std::string target_name_;
};



/*******************************
* Instrument
*******************************/

/**
* Image level instrument.
*/
class Image_Inst : public OASIS::Pin::Image_Instrument <Image_Inst>
{
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
    for (auto include : dynamic_event_monitor_utility::include_list)
    {
      separator = img.name ().find (include);
      if (separator != std::string::npos)
      {
        dynamic_event_monitor_utility::fout << "Finding push method in " << img.name () <<std::endl;

        // the first iteration looks for target method signatures, method calls and their associated event types
        for (auto sec : img) 
        {
          for (auto rtn : sec)
          {
            if (!rtn.valid ())
              continue;

            std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);        
            std::string rtn_name = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_NAME_ONLY);

            RTN_TYPE rtn_type = is_valid_push_method (rtn_signature);
            if (rtn_type == SIGNATURE)                                   // the routine is merely a target method signature; map it with its event type
            {
              ++ push_method_count;
              std::string event_type = get_push_event_type (rtn_signature);
              dynamic_event_monitor_utility::method_event_map[rtn_name] = event_type;
              event_list[event_type] = true;

              if (dynamic_event_monitor_utility::helper_image_loaded)
                check_and_register_valid_helper_method ();

              if (DEBUG)
              {
                dynamic_event_monitor_utility::fout << "Signature found: " << std::endl;
                dynamic_event_monitor_utility::fout << "Image: " << img.name () << std::endl;
                dynamic_event_monitor_utility::fout << "Sign: " << rtn_signature << std::endl;
                dynamic_event_monitor_utility::fout << "Name: " << rtn_name << std::endl;
                dynamic_event_monitor_utility::fout << "Associated event type: " << event_type << std::endl;
                dynamic_event_monitor_utility::fout << std::endl;
              }
            }
            else if (rtn_type == METHOD_CALL)                            // the routine is an actual method call; insert the analysis routine
            {
              OASIS::Pin::Routine_Guard guard (rtn);
              item_type helper_buffer (1);                               // buffers must be used; otherwise the analysis routine cannot be preserved
              item_type::iterator helper = helper_buffer.begin ();
              helper->set_target_name (rtn_name);
              helper->insert (IPOINT_BEFORE, rtn, 0);
              analysis_rtn_buffer_list_.push_back (helper_buffer);

              if (DEBUG)
              {
                dynamic_event_monitor_utility::fout << "Method call found: " << std::endl;
                dynamic_event_monitor_utility::fout << "Image: " << img.name () << std::endl;
                dynamic_event_monitor_utility::fout << "Sign: " << rtn_signature << std::endl;
                dynamic_event_monitor_utility::fout << "Name: " << rtn_name << std::endl;
                dynamic_event_monitor_utility::fout << std::endl;
              }
            }
          }
        }
      }
    }

    // Load methods from the helper class.
    size_t sep = std::string::npos;
    for (auto helper : dynamic_event_monitor_utility::helper_list)
    {
      sep = img.name ().find (helper);
      if (sep != std::string::npos)
      {
        dynamic_event_monitor_utility::fout << "Finding helper method in " << img.name () <<std::endl;

        // Load the methods and address from helper image, so that we can process when we discover events laters.
        load_helper_image_methods (img);

        dynamic_event_monitor_utility::helper_image_loaded = true;
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
    for (auto method : dynamic_event_monitor_utility::target_method_list)
    {
      separator = rtn_signature.find ("::" + method);
      if (separator != std::string::npos)
        break;
    }

    if (separator == std::string::npos)
      return INVALID;

    /*bool valid = false;
    for (auto layer : target_layer_list)
    valid = valid || rtn_signature.find (layer) != std::string::npos;

    if (!valid)
    return INVALID;
    */

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

      if (!dynamic_event_monitor_utility::obv.empty ())
        obv_sep = event_type.find (dynamic_event_monitor_utility::obv);
      else
        obv_sep = event_type.find ("OBV_");

      if (obv_sep == std::string::npos)
        continue;

      // Taking out OBV_ from event type, becuase it is child class
      event_type = event_type.substr (4, event_type.length () - 4);

      // Get the classname to check for constructor, destructor.
      size_t sep2 = event_type.rfind ("::");
      std::string class_name = event_type.substr (0, sep2);

      //check if event is in event list and helper is already registered for the event.
      if ( (event_list.find (event_type) != event_list.end ()) 
        && dynamic_event_monitor_utility::event_helper_map.find (event_type) == dynamic_event_monitor_utility::event_helper_map.end ())   
      {
        std::string method_name = rtn_signature.substr (separator + 2, rtn_signature.length () - separator - 2);

        // exclude constructor, destructor, middleware specific or operator reloading routines
        if (method_name.find (class_name) != std::string::npos 
          || method_name.find ("operator") != std::string::npos 
          || method_name.find ("destructor") != std::string::npos
          || method_name.find ("_copy_value") != std::string::npos
          || method_name.find ("_tao") != std::string::npos
          || method_name.find ("truncation_") != std::string::npos)
          continue;

        dynamic_event_monitor_utility::helper_addr_map_type helper_addr_map = dynamic_event_monitor_utility::event_helper_map[event_type];
        helper_addr_map[method_name] = rtn_addr;
        dynamic_event_monitor_utility::event_helper_map[event_type] = helper_addr_map;

        dynamic_event_monitor_utility::fout << "Registered event " << event_type << " with accessor method " << method_name << std::endl;

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

          data_type_cmd * cmd  = 0;
          data_type_cmd_factory factory;

          // We don't need void return type.
          if (method_return_type.find ("void") == std::string::npos)
          {
            if (method_return_type.find("char const *") != std::string::npos)
            {
              cmd = factory.create_const_char_ptr_cmd ();
              dynamic_event_monitor_utility::helper_return_type_map[method_name] = cmd;
            }

            //dynamic_event_monitor_utility::helper_return_type_map[method_name] = method_return_type;
            //dynamic_event_monitor_utility::fout << "Return type of method is " << method_return_type << std::endl;
          }
        }
      }
      else
        continue;

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
        dynamic_event_monitor_utility::fout << "  Analysis routine for:"
          << " method '" << helper.get_method_name () << "'"
          << " of component '" << helper.get_component_name () << "'"
          << " at layer '" << helper.get_component_layer () << "'"
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

private:
  typedef OASIS::Pin::Buffer <Event_Monitor> item_type;              // a buffer for a routine
  typedef std::list <item_type> list_type;                           // a list of buffers for routines
  list_type analysis_rtn_buffer_list_;                               // the list that carries all the buffers for routines
  
  std::unordered_map <std::string, bool> event_list;                   // map for registered event types

  // map that loads and stores all the methods in the helper image, to be registered later with events
  typedef std::unordered_map <std::string, ADDRINT> helper_method_map_type;
  static helper_method_map_type helper_methods_map;
};

// Defining static member of Image_Inst
Image_Inst::helper_method_map_type Image_Inst::helper_methods_map;

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
  { 
    std::stringstream methods_string (target_methods_);              // parse the target method argument
    std::string method;
    while (std::getline (methods_string, method, ','))
      dynamic_event_monitor_utility::target_method_list.push_back(method);

    std::stringstream include_string (include_);              // parse the include dll argument
    std::string include;
    while (std::getline (include_string, include, ','))
      dynamic_event_monitor_utility::include_list.push_back(include);

    std::stringstream exclude_string (exclude_);              // parse the include dll argument
    std::string exclude;
    while (std::getline (exclude_string, exclude, ','))
      dynamic_event_monitor_utility::exclude_list.push_back(exclude);

    std::stringstream helper_string (helper_);              // parse the include dll argument
    std::string helper;
    while (std::getline (helper_string, helper, ','))
      dynamic_event_monitor_utility::helper_list.push_back(helper);

    /*std::stringstream layers_string (target_layers_);                // parse the target layer argument
    std::string layer;
    while (std::getline (layers_string, layer, ','))
    target_layer_list.push_back(layer);
    */

    dynamic_event_monitor_utility::fout.open (outfile_.Value ().c_str (), ios_base::app);

    // Object by value prefix
    dynamic_event_monitor_utility::obv = obv_.Value ().c_str ();

    dynamic_event_monitor_utility::helper_image_loaded = false;

    this->init_symbols ();

    if (DEBUG)
      this->enable_fini_callback ();
  }

  /**
  * Process posterior to program execution.
  */
  void handle_fini (INT32 code)
  {
    if (DEBUG)
    {
      // Display this info only for include list
      for (auto include : dynamic_event_monitor_utility::include_list)
      {
        dynamic_event_monitor_utility::fout << std::endl << "Pintool information:" << std::endl;

        dynamic_event_monitor_utility::fout << "..Target method:" << std::endl;
        for (auto method : dynamic_event_monitor_utility::target_method_list)
          dynamic_event_monitor_utility::fout << "  " << method << std::endl;

        dynamic_event_monitor_utility::fout << std::endl;

        /*fout << "..Target layers:" << std::endl;
        for (auto layer : target_layer_list)
        fout << "  " << layer << std::endl;

        fout << std::endl;*/

        dynamic_event_monitor_utility::fout << "..Helper methods list:" << std::endl;
        instrument_.output_helper_list ();
        dynamic_event_monitor_utility::fout << std::endl;

        dynamic_event_monitor_utility::fout << "..Mapping between push method and event type:" << std::endl;
        for (auto pair : dynamic_event_monitor_utility::method_event_map)
          dynamic_event_monitor_utility::fout << "  " << pair.first << " <-> " << pair.second << std::endl;      

        dynamic_event_monitor_utility::fout << std::endl;

        dynamic_event_monitor_utility::fout << "..Helper methods:" << std::endl;
        for (auto event : dynamic_event_monitor_utility::event_helper_map)
        {
          dynamic_event_monitor_utility::fout << "  Event: " << event.first << std::endl;
          for (auto method : event.second)
            dynamic_event_monitor_utility::fout << "    Method: " << method.first << " <-> " << method.second << std::endl;
        }
        dynamic_event_monitor_utility::fout << std::endl;
      }
    }
    dynamic_event_monitor_utility::fout.close ();
  }

private:
  Image_Inst instrument_;
  static KNOB <string> target_layers_;
  static KNOB <string> target_methods_;
  static KNOB <string> include_;
  static KNOB <string> exclude_;
  static KNOB <string> outfile_;
  static KNOB <string> helper_;
  static KNOB <string> obv_;
};

/*******************************
* KNOB declaration
*******************************/

// syntax:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -l <layer1>,<layer2>,... -m <method> -- <program>

// example:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -l Context,Servant -m push -- <program>

KNOB <string> dynamic_event_monitor::target_layers_ (KNOB_MODE_WRITEONCE, "pintool", "l", "Context,Servant",
                                                     "(case sensitive) name of the layers of the components to be instrumented");

KNOB <string> dynamic_event_monitor::target_methods_ (KNOB_MODE_WRITEONCE, "pintool", "m", "push_",
                                                      "(case sensitive) name of the method call to be instrumented");

KNOB <string> dynamic_event_monitor::include_ (KNOB_MODE_WRITEONCE, "pintool", "i", "StockBroker_exec,StockDistributor_svnt",
                                               "(case sensitive) name of the dll to be included to find push method");

KNOB <string> dynamic_event_monitor::helper_ (KNOB_MODE_WRITEONCE, "pintool", "ih", "Stock_Base_stub",
                                              "(case sensitive) name of the dll to be included to find helper method");

KNOB <string> dynamic_event_monitor::exclude_ (KNOB_MODE_WRITEONCE, "pintool", "e", "ACEd_",
                                               "(case sensitive) name of the dlls to be excluded");

KNOB <string> dynamic_event_monitor::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "f", "dynamic_event_monitor.out", 
                                               "specify output file name");

KNOB <string> dynamic_event_monitor::obv_ (KNOB_MODE_WRITEONCE, "pintool", "obv", "OBV_", 
                                               "Object by value prefix");
/*******************************
* Pintool declaration
*******************************/

DECLARE_PINTOOL (dynamic_event_monitor);
