// -*- C++ -*-

//==============================================================================
/**
 *  @file        Static_Pintool.h
 *
 *  $Id: Static_Pintool.h 2304 2013-10-05 18:54:01Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_STATIC_PINTOOL_H_
#define _OASIS_PIN_STATIC_PINTOOL_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Static_Pintool
 */
class Static_Pintool
{
public:
  static void init (INT32 argc, CHAR ** argv, bool init_symbols = false);
};

} // namespace OASIS
} // namespace Pin

#endif  // _OASIS_PIN_STATIC_PINTOOL_H_
