// $Id: inscount_tls.cpp 2286 2013-09-19 18:40:30Z hillj $

#include "pin++/Buffer.h"
#include "pin++/Callback.h"
#include "pin++/Guard.h"
#include "pin++/Lock.h"
#include "pin++/Trace_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/TLS.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

// Force each thread's data to be in its own data cache line so that
// multiple threads do not contend for the same data cache line.
// This avoids the false sharing problem.
#define PADSIZE 56  // 64 byte line size: 64-8

class thread_data_t
{
public:
  thread_data_t (void)
    : count_ (0) { }

  UINT64 count_;
  UINT8 pad_[PADSIZE];
};

class docount : public OASIS::Pin::Callback < docount (OASIS::Pin::ARG_THREAD_ID) >
{
public:
  docount (void)
    : tls_ (0),
      ins_count_ (0)
  {

  }

  void init (OASIS::Pin::TLS <thread_data_t> * tls, UINT64 count)
  {
    this->tls_ = tls;
    this->ins_count_ = count;
  }

  void handle_analyze (THREADID thr_id)
  {
    this->tls_->get (thr_id)->count_ += this->ins_count_;
  }

private:
  OASIS::Pin::TLS <thread_data_t> * tls_;
  UINT64 ins_count_;
};

class Trace : public OASIS::Pin::Trace_Instrument <Trace>
{
public:
  Trace (void)
    : num_threads_ (0)
  {

  }

  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    // Visit every block in the trace, and attach a counter.
    item_type item (trace.num_bbl ());
    item_type::iterator callback = item.begin ();

#if defined (TARGET_WINDOWS) && (_MSC_VER == 1600)
   for each (OASIS::Pin::Bbl & bbl in trace)
#else
   for (OASIS::Pin::Bbl & bbl : trace)
#endif
    {
      callback->init (&this->tls_, bbl.ins_count ());
      callback->insert (IPOINT_BEFORE, bbl);

      ++ callback;
    }

    this->traces_.push_back (item);
  }

  void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctxt, INT32 flags)
  {
    do
    {
      OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_);
      ++ this->num_threads_;
    } while (false);

    this->tls_.set (thr_id, new thread_data_t ());
  }

  void handle_fini (INT32)
  {
    std::ofstream fout ("inscount_tls.out");
    fout << "Total number of threads = " << this->num_threads_ << endl;

    for (INT32 t = 0; t < this->num_threads_; t ++)
      fout << "Count[" << decstr (t) << "]= " << this->tls_.get (t)->count_ << std::endl;

    fout.close ();
  }

  inline int num_threads (void) const
  {
    return this->num_threads_;
  }

  inline const OASIS::Pin::TLS <thread_data_t> & tls (void) const
  {
    return this->tls_;
  }

private:
  typedef OASIS::Pin::Buffer <docount> item_type;
  typedef std::list <item_type> list_type;

  OASIS::Pin::TLS <thread_data_t> tls_;
  OASIS::Pin::Lock lock_;
  int num_threads_;
  list_type traces_;
};

class inscount_tls : public OASIS::Pin::Tool <inscount_tls>
{
public:
  inscount_tls (void)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
    this->enable_thread_start_callback ();
  }

  void handle_fini (INT32)
  {
    std::ofstream fout ("inscount_tls.out");
    fout << "Total number of threads = " << this->trace_.num_threads () << endl;

    for (INT32 t = 0; t < this->trace_.num_threads (); t ++)
      fout << "Count[" << decstr (t) << "]= " << this->trace_.tls ().get (t)->count_ << std::endl;

    fout.close ();
  }

  void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctxt, INT32 flags)
  {
    this->trace_.handle_thread_start (thr_id, ctxt, flags);
  }

private:
  Trace trace_;
};

DECLARE_PINTOOL (inscount_tls)
