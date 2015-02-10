
#include "pin++/Lock.h"
#include "pin++/Guard.h"
#include "pin++/Trace_Buffer.h"
#include "pin++/Trace_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Operand.h"

#if !defined (TARGET_WINDOWS)
#include "pin++/TLS.h"
#endif

#include <fstream>
#include <sstream>

#if !defined (TARGET_WINDOWS)
#include "portability.H"
#endif

/*
 * Record of memory references.  Rather than having two separate
 * buffers for reads and writes, we just use one struct that includes a
 * flag for type.
 */
struct MEMREF
{
  THREADID tid;
  ADDRINT pc;
  ADDRINT ea;
  UINT32 size;
  UINT32 read;
};

#if !defined (TARGET_WINDOWS)
/*
 * MLOG - thread specific data that is not handled by the buffering API.
 */
class MLOG
{
public:
  MLOG (THREADID tid)
  {
    std::ostringstream filename;
    filename << "buffer." << getpid_portable () << "." << tid;
    this->file_.open (filename.str ().c_str ());

    if (!this->file_.is_open ())
    {
      cerr << "Error: could not open output file." << endl;
      exit (1);
    }

    this->file_ << std::hex;
  }

  ~MLOG (void)
  {
    if (this->file_.is_open ())
      this->file_.close ();
  }

  VOID dump_buffer_to_file (struct MEMREF * reference, UINT64 elements, THREADID tid)
  {
    for (UINT64 i = 0; i < elements; ++ i, ++ reference)
    {
      if (reference->ea != 0)
        this->file_ << reference->pc << "   " << reference->ea << std::endl;
    }
  }

private:
  std::ofstream file_;
};
#endif

/**
 * @class Buffer_Fill
 *
 * Class responsible for handling callbacks when the trace buffer is full.
 */
class Buffer_Full : public OASIS::Pin::Trace_Buffer <Buffer_Full, MEMREF>
{
public:
#if defined (TARGET_WINDOWS)
  Buffer_Full (const OASIS::Pin::Lock & lock, std::ostream & out, UINT32 pages)
    : OASIS::Pin::Trace_Buffer <Buffer_Full, MEMREF> (pages),
      lock_ (lock),
      out_ (out),
      write_to_output_file_ (false)
#else
  Buffer_Full (const OASIS::Pin::TLS <MLOG> & tls_mlog, UINT32 pages)
    : OASIS::Pin::Trace_Buffer <Buffer_Full, MEMREF> (pages)
#endif
  {

  }


  element_type * handle_trace_buffer (BUFFER_ID id, THREADID tid, const OASIS::Pin::Context & ctx, element_type * buf, UINT64 elements)
  {
    cerr << "handle trace buffer" << std::endl;
    
#if defined (TARGET_WINDOWS)
    // Windows implementation for writing buffer to the file. It must take
    // a lock to ensure that no other operations occur on the file while the
    // current thread is writing to the file. This is very slow, but the only
    // workaround according to Pin.
    if (!this->write_to_output_file_)
      return buf;

    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_);

    for (UINT64 i = 0; i < elements; ++ i, ++ buf)
    {
      if (0 != buf->ea)
        this->out_ << tid << "   "  << buf->pc << "   " << buf->ea << std::endl;
    }
#else
    // Non-Windows implementation for writing trace buffer to a file. This
    // version is more effecient than the Window implementation above according
    // to the Pin documentation.
    this->tls_mlog_.get (tid)->dump_buffer_to_file (buf, elements, tid);
#endif

    return buf;
  }

#if defined (TARGET_WINDOWS)
  void write_to_output_file (bool flag)
  {
    this->write_to_output_file_ = flag;
  }
#endif

private:
#if defined (TARGET_WINDOWS)
  OASIS::Pin::Lock lock_;
  std::ostream & out_;
  bool write_to_output_file_;
#else
  OASIS::Pin::TLS <MLOG> tls_mlog_;
#endif
};

