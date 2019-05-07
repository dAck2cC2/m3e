/*
*  https://locklessinc.com/articles/pthreads_on_windows/
*/

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

#include <sys/cdefs.h>
#include <msvc_export.h>

__BEGIN_DECLS

/******************************************************************************
	Critical Sections for Mutexes
******************************************************************************/
typedef int pthread_mutexattr_t;
#define PTHREAD_MUTEX_NORMAL 0
#define PTHREAD_MUTEX_ERRORCHECK 1
#define PTHREAD_MUTEX_RECURSIVE 2
#define PTHREAD_MUTEX_DEFAULT 3
#define PTHREAD_MUTEX_SHARED 4
#define PTHREAD_MUTEX_PRIVATE 0

#define pthread_mutex_getprioceiling(M, P) ENOTSUP
#define pthread_mutex_setprioceiling(M, P) ENOTSUP

MSVC_EXPORT int pthread_mutexattr_init(pthread_mutexattr_t *a);
MSVC_EXPORT int pthread_mutexattr_destroy(pthread_mutexattr_t *a);
MSVC_EXPORT int pthread_mutexattr_gettype(pthread_mutexattr_t *a, int *type);
MSVC_EXPORT int pthread_mutexattr_settype(pthread_mutexattr_t *a, int type);
MSVC_EXPORT int pthread_mutexattr_getpshared(pthread_mutexattr_t *a, int *type);
MSVC_EXPORT int pthread_mutexattr_setpshared(pthread_mutexattr_t * a, int type);
MSVC_EXPORT int pthread_mutexattr_getprotocol(pthread_mutexattr_t *a, int *type);
MSVC_EXPORT int pthread_mutexattr_setprotocol(pthread_mutexattr_t *a, int type);
MSVC_EXPORT int pthread_mutexattr_getprioceiling(pthread_mutexattr_t *a, int * prio);
MSVC_EXPORT int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *a, int prio);

typedef CRITICAL_SECTION pthread_mutex_t;
MSVC_EXPORT int pthread_mutex_lock(pthread_mutex_t *m);
MSVC_EXPORT int pthread_mutex_unlock(pthread_mutex_t *m);
MSVC_EXPORT int pthread_mutex_trylock(pthread_mutex_t *m);
MSVC_EXPORT int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *a);
MSVC_EXPORT int pthread_mutex_destroy(pthread_mutex_t *m);

#define PTHREAD_MUTEX_INITIALIZER {(PRTL_CRITICAL_SECTION_DEBUG)-1,-1,0,0,0,0}
MSVC_EXPORT int pthread_mutex_timedlock(pthread_mutex_t *m, struct timespec *ts);

/******************************************************************************
	Slim Read Write Locks for rwlocks
******************************************************************************/
typedef int pthread_rwlockattr_t;
MSVC_EXPORT int pthread_rwlockattr_destroy(pthread_rwlockattr_t *a);
MSVC_EXPORT int pthread_rwlockattr_init(pthread_rwlockattr_t *a);
MSVC_EXPORT int pthread_rwlockattr_getpshared(pthread_rwlockattr_t *a, int *s);
MSVC_EXPORT int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *a, int s);

typedef SRWLOCK pthread_rwlock_t;
MSVC_EXPORT int pthread_rwlock_init(pthread_rwlock_t *l, pthread_rwlockattr_t *a);
MSVC_EXPORT int pthread_rwlock_destroy(pthread_rwlock_t *l);
MSVC_EXPORT int pthread_rwlock_rdlock(pthread_rwlock_t *l);
MSVC_EXPORT int pthread_rwlock_wrlock(pthread_rwlock_t *l);

#define PTHREAD_RWLOCK_INITIALIZER {0}
MSVC_EXPORT int pthread_rwlock_tryrdlock(pthread_rwlock_t *l);
MSVC_EXPORT int pthread_rwlock_trywrlock(pthread_rwlock_t *l);
MSVC_EXPORT int pthread_rwlock_unlock(pthread_rwlock_t *l);
MSVC_EXPORT int pthread_rwlock_timedrdlock(pthread_rwlock_t *l, const struct timespec *ts);
MSVC_EXPORT int pthread_rwlock_timedwrlock(pthread_rwlock_t *l, const struct timespec *ts);

/******************************************************************************
	Condition Variables
******************************************************************************/
typedef int pthread_condattr_t;
MSVC_EXPORT int pthread_condattr_destroy(pthread_condattr_t *a);

#define pthread_condattr_getclock(A, C) ENOTSUP
#define pthread_condattr_setclock(A, C) ENOTSUP

