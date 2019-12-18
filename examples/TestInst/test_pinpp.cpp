#include "pin++/Pintool.h"
#include "pin++/Image_Instrument.h"
#include "pin++/Image.h"
#include "pin++/Section.h"
#include "pin++/Routine.h"
#include "pin++/Callback.h"
#include <iostream>
#include <string>
#include <list>

class HandleNyalia : public OASIS::Pin::Callback <HandleNyalia (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
	OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
	OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)> {
  public:
	HandleNyalia(void)
	{ }

	//Nyalia - The handle for the RTN callback. Placing std::string in parameter throws compile error because
	//there is not conversion from ADDRINT to std::string. Can't even use reinterpret_cast.
	void handle_analyze (std::string& a, int b, int c) {
		std::cout << "Pin++: ";
		std::cout << a << " | ";
		std::cout << b << " | ";
		std::cout << c << std::endl;
	}
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument> {
public:
	void handle_instrument (const OASIS::Pin::Image & img) {
		for (auto sec : img) {
			for (auto rtn : sec) {
				if (!rtn.valid())
					continue;

				using OASIS::Pin::Section;
				using OASIS::Pin::Image;

				std::string signature(rtn.name ());
				if (signature.find("_Z6NyaliaRSsii") != std::string::npos) {
					HandleNyalia * m_info = new HandleNyalia;
			
					this->output_list_.push_back (m_info);
					OASIS::Pin::Routine_Guard guard (rtn);
					m_info->insert (IPOINT_BEFORE, rtn, 0, 1, 2);
				}

			}
		}
	}

private:
	std::list<HandleNyalia*> output_list_;
};

class Empty_Tool : public OASIS::Pin::Tool <Empty_Tool> {

public:

    Empty_Tool (void)
    {
        this->init_symbols();
    }

private:
	Instrument inst_;
};

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main (int argc, char * argv []) {
    OASIS::Pin::Pintool <Empty_Tool>(argc, argv).start_program();
    return 0;
}

