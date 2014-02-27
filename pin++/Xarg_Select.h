#ifndef _OASIS_PIN_XARG_SELECT_H_
#define _OASIS_PIN_XARG_SELECT_H_

namespace OASIS
{
namespace Pin
{

template <int N>
struct Xarg_Select;

template < >
struct Xarg_Select <1>
{
  template <typename XARG1>
  inline static XARG1 execute (const XARG1 & xarg1)
  {
    return xarg1;
  }

  template <typename XARG1, typename XARG2>
  inline static XARG1 execute (const XARG1 & xarg1, const XARG2 &)
  {
    return xarg1;
  }

  template <typename XARG1, typename XARG2, typename XARG3>
  inline static XARG1 execute (const XARG1 & xarg1, const XARG2 &, const XARG3 &)
  {
    return xarg1;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static XARG1 execute (const XARG1 & xarg1, const XARG2 &, const XARG3 &, const XARG4 &)
  {
    return xarg1;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static XARG1 execute (const XARG1 & xarg1, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 &)
  {
    return xarg1;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 & xarg1, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 &, const XARG6 &)
  {
    return xarg1;
  }
};

template < >
struct Xarg_Select <2>
{
  template <typename XARG1, typename XARG2>
  inline static XARG1 execute (const XARG1 &, const XARG2 & xarg2)
  {
    return xarg2;
  }

  template <typename XARG1, typename XARG2, typename XARG3>
  inline static XARG1 execute (const XARG1 &, const XARG2 & xarg2, const XARG3 &)
  {
    return xarg2;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static XARG1 execute (const XARG1 &, const XARG2 & xarg2, const XARG3 &, const XARG4 &)
  {
    return xarg2;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static XARG1 execute (const XARG1 &, const XARG2 & xarg2, const XARG3 &, const XARG4 &, const XARG5 &)
  {
    return xarg2;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 &, const XARG2 & xarg2, const XARG3 &, const XARG4 &, const XARG5 &, const XARG6 &)
  {
    return xarg2;
  }
};

template < >
struct Xarg_Select <3>
{
  template <typename XARG1, typename XARG2, typename XARG3>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 & xarg3)
  {
    return xarg3;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 & xarg3, const XARG4 &)
  {
    return xarg3;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 & xarg3, const XARG4 &, const XARG5 &)
  {
    return xarg3;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 & xarg3, const XARG4 &, const XARG5 &, const XARG6 &)
  {
    return xarg3;
  }
};

template < >
struct Xarg_Select <4>
{
  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 & xarg4)
  {
    return xarg4;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 & xarg4, const XARG5 &)
  {
    return xarg4;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 & xarg4, const XARG5 &, const XARG6 &)
  {
    return xarg4;
  }
};

template < >
struct Xarg_Select <5>
{
  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 & xarg5)
  {
    return xarg5;
  }

  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 & xarg5, const XARG6 &)
  {
    return xarg5;
  }
};

template < >
struct Xarg_Select <6>
{
  template <typename XARG1, typename XARG2, typename XARG3, typename XARG4, typename XARG5, typename XARG6>
  inline static XARG1 execute (const XARG1 &, const XARG2 &, const XARG3 &, const XARG4 &, const XARG5 &, const XARG6 & xarg6)
  {
    return xarg6;
  }
};

}
}

#endif  // !defined _OASIS_PIN_XARG_SELECT_H_
