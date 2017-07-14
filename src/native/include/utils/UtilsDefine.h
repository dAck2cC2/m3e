#ifndef __UTILS_DEFINE_H__
#define __UTILS_DEFINE_H__

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

#define _UTILS_BEGIN  namespace _UTILS_NAME {
#define _UTILS_END    }
#define _UTILS_NAME   android


//#define LOG_NDEBUG      0
#define LOG_NDEBUG      1


#if LOG_NDEBUG == 0
#define LOG_FILE_NAME   "./logcat.log"
#endif // LOG_NDEBUG

/******************************************/
// ENABLE
/******************************************/

#ifndef ENABLE_CUSTOMISE
#define ENABLE_CUSTOMISE
#endif // ENABLE_CUSTOMISE

/******************************************/
// DISABLE
/******************************************/

#ifdef ENABLE_CALL_STACK
#undef ENABLE_CALL_STACK
#endif // ENABLE_CALL_STACK


#ifdef ENABLE_TEXT_OUTPUT
#undef ENABLE_TEXT_OUTPUT
#endif // ENABLE_TEXT_OUTPUT


#ifdef ENABLE_STRING16
#undef ENABLE_STRING16
#endif // ENABLE_STRING16


#ifdef ENABLE_AMESSAGE
#undef ENABLE_AMESSAGE
#endif // ENABLE_AMESSAGE


//#ifdef ENABLE_ALOOPER
//#undef ENABLE_ALOOPER
//#endif // ENABLE_ALOOPER
#define ENABLE_ALOOPER


#ifdef ENABLE_PARCEL
#undef ENABLE_PARCEL
#endif // ENABLE_PARCEL


#endif // __UTILS_DEFINE_H__

