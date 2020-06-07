/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "ProcessState"

#include <binder/ProcessState.h>

#include <binder/BpBinder.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <cutils/atomic.h>
#include <utils/Log.h>
#include <utils/String8.h>
#include <utils/String8.h>
#include <utils/threads.h>

#include <private/binder/binder_module.h>
#include <private/binder/Static.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/ioctl.h> /* M3E: */
#include <sys/mman.h>
//#include <sys/stat.h>  /* M3E: */
//#include <sys/types.h> /* M3E: */

/* M3E: Add */
#include <cutils/threads.h>

#define BINDER_VM_SIZE ((1 * 1024 * 1024) - (4096 *2))
#define DEFAULT_MAX_BINDER_THREADS 15

// -------------------------------------------------------------------------

namespace android {

/* M3E: local binder ioctl */
extern int      binder_open_local(const char* name);
extern status_t binder_close_local(int handler);
extern status_t binder_ioctl_local(int handler, int cmd, void* data);

/* M3E: used cutils/threads instead of pthread */
static thread_store_t gTLS = THREAD_STORE_INITIALIZER;
static  void  threadDestructor(void *st) {
    ProcessState* const self = static_cast<ProcessState*>(st);
    if (self != NULL) {
        self->decStrong((void*)threadDestructor);
    }
};

class PoolThread : public Thread
{
public:
    explicit PoolThread(bool isMain)
        : mIsMain(isMain)
    {
    }
    
protected:
    virtual bool threadLoop()
    {
        IPCThreadState::self()->joinThreadPool(mIsMain);
        return false;
    }
    
