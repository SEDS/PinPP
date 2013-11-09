// $Id: Replacement_Routine.inl 2294 2013-10-01 20:09:09Z hillj $

namespace OASIS
{
namespace Pin
{

///////////////////////////////////////////////////////////////////////////////
// R (void)

template <typename T, typename R>
typename Replacement_Routine <T, R (void)>::funcptr_type
Replacement_Routine <T, R (void)>::orig_funcptr_ = 0;

template <typename T, typename R>
inline
void Replacement_Routine <T, R (void)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R>
inline
typename Replacement_Routine <T, R (void)>::funcptr_type
Replacement_Routine <T, R (void)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R>
inline
Prototype Replacement_Routine <T, R (void)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG_END ());
}

template <typename T, typename R>
inline
R Replacement_Routine <T, R (void)>::call_original (void)
{
  return orig_funcptr_ ();
}

///////////////////////////////////////////////////////////////////////////////
// R (P1)

template <typename T, typename R, typename P1>
typename Replacement_Routine <T, R (P1)>::funcptr_type
Replacement_Routine <T, R (P1)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1>
inline
void Replacement_Routine <T, R (P1)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1>
inline
typename Replacement_Routine <T, R(P1)>::funcptr_type
Replacement_Routine <T, R(P1)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1>
inline
Prototype Replacement_Routine <T, R(P1)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1>
inline
R Replacement_Routine <T, R(P1)>::call_original (P1 p1)
{
  return orig_funcptr_ (p1);
}

///////////////////////////////////////////////////////////////////////////////
// R (P1, P2)

template <typename T, typename R, typename P1, typename P2>
typename Replacement_Routine <T, R(P1, P2)>::funcptr_type
Replacement_Routine <T, R(P1, P2)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1, typename P2>
inline
void Replacement_Routine <T, R(P1, P2)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1, typename P2>
inline
typename Replacement_Routine <T, R(P1, P2)>::funcptr_type
Replacement_Routine <T, R(P1, P2)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1, typename P2>
inline
Prototype Replacement_Routine <T, R(P1, P2)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG (P2),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1, typename P2>
inline
R Replacement_Routine <T, R(P1, P2)>::call_original (P1 p1, P2 p2)
{
  return orig_funcptr_ (p1, p2);
}

///////////////////////////////////////////////////////////////////////////////
// R (P1, P2, P3)

template <typename T, typename R, typename P1, typename P2, typename P3>
typename Replacement_Routine <T, R(P1, P2, P3)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1, typename P2, typename P3>
inline
void Replacement_Routine <T, R(P1, P2, P3)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1, typename P2, typename P3>
inline
typename Replacement_Routine <T, R(P1, P2, P3)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1, typename P2, typename P3>
inline
Prototype Replacement_Routine <T, R(P1, P2, P3)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG (P2),
                         PIN_PARG (P3),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1, typename P2, typename P3>
inline
R Replacement_Routine <T, R(P1, P2, P3)>::call_original (P1 p1, P2 p2, P3 p3)
{
  return orig_funcptr_ (p1, p2, p3);
}

///////////////////////////////////////////////////////////////////////////////
// R (P1, P2, P3, P4)

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
typename Replacement_Routine <T, R(P1, P2, P3, P4)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
inline
void Replacement_Routine <T, R(P1, P2, P3, P4)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
inline
typename Replacement_Routine <T, R(P1, P2, P3, P4)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
inline
Prototype Replacement_Routine <T, R(P1, P2, P3, P4)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG (P2),
                         PIN_PARG (P3),
                         PIN_PARG (P4),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
inline
R Replacement_Routine <T, R(P1, P2, P3, P4)>::call_original (P1 p1, P2 p2, P3 p3, P4 p4)
{
  return orig_funcptr_ (p1, p2, p3, p4);
}

///////////////////////////////////////////////////////////////////////////////
// R (P1, P2, P3, P4, P5)

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
typename Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
inline
void Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
inline
typename Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
inline
Prototype Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG (P2),
                         PIN_PARG (P3),
                         PIN_PARG (P4),
                         PIN_PARG (P5),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
inline
R Replacement_Routine <T, R(P1, P2, P3, P4, P5)>::call_original (P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
  return orig_funcptr_ (p1, p2, p3, p4, p5);
}

///////////////////////////////////////////////////////////////////////////////
// R (P1, P2, P3, P4, P5, P6)

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
typename Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::orig_funcptr_ = 0;

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline
void Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::original_funcptr (funcptr_type funcptr)
{
  orig_funcptr_ = funcptr;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline
typename Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::funcptr_type
Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::original_funcptr (void)
{
  return orig_funcptr_;
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline
Prototype Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::
make_prototype (const char * name, CALLINGSTD_TYPE callstd_type)
{
  return PROTO_Allocate (PIN_PARG (R),
                         callstd_type,
                         name,
                         PIN_PARG (P1),
                         PIN_PARG (P2),
                         PIN_PARG (P3),
                         PIN_PARG (P4),
                         PIN_PARG (P5),
                         PIN_PARG (P6),
                         PIN_PARG_END ());
}

template <typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline
R Replacement_Routine <T, R(P1, P2, P3, P4, P5, P6)>::call_original (P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
  return orig_funcptr_ (p1, p2, p3, p4, p5, p6);
}

}
}
