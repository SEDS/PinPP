// -*- C++ -*-
// $Id: Exception.inl 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

///////////////////////////////////////////////////////////////////////////////
// Exception_Base

inline
EXCEPTION_CLASS Exception_Base::exception_class (EXCEPTION_CODE code)
{
  return PIN_GetExceptionClass (code);
}

///////////////////////////////////////////////////////////////////////////////
// Emulated_Exception

inline
Emulated_Exception::
Emulated_Exception (EXCEPTION_CODE code, ADDRINT addr)
{
  PIN_InitExceptionInfo (&this->ex_info_, code, addr);
}

inline
Emulated_Exception::
Emulated_Exception (EXCEPTION_CODE code, ADDRINT addr, ADDRINT access_addr, FAULTY_ACCESS_TYPE access_type)
{
  PIN_InitAccessFaultInfo (&this->ex_info_, code, addr, access_addr, access_type);
}


#if defined (TARGET_WINDOWS)
inline
Emulated_Exception::Emulated_Exception (UINT32 code, ADDRINT addr, UINT32 args, const ADDRINT *pargs)
{
  PIN_InitWindowsExceptionInfo (&this->ex_info_, code, addr, args, pargs);
}
#endif

inline
Emulated_Exception::~Emulated_Exception (void)
{

}

inline
EXCEPTION_CODE Emulated_Exception::exception_code (void) const
{
  return PIN_GetExceptionCode (&this->ex_info_);
}

inline
EXCEPTION_CLASS Emulated_Exception::exception_class (void) const
{
  return Exception_Base::exception_class (this->exception_code ());
}

inline
ADDRINT Emulated_Exception::exception_address (void) const
{
  return PIN_GetExceptionAddress (&this->ex_info_);
}

inline
VOID Emulated_Exception::exception_address (ADDRINT addr)
{
  PIN_SetExceptionAddress (&this->ex_info_, addr);
}

inline
FAULTY_ACCESS_TYPE Emulated_Exception::faulty_access_type (void) const
{
  return PIN_GetFaultyAccessType (&this->ex_info_);
}

inline
BOOL Emulated_Exception::faulty_access_address (ADDRINT * access_addr) const
{
  return PIN_GetFaultyAccessAddress (&this->ex_info_, access_addr);
}

inline
UINT32 Emulated_Exception::fp_error_set (void) const
{
  return PIN_GetFpErrorSet (&this->ex_info_);
}

#if defined (TARGET_WINDOWS)
inline
UINT32 Emulated_Exception::windows_exception_code (void) const
{
  return PIN_GetWindowsExceptionCode (&this->ex_info_);
}

inline
UINT32 Emulated_Exception::count_windows_exception_arguments (void) const
{
  return PIN_CountWindowsExceptionArguments (&this->ex_info_);
}

inline
ADDRINT Emulated_Exception::windows_exception_argument (UINT32 arg) const
{
  return PIN_GetWindowsExceptionArgument (&this->ex_info_, arg);
}
#endif

inline
std::string Emulated_Exception::to_string (void) const
{
  return PIN_ExceptionToString (&this->ex_info_);
}

inline
void Emulated_Exception::raise (const CONTEXT *ctx, THREADID thr_id)
{
  PIN_RaiseException (ctx, thr_id, &this->ex_info_);
}

///////////////////////////////////////////////////////////////////////////////
// Exception

inline
Exception::Exception (EXCEPTION_INFO * ex_info)
: ex_info_ (ex_info)
{

}

inline
Exception::~Exception (void)
{

}

inline
EXCEPTION_CODE Exception::exception_code (void) const
{
  return PIN_GetExceptionCode (this->ex_info_);
}

inline
EXCEPTION_CLASS Exception::exception_class (void) const
{
  return Exception_Base::exception_class (this->exception_code ());
}

inline
ADDRINT Exception::exception_address (void) const
{
  return PIN_GetExceptionAddress (this->ex_info_);
}

inline
VOID Exception::exception_address (ADDRINT addr)
{
  PIN_SetExceptionAddress (this->ex_info_, addr);
}

inline
FAULTY_ACCESS_TYPE Exception::faulty_access_type (void) const
{
  return PIN_GetFaultyAccessType (this->ex_info_);
}

inline
BOOL Exception::faulty_access_address (ADDRINT * access_addr) const
{
  return PIN_GetFaultyAccessAddress (this->ex_info_, access_addr);
}

inline
UINT32 Exception::fp_error_set (void) const
{
  return PIN_GetFpErrorSet (this->ex_info_);
}

#if defined (TARGET_WINDOWS)
inline
UINT32 Exception::windows_exception_code (void) const
{
  return PIN_GetWindowsExceptionCode (this->ex_info_);
}

inline
UINT32 Exception::count_windows_exception_arguments (void) const
{
  return PIN_CountWindowsExceptionArguments (this->ex_info_);
}

inline
ADDRINT Exception::windows_exception_argument (UINT32 arg) const
{
  return PIN_GetWindowsExceptionArgument (this->ex_info_, arg);
}
#endif

inline
std::string Exception::to_string (void) const
{
  return PIN_ExceptionToString (this->ex_info_);
}

inline
void Exception::raise (const CONTEXT *ctx, THREADID thr_id)
{
  PIN_RaiseException (ctx, thr_id, this->ex_info_);
}

} // namespace OASIS
} // namespace Pin

inline
std::ostream & operator << (std::ostream & ostr, const OASIS::Pin::Exception_Base & ex)
{
  ostr << ex.to_string ();
  return ostr;
}
