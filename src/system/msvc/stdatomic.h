
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_STDATOMIC_H_ // [
#define _MSC_STDATOMIC_H_

#if _MSC_VER > 1000
#pragma once
#endif

//#define RC_INVOKED
//#include <atomic>

typedef int atomic_int;
typedef unsigned int atomic_uintptr_t;

#endif // _MSC_STDATOMIC_H_ ]
