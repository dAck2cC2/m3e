
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

typedef struct _pthread_Details {
	void* (*func)(void*);
	void* arg;
} pthread_Details;
static unsigned int pthread_Intermediary(void* vDetails)
{
	pthread_Details* pDetails = (pthread_Details*) vDetails;

	(*(pDetails->func))(pDetails->arg);

	free(pDetails);

	return 0;
};

typedef DWORD pthread_t;
typedef int pthread_attr_t;
static inline int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg)
{
	if (NULL == start_routine) {
		return -1;
	}

	HANDLE hThread;
	pthread_Details* pDetails = (pthread_Details*)malloc(sizeof(pthread_Details)); // must be on heap
	DWORD thrdaddr;

	pDetails->func = start_routine;
	pDetails->arg = arg;

	hThread = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)pthread_Intermediary,
		(void*)pDetails, 0, (DWORD*)&thrdaddr);
	if (hThread == NULL)
	{
		return -2;
	}

	/* close the management handle */
	CloseHandle(hThread);

	if (thread != NULL) {
		*thread = thrdaddr;
	}


	return 0;
}

#endif // _MSC_PTHREAD_H_ ]
