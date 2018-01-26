
#ifndef _BIONIC_LOCK_H
#define _BIONIC_LOCK_H

#if defined(_MSC_VER)
#include <windows.h>
#endif // _MSC_VER

// Lock is used in places like pthread_rwlock_t, which can be initialized without calling
// an initialization function. So make sure Lock can be initialized by setting its memory to 0.
class Lock {
 private:
#if !defined(WIN32)
	 pthread_mutex_t _l;
#elif defined(_MSC_VER)
	 HANDLE _l;
#else  // WIN32
#endif // WIN32

 public:
  void init(bool process_shared) {
#if !defined(WIN32)
	  _l = PTHREAD_MUTEX_INITIALIZER;
#elif defined(_MSC_VER)
	  _l = CreateMutex(NULL, FALSE, NULL);
#else  // WIN32
#endif // WIN32
  }

#if defined(_MSC_VER)  
  ~Lock() {
	  CloseHandle(_l);
  }
#endif // _MSC_VER

#if 0
  bool trylock() {
	  return false;
  }
#endif
  void lock() {
#if !defined(WIN32)
	  pthread_mutex_lock(&_l);
#elif defined(_MSC_VER)
	  WaitForSingleObject(_l, INFINITE);
#else  // WIN32
#endif // WIN32
  }

  void unlock() {
#if !defined(WIN32)
	  pthread_mutex_unlock(&fileLogDeviceLock);
#elif defined(_MSC_VER)
	  ReleaseMutex(_l);
#else  // WIN32
#endif // WIN32
  }
};

#endif  // _BIONIC_LOCK_H
