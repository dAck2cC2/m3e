
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

#include "msvc_export.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void*	timer_t;

#ifndef sleep
#define sleep(t) Sleep((t)*1000)
#endif

MSVC_EXPORT
int gettimeofday(struct timeval *tv/*in*/, struct timezone *tz/*in*/);

MSVC_EXPORT
void usleep(DWORD waitTime);

MSVC_EXPORT
int clock_nanosleep(int clock_id, int flags,
	const struct timespec *request,
	struct timespec *remain);

MSVC_EXPORT
int nanosleep(const struct timespec *req, struct timespec *rem);

typedef enum {
	CLOCK_MONOTONIC = 0,
	CLOCK_REALTIME,
} clockid_t;

MSVC_EXPORT
int clock_gettime(clockid_t clk_id, struct timespec *tp);

MSVC_EXPORT
struct tm *localtime_r(const time_t *timep, struct tm *result);

#ifdef __cplusplus
}
#endif

#endif // _MSC_TIME_H_ ]
