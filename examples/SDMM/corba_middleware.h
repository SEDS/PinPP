#include "pin++/Callback.h"
#include "pin++/Routine.h"
#include "pin++/Symbol.h"
#include "pin++/Buffer.h"
#include "pin++/Copy.h"
#include "middleware.h"
#include "writer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <time.h>
#include <fstream>

#include "data_type_cmd.h"
#include "data_type_cmd_factory.h"

#ifndef CORBA_MIDDLEWARE_H
#define CORBA_MIDDLEWARE_H

namespace OASIS {
namespace Pin {

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

    struct event_info : public Writer {
        std::string method_name;
        std::string date_time;
        std::string severity;
        THREADID tid;
        std::string component;
        std::string type;
        std::string element;
        std::string return_type;

        virtual void write_to(std::ostream & out) {
            out << "{"
            << "\"Method\": \"" << this->method_name << "\","
            << "\"Date Time\": \"" << this->date_time << "\","
            << "\"Severity\": \"" << this->severity << "\","
            << "\"Thread ID\": \"" << this->tid << "\","
            << "\"Component\": \"" << this->component << "\","
            << "\"Event Type\": \"" << this->type << "\","
            << "\"Element\": \"" << this->element << "\","
            << "\"Return Type\": \"" << this->return_type << "\","
            << "\"Information Class\": \"Event Info\"}";
        }
    };

    struct signature_helper_info : public Writer {
        std::string sign;
        std::string method;
        std::string return_type;

        signature_helper_info(std::string signature,
            std::string method_name,
            std::string ret_type)
        :sign(signature),
        method(method_name),
        return_type(ret_type)
        { }

        virtual void write_to (std::ostream & out) {
            out << "{"
            << "\"Signature\": \"" << this->sign << "\","
            << "\"Method\": \"" << this->method << "\","
            << "\"Return Type\": \"" << this->return_type << "\","
            << "\"Information Class\": \"Sign Help Info\"}";
        }
    };

    struct signature_info : public Writer {
        std::string img;
        std::string sign;
        std::string method_name;
        std::string event_type;

        signature_info(std::string image,
            std::string signature,
            std::string name,
            std::string type)
        :img(image),
        sign(signature),
        method_name(name),
        event_type(type)
        { }

        virtual void write_to(std::ostream & out) {
            out << "{";
            out << "\"Image\": \"" << this->img << "\",";
            out << "\"Signature\": \"" << this->sign << "\",";
            out << "\"Method Name\": \"" << this->method_name << "\",";
            out << "\"Event Type\": \"" << this->event_type << "\",";
            out << "\"Information Class\": \"Sign Info\"}";
        }
    };

    struct helper_method_info : public Writer {
        std::string img;
        std::string sign;
        std::string method_name;

        helper_method_info(std::string image,
            std::string signature,
            std::string name)
        :img(image),
        sign(signature),
        method_name(name)
        { }

        virtual void write_to(std::ostream & out) {
            out << "{"
            << "\"Image\": \"" << this->img << "\","
            << "\"Signature\": \"" << this->sign << "\","
            << "\"Method Name\": \"" << this->method_name << "\","
            << "\"Information Class\": \"Method Info\"}";
        }
    };