class Trace : public OASIS::Pin::Trace_Instrument <Trace>
{
public:
#if defined (TARGET_WINDOWS)
  Trace (void)
    : fout_ ("buffer.out"),
      buffer_full_ (lock_, fout_, 1024)
#else
  Trace (const OASIS::Pin::TLS <MLOG> & tls_mlog)
    : buffer_full_ (tls_mlog, 1024)
#endif
  {
#if defined (TARGET_WINDOWS)
    this->buffer_full_.write_to_output_file (true);
#endif
  }

  void handle_instrument (const OASIS::Pin::Trace & trace)
  {
    using OASIS::Pin::Operand;

    for (OASIS::Pin::Bbl & bbl : trace)
    {
      for (OASIS::Pin::Ins & ins : bbl)
      {
        UINT32 mem_operands = ins.memory_operand_count ();

        for (UINT32 mem_op = 0; mem_op < mem_operands; ++ mem_op)
        {
          Memory_Operand operand = ins.memory_operand (mem_op);
          UINT32 ref_size = operand.size ();

          // Note that if the operand is both read and written we log it once
          // for each.
          if (operand.is_read ())
            INS_InsertFillBuffer (ins,
                                  IPOINT_BEFORE, this->buffer_full_.buffer_id (),
                                  IARG_INST_PTR, offsetof (struct MEMREF, pc),
                                  IARG_MEMORYOP_EA, mem_op, offsetof (struct MEMREF, ea),
                                  IARG_UINT32, ref_size, offsetof (struct MEMREF, size),
                                  IARG_BOOL, TRUE, offsetof (struct MEMREF, read),
                                  IARG_END);

          if (operand.is_memory_written ())
            INS_InsertFillBuffer (ins,
                                  IPOINT_BEFORE, this->buffer_full_.buffer_id (),
                                  IARG_INST_PTR, offsetof(struct MEMREF, pc),
                                  IARG_MEMORYOP_EA, mem_op, offsetof(struct MEMREF, ea),
                                  IARG_UINT32, ref_size, offsetof(struct MEMREF, size),
                                  IARG_BOOL, FALSE, offsetof(struct MEMREF, read),
                                  IARG_END);
        }
      }
    }
  }

#if defined (TARGET_WINDOWS)
  void handle_fini (void)
  {
    OASIS::Pin::Guard <OASIS::Pin::Lock> guard (this->lock_);
    this->fout_.close ();
  }
#endif

private:
#if defined (TARGET_WINDOWS)
  OASIS::Pin::Lock lock_;
  std::ofstream fout_;
#endif

  Buffer_Full buffer_full_;
};

class buffer : public OASIS::Pin::Tool <buffer>
{
public:
  buffer (void)
#if !defined (TARGET_WINDOWS)
    : trace_ (tls_mlog_)
#endif
  {
#if defined (TARGET_WINDOWS)
    this->enable_fini_callback ();
#else
    this->enable_thread_start_callback ();
    this->enable_thread_fini_callback ();
#endif
  }

  void handle_thread_start (THREADID thr_id, OASIS::Pin::Context & ctx, INT32 flags)
  {
#if !defined (TARGET_WINDOWS)
    this->tls_mlog_.set (thr_id, new MLOG (thr_id));
#endif
  }

  void handle_thread_fini (THREADID thr_id, const OASIS::Pin::Context & ctx, INT32 flags)
  {
#if !defined (TARGET_WINDOWS)
    std::cerr << "Deleting TLS data" << std::endl;
    delete this->tls_mlog_.get (thr_id);
    this->tls_mlog_.set (thr_id, 0);
#endif
  }

#if defined (TARGET_WINDOWS)
  void handle_fini (INT32 code)
  {
    this->trace_.handle_fini ();
  }
#endif

private:
#if !defined (TARGET_WINDOWS)
  OASIS::Pin::TLS <MLOG> tls_mlog_;
#endif

  Trace trace_;
};

DECLARE_PINTOOL (buffer);
