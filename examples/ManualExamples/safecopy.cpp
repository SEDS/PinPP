// $Id: inscount0.cpp 2285 2013-09-18 05:24:04Z hillj $

#include "pin++/Callback.h"
#include "pin++/Instruction_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Copy.h"
#include "pin++/Operand.h"

#include <fstream>
#include <memory>

class do_load : public OASIS::Pin::Callback < do_load (OASIS::Pin::ARG_MEMORYREAD_EA) >
{
public:
  do_load (std::ofstream & fout, REG reg)
  : fout_ (fout),
    reg_ (reg)
  {
  }
  
  void handle_analyze (ADDRINT addr)
  {
    this->fout_ << "Emulate loading from addr " << addr << " to " << REG_StringShort (this->reg_) << std::endl;
    OASIS::Pin::Copy <ADDRINT> value ((VOID *)addr);
    
    // TODO Add support for return value from analysis function.
    
    //return value;
  }
  
private:
  std::ofstream & fout_;
  REG reg_;
};

class Emulate_Load : public OASIS::Pin::Instruction_Instrument <Emulate_Load>
{
public:
  Emulate_Load (std::ofstream & fout)
  : fout_ (fout)
  {
    
  }
  
  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    if (ins.opcode () == XED_ICLASS_MOV &&
        ins.is_memory_read () &&
        ins.operand (0).is_reg () &&
        ins.operand (1).is_memory ())
    {
      // Allocate a new callback for the instruction.
      auto callback = std::shared_ptr <do_load> (new do_load (this->fout_, ins.operand (0).reg ()));
      callback->insert (IPOINT_BEFORE, ins);
      
      // Save the callback.
      this->callbacks_.push_back (callback);
      
      /*
       
        TODO Implement the correct callback.
       
      // op0 <- *op1
      INS_InsertCall(ins,
                     IPOINT_BEFORE,
                     AFUNPTR(DoLoad),
                     IARG_UINT32,
                     REG(INS_OperandReg(ins, 0)),
                     IARG_MEMORYREAD_EA,
                     IARG_RETURN_REGS,
                     INS_OperandReg(ins, 0),
                     IARG_END);
      
      // Delete the instruction
      INS_Delete(ins); */
    }
  }
  
private:
  std::ofstream & fout_;
  std::vector < std::shared_ptr <do_load> > callbacks_;
};

class safecopy : public OASIS::Pin::Tool <safecopy>
{
public:
  safecopy (void)
  : fout_ ("safecopy.out"),
    emulate_load_ (fout_)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }
  
  void handle_fini (INT32 code)
  {
    this->fout_.close ();
  }
  
private:
  std::ofstream fout_;
  Emulate_Load emulate_load_;
};

DECLARE_PINTOOL (safecopy);