MSVC_EXPORT int pthread_condattr_init(pthread_condattr_t *a);
MSVC_EXPORT int pthread_condattr_getpshared(pthread_condattr_t *a, int *s);
MSVC_EXPORT int pthread_condattr_setpshared(pthread_condattr_t *a, int s);

typedef CONDITION_VARIABLE pthread_cond_t;
#define PTHREAD_COND_INITIALIZER {0}
MSVC_EXPORT int pthread_cond_init(pthread_cond_t *c, const pthread_condattr_t *a);
MSVC_EXPORT int pthread_cond_signal(pthread_cond_t *c);
MSVC_EXPORT int pthread_cond_broadcast(pthread_cond_t *c);
MSVC_EXPORT int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m);
MSVC_EXPORT int pthread_cond_destroy(pthread_cond_t *c);
MSVC_EXPORT int pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, struct timespec *t);

/******************************************************************************
	Barriers
******************************************************************************/
#define PTHREAD_BARRIER_INITIALIZER \
	{0,0,PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER}
#define PTHREAD_BARRIER_SERIAL_THREAD 1

typedef struct pthread_barrier_t pthread_barrier_t;
struct pthread_barrier_t
{
	int count;
	int total;
	CRITICAL_SECTION m;
	CONDITION_VARIABLE cv;
};
typedef void *pthread_barrierattr_t;

MSVC_EXPORT int pthread_barrier_destroy(pthread_barrier_t *b);
MSVC_EXPORT int pthread_barrier_init(pthread_barrier_t *b, void *attr, int count);

#define _PTHREAD_BARRIER_FLAG (1<<30)
MSVC_EXPORT int pthread_barrier_wait(pthread_barrier_t *b);
MSVC_EXPORT int pthread_barrierattr_init(void **attr);
MSVC_EXPORT int pthread_barrierattr_destroy(void **attr);
MSVC_EXPORT int pthread_barrierattr_setpshared(void **attr, int s);
MSVC_EXPORT int pthread_barrierattr_getpshared(void **attr, int *s);

/******************************************************************************
	Spinlocks
******************************************************************************/
#define PTHREAD_SPINLOCK_INITIALIZER 0
typedef long pthread_spinlock_t;

MSVC_EXPORT int pthread_spin_init(pthread_spinlock_t *l, int pshared);
MSVC_EXPORT int pthread_spin_destroy(pthread_spinlock_t *l);
MSVC_EXPORT int pthread_spin_lock(pthread_spinlock_t *l);
MSVC_EXPORT int pthread_spin_trylock(pthread_spinlock_t *l);
MSVC_EXPORT int pthread_spin_unlock(pthread_spinlock_t *l);

/******************************************************************************
	pthread_once()
******************************************************************************/
#define PTHREAD_ONCE_INIT 0
typedef long pthread_once_t;

typedef struct _pthread_cleanup _pthread_cleanup;
struct _pthread_cleanup
{
	void(*func)(void *);
	void *arg;
	_pthread_cleanup *next;
};

#define pthread_cleanup_push(F, A)\
{\
	const _pthread_cleanup _pthread_cup = {(F), (A), pthread_self()->clean};\
	_ReadWriteBarrier();\
	pthread_self()->clean = (_pthread_cleanup *) &_pthread_cup;\
	_ReadWriteBarrier()

/* Note that if async cancelling is used, then there is a race here */
#define pthread_cleanup_pop(E)\
	(pthread_self()->clean = _pthread_cup.next, (E?_pthread_cup.func(_pthread_cup.arg):0));}

MSVC_EXPORT int pthread_once(pthread_once_t *o, void(*func)(void));

/******************************************************************************
	Cancelling
******************************************************************************/
//#define accept(...) (pthread_testcancel(), accept(__VA_ARGS__))
//#define aio_suspend(...) (pthread_testcancel(), aio_suspend(__VA_ARGS__))
//#define clock_nanosleep(...) (pthread_testcancel(), clock_nanosleep(__VA_ARGS__))
//#define close(...) (pthread_testcancel(), close(__VA_ARGS__))

/* More here */

/* Even for library functions defined as macros */
//#undef getwc
//#define getwc(...) (pthread_testcancel(), getwc(__VA_ARGS__))
//#undef getwchar
//#define getwchar(...) (pthread_testcancel(), getwcahr(__VA_ARGS__))

/* And so on */

#define PTHREAD_CANCEL_DISABLE 0
#define PTHREAD_CANCEL_ENABLE 0x01

#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_ASYNCHRONOUS 0x02

#define PTHREAD_CANCELED ((void *) 0xDEADBEEF)

MSVC_EXPORT void pthread_testcancel(void);

