// $Id: pinatrace.cpp 2290 2013-09-20 05:02:26Z hillj $

#include <stdio.h>

#include "pin++/Instruction_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Operand.h"

#if defined (TARGET_MAC)
  #define MALLOC "_malloc"
  #define FREE "_free"
#else
  #define MALLOC "malloc"
  #define FREE "free"
#endif

/**
 * @class Record_Memory_Read
 */
class Record_Memory_Read :
public OASIS::Pin::Callback <Record_Memory_Read (OASIS::Pin::ARG_INST_PTR,
                                                 OASIS::Pin::ARG_MEMORYOP_EA) >
{
public:
  Record_Memory_Read (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ip, ADDRINT addr)
  {
    fprintf (this->file_, "%p: R %p\n", ip, addr);
  }

private:
  FILE * file_;
};

/**
 * @class Record_Memory_Write
 */
class Record_Memory_Write :
  public OASIS::Pin::Callback <Record_Memory_Write (OASIS::Pin::ARG_INST_PTR,
                                                    OASIS::Pin::ARG_MEMORYOP_EA) >
{
public:
  Record_Memory_Write (FILE * file)
    : file_ (file)
  {

  }

  inline void handle_analyze (ADDRINT ip, ADDRINT addr)
  {
    fprintf (this->file_,"%p: W %p\n", ip, addr);
  }

private:
  FILE * file_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : mem_read_ (file),
      mem_write_ (file)
  {

  }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    // Instruments memory accesses using a predicated call, i.e.
    // the instrumentation is called iff the instruction will actually be executed.
    //
    // On the IA-32 and Intel(R) 64 architectures conditional moves and REP
    // prefixed instructions appear as predicated instructions in Pin.
    UINT32 operands = ins.memory_operand_count ();

    // Iterate over each memory operand of the instruction.
    for (UINT32 mem_op = 0; mem_op < operands; ++ mem_op)
    {
      if (ins [mem_op].is_memory_read ())
        this->mem_read_.insert_predicated (IPOINT_BEFORE, ins, mem_op);

      // Note that in some architectures a single memory operand can be
      // both read and written (for instance incl (%eax) on IA-32)
      // In that case we instrument it once for read and once for write.
      if (ins [mem_op].is_memory_written ())
        this->mem_write_.insert_predicated (IPOINT_BEFORE, ins, mem_op);
    }
  }

private:
  FILE * file_;
  Record_Memory_Read mem_read_;
  Record_Memory_Write mem_write_;
};

class pinatrace : public OASIS::Pin::Tool <pinatrace>
{
public:
  pinatrace (void)
    : file_ (fopen ("pinatrace.out", "w")),
      inst_ (file_)
  {
    this->enable_fini_callback ();
  }

  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  Instrument inst_;
};

DECLARE_PINTOOL (pinatrace);
