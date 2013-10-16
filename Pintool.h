// -*- C++ -*-

//==============================================================================
/**
 *  @file        Pintool.h
 *
 *  $Id: Pintool.h 2306 2013-10-07 05:03:46Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_PINTOOL_H_
#define _OASIS_PIN_PINTOOL_H_

#include "Tool.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Pintool
 *
 * Runner class for all pintools. This class is responsible for initializing
 * the Pin environment, and starting the instrumented program.
 */
template <typename T>
class Pintool
{
public:
  /// Type definition of the tool.
  typedef T type;

  /**
   * Initializing constructor.
   */
  Pintool (int argc, char * argv []);

  /// Destructor.
  ~Pintool (void);

  /// Start the program in JIT mode.
  void start_program (void);

  /// Start the program in probed mode. It is recommended that the
  /// program is only started in this mode when instrumenting at
  /// routine or image level.
  ///
  /// @TODO Add a static check validates T is of type Routine_Tool or
  /// Image_Tool when this method is invoked.
  void start_program_probed (void);

private:
  /// Implementation of the tool.
  T * tool_;

  /// Command-line error.
  bool cmdline_error_;
};

} // namespace OASIS
} // namespace Pin

#include "Pintool.inl"
#include "Pintool.cpp"

#define DECLARE_PINTOOL(T) \
  int main (int argc, char * argv []) { \
    OASIS::Pin::Pintool <T> (argc, argv).start_program (); \
  }

#define DECLARE_PINTOOL_PROBED(T) \
  int main (int argc, char * argv []) { \
    OASIS::Pin::Pintool <T> (argc, argv).start_program_probed (); \
  }

#endif  // _OASIS_PIN_PINTOOL_H_
