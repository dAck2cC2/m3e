
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

typedef struct {
	int reserved;
} pthread_mutexattr_t;

typedef struct {
	int                init;
	CRITICAL_SECTION   lock[1];
} pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER  { 0, {{ NULL, 0, 0, NULL, NULL, 0 }} }

static inline int pthread_mutex_init(pthread_mutex_t * lock,
	const pthread_mutexattr_t * attr)
{
	if (!lock) {
		return -1;
	}

	lock->init = 1;
	InitializeCriticalSection(lock->lock);
	lock->init = 2;

	return 0;
}

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

struct _pthread_once_t {
	int inited;
	long semaphore;
};

typedef struct _pthread_once_t pthread_once_t;
#define PTHREAD_ONCE_INIT { 0, -1 }

static inline int pthread_once(pthread_once_t *once, void(*init_func)())
{
	if (once == NULL || init_func == NULL)
		return EINVAL;

	if (once->inited)
		return 0;

	if (InterlockedIncrement(&once->semaphore) == 0)
	{
		init_func();
		once->inited = 1;
	}
	else
	{
		while (!once->inited)
			Sleep(0);
	}

	return 0;
}

#endif // _MSC_PTHREAD_H_ ]
