// $Id: stubcount.cpp 11:28 AM 7/22/2019 nlui $

#include "pin++/Image_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Section.h"
#include "pin++/Image.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <memory>
#include <regex>

template <class T>
struct return_type;

template <class T, class... Args>
struct return_type<T(*)(Args...)> {
	typedef T type;
};

template <class T, class... Args>
struct return_type<T(*)(Args..., ...)> {
	typedef T type;
};

template<typename T>
struct type_to_string {
	static std::string str() {
		return typeid(T).name();
	}
};

template<>
struct type_to_string<void> {
	static std::string str() {
		return std::string("void");
	}
};

template<>
struct type_to_string<short int> {
	static std::string str() {
		return std::string("short int");
	}
};

template<>
struct type_to_string<unsigned short int> {
	static std::string str() {
		return std::string("unsigned short int");
	}
};

template<>
struct type_to_string<unsigned int> {
	static std::string str() {
		return std::string("unsigned int");
	}
};

template<>
struct type_to_string<int> {
	static std::string str() {
		return std::string("int");
	}
};

template<>
struct type_to_string<long int> {
	static std::string str() {
		return std::string("long int");
	}
};

template<>
struct type_to_string<unsigned long int> {
	static std::string str() {
		return std::string("unsigned long int");
	}
};

template<>
struct type_to_string<long long int> {
	static std::string str() {
		return std::string("long long int");
	}
};

template<>
struct type_to_string<unsigned long long int> {
	static std::string str() {
		return std::string("unsigned long long int");
	}
};

template<>
struct type_to_string<char> {
	static std::string str() {
		return std::string("char");
	}
};

template<>
struct type_to_string<signed char> {
	static std::string str() {
		return std::string("signed char");
	}
};

template<>
struct type_to_string<unsigned char> {
	static std::string str() {
		return std::string("unsigned char");
	}
};

template<>
struct type_to_string<float> {
	static std::string str() {
		return std::string("float");
	}
};

template<>
struct type_to_string<double> {
	static std::string str() {
		return std::string("double");
	}
};

template<>
struct type_to_string<long double> {
	static std::string str() {
		return std::string("long double");
	}
};

template<>
struct type_to_string<bool> {
	static std::string str() {
		return std::string("bool");
	}
};

template<>
struct type_to_string<wchar_t> {
	static std::string str() {
		return std::string("wchar_t");
	}
};

struct func_info {
	std::string sign;
	std::string returntype;
	std::string image;
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument> {
public:
  typedef std::list <func_info> list_type;

  Instrument(void) { }

  void handle_instrument (const OASIS::Pin::Image & img) {
    for (auto sec : img) {
        for (auto rtn : sec) {
            if (!rtn.valid ())
              continue;

            std::string rtn_sign = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_COMPLETE);
	    auto p = rtn.function_ptr();
	    std::string rtn_returntype = type_to_string<return_type<decltype(p)>::type>::str();
	    std::string img_name = img.name();

	    func_info info;
	    info.sign = rtn_sign;
	    info.returntype = rtn_returntype;
	    info.image = img_name;

            // Add the signature to the listing.
            this->rtn_signatures_.push_back(info);
        }
    }
  }

  const list_type & rtn_signature (void) const {
    return this->rtn_signatures_;
  }

private:
  list_type rtn_signatures_;
};

class stubcount : public OASIS::Pin::Tool <stubcount> {
public:
  stubcount (void)
    : fout_ ("stubcount.json")
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  void handle_fini (INT32) {
    this->fout_ << "{ \"data\": [" << std::endl;

    //regular expression for finding valid procedures
    //only want procedures that use a Stub followed by a ClientContext, this means
    //the client context is a parameter to the stub call.
    std::regex stub_regex("(.*)(Stub)(.*)(ClientContext)(.*)");

    Instrument::list_type inst_list = inst_.rtn_signature();

    for (func_info info : inst_list) {
       //only print info if the procedure has "Stub" and "ClientContext" in the string
       if (std::regex_match(info.sign, stub_regex)) {
         this->fout_ << "{"
         << "\"Procedure\": \"" << info.sign << "\","
         << "\"ReturnType\": \"" << info.returntype << "\","
         << "\"Image\": \"" << info.image << "\"}," << std::endl;
       }
    }

    this->fout_ << "]}" << std::endl;

    this->fout_.close ();
  }

private:
  Instrument inst_;

  std::ofstream fout_;
};

DECLARE_PINTOOL (stubcount);
