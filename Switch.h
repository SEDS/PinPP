// -*- C++ -*-

//=============================================================================
/**
 * @file      Switch.h
 *
 * $Id: Switch.h 2294 2013-10-01 20:09:09Z hillj $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PIN_SWITCH_H_
#define _OASIS_PIN_SWITCH_H_

#include "If.h"

namespace OASIS
{
namespace Pin
{

struct Nil_Case {};

template <int TAG, typename TYPE, typename NEXT = Nil_Case>
struct Case
{
  static const int tag = TAG;
  typedef TYPE Type;
  typedef NEXT Next;
};

template <int tag, typename Case>
struct Switch
{
private:
  typedef typename Case::Next Next_Case;

  static const int case_tag = Case::tag;
  static const bool found = (case_tag == tag || case_tag == ~(~0u >> 1));

public:
  typedef typename
    If <found,
        typename Case::Type,
        typename Switch <tag, Next_Case>::result_type>::result_type result_type;
};

template <int tag>
struct Switch <tag, Nil_Case>
{
  typedef Nil_Case result_type;
};

}
}

#endif  // !defined _OASIS_PIN_SWITCH_H_
