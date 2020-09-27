
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config_write.h"
#include "log_portability.h"
#include "logger.h"

#if defined(_LINUX) || defined(__APPLE__)
#include <sys/syscall.h>
#endif

#define LOG_FILE_NAME  "logcat.log"

static int fileOpen();
static void fileClose();
static int fileWrite(log_id_t logId, struct timespec *ts,
	struct iovec *vec, size_t nr);

static FILE* logFd = NULL;

LIBLOG_HIDDEN struct android_log_transport_write fileLoggerWrite = {
	.node = { &fileLoggerWrite.node, &fileLoggerWrite.node },
	.context.priv = &logFd,
	.name = "file",
	.available = NULL,
	.open = fileOpen,
	.close = fileClose,
	.write = fileWrite,
};

#if !defined(_WIN32)
/*
* Locking.  Since we're emulating a device, we need to be prepared
* to have multiple callers at the same time.  This lock is used
* to both protect the fd list and to prevent LogStates from being
* freed out from under a user.
*/
static pthread_mutex_t fileLogDeviceLock = PTHREAD_MUTEX_INITIALIZER;

#define lock_create()  ((void)0)
#define lock_delete()  ((void)0) 

static void lock()
{
	/*
	* If we trigger a signal handler in the middle of locked activity and the
	* signal handler logs a message, we could get into a deadlock state.
	*/
	pthread_mutex_lock(&fileLogDeviceLock);
}

static void unlock()
{
	pthread_mutex_unlock(&fileLogDeviceLock);
}

#elif defined(_MSC_VER)

#include <windows.h>

static HANDLE fileLogDeviceLock = 0;

static void lock_create() { fileLogDeviceLock = CreateMutex(NULL, FALSE, NULL); }
static void lock_delete() { CloseHandle(fileLogDeviceLock); }
static void lock()        { WaitForSingleObject(fileLogDeviceLock, INFINITE); }
static void unlock()      { ReleaseMutex(fileLogDeviceLock); }

#else   // !defined(_WIN32)

#define lock_create()  ((void)0)
#define lock_delete()  ((void)0) 
#define lock() ((void)0)
#define unlock() ((void)0)

#endif  // !defined(_WIN32)

static const char* getPriorityString(int priority)
{
	/* the first character of each string should be unique */
	static const char* priorityStrings[] = {
		"Verbose", "Debug", "Info", "Warn", "Error", "Assert"
	};
	int idx;

	idx = (int)priority - (int)ANDROID_LOG_VERBOSE;
	if (idx < 0 ||
		idx >= (int)(sizeof(priorityStrings) / sizeof(priorityStrings[0])))
		return "?unknown?";
	return priorityStrings[idx];
}

/*
* WIN32 does not have writev().
* Make up something to replace it.
*/
static ssize_t file_writev(FILE* fd, const struct iovec *iov, int iovcnt) {
	ssize_t result = 0;
	const struct iovec* end = iov + iovcnt;
	for (; iov < end; iov++) {
		ssize_t w = fwrite(iov->iov_base, 1, iov->iov_len, fd);
		if (w != (ssize_t)iov->iov_len) {
			if (w < 0)
				return w;
			return result + w;
		}
		result += w;
	}
	return result;
}

static int fileOpen()
{
	lock_create();

	if (logFd != NULL) {
		return (-1);
	}

	logFd = fopen(LOG_FILE_NAME, "w");
	if (logFd == NULL) {
		return (-2);
	}

	return 0;
}

static void fileClose()
{
	if (logFd != NULL) {
		fclose(logFd);
		logFd = NULL;
	}

	lock_delete();

	return;
}

static int fileWrite(log_id_t logId, struct timespec *ts,
	struct iovec *vector, size_t count)
{
	if ((NULL == vector) || (count != 3) || (NULL == ts)) {
		return -2;
	}

	if (NULL == logFd) {
		return -3;
	}

	lock();

	/* pull out the three fields */
	int logPrio = *(const char*)vector[0].iov_base;
	const char* tag = (const char*)vector[1].iov_base;
	const char* msg = (const char*)vector[2].iov_base;

#if !defined(_WIN32)
	struct tm tmBuf;
#endif
	struct tm* ptm;
	char timeBuf[32];
	char prefixBuf[128], suffixBuf[128];
	char priChar;
	//time_t when;
#if !defined(_WIN32)
	pid_t pid, tid;
#else
	uint32_t pid, tid;
#endif

	priChar = getPriorityString(logPrio)[0];
	pid = tid = getpid();       // find gettid()?
#if defined(_MSC_VER)
	tid = GetCurrentThreadId();
#elif defined(_LINUX)
	tid = syscall(__NR_gettid);
#elif defined(__APPLE__)
    tid = syscall(SYS_thread_selfid);
#endif