    /**
    * Analysis routine that executes a helper method.
    */
    class Event_Monitor : public OASIS::Pin::Callback <Event_Monitor (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)> //, OASIS::Pin::ARG_CONTEXT)>
    {
    public:
    Event_Monitor ()
        :info_(new event_info),
        method_event_map_ (0),
        helper_return_type_map_ (0)
    {
    }
    /**
     * Analysis routine.
     */
    void handle_analyze (ADDRINT object_addr) //, OASIS::Pin::Context & ctx)
    {
        if (object_addr == 0)
        {
            std::cerr << "..Error: the object passed in is null." << std::endl;
            return;
        }
        // check the existence of the helper methods
        method_event_map_type::iterator push_event_iter = method_event_map_->find (target_name_);
        if (push_event_iter == method_event_map_->end ())
        {
            std::cerr << "..Error: push method '" << target_name_ << "' not registered." << std::endl;
            return;
        }

        std::string event_type = push_event_iter->second;

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
        for (event_helper_it = it.first; event_helper_it != it.second; ++ event_helper_it) {
            helper_addr_map_type helper_addr_map = event_helper_it->second;

            for (auto method : helper_addr_map) {
                ADDRINT helper_addr = method.second;
                ADDRINT result_addr = 0;

                // Create a command for the return type.
                data_type_cmd * cmd = (*helper_return_type_map_)[method.first];

                this->info_->method_name = method.first;

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
                this->info_->date_time = current_date_time();
                this->info_->severity = "16854";
                this->info_->tid = PIN_GetTid();
                this->info_->component = get_component_name();
                this->info_->type = event_type;
                this->info_->element = method.first;

                if (cmd != 0) {
                    cmd->execute (result_addr, this->info_->return_type);
                }          
            }
        }
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

    //The information on the event that we care about
    event_info * info_;

    private:
    std::string target_name_;

    // Map between events and methods
    method_event_map_type * method_event_map_;

    // Map between event and helper
    event_helper_map_type * event_helper_map_;

    // Map between helper and its return type
    helper_returntype_map_type * helper_return_type_map_;
    };
    
    class CORBA_Middleware : public Middleware {
        enum RTN_TYPE {SIGNATURE, METHOD_CALL, INVALID};
        //item_type - a buffer for a routine
        typedef OASIS::Pin::Buffer <Event_Monitor> item_type;

    public:
        //list_type - a list of buffers for routines
        typedef std::list <item_type> analysis_rtn_list_type;
        
        CORBA_Middleware(std::vector<std::string> & method_list, std::string & obv)
            :target_method_list_(method_list),
            obv_(obv),
            helper_image_loaded_(false)
        { }

	virtual std::string name(void) {
		return "CORBA Middleware";
	}

