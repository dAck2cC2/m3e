#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef	_MSVC_EXPORT_H_
#define	_MSVC_EXPORT_H_

#if !defined(MSVC_EXPORT)
#if defined(MSVC_WRAP_DLL)
#if defined(MSVC_WRAP_IMPLEMENTATION) 
#       define MSVC_EXPORT __declspec(dllexport)
#   else
#       define MSVC_EXPORT __declspec(dllimport)
#   endif // MSVC_WRAPPER_IMPLEMENTATION
#else
#   define MSVC_EXPORT 
#endif  // MSVC_WRAPPER_DLL
#endif  // MSVC_EXPORT

#endif  // _MSVC_EXPORT_H_