	/*
	* Get the current date/time in pretty form
	*
	* It's often useful when examining a log with "less" to jump to
	* a specific point in the file by searching for the date/time stamp.
	* For this reason it's very annoying to have regexp meta characters
	* in the time stamp.  Don't use forward slashes, parenthesis,
	* brackets, asterisks, or other special chars here.
	*/
#if !defined(_WIN32)
	ptm = localtime_r(&(ts->tv_sec), &tmBuf);
#else
	ptm = localtime(&(ts->tv_sec));
#endif
	//strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", ptm);
	strftime(timeBuf, sizeof(timeBuf), "%m-%d %H:%M:%S", ptm);

	/*
	* Construct a buffer containing the log header and log message.
	*/
	size_t prefixLen, suffixLen;
	prefixLen = snprintf(prefixBuf, sizeof(prefixBuf),
		"[%s.%03ld P%05d:T%05d %c/%-8s] ",
		timeBuf, ts->tv_nsec/1000000, pid, tid, priChar, tag);
	strcpy(suffixBuf, "\n"); suffixLen = 1;

	/*
	* Figure out how many lines there will be.
	*/
	const char* end = msg + strlen(msg);
	size_t numLines = 0;
	const char* p = msg;
	while (p < end) {
		if (*p++ == '\n') numLines++;
	}
	if (p > msg && *(p - 1) != '\n') {
		numLines++;
	}

	/*
	* Create an array of iovecs large enough to write all of
	* the lines with a prefix and a suffix.
	*/
#ifdef _MSC_VER
#define INLINE_VECS  (64)
#else  // MSVC
	const size_t INLINE_VECS = 64;
#endif // MSVC
	const size_t MAX_LINES = ((size_t)~0) / (3 * sizeof(struct iovec*));
	struct iovec stackVec[INLINE_VECS];
	struct iovec* vec = stackVec;
	size_t numVecs;

	if (numLines > MAX_LINES)
		numLines = MAX_LINES;

	numVecs = numLines * 3;  // 3 iovecs per line.
	if (numVecs > INLINE_VECS) {
		vec = (struct iovec*)malloc(sizeof(struct iovec)*numVecs);
		if (vec == NULL) {
			msg = "LOG: write failed, no memory";
			numVecs = INLINE_VECS;
			numLines = numVecs / 3;
			vec = stackVec;
		}
	}

	/*
	* Fill in the iovec pointers.
	*/
	p = msg;
	struct iovec* v = vec;
	int totalLen = 0;
	while (numLines > 0 && p < end) {
		if (prefixLen > 0) {
			v->iov_base = prefixBuf;
			v->iov_len = prefixLen;
			totalLen += prefixLen;
			v++;
		}
		const char* start = p;
		while (p < end && *p != '\n') {
			p++;
		}
		if ((p - start) > 0) {
			v->iov_base = (void*)start;
			v->iov_len = p - start;
			totalLen += p - start;
			v++;
		}
		if (*p == '\n') p++;
		if (suffixLen > 0) {
			v->iov_base = suffixBuf;
			v->iov_len = suffixLen;
			totalLen += suffixLen;
			v++;
		}
		numLines -= 1;
	}

	/*
	* Write the entire message to the log file with a single writev() call.
	* We need to use this rather than a collection of printf()s on a FILE*
	* because of multi-threading and multi-process issues.
	*
	* If the file was not opened with O_APPEND, this will produce interleaved
	* output when called on the same file from multiple processes.
	*
	* If the file descriptor is actually a network socket, the writev()
	* call may return with a partial write.  Putting the writev() call in
	* a loop can result in interleaved data.  This can be alleviated
	* somewhat by wrapping the writev call in the Mutex.
	*/

	for (;;) {
		int cc = file_writev(logFd, vec, v - vec);

		if (cc == totalLen) break;

		if (cc < 0) {
			if (errno == EINTR) continue;

			/* can't really log the failure; for now, throw out a stderr */
			fprintf(stderr, "+++ LOG: write failed (errno=%d)\n", errno);
			break;
		}
		else {
			/* shouldn't happen when writing to file or tty */
			fprintf(stderr, "+++ LOG: write partial (%d of %d)\n", cc, totalLen);
			break;
		}
	}

	/* if we allocated storage for the iovecs, free it */
	if (vec != stackVec)
		free(vec);

bail:
	unlock();
	return vector[0].iov_len + vector[1].iov_len + vector[2].iov_len;
error:
	unlock();
	return -1;
}
