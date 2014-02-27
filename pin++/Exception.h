// -*- C++ -*-

//==============================================================================
/**
 *  @file        Exception.h
 *
 *  $Id: Exception.h 2307 2013-10-07 05:05:04Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_EXCEPTION_H_
#define _OASIS_PIN_EXCEPTION_H_

namespace OASIS
{
namespace Pin
{

/**
 * @class Exception_Base
 *
 * Interface that defines all method expected in the Exception API.
 */
class Exception_Base
{
public:
  virtual EXCEPTION_CODE exception_code (void) const = 0;
  virtual EXCEPTION_CLASS exception_class (void) const = 0;
  static EXCEPTION_CLASS exception_class (EXCEPTION_CODE code);

  virtual ADDRINT exception_address (void) const = 0;
  virtual VOID exception_address (ADDRINT addr) = 0;

  virtual FAULTY_ACCESS_TYPE faulty_access_type (void) const = 0;
  virtual BOOL faulty_access_address (ADDRINT * pAccessAddress) const = 0;

  virtual UINT32 fp_error_set (void) const = 0;

#if defined (TARGET_WINDOWS)
  virtual UINT32 windows_exception_code (void) const = 0;
  virtual UINT32 count_windows_exception_arguments (void) const = 0;
  virtual ADDRINT windows_exception_argument (UINT32 arg) const = 0;
#endif

  virtual std::string to_string (void) const = 0;
  virtual void raise (const CONTEXT * ctx, THREADID thr_id) = 0;
};

/**
 * @class Emulated_Exception
 *
 * Exception that can be raised from a tool.
 */
class Emulated_Exception : public Exception_Base
{
public:
  /// Default constructor.
  Emulated_Exception (EXCEPTION_CODE code, ADDRINT addr);
  Emulated_Exception (EXCEPTION_CODE code, ADDRINT addr, ADDRINT access_addr, FAULTY_ACCESS_TYPE access_type = FAULTY_ACCESS_TYPE_UNKNOWN);

#if defined (TARGET_WINDOWS)
  Emulated_Exception (UINT32 code, ADDRINT addr, UINT32 args = 0, const ADDRINT *pargs = 0);
#endif

  /// Destructor.
  ~Emulated_Exception (void);

  EXCEPTION_CODE exception_code (void) const;
  EXCEPTION_CLASS exception_class (void) const;

  ADDRINT exception_address (void) const;
  VOID exception_address (ADDRINT addr);

  FAULTY_ACCESS_TYPE faulty_access_type (void) const;
  BOOL faulty_access_address (ADDRINT * pAccessAddress) const;

  UINT32 fp_error_set (void) const;

#if defined (TARGET_WINDOWS)
  UINT32 windows_exception_code (void) const;
  UINT32 count_windows_exception_arguments (void) const;
  ADDRINT windows_exception_argument (UINT32 arg) const;
#endif

  std::string to_string (void) const;
  void raise (const CONTEXT * ctx, THREADID thr_id);

private:
  EXCEPTION_INFO ex_info_;
};

/**
 * @class Exception
 *
 * Wrapper class for handled exceptions
 */
class Exception : public Exception_Base
{
public:
  /// Default constructor.
  Exception (EXCEPTION_INFO * ex_info);

  /// Destructor.
  ~Exception (void);

  EXCEPTION_CODE exception_code (void) const;
  EXCEPTION_CLASS exception_class (void) const;

  ADDRINT exception_address (void) const;
  VOID exception_address (ADDRINT addr);

  FAULTY_ACCESS_TYPE faulty_access_type (void) const;
  BOOL faulty_access_address (ADDRINT * pAccessAddress) const;

  UINT32 fp_error_set (void) const;

#if defined (TARGET_WINDOWS)
  UINT32 windows_exception_code (void) const;
  UINT32 count_windows_exception_arguments (void) const;
  ADDRINT windows_exception_argument (UINT32 arg) const;
#endif

  std::string to_string (void) const;
  void raise (const CONTEXT * ctx, THREADID thr_id);

private:
  EXCEPTION_INFO * ex_info_;
};

} // namespace OASIS
} // namespace Pin

std::ostream & operator << (std::ostream & ostr, const OASIS::Pin::Exception_Base & ex);

#include "Exception.inl"

#endif  // _OASIS_PIN_EXCEPTION_H_