    const bool mIsMain;
};

sp<ProcessState> ProcessState::self()
{
	return initWithDriver("default");
}

sp<ProcessState> ProcessState::initWithDriver(const char* driver)
{
	// create a global ProcessState to store callback of context manager
	// It is created firslty, which should hold the handler of 0 for context manager.
	{
		Mutex::Autolock _l(gProcessMutex);
		if (gProcess == NULL) {
			gProcess = new ProcessState("Context Manager");
		}
	}

	if (gTLS.has_tls) {
		ProcessState* pt = (ProcessState*)thread_store_get(&gTLS);
		if (pt) {
			// Allow for initWithDriver to be called repeatedly with the same
			// driver.
			if (strcmp(pt->getDriverName().c_str(), driver)) {
				LOG_ALWAYS_FATAL("ProcessState was already initialized.");
			}
			return pt;
		}
		else {
			goto create_process;
		}
	}

create_process:
	sp<ProcessState> new_st = new ProcessState(driver);
	if (new_st != NULL) {
		new_st->incStrong((void*)threadDestructor);
		thread_store_set(&gTLS, new_st.get(), threadDestructor);
	}
	return new_st;
}

sp<ProcessState> ProcessState::selfOrNull()
{
	ProcessState* pt = (ProcessState*)thread_store_get(&gTLS);
	return pt;
}

void ProcessState::setContextObject(const sp<IBinder>& object)
{
    setContextObject(object, String16("default"));
}

sp<IBinder> ProcessState::getContextObject(const sp<IBinder>& /*caller*/)
{
    return getStrongProxyForHandle(0);
}

void ProcessState::setContextObject(const sp<IBinder>& object, const String16& name)
{
    AutoMutex _l(mLock);
    mContexts.add(name, object);
}

sp<IBinder> ProcessState::getContextObject(const String16& name, const sp<IBinder>& caller)
{
    mLock.lock();
    sp<IBinder> object(
        mContexts.indexOfKey(name) >= 0 ? mContexts.valueFor(name) : NULL);
    mLock.unlock();
    
    //printf("Getting context object %s for %p\n", String8(name).string(), caller.get());
    
    if (object != NULL) return object;

    // Don't attempt to retrieve contexts if we manage them
    if (mManagesContexts) {
        ALOGE("getContextObject(%s) failed, but we manage the contexts!\n",
            String8(name).string());
        return NULL;
    }
    
    IPCThreadState* ipc = IPCThreadState::self();
    {
        Parcel data, reply;
        // no interface token on this magic transaction
        data.writeString16(name);
        data.writeStrongBinder(caller);
        status_t result = ipc->transact(0 /*magic*/, 0, data, &reply, 0);
        if (result == NO_ERROR) {
            object = reply.readStrongBinder();
        }
    }
    
    ipc->flushCommands();
    
    if (object != NULL) setContextObject(object, name);
    return object;
}

void ProcessState::startThreadPool()
{
    AutoMutex _l(mLock);
    if (!mThreadPoolStarted) {
        mThreadPoolStarted = true;
        spawnPooledThread(true);
    }
}

bool ProcessState::isContextManager(void) const
{
    return mManagesContexts;
}

bool ProcessState::becomeContextManager(context_check_func checkFunc, void* userData)
{
    if (!mManagesContexts) {
        AutoMutex _l(mLock);
		/* M3E: save to global */
		if (gProcess != NULL) {
			gProcess->mBinderContextCheckFunc = checkFunc;
			gProcess->mBinderContextUserData = userData;
		}

        int dummy = 0;
        status_t result = binder_ioctl_local(mDriverFD, BINDER_SET_CONTEXT_MGR, &dummy);
        if (result == 0) {
            mManagesContexts = true;
        } else if (result == -1) {
			/* M3E: save to global */
			if (gProcess != NULL) {
				gProcess->mBinderContextCheckFunc = NULL;
				gProcess->mBinderContextUserData = NULL;
			}
            ALOGE("Binder ioctl to become context manager failed: %s\n", strerror(errno));
        }
    }
    return mManagesContexts;
}

// Get references to userspace objects held by the kernel binder driver
// Writes up to count elements into buf, and returns the total number
// of references the kernel has, which may be larger than count.
// buf may be NULL if count is 0.  The pointers returned by this method
// should only be used for debugging and not dereferenced, they may
// already be invalid.
ssize_t ProcessState::getKernelReferences(size_t buf_count, uintptr_t* buf)
{
#if TODO /* M3E: */
    // TODO: remove these when they are defined by bionic's binder.h
    struct binder_node_debug_info {
        binder_uintptr_t ptr;
        binder_uintptr_t cookie;
        __u32 has_strong_ref;
        __u32 has_weak_ref;
    };
#define BINDER_GET_NODE_DEBUG_INFO _IOWR('b', 11, struct binder_node_debug_info)

    binder_node_debug_info info = {};

    uintptr_t* end = buf ? buf + buf_count : NULL;
    size_t count = 0;

    do {
        status_t result = binder_ioctl_local(mDriverFD, BINDER_GET_NODE_DEBUG_INFO, &info);
        if (result < 0) {
            return -1;
        }
        if (info.ptr != 0) {
            if (buf && buf < end)
                *buf++ = info.ptr;
            count++;
            if (buf && buf < end)
                *buf++ = info.cookie;
            count++;
        }
    } while (info.ptr != 0);

    return count;
#else
	return 0;
#endif
}

ProcessState::handle_entry* ProcessState::lookupHandleLocked(int32_t handle)
{
    const size_t N=mHandleToObject.size();
    if (N <= (size_t)handle) {
        handle_entry e;
        e.binder = NULL;
        e.refs = NULL;
        status_t err = mHandleToObject.insertAt(e, N, handle+1-N);
        if (err < NO_ERROR) return NULL;
    }
    return &mHandleToObject.editItemAt(handle);
}

sp<IBinder> ProcessState::getStrongProxyForHandle(int32_t handle)
{
    sp<IBinder> result;

    AutoMutex _l(mLock);

    handle_entry* e = lookupHandleLocked(handle);

    if (e != NULL) {
        // We need to create a new BpBinder if there isn't currently one, OR we
        // are unable to acquire a weak reference on this current one.  See comment
        // in getWeakProxyForHandle() for more info about this.
        IBinder* b = e->binder;
        if (b == NULL || !e->refs->attemptIncWeak(this)) {
            if (handle == 0) {
                // Special case for context manager...
                // The context manager is the only object for which we create
                // a BpBinder proxy without already holding a reference.
                // Perform a dummy transaction to ensure the context manager
                // is registered before we create the first local reference
                // to it (which will occur when creating the BpBinder).
                // If a local reference is created for the BpBinder when the
                // context manager is not present, the driver will fail to
                // provide a reference to the context manager, but the
                // driver API does not return status.
                //
                // Note that this is not race-free if the context manager
                // dies while this code runs.
                //
                // TODO: add a driver API to wait for context manager, or
                // stop special casing handle 0 for context manager and add
                // a driver API to get a handle to the context manager with
                // proper reference counting.

                Parcel data;
                status_t status = IPCThreadState::self()->transact(
                        0, IBinder::PING_TRANSACTION, data, NULL, 0);
                if (status == DEAD_OBJECT)
                   return NULL;
            }

            b = BpBinder::create(handle);
            e->binder = b;
            if (b) e->refs = b->getWeakRefs();
            result = b;
        } else {
            // This little bit of nastyness is to allow us to add a primary
            // reference to the remote proxy when this team doesn't have one
            // but another team is sending the handle to us.
            result.force_set(b);
            e->refs->decWeak(this);
        }
    }

    return result;
}

wp<IBinder> ProcessState::getWeakProxyForHandle(int32_t handle)
{
    wp<IBinder> result;

    AutoMutex _l(mLock);

    handle_entry* e = lookupHandleLocked(handle);

    if (e != NULL) {        
        // We need to create a new BpBinder if there isn't currently one, OR we
        // are unable to acquire a weak reference on this current one.  The
        // attemptIncWeak() is safe because we know the BpBinder destructor will always
        // call expungeHandle(), which acquires the same lock we are holding now.
        // We need to do this because there is a race condition between someone
        // releasing a reference on this BpBinder, and a new reference on its handle
        // arriving from the driver.
        IBinder* b = e->binder;
        if (b == NULL || !e->refs->attemptIncWeak(this)) {
            b = BpBinder::create(handle);
            result = b;
            e->binder = b;
            if (b) e->refs = b->getWeakRefs();
        } else {
            result = b;
            e->refs->decWeak(this);
        }
    }

    return result;
}

void ProcessState::expungeHandle(int32_t handle, IBinder* binder)
{
    AutoMutex _l(mLock);
    
    handle_entry* e = lookupHandleLocked(handle);

    // This handle may have already been replaced with a new BpBinder
    // (if someone failed the AttemptIncWeak() above); we don't want
    // to overwrite it.
    if (e && e->binder == binder) e->binder = NULL;
}

String8 ProcessState::makeBinderThreadName() {
    int32_t s = android_atomic_add(1, &mThreadPoolSeq);
    pid_t pid = getpid();
    String8 name;
    name.appendFormat("Binder:%d_%X", pid, s);
    return name;
}

void ProcessState::spawnPooledThread(bool isMain)
{
    // M3E: The process is the same as thread. It has no thread pool.
    /* EMPTY */
}

status_t ProcessState::setThreadPoolMaxThreadCount(size_t maxThreads) {
    status_t result = NO_ERROR;
    if (binder_ioctl_local(mDriverFD, BINDER_SET_MAX_THREADS, &maxThreads) != -1) {
        mMaxThreads = maxThreads;
    } else {
        result = -errno;
        ALOGE("Binder ioctl to set max threads failed: %s", strerror(-result));
    }
    return result;
}

void ProcessState::giveThreadPoolName() {
    androidSetThreadName( makeBinderThreadName().string() );
}

String8 ProcessState::getDriverName() {
    return mDriverName;
}

static int open_driver(const char *driver)
{
    int fd = binder_open_local(driver);
    if (fd >= 0) {
        int vers = 0;
        status_t result = binder_ioctl_local(fd, BINDER_VERSION, &vers);
        if (result == -1) {
            ALOGE("Binder ioctl to obtain version failed: %d", result);
			binder_close_local(fd);
            fd = -1;
        }
        if (result != 0 || vers != BINDER_CURRENT_PROTOCOL_VERSION) {
          ALOGE("Binder driver protocol(%d) does not match user space protocol(%d)! ioctl() return value: %d",
                vers, BINDER_CURRENT_PROTOCOL_VERSION, result);
			binder_close_local(fd);
            fd = -1;
        }
        size_t maxThreads = DEFAULT_MAX_BINDER_THREADS;
        result = binder_ioctl_local(fd, BINDER_SET_MAX_THREADS, &maxThreads);
        if (result == -1) {
            ALOGE("Binder ioctl to set max threads failed: %d", result);
        }
    } else {
        ALOGW("Opening binder failed !");
    }
    return fd;
}

ProcessState::ProcessState(const char *driver)
    : mDriverName(String8(driver))
    , mDriverFD(open_driver(driver))
    , mVMStart(MAP_FAILED)
    //, mThreadCountLock(PTHREAD_MUTEX_INITIALIZER)
    //, mThreadCountDecrement(PTHREAD_COND_INITIALIZER)
    , mExecutingThreadsCount(0)
    , mMaxThreads(DEFAULT_MAX_BINDER_THREADS)
    , mStarvationStartTimeMs(0)
    , mManagesContexts(false)
    , mBinderContextCheckFunc(NULL)
    , mBinderContextUserData(NULL)
    , mThreadPoolStarted(false)
    , mThreadPoolSeq(1)
{
    LOG_ALWAYS_FATAL_IF(mDriverFD < 0, "Binder driver could not be opened.  Terminating.");
}

ProcessState::~ProcessState()
{
    if (mDriverFD >= 0) {
        binder_close_local(mDriverFD);
    }
    mDriverFD = -1;
}
        
}; // namespace android
