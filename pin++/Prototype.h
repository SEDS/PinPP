// -*- C++ -*-

//==============================================================================
/**
 *  @file        Prototype.h
 *
 *  $Id: Prototype.h 2294 2013-10-01 20:09:09Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_PROTOTYPE_H_
#define _OASIS_PIN_PROTOTYPE_H_

#include "pin.H"

namespace OASIS
{
namespace Pin
{

/**
 * @class Prototype
 *
 * Wrapper class for managing function prototypes in Pin. The prototypes
 * are used when you need to replace a routine under probed mode.
 */
class Prototype
{
public:
  /**
   * Initializing constructor. The constructor will allocate a
   * prototype for the specified function.
   */
  Prototype (PROTO proto);

  /// Copy constructor.
  Prototype (const Prototype & proto);

  /// Destructor
  ~Prototype (void);

  /// Assignment operator.
  const Prototype & operator = (const Prototype & proto);

  /// Close the prototype function.
  void close (void);

  /// Conversion operator
  operator PROTO () const;

private:
  /// Reference to allocated prototype.
  PROTO proto_;
};

}
}

#include "Prototype.inl"

#endif  // !defined _OASIS_PIN_PROTOTYPE_H_
