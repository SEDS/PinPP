// -*- C++ -*-

namespace OASIS
{
namespace Pin
{

inline
Context::Context (CONTEXT * ctx)
: ctx_ (ctx)
{

}

inline
Context::~Context (void)
{

}

inline
Context::operator CONTEXT * (void)
{
  return this->ctx_;
}
  
inline
Context::operator const CONTEXT * (void) const
{
  return this->ctx_;
}

inline
bool Context::supports_processor_state (const PROCESSOR_STATE state)
{
  return PIN_SupportsProcessorState (state);
}

inline
#if (PIN_BUILD_NUMBER <= 61206)
void Context::get_regval (REG reg, REGVAL *val) const
#else
void Context::get_regval (REG reg, UINT8 *val) const
#endif
{
  PIN_GetContextRegval (this->ctx_, reg, val);
}

inline
ADDRINT Context::get_reg (REG reg) const
{
  return PIN_GetContextReg (this->ctx_, reg);
}

inline
void Context::execute_at (void) const
{
  PIN_ExecuteAt (this->ctx_);
}

inline
ADDRINT Context::get_syscall_return (SYSCALL_STANDARD std) const
{
  return PIN_GetSyscallReturn (this->ctx_, std);
}

inline
ADDRINT Context::get_syscall_number (SYSCALL_STANDARD std) const
{
  return PIN_GetSyscallNumber (this->ctx_, std);
}

inline
ADDRINT Context::get_syscall_argument (SYSCALL_STANDARD std, UINT32 num) const
{
  return PIN_GetSyscallArgument (this->ctx_, std, num);
}

inline
bool Context::contains_state (PROCESSOR_STATE state) const
{
  return PIN_ContextContainsState (this->ctx_, state);
}

inline
#if (PIN_BUILD_NUMBER <= 61206)
void Context::set_regval (REG reg, const REGVAL * val)
#else
void Context::set_regval (REG reg, const UINT8 * val)
#endif
{
  PIN_SetContextRegval (this->ctx_, reg, val);
}

inline
void Context::set_reg (REG reg, ADDRINT val)
{
  PIN_SetContextReg (this->ctx_, reg, val);
}

} // namespace OASIS
} // namespace Pin