/******************************************************************************
	Thread Creation and Destruction
******************************************************************************/
struct _pthread_v
{
	void *ret_arg;
	void *(*func)(void *);
	_pthread_cleanup *clean;
	HANDLE h;
	int cancelled;
	unsigned p_state;
	int keymax;
	void **keyval;

	jmp_buf jb;
};

typedef struct _pthread_v *pthread_t;

typedef struct pthread_attr_t pthread_attr_t;
struct pthread_attr_t
{
	unsigned p_state;
	void *stack;
	size_t s_size;
};

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 0x04

#define PTHREAD_EXPLICT_SCHED 0
#define PTHREAD_INHERIT_SCHED 0x08

#define PTHREAD_SCOPE_PROCESS 0
#define PTHREAD_SCOPE_SYSTEM 0x10

#define PTHREAD_DESTRUCTOR_ITERATIONS 256

#define PTHREAD_PRIO_NONE 0
#define PTHREAD_PRIO_INHERIT 8
#define PTHREAD_PRIO_PROTECT 16
#define PTHREAD_PRIO_MULT 32
#define PTHREAD_PROCESS_SHARED 0
#define PTHREAD_PROCESS_PRIVATE 1

#define PTHREAD_DEFAULT_ATTR 0

MSVC_EXPORT int pthread_cancel(pthread_t t);

MSVC_EXPORT void pthread_tls_init(void);
MSVC_EXPORT pthread_t pthread_self(void);
MSVC_EXPORT int pthread_getconcurrency(int *val);
MSVC_EXPORT int pthread_setconcurrency(int val);

#define pthread_getschedparam(T, P, S) ENOTSUP
#define pthread_setschedparam(T, P, S) ENOTSUP
#define pthread_getcpuclockid(T, C) ENOTSUP

MSVC_EXPORT int pthread_exit(void *res);
MSVC_EXPORT int pthread_attr_init(pthread_attr_t *attr);
MSVC_EXPORT int pthread_attr_destroy(pthread_attr_t *attr);
MSVC_EXPORT int pthread_attr_setdetachstate(pthread_attr_t *a, int flag);
MSVC_EXPORT int pthread_attr_getdetachstate(pthread_attr_t *a, int *flag);
MSVC_EXPORT int pthread_attr_setinheritsched(pthread_attr_t *a, int flag);
MSVC_EXPORT int pthread_attr_getinheritsched(pthread_attr_t *a, int *flag);
MSVC_EXPORT int pthread_attr_setscope(pthread_attr_t *a, int flag);
MSVC_EXPORT int pthread_attr_getscope(pthread_attr_t *a, int *flag);
MSVC_EXPORT int pthread_attr_getstackaddr(pthread_attr_t *attr, void **stack);
MSVC_EXPORT int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack);
MSVC_EXPORT int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *size);
MSVC_EXPORT int pthread_attr_setstacksize(pthread_attr_t *attr, size_t size);

#define pthread_attr_getguardsize(A, S) ENOTSUP
#define pthread_attr_setgaurdsize(A, S) ENOTSUP
#define pthread_attr_getschedparam(A, S) ENOTSUP
#define pthread_attr_setschedparam(A, S) ENOTSUP
#define pthread_attr_getschedpolicy(A, S) ENOTSUP
#define pthread_attr_setschedpolicy(A, S) ENOTSUP

MSVC_EXPORT int pthread_setcancelstate(int state, int *oldstate);
MSVC_EXPORT int pthread_setcanceltype(int type, int *oldtype);
MSVC_EXPORT int pthread_create(pthread_t *th, const pthread_attr_t *attr, void *(*func)(void *), void *arg);
MSVC_EXPORT int pthread_join(pthread_t t, void **res);
MSVC_EXPORT int pthread_detach(pthread_t t);

MSVC_EXPORT int pthread_gettid_np(pthread_t t);
MSVC_EXPORT int pthread_equal(pthread_t t1, pthread_t t2);

/******************************************************************************
	Thread Specific Data
******************************************************************************/
#define PTHREAD_KEYS_MAX (1<<20)
typedef unsigned pthread_key_t;

MSVC_EXPORT int pthread_key_create(pthread_key_t *key, void(*dest)(void *));
MSVC_EXPORT int pthread_key_delete(pthread_key_t key);
MSVC_EXPORT void *pthread_getspecific(pthread_key_t key);
MSVC_EXPORT int pthread_setspecific(pthread_key_t key, const void *value);

/******************************************************************************
	Unimplemented Functions
******************************************************************************/
/* No fork() in windows - so ignore this */
#define pthread_atfork(F1,F2,F3) 0

/* Windows has rudimentary signals support */
#define pthread_kill(T, S) 0
#define pthread_sigmask(H, S1, S2) 0

__END_DECLS

#endif // _MSC_PTHREAD_H_ ]
