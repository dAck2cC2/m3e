// Reference:
// https://stackoverflow.com/questions/341817/is-there-a-replacement-for-unistd-h-for-windows-visual-c
//

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_UNISTD_H
#define _MSC_UNISTD_H    1

/* This file intended to serve as a drop-in replacement for
*  unistd.h on Windows
*  Please add functionality as neeeded
*/

#include "msvc_export.h"

#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h>  /* for _getcwd() and _chdir() */
#include <stdint.h>
/* #include <dirent.h> */ /* Since it will include windows.h, don't include it here */

/* Read user permission */
#if !defined(S_IRUSR)
#   define S_IRUSR S_IREAD
#endif

/* Write user permission */
#if !defined(S_IWUSR)
#   define S_IWUSR S_IWRITE
#endif

/* Block device */
#if !defined(S_IFBLK)
#   define S_IFBLK 0
#endif

#if !defined(S_ISBLK)
#   define S_ISBLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#endif

#define srandom srand
#define random rand

/* Values for the second argument to access.
These may be OR'd together.  */
#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
/* read, write, and close are NOT being #defined here, because while there are file handle specific versions for Windows, they probably don't work for sockets. You need to look at your app and consider whether to call e.g. closesocket(). */

//#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
/* should be in some equivalent to <sys/types.h> */
//typedef __int8            int8_t;
typedef __int16           int16_t;
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

typedef int          pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;

typedef int64_t off64_t;

#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(exp)  exp
#endif // TEMP_FAILURE_RETRY

inline static uid_t getuid() { return 1000; };

MSVC_EXPORT 
void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen);

// disable the __attribute__
#if !defined(__attribute__)
#define __attribute__(A) /* do nothing */
#endif // __attribute__

// disable the __builtin_expect
#if !defined(__builtin_expect)
#define __builtin_expect(cond, result)  ((cond)) 
#endif // __builtin_expect

#endif /* unistd.h  */
