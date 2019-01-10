
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _MSC_PTHREAD_H_ // [
#define _MSC_PTHREAD_H_

#include <windows.h>
#include <sys/time.h>

#ifndef sleep
#define sleep(t) Sleep((t)*1000)
#endif // sleep

typedef struct {
	int                init;
	CRITICAL_SECTION   lock[1];
} pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER  { 0, {{ NULL, 0, 0, NULL, NULL, 0 }} }

static inline int pthread_mutex_trylock(pthread_mutex_t*  lock)
{
	if (!lock->init) {
		lock->init = 1;
		InitializeCriticalSection(lock->lock);
		lock->init = 2;
	}
	else while (lock->init != 2)
		Sleep(10);

	if (!TryEnterCriticalSection(lock->lock)) {
		return EBUSY;
	}

	return 0;
}

static inline void pthread_mutex_lock(pthread_mutex_t*  lock)
{
	if (!lock->init) {
		lock->init = 1;
		InitializeCriticalSection(lock->lock);
		lock->init = 2;
	}
	else while (lock->init != 2)
		Sleep(10);

	EnterCriticalSection(lock->lock);
}

static inline void  pthread_mutex_unlock(pthread_mutex_t*  lock)
{
	LeaveCriticalSection(lock->lock);
}

#endif // _MSC_PTHREAD_H_ ]
