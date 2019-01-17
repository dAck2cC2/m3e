#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_LIBGEN_H
#define _MSC_LIBGEN_H    1

#include "msvc_export.h"

#ifdef __cplusplus
extern "C" {
#endif

MSVC_EXPORT
char * basename(char *name);

MSVC_EXPORT
char * dirname(char *path);

#ifdef __cplusplus
}
#endif

#endif // _MSC_LIBGEN_H
