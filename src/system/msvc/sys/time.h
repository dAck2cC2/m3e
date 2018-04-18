
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_TIME_H_ // [
#define _MSC_TIME_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>
#include <winsock.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
#endif
int gettimeofday(struct timeval *tv/*in*/, struct timezone *tz/*in*/);

#ifdef __cplusplus
extern "C"
#endif
void usleep(DWORD waitTime);

#endif // _MSC_TIME_H_ ]
