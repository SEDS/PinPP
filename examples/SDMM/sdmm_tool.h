#include "pin++/Image_Instrument.h"
#include "grpc_middleware.h"
#include "corba_middleware.h"
#include "writer.h"
#include "pin++/Pintool.h"
#include "pin++/Image.h"
#include "pin++/Section.h"
#include "pin++/Routine.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <regex>
#include <ctime>

namespace OASIS {
namespace Pin {

    class SDMM_Instrument : public OASIS::Pin::Image_Instrument <SDMM_Instrument>
    {
    public:

        SDMM_Instrument(std::vector<std::string> & include_list,
                std::vector<std::string> & helper_list,
                Middleware * middleware)
            :include_list_(include_list),
            helper_list_(helper_list),
            middleware_(middleware)
        { }

        void handle_instrument (const OASIS::Pin::Image & img) {
            std::clock_t start = std::clock ();
            size_t seperator = std::string::npos;

           this->middleware_->analyze_img(img);

            for (auto include : include_list_) {
                seperator = img.name().find(include);

                if (seperator != std::string::npos) {
                    for (auto sec : img) {
                        for (auto rtn : sec) {
                            if (!rtn.valid())
                                continue;

                            this->middleware_->analyze_rtn(rtn);
                        }
                    }
                }
            }

            size_t sep = std::string::npos;
            for (auto helper : helper_list_) {
                sep = img.name ().find (helper);

                if (sep != std::string::npos) {
                    this->middleware_->handle_helpers(img);
                }
            }
            std::clock_t end = std::clock ();
            std::cout << "Instrument Time consumption: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " (ms)" << std::endl;
        }

	typename Middleware::list_type & get_list(void) {
        return this->middleware_.get_list();
	}

    private:
        //include_list_ - list of the dlls to be included in instrumentation
        //helper_list_ - list of the dlls to be instrumetned to find helper methods.
        //middleware_ - the standards based distributed middlware to use such as CORBA or gRPC
        std::vector<std::string> & include_list_;
        std::vector<std::string> & helper_list_;
        Middleware * middleware_;
    };

    struct SDMM_Tool_Knobs {
        std::string include_;
        std::string helper_;
        std::string target_methods_;
        std::string obv_;
        static KNOB <string> config_file_name_;
    };

    class SDMM_Tool : public OASIS::Pin::Tool <SDMM_Tool> {

    public:

    SDMM_Tool (void)
        :fout_("trace.json"),
        middleware_(nullptr),
        inst_(include_list_,
        helper_list_,
        middleware_)
    {
        // parse the configuration file
        parse_config_file();

        // parse the include dll argument
        std::stringstream include_string (knobs_.include_);
        std::string include;
        while (std::getline (include_string, include, ','))
            include_list_.push_back(include);

        // parse the helper dll argument
        std::stringstream helper_string (knobs_.helper_);
        std::string helper;
        while (std::getline (helper_string, helper, ','))
            helper_list_.push_back(helper);

        // parse the target method argument
        std::stringstream methods_string (knobs_.target_methods_);
        std::string method;
        while (std::getline (methods_string, method, ','))
            target_method_list_.push_back(method);

        // Object by value prefix
        obv = knobs_.obv_.c_str();

        this->init_symbols();
        this->enable_fini_callback();
    }

    ~SDMM_Tool(void) {
        if (this->middleware_ != nullptr) {
            delete middleware_;
        }
    }

    void handle_fini (INT32 code) {
        std::clock_t start = std::clock ();
        typedef Middleware::list_type list_type;
        list_type & info_items = inst_.get_list();
        typename list_type::const_iterator iter=info_items.begin(), iter_end=info_items.end();

        this->fout_ << "{ \"data\": [" << std::endl;

        for (; iter != iter_end; ++iter) {
            (*iter)->write_to(fout_);

            if (iter != std::prev(iter_end)) {
                this->fout_ << "," << std::endl;
            }
        }

        this->fout_ << "]}" << std::endl;
        this->fout_.close ();
        std::clock_t end = std::clock ();
        std::cout << "Output Time consumption: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " (ms)" << std::endl;      
    }

    void parse_config_file() {
        std::ifstream config_file(knobs_.config_file_name_.Value().c_str());

        knobs_.include_ = "";
        knobs_.helper_ = "";
        knobs_.target_methods_ = "push_";
        knobs_.obv_ = "OBV_";

        if (config_file.is_open()) {
            std::string line;
            std::string header_sep("=");

            while (std::getline(config_file, line)) {
                size_t pos = line.find(header_sep);

                if (pos != std::string::npos) {
                    //pos-1 and pos+2 accounts for whitespace
                    std::string key(line.substr(0, pos-1));
                    std::string value(line.substr(pos+2));

                    if (key.find("MIDDLEWARE") != std::string::npos) {
                        if (value.find("CORBA") != std::string::npos) {
                            middleware_ = new CORBA_Middleware(this->target_method_list_, this->obv);
                        } else if (value.find("gRPC") != std::string::npos) {
                            middleware_ = new gRPC_Middleware(this->target_method_list_, this->obv);
                        }

                        std::cout << "Using Middleware --> " << knobs_.middle_type_ << std::endl;
                    } else if (key.find("INCLUDE") != std::string::npos) {
                        knobs_.include_ = value;
                    } else if (key.find("HELPER") != std::string::npos) {
                        knobs_.helper_ = value;
                    }
                }
            }
        }
	    config_file.close();
    }

    private:
        //fout_ - the output file
        //knobs_ the command line arguments for SDMM
        //include_list_ - list of the dlls to be included in instrumentation
        //helper_list_ - list of the dlls to be instrumetned to find helper methods
        //target_method_list_ - list of the target method call to be instrumented
        //obv - Object by value prefix
        //inst_ - the instrumentation object  
        std::ofstream fout_;
        SDMM_Tool_Knobs knobs_;
        std::vector<string> include_list_;
        std::vector<string> helper_list_;
        std::vector<string> target_method_list_;
        std::string obv;
        Middleware * middleware_;
        SDMM_Instrument inst_;
    };
}
}

/*******************************
* KNOB declaration
*******************************/

// syntax:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/sdmm.dll -l <layer1>,<layer2>,... -m <method> -- <program>

// example:
// > $PIN_ROOT/pin -t $PINPP_ROOT/lib/sdmm.dll -l Context,Servant -m push -- <program>
KNOB <string> OASIS::Pin::SDMM_Tool_Knobs::config_file_name_ (KNOB_MODE_WRITEONCE, "pintool", "conf", "config.sdmm", 
                                            "The name of the configuration file SDMM should use");
