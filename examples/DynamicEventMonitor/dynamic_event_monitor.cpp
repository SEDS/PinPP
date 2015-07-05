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

#define DEBUG 1

#include <fstream>
#include <chrono>
#include <ctime>

/*******************************
* Global variables
*******************************/

typedef std::unordered_map <std::string, std::string> method_event_map_type;
method_event_map_type method_event_map;                              // map between name of the target method and the event type passed into it

std::unordered_map <std::string, bool> event_list;                   // map for registered event types

// map between event type and its helper methods
typedef std::unordered_map <std::string, ADDRINT> helper_addr_map_type;
typedef std::unordered_map <std::string, helper_addr_map_type> event_helper_map_type;
event_helper_map_type event_helper_map;

enum RTN_TYPE {SIGNATURE, METHOD_CALL, INVALID};

//std::vector<string> target_layer_list;                               // list of the target layers to be instrumented
std::vector<string> target_method_list;                              // list of the target method call to be instrumented
std::vector<string> include_list;                              // list of the dlls to be included in instrumentation
std::vector<string> exclude_list;                              // list of the dlls to be excluded in instrumentation
std::vector<string> helper_list;                              // list of the dlls to be instrumetned to find helper methods.
std::ofstream fout;                                           // file to write output 
std::string obv;


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
        fout << "..Error: the object passed in is null." << std::endl;

      return;
    }
    // check the existence of the helper methods
    method_event_map_type::iterator push_event_iter = method_event_map.find (target_name_);
    if (push_event_iter == method_event_map.end ())
    {
      if (DEBUG)        
        fout << "..Error: push method '" << target_name_ << "' not registered." << std::endl;

      return;
    }

    std::string event_type = push_event_iter->second;

    if (DEBUG)
      fout << "..Intercepted a push method call '" << target_name_ << "' with event type '" << event_type << "'" << std::endl;

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
    if (event_helper_map.find (event_type) != event_helper_map.end ())
    {
      helper_addr_map_type helper_addr_map = event_helper_map[event_type];

      for (auto method : helper_addr_map)
      {
        ADDRINT helper_addr = method.second;
        ADDRINT result_addr = 0;
        if (DEBUG)
          fout << "  Method: " << method.first << std::endl;

        __asm
        {
          mov ecx, object_addr
          call helper_addr
          mov result_addr, eax
        }

        if (DEBUG)
          fout << "  Return value: " << (const char *)result_addr << std::endl;
      }
    }
    else
    {
      if (DEBUG)
        fout << "..No helper method found." << std::endl;
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
    for (auto include : include_list)
    {
      separator = img.name ().find (include);
      if (separator != std::string::npos)
      {
        fout << "Finding push method in " << img.name () <<std::endl;

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
              method_event_map[rtn_name] = event_type;
              event_list[event_type] = true;

              if (DEBUG)
              {
                fout << "Signature found: " << std::endl;
                fout << "Image: " << img.name () << std::endl;
                fout << "Sign: " << rtn_signature << std::endl;
                fout << "Name: " << rtn_name << std::endl;
                fout << "Associated event type: " << event_type << std::endl;
                fout << std::endl;
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
                fout << "Method call found: " << std::endl;
                fout << "Image: " << img.name () << std::endl;
                fout << "Sign: " << rtn_signature << std::endl;
                fout << "Name: " << rtn_name << std::endl;
                fout << std::endl;
              }
            }
          }
        }
      }
    }

    size_t sep = std::string::npos;
    for (auto helper : helper_list)
    {
      sep = img.name ().find (helper);
      if (sep != std::string::npos)
      {
        fout << "Finding helper method in " << img.name () <<std::endl;

        // the second iteration looks for helper methods of the event
        for (auto sec : img)
        {
          for (auto rtn : sec)
          {
            if (!rtn.valid ())
              continue;

            std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE); 
            check_and_register_valid_helper_method (rtn_signature, rtn.address ());
          }
        }
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
    for (auto method : target_method_list)
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
  * Determine whether the passed in routine is a valid helper method for any registered event class.
  *
  * @param[in]      rtn_signature      a complete and undecorated routine name
  */
  void check_and_register_valid_helper_method (std::string rtn_signature, ADDRINT rtn_addr)
  {
    size_t separator = rtn_signature.rfind ("::");
    if (separator == std::string::npos)
      return;

    std::string event_type = rtn_signature.substr (0, separator);

    // Find Object by value (obv) prefix in the event type. 
    // If it is not found, then default to OBV_, which is obv prefix for TAO middleware
    size_t obv_sep;

    if (!obv.empty ())
      obv_sep = event_type.find (obv);
    else
      obv_sep = event_type.find ("OBV_");

    if (obv_sep == std::string::npos)
      return;

    // Taking out OBV_ from event type, becuase it is child class
    event_type = event_type.substr (4, event_type.length () - 4);

    size_t sep2 = event_type.rfind ("::");
    std::string class_name = event_type.substr (0, sep2);

    if (event_list.find (event_type) != event_list.end ())
    {
      std::string method_name = rtn_signature.substr (separator + 2, rtn_signature.length () - separator - 2);

      // exclude constructor, destructor, middleware specific or operator reloading routines
      if (method_name.find (class_name) != std::string::npos 
        || method_name.find ("operator") != std::string::npos 
        || method_name.find ("destructor") != std::string::npos
        || method_name.find ("_copy_value") != std::string::npos
        || method_name.find ("_tao") != std::string::npos
        || method_name.find ("truncation_") != std::string::npos)
        return;

      helper_addr_map_type helper_addr_map = event_helper_map[event_type];
      helper_addr_map[method_name] = rtn_addr;
      event_helper_map[event_type] = helper_addr_map;

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
        fout << "  Analysis routine for:"
          << " method '" << helper.get_method_name () << "'"
          << " of component '" << helper.get_component_name () << "'"
          << " at layer '" << helper.get_component_layer () << "'"
          << std::endl;
      }
    }
  }

