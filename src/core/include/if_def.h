#ifndef __CORE_IF_DEFINE_H__
#define __CORE_IF_DEFINE_H__

/* Some compilers use a special export keyword */
#ifndef DECLSPEC
# if defined(WIN32) || defined(__WINRT__)
#  ifdef __BORLANDC__
#   ifdef BUILD_SDL
#    define DECLSPEC
#   else
#    define DECLSPEC    __declspec(dllimport)
#   endif
#  else
#   define DECLSPEC __declspec(dllexport)
#  endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define DECLSPEC __attribute__ ((visibility("default")))
#  else
#   define DECLSPEC
#  endif
# endif
#endif

#endif // __CORE_IF_DEFINE_H__
