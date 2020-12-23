
#ifndef _BIONIC_LOCK_H
#define _BIONIC_LOCK_H

#include <cutils/threads.h>

/***********************************************************************/
/***********************************************************************/
/*****                                                             *****/
/*****         mutexes                                             *****/
/*****                                                             *****/
/***********************************************************************/
/***********************************************************************/

#if !defined(_WIN32)

typedef pthread_mutex_t   mutex_t;

#define  MUTEX_INITIALIZER  PTHREAD_MUTEX_INITIALIZER

static __inline__ void  mutex_lock(mutex_t* lock)
{
    pthread_mutex_lock(lock);
}
static __inline__ void  mutex_unlock(mutex_t* lock)
{
    pthread_mutex_unlock(lock);
}
static __inline__ int  mutex_init(mutex_t* lock)
{
    return pthread_mutex_init(lock, NULL);
}
static __inline__ void mutex_destroy(mutex_t* lock)
{
    pthread_mutex_destroy(lock);
}

#else // !defined(_WIN32)

typedef struct {
    int                init;
    CRITICAL_SECTION   lock[1];
} mutex_t;

#define  MUTEX_INITIALIZER  { 0, {{ NULL, 0, 0, NULL, NULL, 0 }} }

static __inline__ void  mutex_lock(mutex_t* lock)
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

static __inline__ void  mutex_unlock(mutex_t* lock)
{
    LeaveCriticalSection(lock->lock);
}
static __inline__ int  mutex_init(mutex_t* lock)
{
    InitializeCriticalSection(lock->lock);
    lock->init = 2;
    return 0;
}
static __inline__ void  mutex_destroy(mutex_t* lock)
{
    if (lock->init) {
        lock->init = 0;
        DeleteCriticalSection(lock->lock);
    }
}
#endif // !defined(_WIN32)


// Lock is used in places like pthread_rwlock_t, which can be initialized without calling
// an initialization function. So make sure Lock can be initialized by setting its memory to 0.
class BionicLock {
public:
  BionicLock() {
      mutex_init(&_l);
  }

  ~BionicLock() {
      mutex_destroy(&_l);
  }

  void lock() {
      mutex_lock(&_l);
  }

  void unlock() {
      mutex_unlock(&_l);
  }
    
private:
    mutex_t _l;
};

#endif  // _BIONIC_LOCK_H