private:
  typedef OASIS::Pin::Buffer <Event_Monitor> item_type;              // a buffer for a routine
  typedef std::list <item_type> list_type;                           // a list of buffers for routines
  list_type analysis_rtn_buffer_list_;                               // the list that carries all the buffers for routines
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
  { 
    std::stringstream methods_string (target_methods_);              // parse the target method argument
    std::string method;
    while (std::getline (methods_string, method, ','))
      target_method_list.push_back(method);

    std::stringstream include_string (include_);              // parse the include dll argument
    std::string include;
    while (std::getline (include_string, include, ','))
      include_list.push_back(include);

    std::stringstream exclude_string (exclude_);              // parse the include dll argument
    std::string exclude;
    while (std::getline (exclude_string, exclude, ','))
      exclude_list.push_back(exclude);

    std::stringstream helper_string (helper_);              // parse the include dll argument
    std::string helper;
    while (std::getline (helper_string, helper, ','))
      helper_list.push_back(helper);

    /*std::stringstream layers_string (target_layers_);                // parse the target layer argument
    std::string layer;
    while (std::getline (layers_string, layer, ','))
    target_layer_list.push_back(layer);
    */

    fout.open (outfile_.Value ().c_str (), ios_base::app);

    // Object by value prefix
    obv = obv_.Value ().c_str ();

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
      for (auto include : include_list)
      {
        fout << std::endl << "Pintool information:" << std::endl;

        fout << "..Target method:" << std::endl;
        for (auto method : target_method_list)
          fout << "  " << method << std::endl;

        fout << std::endl;

        /*fout << "..Target layers:" << std::endl;
        for (auto layer : target_layer_list)
        fout << "  " << layer << std::endl;

        fout << std::endl;*/

        fout << "..Helper methods list:" << std::endl;
        instrument_.output_helper_list ();
        fout << std::endl;

        fout << "..Mapping between push method and event type:" << std::endl;
        for (auto pair : method_event_map)
          fout << "  " << pair.first << " <-> " << pair.second << std::endl;      

        fout << std::endl;

        fout << "..Helper methods:" << std::endl;
        for (auto event : event_helper_map)
        {
          fout << "  Event: " << event.first << std::endl;
          for (auto method : event.second)
            fout << "    Method: " << method.first << " <-> " << method.second << std::endl;
        }
        fout << std::endl;
      }
    }
    fout.close ();
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

KNOB <string> dynamic_event_monitor::include_ (KNOB_MODE_WRITEONCE, "pintool", "i", "StockBroker_exec",
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
