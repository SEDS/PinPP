// $Id: Routine.cpp 2302 2013-10-05 05:54:21Z hillj $

#include "Switch.h"

namespace OASIS
{
namespace Pin
{

template <typename REPLACEMENT>
void Routine::replace (void)
{
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  AFUNPTR funcptr = RTN_Replace (this->rtn_, AFUNPTR (REPLACEMENT::execute));
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));
}

template <typename REPLACEMENT>
void Routine::replace_probed (void)
{
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  AFUNPTR funcptr = RTN_ReplaceProbed (this->rtn_, AFUNPTR (REPLACEMENT::execute));
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));
}

template <typename REPLACEMENT>
void Routine::replace_probed (PROBE_MODE mode)
{
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  AFUNPTR funcptr = RTN_ReplaceProbedEx (this->rtn_, mode, AFUNPTR (REPLACEMENT::execute));
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));
}

namespace Impl
{
  template <typename REPLACEMENT>
  struct Replace_Signature0
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignature (rtn,
                              AFUNPTR (REPLACEMENT::execute),
                              IARG_PROTOTYPE,
                              (PROTO)prototype,
                              IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature1
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignature (rtn,
                              AFUNPTR (REPLACEMENT::execute),
                              IARG_PROTOTYPE,
                              (PROTO)prototype,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                              IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature2
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignature (rtn,
                              AFUNPTR (REPLACEMENT::execute),
                              IARG_PROTOTYPE,
                              (PROTO)prototype,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                              IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature3
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignature (rtn,
                              AFUNPTR (REPLACEMENT::execute),
                              IARG_PROTOTYPE,
                              (PROTO)prototype,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                              IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                              IARG_END);
    }
  };
}

template <typename REPLACEMENT>
void Routine::replace_signature (CALLINGSTD_TYPE callstd_type)
{
  Prototype prototype = REPLACEMENT::make_prototype (this->name ().c_str (), callstd_type);

  typedef typename
    Switch <REPLACEMENT::arg_count,
      Case <0, Impl::Replace_Signature0 <REPLACEMENT>,
      Case <1, Impl::Replace_Signature1 <REPLACEMENT>,
      Case <2, Impl::Replace_Signature2 <REPLACEMENT>,
      Case <3, Impl::Replace_Signature3 <REPLACEMENT> > > > > >::result_type
      impl_type;

  AFUNPTR funcptr = impl_type::execute (*this, prototype, callstd_type);

  // Store the orginal function pointer, and close the prototype.
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));

  prototype.close ();
}

namespace Impl
{
  template <typename REPLACEMENT>
  struct Replace_Signature_Probe0
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbed (rtn,
                                    AFUNPTR (REPLACEMENT::execute),
                                    IARG_PROTOTYPE,
                                    (PROTO)prototype,
                                    IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe1
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbed (rtn,
                                    AFUNPTR (REPLACEMENT::execute),
                                    IARG_PROTOTYPE,
                                    (PROTO)prototype,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                    IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe2
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbed (rtn,
                                    AFUNPTR (REPLACEMENT::execute),
                                    IARG_PROTOTYPE,
                                    (PROTO)prototype,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                                    IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe3
  {
    inline static AFUNPTR execute (const Routine & rtn, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbed (rtn,
                                    AFUNPTR (REPLACEMENT::execute),
                                    IARG_PROTOTYPE,
                                    (PROTO)prototype,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                                    IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                                    IARG_END);
    }
  };
}

template <typename REPLACEMENT>
void Routine::replace_signature_probed (CALLINGSTD_TYPE callstd_type)
{
  Prototype prototype = REPLACEMENT::make_prototype (this->name ().c_str (), callstd_type);

  typedef typename
    Switch <REPLACEMENT::arg_count,
      Case <0, Impl::Replace_Signature_Probe0 <REPLACEMENT>,
      Case <1, Impl::Replace_Signature_Probe1 <REPLACEMENT>,
      Case <2, Impl::Replace_Signature_Probe2 <REPLACEMENT>,
      Case <3, Impl::Replace_Signature_Probe3 <REPLACEMENT> > > > > >::result_type
      impl_type;

  AFUNPTR funcptr = impl_type::execute (*this, prototype, callstd_type);

  // Store the orginal function pointer, and close the prototype.
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));

  prototype.close ();
}

namespace Impl
{
  template <typename REPLACEMENT>
  struct Replace_Signature_Probe_Ex0
  {
    inline static AFUNPTR execute (const Routine & rtn, PROBE_MODE mode, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbedEx (rtn,
                                      mode,
                                      AFUNPTR (REPLACEMENT::execute),
                                      IARG_PROTOTYPE,
                                      (PROTO)prototype,
                                      IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe_Ex1
  {
    inline static AFUNPTR execute (const Routine & rtn, PROBE_MODE mode, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbedEx (rtn,
                                      mode,
                                      AFUNPTR (REPLACEMENT::execute),
                                      IARG_PROTOTYPE,
                                      (PROTO)prototype,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                      IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe_Ex2
  {
    inline static AFUNPTR execute (const Routine & rtn, PROBE_MODE mode, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbedEx (rtn,
                                      mode,
                                      AFUNPTR (REPLACEMENT::execute),
                                      IARG_PROTOTYPE,
                                      (PROTO)prototype,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                                      IARG_END);
    }
  };

  template <typename REPLACEMENT>
  struct Replace_Signature_Probe_Ex3
  {
    inline static AFUNPTR execute (const Routine & rtn, PROBE_MODE mode, const Prototype & prototype, CALLINGSTD_TYPE callstd_type)
    {
      return
        RTN_ReplaceSignatureProbedEx (rtn,
                                      mode,
                                      AFUNPTR (REPLACEMENT::execute),
                                      IARG_PROTOTYPE,
                                      (PROTO)prototype,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                                      IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                                      IARG_END);
    }
  };
}

template <typename REPLACEMENT>
void Routine::replace_signature_probed (PROBE_MODE mode, CALLINGSTD_TYPE callstd_type)
{
  Prototype prototype = REPLACEMENT::make_prototype (this->name ().c_str (), callstd_type);

  typedef typename
    Switch <REPLACEMENT::arg_count,
      Case <0, Impl::Replace_Signature_Probe_Ex0 <REPLACEMENT>,
      Case <1, Impl::Replace_Signature_Probe_Ex1 <REPLACEMENT>,
      Case <2, Impl::Replace_Signature_Probe_Ex2 <REPLACEMENT>,
      Case <3, Impl::Replace_Signature_Probe_Ex3 <REPLACEMENT> > > > > >::result_type
      impl_type;

  AFUNPTR funcptr = impl_type::execute (*this, mode, prototype, callstd_type);

  // Store the orginal function pointer, and close the prototype.
  typedef typename REPLACEMENT::funcptr_type funcptr_type;
  REPLACEMENT::original_funcptr (reinterpret_cast <funcptr_type> (funcptr));

  prototype.close ();
}

}
}
