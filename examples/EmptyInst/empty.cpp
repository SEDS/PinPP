#include "pin.H"
#include <iostream>
#include <string>

/* ===================================================================== */


/* ===================================================================== */
/* Analysis routines                                                     */
/* ===================================================================== */
 
VOID HandleNyalia(CHAR * name, std::string a, int b, int c)
{
  std::cout << name << " | ";
  std::cout << a << " | ";
  std::cout << b << " | ";
  std::cout << c << std::endl;
}


/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */
   
VOID Image(IMG img, VOID *v)
{
    RTN nyalia_rtn = RTN_FindByName(img, "_Z6NyaliaSsii");
    
    if (RTN_Valid(nyalia_rtn))
    {
        RTN_Open(nyalia_rtn);
        RTN_InsertCall(nyalia_rtn, IPOINT_BEFORE, (AFUNPTR)HandleNyalia,
                       IARG_ADDRINT, "_Z6NyaliaSsii",
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                       IARG_END);
        RTN_Close(nyalia_rtn);
    }
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
   
INT32 Usage()
{
    std::cerr << "This tool is used for testing PIN and Pin++" << std::endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
