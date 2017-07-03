#ifndef ANDROID_CUTILS_ATOMIC_MSVC_H
#define ANDROID_CUTILS_ATOMIC_MSVC_H

#include <intrin.h>
#include <stdint.h>

extern inline void android_compiler_barrier(void)
{
    //__asm __volatile__ ("" : : : "memory");
	_ReadWriteBarrier();
}

#if ANDROID_SMP == 0
extern inline void android_memory_barrier(void)
{
    android_compiler_barrier();
}
extern inline void android_memory_store_barrier(void)
{
    android_compiler_barrier();
}
#else
extern inline void android_memory_barrier(void)
{
    __asm__ __volatile__ ("mfence" : : : "memory");
}
extern inline void android_memory_store_barrier(void)
{
    android_compiler_barrier();
}
#endif

extern inline int32_t android_atomic_acquire_load(volatile const int32_t *ptr)
{
    int32_t value = *ptr;
    android_compiler_barrier();
    return value;
}

extern inline int32_t android_atomic_release_load(volatile const int32_t *ptr)
{
    android_memory_barrier();
    return *ptr;
}

extern inline void android_atomic_acquire_store(int32_t value,
        volatile int32_t *ptr)
{
    *ptr = value;
    android_memory_barrier();
}

extern inline void android_atomic_release_store(int32_t value,
        volatile int32_t *ptr)
{
    android_compiler_barrier();
    *ptr = value;
}

extern inline int android_atomic_cas(int32_t old_value, int32_t new_value,
                                     volatile int32_t *ptr)
{
	/*
    int32_t prev;
    __asm__ __volatile__ ("lock; cmpxchgl %1, %2"
                          : "=a" (prev)
                          : "q" (new_value), "m" (*ptr), "0" (old_value)
                          : "memory");
    return prev != old_value;
	*/
	return _InterlockedCompareExchange((long *)ptr, old_value, new_value);
}

extern inline int android_atomic_acquire_cas(int32_t old_value,
        int32_t new_value,
        volatile int32_t *ptr)
{
    /* Loads are not reordered with other loads. */
    return android_atomic_cas(old_value, new_value, ptr);
}

extern inline int android_atomic_release_cas(int32_t old_value,
        int32_t new_value,
        volatile int32_t *ptr)
{
    /* Stores are not reordered with other stores. */
    return android_atomic_cas(old_value, new_value, ptr);
}

extern inline int32_t android_atomic_add(int32_t increment,
        volatile int32_t *pi /*ptr*/)
{
	/*
    __asm__ __volatile__ ("lock; xaddl %0, %1"
                          : "+r" (increment), "+m" (*ptr)
                          : : "memory");
	*/

	// reference:
	// http://read.pudn.com/downloads154/sourcecode/unix_linux/679423/src/pi/Atomic.cpp__.htm

	int rv;
	__asm {
		mov ecx, pi
		mov eax, increment
		lock xadd[ecx], eax
		mov rv, eax
	}
	increment += rv;

    /* increment now holds the old value of *ptr */
    return increment;
}

extern inline int32_t android_atomic_inc(volatile int32_t *addr)
{
    return android_atomic_add(1, addr);
}

extern inline int32_t android_atomic_dec(volatile int32_t *addr)
{
    return android_atomic_add(-1, addr);
}

extern inline int32_t android_atomic_and(int32_t value,
        volatile int32_t *ptr)
{
    int32_t prev, status;

    do {
        prev = *ptr;
        status = android_atomic_cas(prev, prev & value, ptr);
    } while (__builtin_expect(status != 0, 0));

    return prev;
}

extern inline int32_t android_atomic_or(int32_t value, volatile int32_t *ptr)
{
    int32_t prev, status;

    do {
        prev = *ptr;
        status = android_atomic_cas(prev, prev | value, ptr);
    } while (__builtin_expect(status != 0, 0));

    return prev;
}

#endif /* ANDROID_CUTILS_ATOMIC_MSVC_H */
