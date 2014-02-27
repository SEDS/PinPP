// $Id: malloc_mt.cpp 2300 2013-10-05 05:33:16Z hillj $

#include "pin++/Image_Instrument.h"
#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Guard.h"
#include "pin++/Routine.h"

#include <stdio.h>

#if defined (TARGET_MAC)
  #define MALLOC "_malloc"
#else
  #define MALLOC "malloc"
#endif

class Before_Malloc :
public OASIS::Pin::Callback <Before_Malloc (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE,
                                            OASIS::Pin::ARG_THREAD_ID) >
{
public:
  Before_Malloc (FILE * file, OASIS::Pin::Lock & lock)
    : file_ (file),
      lock_ (lock)
  {
  }

  void handle_analyze (int size, THREADID thr_id)
  {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_, thr_id + 1);

    fprintf (this->file_, "thread %d entered malloc(%d)\n", thr_id, size);
    fflush (this->file_);
  }

private:
  FILE * file_;
  OASIS::Pin::Lock & lock_;
};

class Instrument : public OASIS::Pin::Image_Instrument <Instrument>
{
public:
  Instrument (FILE * file, OASIS::Pin::Lock & lock)
    : before_malloc_ (file, lock)
  {

  }

  void handle_instrument (const OASIS::Pin::Image & img)
  {
    using OASIS::Pin::Routine;
    Routine rtn = img.find_routine (MALLOC);

    if (rtn.valid ())
    {
      using OASIS::Pin::Routine_Guard;
      Routine_Guard guard (rtn);

      rtn.insert_call (IPOINT_BEFORE, &this->before_malloc_, 0);
    }
  }

private:
  Before_Malloc before_malloc_;
};

class malloc_mt : public OASIS::Pin::Tool <malloc_mt>
{
public:
  malloc_mt (void)
    : file_ (fopen ("malloc_mt.out", "w")),
      inst_ (file_, lock_)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
    this->enable_thread_start_callback ();
    this->enable_thread_fini_callback ();
  }

  void handle_fini (INT32)
  {
    fclose (this->file_);
  }

  void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctxt, INT32 code)
  {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_, thr_id + 1);
    fprintf (this->file_, "thread begin %d\n", thr_id);
    fflush (this->file_);
  }

  void handle_thread_fini (THREADID thr_id, const OASIS::Pin::Const_Context & ctxt, INT32 code)
  {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_, thr_id + 1);
    fprintf (this->file_, "thread end %d code %d\n",thr_id, code);
    fflush (this->file_);
  }

private:
  FILE * file_;
  OASIS::Pin::Lock lock_;
  Instrument inst_;
};

DECLARE_PINTOOL (malloc_mt);
