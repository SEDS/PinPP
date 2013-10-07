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

}
}
