#ifndef OASIS_PIN_EXPORT_H
#define OASIS_PIN_EXPORT_H

#if !defined(OASIS_PIN_HAS_DLL)
# if defined(OASIS_PIN_AS_STATIC_LIBS)
#   define OASIS_PIN_HAS_DLL 0
# else
#   define OASIS_PIN_HAS_DLL 1
# endif
#endif

#if (OASIS_PIN_HAS_DLL == 1)
#  if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550)
#    if defined(OASIS_PIN_BUILD_DLL)
#      define OASIS_PIN_Export __symbolic
#    else
#      define OASIS_PIN_Export __global
#    endif
#  elif defined(WIN32) || defined(UNDER_CE) || defined(__CYGWIN__)
#    if defined(OASIS_PIN_BUILD_DLL)
#      define OASIS_PIN_Export __declspec(dllexport)
#    else
#      define OASIS_PIN_Export __declspec(dllimport)
#    endif
#  elif (defined(__GNUC__) && (__GNUC__ >= 4))
#    if defined(OASIS_PIN_BUILD_DLL)
#      define OASIS_PIN_Export __attribute__((visibility("default")))
#    else
#      define OASIS_PIN_Export
#    endif
#  else
#    define OASIS_PIN_Export
#  endif
#else
#  define OASIS_PIN_Export
#endif

#endif
