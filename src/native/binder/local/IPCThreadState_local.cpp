#define LOG_TAG "IPCThreadState"

#include <binder/IPCThreadState.h>
#include <utils/Log.h>
#include <errno.h>

#if LOG_NDEBUG

#define IF_LOG_TRANSACTIONS() if (false)
#define IF_LOG_COMMANDS() if (false)
#define LOG_REMOTEREFS(...) 
#define IF_LOG_REMOTEREFS() if (false)
#define LOG_THREADPOOL(...) 
#define LOG_ONEWAY(...) 

#else

#define IF_LOG_TRANSACTIONS() IF_ALOG(LOG_VERBOSE, "transact")
#define IF_LOG_COMMANDS() IF_ALOG(LOG_VERBOSE, "ipc")
#define LOG_REMOTEREFS(...) ALOG(LOG_DEBUG, "remoterefs", __VA_ARGS__)
#define IF_LOG_REMOTEREFS() IF_ALOG(LOG_DEBUG, "remoterefs")
#define LOG_THREADPOOL(...) ALOG(LOG_DEBUG, "threadpool", __VA_ARGS__)
#define LOG_ONEWAY(...) ALOG(LOG_DEBUG, "ipc", __VA_ARGS__)

#endif

// ---------------------------------------------------------------------------

namespace android {

IPCThreadState* IPCThreadState::self()
{
    return NULL;
}

void IPCThreadState::flushCommands()
{

}

void IPCThreadState::incStrongHandle(int32_t handle)
{
    LOG_REMOTEREFS("IPCThreadState::incStrongHandle(%d)\n", handle);
    //mOut.writeInt32(BC_ACQUIRE);
    mOut.writeInt32(handle);
}

void IPCThreadState::decStrongHandle(int32_t handle)
{
    LOG_REMOTEREFS("IPCThreadState::decStrongHandle(%d)\n", handle);
    //mOut.writeInt32(BC_RELEASE);
    mOut.writeInt32(handle);
}

void IPCThreadState::incWeakHandle(int32_t handle)
{
    LOG_REMOTEREFS("IPCThreadState::incWeakHandle(%d)\n", handle);
    //mOut.writeInt32(BC_INCREFS);
    mOut.writeInt32(handle);
}

void IPCThreadState::decWeakHandle(int32_t handle)
{
    LOG_REMOTEREFS("IPCThreadState::decWeakHandle(%d)\n", handle);
    //mOut.writeInt32(BC_DECREFS);
    mOut.writeInt32(handle);
}

status_t IPCThreadState::attemptIncStrongHandle(int32_t handle)
{
    (void)handle;
    ALOGE("%s(%d): Not supported\n", __func__, handle);
    return INVALID_OPERATION;
}

void IPCThreadState::expungeHandle(int32_t handle, IBinder* binder)
{
#if LOG_REFCOUNTS
    printf("IPCThreadState::expungeHandle(%ld)\n", handle);
#endif
    //self()->mProcess->expungeHandle(handle, binder);
}

status_t IPCThreadState::requestDeathNotification(int32_t handle, BpBinder* proxy)
{
    //mOut.writeInt32(BC_REQUEST_DEATH_NOTIFICATION);
    mOut.writeInt32((int32_t)handle);
    mOut.writePointer((uintptr_t)proxy);
    return NO_ERROR;
}

status_t IPCThreadState::clearDeathNotification(int32_t handle, BpBinder* proxy)
{
    //mOut.writeInt32(BC_CLEAR_DEATH_NOTIFICATION);
    mOut.writeInt32((int32_t)handle);
    mOut.writePointer((uintptr_t)proxy);
    return NO_ERROR;
}

status_t IPCThreadState::transact(int32_t handle,
                                  uint32_t code, const Parcel& data,
                                  Parcel* reply, uint32_t flags)
{
    return NO_ERROR;
}

}