        RTN_TYPE is_valid_push_method (std::string rtn_signature) {
            size_t separator = std::string::npos;
            for (auto method : target_method_list_) {
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

        std::string get_push_event_type (std::string rtn_signature) {
            size_t start = rtn_signature.find ("(class ") + 7;
            size_t end = rtn_signature.find (" ", start);
            return rtn_signature.substr (start, end - start);
        }

        data_type_cmd * create_data_type_cmd (std::string return_type) {
            data_type_cmd_factory factory;
        
            if (return_type.find("char const *") != std::string::npos)
                return factory.create_const_char_ptr_cmd ();
            else if (return_type.find("int") != std::string::npos)
                return factory.create_long_cmd ();
            else if (return_type.find("unsigned short") != std::string::npos)
                return factory.create_unsigned_short_cmd ();
            else {
                return 0;
            }

        }

        void find_helper_return_type (std::string event_type, std::string method_name) {
            // Check the return signature to look for the helper signature.
            for (auto rtn : helper_methods_map) {
                std::string rtn_signature = rtn.first;

                // If rtn_signature has (, it is signature and not a method call. 
                // Method calls don't have return types and parameteres, so we ignore.
                if (rtn_signature.find("(") != std::string::npos) {
                    // Look if the signature has event_type::method_name, i.e. the method we are looking for.
                    if (rtn_signature.find(event_type + "::" + method_name) != std::string::npos) {
                        size_t position1 = rtn_signature.find ("public: ");
                        size_t position2 = rtn_signature.find (" __thiscall");

                        std::string method_return_type = rtn_signature.substr (position1 + 8, position2 - (position1 + 8));         
                        
                        // If there is virtual, trim it
                        if (method_return_type.find("virtual ") != std::string::npos)
                            method_return_type = method_return_type.substr (8, method_return_type.length () - 8);
                        
                        // We don't need void return type.
                        if (method_return_type.find ("void") == std::string::npos) {
                            data_type_cmd * cmd  = create_data_type_cmd (method_return_type);
                            helper_returntype_map_[method_name] = cmd;

                            signature_helper_info * sighelp_info = new signature_helper_info(rtn_signature, method_name, method_return_type);
                            output_list_.push_back(sighelp_info);
                        }
                    }
                } else {
                    continue;
                }
            }
        }

        void check_and_register_valid_helper_method (void) {
            for (auto rtn : helper_methods_map) {
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
                if ( (event_list.find (event_type) != event_list.end ())) {
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

                    find_helper_return_type (event_type, method_name);
                }
            }
        }

        virtual void handle_helpers(const OASIS::Pin::Image & img) {
            // the second iteration looks for helper methods of the event
            for (auto sec : img) {
                for (auto rtn : sec) {
                    if (!rtn.valid ())
                        continue;

                    std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
                    helper_methods_map[rtn_signature] = rtn.address ();  // Store the method name and its return address.
                }
            }

            // If event list is not empty, i.e. it was loaded before the helper image was loaded,
            // then register helper methods immediately.
            if (!event_list.empty()) {
                for (auto event : event_list)
                    check_and_register_valid_helper_method ();
            }
        }

        virtual void analyze_img(const OASIS::Pin::Image & img) {
            this->img_name_ = img.name();
        }

        virtual void analyze_rtn(const OASIS::Pin::Routine & rtn) {
            std::string rtn_signature = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
            std::string rtn_name = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_NAME_ONLY);

            RTN_TYPE rtn_type = is_valid_push_method (rtn_signature);
            
            // the routine is merely a target method signature; map it with its event type
            if (rtn_type == SIGNATURE)
            {
              std::string event_type = get_push_event_type (rtn_signature);
              method_event_map_[rtn_name] = event_type;
              event_list[event_type] = true;

              if (helper_image_loaded_)
                check_and_register_valid_helper_method ();
                
                signature_info * sig_info = new signature_info(this->img_name_, rtn_signature, rtn_name, event_type);
                output_list_.push_back(sig_info);
            }
            // the routine is an actual method call; insert the analysis routine
            else if (rtn_type == METHOD_CALL)
            {
                OASIS::Pin::Routine_Guard guard (rtn);
                // buffers must be used; otherwise the analysis routine cannot be preserved
                item_type helper_buffer (1);
                item_type::iterator helper = helper_buffer.begin ();
                helper->set_target_name (rtn_name);
                helper->set_method_event_map (method_event_map_);
                helper->set_event_helper_map (event_helper_map_);
                helper->set_helper_returntype_map (helper_returntype_map_);
                helper->insert (IPOINT_BEFORE, rtn, 0);
                output_list_.push_back (helper->info_);
                analysis_rtn_buffer_list_.push_back (helper_buffer);

                helper_method_info * helpmeth_info = new helper_method_info(this->img_name_, rtn_signature, rtn_name);
                output_list_.push_back(helpmeth_info);
            }
        }

        virtual list_type & get_list(void) {
          return this->output_list_;
        }
    private:
        //output_list_ - the list of output data
        //analysis_rtn_buffer_list_ - the list that carries all the buffers for routimes
        //event_list - map for registered event types
        //helper_methods_map - map that loads and stores all the methods in the helper image, to be registered later with events
        //method_event_map_ - map between name of the target method and the event type passed into it
        //target_method_list_ - list of the target method call to be instrumented
        //obv_ - Object by value prefix.
        //helper_image_loaded_ - Check if helper image loaded.
        //event_helper_map_ - Map between event and helper
        //helper_returntype_map_ - map between helper and its return types
        //img_name_ - the name of the image
        list_type output_list_;
        analysis_rtn_list_type analysis_rtn_buffer_list_;
        std::unordered_map <std::string, bool> event_list;
        typedef std::unordered_map <std::string, ADDRINT> helper_method_map_type;
        helper_method_map_type helper_methods_map;
        method_event_map_type method_event_map_;
        std::vector<std::string> & target_method_list_;
        std::string & obv_;
        bool helper_image_loaded_;
        event_helper_map_type event_helper_map_;
        helper_returntype_map_type helper_returntype_map_;
        std::string img_name_;
    };

}
}

#endif // !CORBA_MIDDLEWARE_H
