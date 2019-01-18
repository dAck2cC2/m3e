
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_MMAN_H_ // [
#define _MSC_MMAN_H_

#include "msvc_export.h"

#define MAP_FAILED  ((void*)(-1))

#ifdef __cplusplus
extern "C" {
#endif

MSVC_EXPORT
extern int getpagesize(void);

#ifdef __cplusplus
}
#endif

#endif // _MSC_MMAN_H_
