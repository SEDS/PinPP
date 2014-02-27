#ifndef _OASIS_PIN_IF_H_
#define _OASIS_PIN_IF_H_

namespace OASIS
{
namespace Pin
{

/**
 * @struct If
 *
 * Compile-time if-else evalation. The result of either branch is a
 * type definition.
 */
template <bool Expr, typename Then, typename Else>
struct If
{
  typedef Then result_type;
};

template <typename Then, typename Else>
struct If <false, Then, Else>
{
  typedef Else result_type;
};

}
}

#endif  // !defined _OASIS_PIN_IF_
