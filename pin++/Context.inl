// -*- C++ -*-
// $Id: Context.inl 2289 2013-09-20 05:01:08Z hillj $

namespace OASIS
{
namespace Pin
{

///////////////////////////////////////////////////////////////////////////////
// class Context_Base

//
// Context_Base
//
template <typename T>
inline
Context_Base <T>::Context_Base (T ctx)
: ctx_ (ctx)
{

}

//
// ~Context_Base
//
template <typename T>
inline
Context_Base <T>::~Context_Base (void)
{

}

//
// operator CONTEXT * ()
//
template <typename T>
inline
Context_Base <T>::operator T () const
{
  return this->ctx_;
}

//
// supports_processor_state
//
template <typename T>
inline
bool Context_Base <T>::supports_processor_state (const PROCESSOR_STATE state)
{
  return PIN_SupportsProcessorState (state);
}

//
// get_regval
//
template <typename T>
inline
#if (PIN_BUILD_NUMBER <= 61206)
void Context_Base <T>::get_regval (REG reg, REGVAL *val) const
#else
void Context_Base <T>::get_regval (REG reg, UINT8 *val) const
#endif
{
  PIN_GetContextRegval (this->ctx_, reg, val);
}

//
// get_reg
//
template <typename T>
inline
ADDRINT Context_Base <T>::get_reg (REG reg) const
{
  return PIN_GetContextReg (this->ctx_, reg);
}

//
// execute_at
//
template <typename T>
inline
void Context_Base <T>::execute_at (void) const
{
  PIN_ExecuteAt (this->ctx_);
}

//
// get_syscall_return
//
template <typename T>
inline
ADDRINT Context_Base <T>::get_syscall_return (SYSCALL_STANDARD std) const
{
  return PIN_GetSyscallReturn (this->ctx_, std);
}

//
// get_syscall_number
//
template <typename T>
inline
ADDRINT Context_Base <T>::get_syscall_number (SYSCALL_STANDARD std) const
{
  return PIN_GetSyscallNumber (this->ctx_, std);
}

//
// get_syscall_argument
//
template <typename T>
inline
ADDRINT Context_Base <T>::get_syscall_argument (SYSCALL_STANDARD std, UINT32 num) const
{
  return PIN_GetSyscallArgument (this->ctx_, std, num);
}

///////////////////////////////////////////////////////////////////////////////
// class Const_Context

//
// Const_Context
//
inline
Const_Context::Const_Context (const CONTEXT * ctx)
: Context_Base <const CONTEXT *>  (ctx)
{

}

//
// ~Const_Context
//
inline
Const_Context::~Const_Context (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// class Context

//
// Context
//
inline
Context::Context (const Context & ctx)
: Context_Base <CONTEXT *> (ctx.ctx_)
{

}

//
// Context
//
inline
Context::Context (CONTEXT * ctx)
: Context_Base <CONTEXT *> (ctx)
{

}

//
// ~Context
//
inline
Context::~Context (void)
{

}

//
// supports_processor_state
//
inline
bool Context::supports_processor_state (PROCESSOR_STATE state)
{
  return PIN_SupportsProcessorState (state);
}

//
// contains_state
//
inline
bool Context::contains_state (PROCESSOR_STATE state)
{
  return PIN_ContextContainsState (this->ctx_, state);
}

//
// set_regval
//
inline
#if (PIN_BUILD_NUMBER <= 61206)
void Context::set_regval (REG reg, const REGVAL *val)
#else
void Context::set_regval (REG reg, const UINT8 *val)
#endif
{
  PIN_SetContextRegval (this->ctx_, reg, val);
}

//
// set_reg
//
inline
void Context::set_reg (REG reg, ADDRINT val)
{
  PIN_SetContextReg (this->ctx_, reg, val);
}

} // namespace OASIS
} // namespace Pin
