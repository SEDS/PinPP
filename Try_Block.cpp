// $Id: Try_Block.cpp 2306 2013-10-07 05:03:46Z hillj $

namespace OASIS
{
namespace Pin
{

template <typename T>
EXCEPT_HANDLING_RESULT Try_Block <T>::
__internal_exception_handler (THREADID thr_id, EXCEPTION_INFO * ex_info, PHYSICAL_CONTEXT * ctx, VOID * obj)
{
#if defined (TARGET_WINDOWS)
  return reinterpret_cast <T *> (obj)->handle_exception (thr_id, Exception (ex_info), ctx);
#else
  Exception ex (ex_info);
  return reinterpret_cast <T *> (obj)->handle_exception (thr_id, ex, ctx);
#endif
}

} // namespace OASIS
} // namespace Pin
