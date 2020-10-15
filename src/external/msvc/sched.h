#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_SCHED_H
#define _MSC_SCHED_H    1

#define sched_yield()  Sleep(0)

#endif // _MSC_SCHED_H
