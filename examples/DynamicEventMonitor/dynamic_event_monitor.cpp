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

std::vector<string> target_layer_list;                               // list of the target layers to be instrumented
std::vector<string> target_method_list;                              // list of the target method call to be instrumented


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
      {
        std::cout << "..Error: the object passed in is null." << std::endl;
      }
      return;
    }
                                                                     // check the existence of the helper methods
    method_event_map_type::iterator push_event_iter = method_event_map.find (target_name_);
    if (push_event_iter == method_event_map.end ())
    {
      if (DEBUG)
      {        
        std::cout << "..Error: push method '" << target_name_ << "' not registered." << std::endl;
      }
      return;
    }

    std::string event_type = push_event_iter->second;
    
    if (DEBUG)
    {
      std::cout << "..Intercepted a push method call '" << target_name_ << "' with event type '" << event_type << "'" << std::endl;
    }

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
        {
          std::cout << "  Method: " << method.first << std::endl;
        }
        __asm
        {
          mov ecx, object_addr
          call helper_addr
          mov result_addr, eax
        }
        if (DEBUG)
        {
          std::cout << "  Return addr: " << result_addr << std::endl;
        }
      }
    }
    else
    {
      if (DEBUG)
      {
        std::cout << "..No helper method found." << std::endl;
      }
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
    
    // the first iteration looks for target method signatures, method calls and their associated event types
    for (auto sec : img) 
    {
      for (auto rtn : sec)
      {
        if (!rtn.valid ())
        {
          continue;
        }

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
            std::cout << "Signature found: " << std::endl;
            std::cout << "Image: " << img.name () << std::endl;
            std::cout << "Sign: " << rtn_signature << std::endl;
            std::cout << "Name: " << rtn_name << std::endl;
            std::cout << "Associated event type: " << event_type << std::endl;
            std::cout << std::endl;
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
            std::cout << "Method call found: " << std::endl;
            std::cout << "Image: " << img.name () << std::endl;
            std::cout << "Sign: " << rtn_signature << std::endl;
            std::cout << "Name: " << rtn_name << std::endl;
            std::cout << std::endl;
          }
        }
      }
    }

    // the second iteration looks for helper methods of the event
    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        if (!rtn.valid ())
        {
          continue;
        }
        std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);        
        check_and_register_valid_helper_method (rtn_signature, rtn.address ());
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
      {
        break;
      }
    }

    if (separator == std::string::npos)
    {
      return INVALID;
    }
    
    bool valid = false;
    for (auto layer : target_layer_list)
    {
      valid = valid || rtn_signature.find (layer) != std::string::npos;
    }

    if (!valid)
    {
      return INVALID;
    }

    if (rtn_signature.find ("(", separator) != std::string::npos)
    {
      return SIGNATURE;
    }
    else
    {
      return METHOD_CALL;
    }
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
    {
      return;
    }
    std::string event_type = rtn_signature.substr (0, separator);
    if (event_list.find (event_type) != event_list.end ())
    {
      std::string method_name = rtn_signature.substr (separator + 2, rtn_signature.length () - separator - 2);
      
      // exclude constructor, destructor or operator reloading routines
      if (method_name.find (event_type) != std::string::npos || method_name.find ("operator") != std::string::npos)
      {
        return;
      }
      
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
        std::cout << "  Analysis routine for:"
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
    {
      target_method_list.push_back(method);
    }
    
    std::stringstream layers_string (target_layers_);                // parse the target layer argument
    std::string layer;
    while (std::getline (layers_string, layer, ','))
    {
      target_layer_list.push_back(layer);
    }

    this->init_symbols ();
    
    if (DEBUG)
    {
      this->enable_fini_callback ();
    }
  }

  /**
   * Process posterior to program execution.
   */
  void handle_fini (INT32 code)
  {
    if (DEBUG)
    {
      std::cout << std::endl << "Pintool information:" << std::endl;

      std::cout << "..Target method:" << std::endl;
      for (auto method : target_method_list)
      {
        std::cout << "  " << method << std::endl;
      }
      std::cout << std::endl;

      std::cout << "..Target layers:" << std::endl;
      for (auto layer : target_layer_list)
      {
        std::cout << "  " << layer << std::endl;
      }
      std::cout << std::endl;

      std::cout << "..Helper methods list:" << std::endl;
      instrument_.output_helper_list ();
      std::cout << std::endl;

      std::cout << "..Mapping between push method and event type:" << std::endl;
      for (auto pair : method_event_map)
      {
        std::cout << "  " << pair.first << " <-> " << pair.second << std::endl;      
      }
      std::cout << std::endl;

      std::cout << "..Helper methods:" << std::endl;
      for (auto event : event_helper_map)
      {
        std::cout << "  Event: " << event.first << std::endl;
        for (auto method : event.second)
        {
          std::cout << "    Method: " << method.first << " <-> " << method.second << std::endl;
        }
      }
      std::cout << std::endl;
    }
  }

private:
  Image_Inst instrument_;
  static KNOB <string> target_layers_;
  static KNOB <string> target_methods_;
};



/*******************************
 * KNOB declaration
 *******************************/

// syntax:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -c <layer1>,<layer2>,... -m <method> -- <program>

// example:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -c Context,Servant -m push -- <program>

KNOB <string> dynamic_event_monitor::target_layers_ (KNOB_MODE_WRITEONCE, "pintool", "l", "Context,Servant",
                                                    "(case sensitive) name of the layers of the components to be instrumented");

KNOB <string> dynamic_event_monitor::target_methods_ (KNOB_MODE_WRITEONCE, "pintool", "m", "push",
                                                     "(case sensitive) name of the method call to be instrumented");



/*******************************
 * Pintool declaration
 *******************************/

DECLARE_PINTOOL (dynamic_event_monitor);
