
#ifndef _BIONIC_LOCK_H
#define _BIONIC_LOCK_H

#include <cutils/threads.h>

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
