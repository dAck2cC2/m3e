
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_STRINGS_H_ // [
#define _MSC_STRINGS_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>

# define strtok_r strtok_s

#endif // _MSC_STRINGS_H_ ]
