// -*- C++ -*-

//==============================================================================
/**
 *  @file        Image_Tool.h
 *
 *  $Id: Image_Tool.h 2294 2013-10-01 20:09:09Z hillj $
 *
 *  @author      James H. Hill
 */
//==============================================================================

#ifndef _OASIS_PIN_IMAGE_TOOL_H_
#define _OASIS_PIN_IMAGE_TOOL_H_

#include "Tool.h"
#include "Image.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Image_Tool
 *
 * Base class for instruction-level instrumentation Pin tools.
 */
template <typename T>
class Image_Tool : public Tool
{
public:
  /// Default constructor.
  Image_Tool (void);

  /// Destructor.
  ~Image_Tool (void);

  /// Initialize the tool.
  void handle_init (int argc, char * argv []);
  void handle_unload (const Image & img);

private:
  // PIN Instrumentation hook
  static VOID __instrument (IMG image, VOID * v);
  static VOID __unload (IMG image, VOID * v);
};

} // namespace Pin
} // namespace OASIS

#include "Image_Tool.inl"
#include "Image_Tool.cpp"

#endif  // _OASIS_PIN_IMAGE_TOOL_H_
