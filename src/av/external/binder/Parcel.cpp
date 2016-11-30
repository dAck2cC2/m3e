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

#define LOG_TAG "Parcel"
//#define LOG_NDEBUG 0
#define UNEXPECTED_NULL -1
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

//#include <binder/Binder.h>
//#include <binder/BpBinder.h>
//#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>
//#include <binder/ProcessState.h>
//#include <binder/Status.h>
//#include <binder/TextOutput.h>

//#include <cutils/ashmem.h>
//#include <utils/Debug.h>
//#include <utils/Flattenable.h>
//#include <utils/Log.h>
#include <utils/misc.h>
#include <utils/String8.h>
#include <utils/String16.h>

//#include <private/binder/binder_module.h>
//#include <private/binder/Static.h>

#ifndef INT32_MAX
#define INT32_MAX ((int32_t)(2147483647))
#endif

#define LOG_REFS(...)
//#define LOG_REFS(...) ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_ALLOC(...)
//#define LOG_ALLOC(...) ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// ---------------------------------------------------------------------------

// This macro should never be used at runtime, as a too large value
// of s could cause an integer overflow. Instead, you should always
// use the wrapper function pad_size()
#define PAD_SIZE_UNSAFE(s) (((s)+3)&~3)

static size_t pad_size(size_t s) {
    return 0;
}

// Note: must be kept in sync with android/os/StrictMode.java's PENALTY_GATHER
#define STRICT_MODE_PENALTY_GATHER (0x40 << 16)

// XXX This can be made public if we want to provide
// support for typed data.
struct small_flat_data
{
    uint32_t type;
    uint32_t data;
};

namespace android {

//static pthread_mutex_t gParcelGlobalAllocSizeLock = PTHREAD_MUTEX_INITIALIZER;
static size_t gParcelGlobalAllocSize = 0;
static size_t gParcelGlobalAllocCount = 0;

static size_t gMaxFds = 0;

// Maximum size of a blob to transfer in-place.
static const size_t BLOB_INPLACE_LIMIT = 16 * 1024;

enum {
    BLOB_INPLACE = 0,
    BLOB_ASHMEM_IMMUTABLE = 1,
    BLOB_ASHMEM_MUTABLE = 2,
};
#if 0
static dev_t ashmem_rdev()
{
    static dev_t __ashmem_rdev;
    static pthread_mutex_t __ashmem_rdev_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&__ashmem_rdev_lock);

    dev_t rdev = __ashmem_rdev;
    if (!rdev) {
        int fd = TEMP_FAILURE_RETRY(open("/dev/ashmem", O_RDONLY));
        if (fd >= 0) {
            struct stat st;

            int ret = TEMP_FAILURE_RETRY(fstat(fd, &st));
            close(fd);
            if ((ret >= 0) && S_ISCHR(st.st_mode)) {
                rdev = __ashmem_rdev = st.st_rdev;
            }
        }
    }

    pthread_mutex_unlock(&__ashmem_rdev_lock);

    return rdev;
}

void acquire_object(const sp<ProcessState>& proc,
    const flat_binder_object& obj, const void* who, size_t* outAshmemSize)
{
    switch (obj.type) {
        case BINDER_TYPE_BINDER:
            if (obj.binder) {
                LOG_REFS("Parcel %p acquiring reference on local %p", who, obj.cookie);
                reinterpret_cast<IBinder*>(obj.cookie)->incStrong(who);
            }
            return;
        case BINDER_TYPE_WEAK_BINDER:
            if (obj.binder)
                reinterpret_cast<RefBase::weakref_type*>(obj.binder)->incWeak(who);
            return;
        case BINDER_TYPE_HANDLE: {
            const sp<IBinder> b = proc->getStrongProxyForHandle(obj.handle);
            if (b != NULL) {
                LOG_REFS("Parcel %p acquiring reference on remote %p", who, b.get());
                b->incStrong(who);
            }
            return;
        }
        case BINDER_TYPE_WEAK_HANDLE: {
            const wp<IBinder> b = proc->getWeakProxyForHandle(obj.handle);
            if (b != NULL) b.get_refs()->incWeak(who);
            return;
        }
        case BINDER_TYPE_FD: {
            if ((obj.cookie != 0) && (outAshmemSize != NULL)) {
                struct stat st;
                int ret = fstat(obj.handle, &st);
                if (!ret && S_ISCHR(st.st_mode) && (st.st_rdev == ashmem_rdev())) {
                    // If we own an ashmem fd, keep track of how much memory it refers to.
                    int size = ashmem_get_size_region(obj.handle);
                    if (size > 0) {
                        *outAshmemSize += size;
                    }
                }
            }
            return;
        }
    }

    ALOGD("Invalid object type 0x%08x", obj.type);
}

void acquire_object(const sp<ProcessState>& proc,
    const flat_binder_object& obj, const void* who)
{
    acquire_object(proc, obj, who, NULL);
}

static void release_object(const sp<ProcessState>& proc,
    const flat_binder_object& obj, const void* who, size_t* outAshmemSize)
{
    switch (obj.type) {
        case BINDER_TYPE_BINDER:
            if (obj.binder) {
                LOG_REFS("Parcel %p releasing reference on local %p", who, obj.cookie);
                reinterpret_cast<IBinder*>(obj.cookie)->decStrong(who);
            }
            return;
        case BINDER_TYPE_WEAK_BINDER:
            if (obj.binder)
                reinterpret_cast<RefBase::weakref_type*>(obj.binder)->decWeak(who);
            return;
        case BINDER_TYPE_HANDLE: {
            const sp<IBinder> b = proc->getStrongProxyForHandle(obj.handle);
            if (b != NULL) {
                LOG_REFS("Parcel %p releasing reference on remote %p", who, b.get());
                b->decStrong(who);
            }
            return;
        }
        case BINDER_TYPE_WEAK_HANDLE: {
            const wp<IBinder> b = proc->getWeakProxyForHandle(obj.handle);
            if (b != NULL) b.get_refs()->decWeak(who);
            return;
        }
        case BINDER_TYPE_FD: {
            if (obj.cookie != 0) { // owned
                if (outAshmemSize != NULL) {
                    struct stat st;
                    int ret = fstat(obj.handle, &st);
                    if (!ret && S_ISCHR(st.st_mode) && (st.st_rdev == ashmem_rdev())) {
                        int size = ashmem_get_size_region(obj.handle);
                        if (size > 0) {
                            *outAshmemSize -= size;
                        }
                    }
                }

                close(obj.handle);
            }
            return;
        }
    }

    ALOGE("Invalid object type 0x%08x", obj.type);
}

void release_object(const sp<ProcessState>& proc,
    const flat_binder_object& obj, const void* who)
{
    release_object(proc, obj, who, NULL);
}

inline static status_t finish_flatten_binder(
    const sp<IBinder>& /*binder*/, const flat_binder_object& flat, Parcel* out)
{
    return out->writeObject(flat, false);
}

status_t flatten_binder(const sp<ProcessState>& /*proc*/,
    const sp<IBinder>& binder, Parcel* out)
{
    flat_binder_object obj;

    obj.flags = 0x7f | FLAT_BINDER_FLAG_ACCEPTS_FDS;
    if (binder != NULL) {
        IBinder *local = binder->localBinder();
        if (!local) {
            BpBinder *proxy = binder->remoteBinder();
            if (proxy == NULL) {
                ALOGE("null proxy");
            }
            const int32_t handle = proxy ? proxy->handle() : 0;
            obj.type = BINDER_TYPE_HANDLE;
            obj.binder = 0; /* Don't pass uninitialized stack data to a remote process */
            obj.handle = handle;
            obj.cookie = 0;
        } else {
            obj.type = BINDER_TYPE_BINDER;
            obj.binder = reinterpret_cast<uintptr_t>(local->getWeakRefs());
            obj.cookie = reinterpret_cast<uintptr_t>(local);
        }
    } else {
        obj.type = BINDER_TYPE_BINDER;
        obj.binder = 0;
        obj.cookie = 0;
    }

    return finish_flatten_binder(binder, obj, out);
}

status_t flatten_binder(const sp<ProcessState>& /*proc*/,
    const wp<IBinder>& binder, Parcel* out)
{
    flat_binder_object obj;

    obj.flags = 0x7f | FLAT_BINDER_FLAG_ACCEPTS_FDS;
    if (binder != NULL) {
        sp<IBinder> real = binder.promote();
        if (real != NULL) {
            IBinder *local = real->localBinder();
            if (!local) {
                BpBinder *proxy = real->remoteBinder();
                if (proxy == NULL) {
                    ALOGE("null proxy");
                }
                const int32_t handle = proxy ? proxy->handle() : 0;
                obj.type = BINDER_TYPE_WEAK_HANDLE;
                obj.binder = 0; /* Don't pass uninitialized stack data to a remote process */
                obj.handle = handle;
                obj.cookie = 0;
            } else {
                obj.type = BINDER_TYPE_WEAK_BINDER;
                obj.binder = reinterpret_cast<uintptr_t>(binder.get_refs());
                obj.cookie = reinterpret_cast<uintptr_t>(binder.unsafe_get());
            }
            return finish_flatten_binder(real, obj, out);
        }

        // XXX How to deal?  In order to flatten the given binder,
        // we need to probe it for information, which requires a primary
        // reference...  but we don't have one.
        //
        // The OpenBinder implementation uses a dynamic_cast<> here,
        // but we can't do that with the different reference counting
        // implementation we are using.
        ALOGE("Unable to unflatten Binder weak reference!");
        obj.type = BINDER_TYPE_BINDER;
        obj.binder = 0;
        obj.cookie = 0;
        return finish_flatten_binder(NULL, obj, out);

    } else {
        obj.type = BINDER_TYPE_BINDER;
        obj.binder = 0;
        obj.cookie = 0;
        return finish_flatten_binder(NULL, obj, out);
    }
}

inline static status_t finish_unflatten_binder(
    BpBinder* /*proxy*/, const flat_binder_object& /*flat*/,
    const Parcel& /*in*/)
{
    return NO_ERROR;
}

status_t unflatten_binder(const sp<ProcessState>& proc,
    const Parcel& in, sp<IBinder>* out)
{
    const flat_binder_object* flat = in.readObject(false);

    if (flat) {
        switch (flat->type) {
            case BINDER_TYPE_BINDER:
                *out = reinterpret_cast<IBinder*>(flat->cookie);
                return finish_unflatten_binder(NULL, *flat, in);
            case BINDER_TYPE_HANDLE:
                *out = proc->getStrongProxyForHandle(flat->handle);
                return finish_unflatten_binder(
                    static_cast<BpBinder*>(out->get()), *flat, in);
        }
    }
    return BAD_TYPE;
}

status_t unflatten_binder(const sp<ProcessState>& proc,
    const Parcel& in, wp<IBinder>* out)
{
    const flat_binder_object* flat = in.readObject(false);

    if (flat) {
        switch (flat->type) {
            case BINDER_TYPE_BINDER:
                *out = reinterpret_cast<IBinder*>(flat->cookie);
                return finish_unflatten_binder(NULL, *flat, in);
            case BINDER_TYPE_WEAK_BINDER:
                if (flat->binder != 0) {
                    out->set_object_and_refs(
                        reinterpret_cast<IBinder*>(flat->cookie),
                        reinterpret_cast<RefBase::weakref_type*>(flat->binder));
                } else {
                    *out = NULL;
                }
                return finish_unflatten_binder(NULL, *flat, in);
            case BINDER_TYPE_HANDLE:
            case BINDER_TYPE_WEAK_HANDLE:
                *out = proc->getWeakProxyForHandle(flat->handle);
                return finish_unflatten_binder(
                    static_cast<BpBinder*>(out->unsafe_get()), *flat, in);
        }
    }
    return BAD_TYPE;
}
#endif
// ---------------------------------------------------------------------------

Parcel::Parcel()
{
    LOG_ALLOC("Parcel %p: constructing", this);
    initState();
}

Parcel::~Parcel()
{
    freeDataNoInit();
    LOG_ALLOC("Parcel %p: destroyed", this);
}

size_t Parcel::getGlobalAllocSize() {
    //pthread_mutex_lock(&gParcelGlobalAllocSizeLock);
    size_t size = gParcelGlobalAllocSize;
    //pthread_mutex_unlock(&gParcelGlobalAllocSizeLock);
    return size;
}

size_t Parcel::getGlobalAllocCount() {
    //pthread_mutex_lock(&gParcelGlobalAllocSizeLock);
    size_t count = gParcelGlobalAllocCount;
    //pthread_mutex_unlock(&gParcelGlobalAllocSizeLock);
    return count;
}

const uint8_t* Parcel::data() const
{
    return mData;
}

size_t Parcel::dataSize() const
{
    return (mDataSize > mDataPos ? mDataSize : mDataPos);
}

size_t Parcel::dataAvail() const
{
    size_t result = dataSize() - dataPosition();
    if (result > INT32_MAX) {
        abort();
    }
    return result;
}

size_t Parcel::dataPosition() const
{
    return mDataPos;
}

size_t Parcel::dataCapacity() const
{
    return mDataCapacity;
}

status_t Parcel::setDataSize(size_t size)
{
    if (size > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    status_t err;
    //err = continueWrite(size);
    if (err == NO_ERROR) {
        mDataSize = size;
        ALOGV("setDataSize Setting data size of %p to %zu", this, mDataSize);
    }
    return err;
}

void Parcel::setDataPosition(size_t pos) const
{
    if (pos > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        abort();
    }

    mDataPos = pos;
    mNextObjectHint = 0;
}

status_t Parcel::setDataCapacity(size_t size)
{
    if (size > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    //if (size > mDataCapacity) return continueWrite(size);
    return NO_ERROR;
}

status_t Parcel::setData(const uint8_t* buffer, size_t len)
{
    return 0;
}

status_t Parcel::appendFrom(const Parcel *parcel, size_t offset, size_t len)
{
    //const sp<ProcessState> proc(ProcessState::self());
    status_t err;
    const uint8_t *data = parcel->mData;
    const binder_size_t *objects = parcel->mObjects;
    size_t size = parcel->mObjectsSize;
    int startPos = mDataPos;
    int firstIndex = -1, lastIndex = -2;

    if (len == 0) {
        return NO_ERROR;
    }

    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    // range checks against the source parcel size
    if ((offset > parcel->mDataSize)
            || (len > parcel->mDataSize)
            || (offset + len > parcel->mDataSize)) {
        return BAD_VALUE;
    }

    // Count objects in range
    for (int i = 0; i < (int) size; i++) {
        size_t off = objects[i];
        //if ((off >= offset) && (off + sizeof(flat_binder_object) <= offset + len)) {
        //    if (firstIndex == -1) {
        //        firstIndex = i;
        //    }
        //    lastIndex = i;
        //}
    }
    int numObjects = lastIndex - firstIndex + 1;

    if ((mDataSize+len) > mDataCapacity) {
        // grow data
        //err = growData(len);
        if (err != NO_ERROR) {
            return err;
        }
    }

    // append data
    memcpy(mData + mDataPos, data + offset, len);
    mDataPos += len;
    mDataSize += len;

    err = NO_ERROR;

    if (numObjects > 0) {
        // grow objects
        if (mObjectsCapacity < mObjectsSize + numObjects) {
            size_t newSize = ((mObjectsSize + numObjects)*3)/2;
            if (newSize < mObjectsSize) return NO_MEMORY;   // overflow
            //binder_size_t *objects =
            //    (binder_size_t*)realloc(mObjects, newSize*sizeof(binder_size_t));
            //if (objects == (binder_size_t*)0) {
            //    return NO_MEMORY;
            //}
            mObjects = objects;
            mObjectsCapacity = newSize;
        }

        // append and acquire objects
        int idx = mObjectsSize;
        for (int i = firstIndex; i <= lastIndex; i++) {
            size_t off = objects[i] - offset + startPos;
            mObjects[idx++] = off;
            mObjectsSize++;

            //flat_binder_object* flat
            //    = reinterpret_cast<flat_binder_object*>(mData + off);
            //acquire_object(proc, *flat, this, &mOpenAshmemSize);

            //if (flat->type == BINDER_TYPE_FD) {
                // If this is a file descriptor, we need to dup it so the
                // new Parcel now owns its own fd, and can declare that we
                // officially know we have fds.
            //    flat->handle = dup(flat->handle);
            //    flat->cookie = 1;
            //    mHasFds = mFdsKnown = true;
            //    if (!mAllowFds) {
            //        err = FDS_NOT_ALLOWED;
            //    }
            //}
        }
    }

    return err;
}

bool Parcel::allowFds() const
{
    return mAllowFds;
}

bool Parcel::pushAllowFds(bool allowFds)
{
    const bool origValue = mAllowFds;
    if (!allowFds) {
        mAllowFds = false;
    }
    return origValue;
}

void Parcel::restoreAllowFds(bool lastValue)
{
    mAllowFds = lastValue;
}

bool Parcel::hasFileDescriptors() const
{
    if (!mFdsKnown) {
        //scanForFds();
    }
    return mHasFds;
}

// Write RPC headers.  (previously just the interface token)
status_t Parcel::writeInterfaceToken(const String16& interface)
{
    //writeInt32(IPCThreadState::self()->getStrictModePolicy() |
    //           STRICT_MODE_PENALTY_GATHER);
    // currently the interface identification token is just its name as a string
    return writeString16(interface);
}

bool Parcel::checkInterface(IBinder* binder) const
{
    //return enforceInterface(binder->getInterfaceDescriptor());
    return false;
}

bool Parcel::enforceInterface(const String16& interface,
                              IPCThreadState* threadState) const
{
    int32_t strictPolicy = readInt32();
    //if (threadState == NULL) {
    //    threadState = IPCThreadState::self();
    //}
    //if ((threadState->getLastTransactionBinderFlags() &
    //     IBinder::FLAG_ONEWAY) != 0) {
      // For one-way calls, the callee is running entirely
      // disconnected from the caller, so disable StrictMode entirely.
      // Not only does disk/network usage not impact the caller, but
      // there's no way to commuicate back any violations anyway.
    //  threadState->setStrictModePolicy(0);
    //} else {
    //  threadState->setStrictModePolicy(strictPolicy);
    //}
    const String16 str(readString16());
    if (str == interface) {
        return true;
    } else {
        ALOGW("**** enforceInterface() expected '%s' but read '%s'",
                String8(interface).string(), String8(str).string());
        return false;
    }
}

const binder_size_t* Parcel::objects() const
{
    return mObjects;
}

size_t Parcel::objectsCount() const
{
    return mObjectsSize;
}

status_t Parcel::errorCheck() const
{
    return mError;
}

void Parcel::setError(status_t err)
{
    mError = err;
}

status_t Parcel::finishWrite(size_t len)
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    //printf("Finish write of %d\n", len);
    mDataPos += len;
    ALOGV("finishWrite Setting data pos of %p to %zu", this, mDataPos);
    if (mDataPos > mDataSize) {
        mDataSize = mDataPos;
        ALOGV("finishWrite Setting data size of %p to %zu", this, mDataSize);
    }
    //printf("New pos=%d, size=%d\n", mDataPos, mDataSize);
    return NO_ERROR;
}

status_t Parcel::writeUnpadded(const void* data, size_t len)
{
    return 0;
}

status_t Parcel::write(const void* data, size_t len)
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    //void* const d = writeInplace(len);
    //if (d) {
    //    memcpy(d, data, len);
    //    return NO_ERROR;
    //}
    return mError;
}

void* Parcel::writeInplace(size_t len)
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return NULL;
    }

    const size_t padded = 0;
    //pad_size(len);

    // sanity check for integer overflow
    if (mDataPos+padded < mDataPos) {
        return NULL;
    }

    if ((mDataPos+padded) <= mDataCapacity) {
restart_write:
        //printf("Writing %ld bytes, padded to %ld\n", len, padded);
        uint8_t* const data = mData+mDataPos;

        // Need to pad at end?
        if (padded != len) {
#if BYTE_ORDER == BIG_ENDIAN
            static const uint32_t mask[4] = {
                0x00000000, 0xffffff00, 0xffff0000, 0xff000000
            };
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
            static const uint32_t mask[4] = {
                0x00000000, 0x00ffffff, 0x0000ffff, 0x000000ff
            };
#endif
            //printf("Applying pad mask: %p to %p\n", (void*)mask[padded-len],
            //    *reinterpret_cast<void**>(data+padded-4));
            *reinterpret_cast<uint32_t*>(data+padded-4) &= mask[padded-len];
        }

        //finishWrite(padded);
        return data;
    }

    //status_t err = growData(padded);
    //if (err == NO_ERROR) goto restart_write;
    return NULL;
}

status_t Parcel::writeUtf8AsUtf16(const std::string& str) {
    const uint8_t* strData = (uint8_t*)str.data();
    const size_t strLen= str.length();
    const ssize_t utf16Len = -1;
    //utf8_to_utf16_length(strData, strLen);
    if (utf16Len < 0 || utf16Len> std::numeric_limits<int32_t>::max()) {
        return BAD_VALUE;
    }

    status_t err = writeInt32(utf16Len);
    if (err) {
        return err;
    }

    // Allocate enough bytes to hold our converted string and its terminating NULL.
    void* dst = writeInplace((utf16Len + 1) * sizeof(char16_t));
    if (!dst) {
        return NO_MEMORY;
    }

    //utf8_to_utf16(strData, strLen, (char16_t*)dst);

    return NO_ERROR;
}

status_t Parcel::writeUtf8AsUtf16(const std::unique_ptr<std::string>& str) {
  if (!str) {
    return writeInt32(-1);
  }
  return writeUtf8AsUtf16(*str);
}

namespace {

template<typename T>
status_t writeByteVectorInternal(Parcel* parcel, const std::vector<T>& val)
{
    status_t status;
    if (val.size() > std::numeric_limits<int32_t>::max()) {
        status = BAD_VALUE;
        return status;
    }

    status = parcel->writeInt32(val.size());
    if (status != OK) {
        return status;
    }

    void* data = parcel->writeInplace(val.size());
    if (!data) {
        status = BAD_VALUE;
        return status;
    }

    memcpy(data, val.data(), val.size());
    return status;
}

template<typename T>
status_t writeByteVectorInternalPtr(Parcel* parcel,
                                    const std::unique_ptr<std::vector<T>>& val)
{
    if (!val) {
        return parcel->writeInt32(-1);
    }

    return writeByteVectorInternal(parcel, *val);
}

}  // namespace

status_t Parcel::writeByteVector(const std::vector<int8_t>& val) {
    return writeByteVectorInternal(this, val);
}

status_t Parcel::writeByteVector(const std::unique_ptr<std::vector<int8_t>>& val)
{
    return writeByteVectorInternalPtr(this, val);
}

status_t Parcel::writeByteVector(const std::vector<uint8_t>& val) {
    return writeByteVectorInternal(this, val);
}

status_t Parcel::writeByteVector(const std::unique_ptr<std::vector<uint8_t>>& val)
{
    return writeByteVectorInternalPtr(this, val);
}

status_t Parcel::writeInt32Vector(const std::vector<int32_t>& val)
{
    return writeTypedVector(val, &Parcel::writeInt32);
}

status_t Parcel::writeInt32Vector(const std::unique_ptr<std::vector<int32_t>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeInt32);
}

status_t Parcel::writeInt64Vector(const std::vector<int64_t>& val)
{
    return writeTypedVector(val, &Parcel::writeInt64);
}

status_t Parcel::writeInt64Vector(const std::unique_ptr<std::vector<int64_t>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeInt64);
}

status_t Parcel::writeFloatVector(const std::vector<float>& val)
{
    return writeTypedVector(val, &Parcel::writeFloat);
}

status_t Parcel::writeFloatVector(const std::unique_ptr<std::vector<float>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeFloat);
}

status_t Parcel::writeDoubleVector(const std::vector<double>& val)
{
    return writeTypedVector(val, &Parcel::writeDouble);
}

status_t Parcel::writeDoubleVector(const std::unique_ptr<std::vector<double>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeDouble);
}

status_t Parcel::writeBoolVector(const std::vector<bool>& val)
{
    return writeTypedVector(val, &Parcel::writeBool);
}

status_t Parcel::writeBoolVector(const std::unique_ptr<std::vector<bool>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeBool);
}

status_t Parcel::writeCharVector(const std::vector<char16_t>& val)
{
    return writeTypedVector(val, &Parcel::writeChar);
}

status_t Parcel::writeCharVector(const std::unique_ptr<std::vector<char16_t>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeChar);
}

status_t Parcel::writeString16Vector(const std::vector<String16>& val)
{
    return writeTypedVector(val, &Parcel::writeString16);
}

status_t Parcel::writeString16Vector(
        const std::unique_ptr<std::vector<std::unique_ptr<String16>>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeString16);
}

status_t Parcel::writeUtf8VectorAsUtf16Vector(
                        const std::unique_ptr<std::vector<std::unique_ptr<std::string>>>& val) {
    return writeNullableTypedVector(val, &Parcel::writeUtf8AsUtf16);
}

status_t Parcel::writeUtf8VectorAsUtf16Vector(const std::vector<std::string>& val) {
    return writeTypedVector(val, &Parcel::writeUtf8AsUtf16);
}

status_t Parcel::writeInt32(int32_t val)
{
    return writeAligned(val);
}

status_t Parcel::writeUint32(uint32_t val)
{
    return writeAligned(val);
}

status_t Parcel::writeInt32Array(size_t len, const int32_t *val) {
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    if (!val) {
        return writeInt32(-1);
    }
    status_t ret = writeInt32(static_cast<uint32_t>(len));
    if (ret == NO_ERROR) {
        ret = write(val, len * sizeof(*val));
    }
    return ret;
}
status_t Parcel::writeByteArray(size_t len, const uint8_t *val) {
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    if (!val) {
        return writeInt32(-1);
    }
    status_t ret = writeInt32(static_cast<uint32_t>(len));
    if (ret == NO_ERROR) {
        ret = write(val, len * sizeof(*val));
    }
    return ret;
}

status_t Parcel::writeBool(bool val)
{
    return writeInt32(int32_t(val));
}

status_t Parcel::writeChar(char16_t val)
{
    return writeInt32(int32_t(val));
}

status_t Parcel::writeByte(int8_t val)
{
    return writeInt32(int32_t(val));
}

status_t Parcel::writeInt64(int64_t val)
{
    return writeAligned(val);
}

status_t Parcel::writeUint64(uint64_t val)
{
    return writeAligned(val);
}

status_t Parcel::writePointer(uintptr_t val)
{
    return 0;
}

status_t Parcel::writeFloat(float val)
{
    return writeAligned(val);
}

#if defined(__mips__) && defined(__mips_hard_float)

status_t Parcel::writeDouble(double val)
{
    union {
        double d;
        unsigned long long ll;
    } u;
    u.d = val;
    return writeAligned(u.ll);
}

#else

status_t Parcel::writeDouble(double val)
{
    return writeAligned(val);
}

#endif

status_t Parcel::writeCString(const char* str)
{
    return write(str, strlen(str)+1);
}

status_t Parcel::writeString8(const String8& str)
{
    status_t err = writeInt32(str.bytes());
    // only write string if its length is more than zero characters,
    // as readString8 will only read if the length field is non-zero.
    // this is slightly different from how writeString16 works.
    if (str.bytes() > 0 && err == NO_ERROR) {
        err = write(str.string(), str.bytes()+1);
    }
    return err;
}

status_t Parcel::writeString16(const std::unique_ptr<String16>& str)
{
    if (!str) {
        return writeInt32(-1);
    }

    return writeString16(*str);
}

status_t Parcel::writeString16(const String16& str)
{
    return writeString16(str.string(), str.size());
}

status_t Parcel::writeString16(const char16_t* str, size_t len)
{
    if (str == NULL) return writeInt32(-1);

    status_t err = writeInt32(len);
    if (err == NO_ERROR) {
        len *= sizeof(char16_t);
        uint8_t* data = (uint8_t*)writeInplace(len+sizeof(char16_t));
        if (data) {
            memcpy(data, str, len);
            *reinterpret_cast<char16_t*>(data+len) = 0;
            return NO_ERROR;
        }
        err = mError;
    }
    return err;
}

status_t Parcel::writeStrongBinder(const sp<IBinder>& val)
{
    //return flatten_binder(ProcessState::self(), val, this);
    return 0;
}

status_t Parcel::writeStrongBinderVector(const std::vector<sp<IBinder>>& val)
{
    return writeTypedVector(val, &Parcel::writeStrongBinder);
}

status_t Parcel::writeStrongBinderVector(const std::unique_ptr<std::vector<sp<IBinder>>>& val)
{
    return writeNullableTypedVector(val, &Parcel::writeStrongBinder);
}

status_t Parcel::readStrongBinderVector(std::unique_ptr<std::vector<sp<IBinder>>>* val) const {
    return readNullableTypedVector(val, &Parcel::readStrongBinder);
}

status_t Parcel::readStrongBinderVector(std::vector<sp<IBinder>>* val) const {
    return readTypedVector(val, &Parcel::readStrongBinder);
}

status_t Parcel::writeWeakBinder(const wp<IBinder>& val)
{
    //return flatten_binder(ProcessState::self(), val, this);
    return 0;
}

status_t Parcel::writeFileDescriptor(int fd, bool takeOwnership)
{
    return 0;
}

status_t Parcel::writeDupFileDescriptor(int fd)
{
    int dupFd = dup(fd);
    if (dupFd < 0) {
        return -errno;
    }
    status_t err = writeFileDescriptor(dupFd, true /*takeOwnership*/);
    if (err != OK) {
        close(dupFd);
    }
    return err;
}

status_t Parcel::writeBlob(size_t len, bool mutableCopy, WritableBlob* outBlob)
{
    return 0;
}

status_t Parcel::writeDupImmutableBlobFileDescriptor(int fd)
{
    // Must match up with what's done in writeBlob.
    if (!mAllowFds) return FDS_NOT_ALLOWED;
    status_t status = writeInt32(BLOB_ASHMEM_IMMUTABLE);
    if (status) return status;
    return writeDupFileDescriptor(fd);
}

status_t Parcel::write(const FlattenableHelperInterface& val)
{
    status_t err;

    // size if needed
    const size_t len = val.getFlattenedSize();
    const size_t fd_count = val.getFdCount();

    if ((len > INT32_MAX) || (fd_count >= gMaxFds)) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    err = this->writeInt32(len);
    if (err) return err;

    err = this->writeInt32(fd_count);
    if (err) return err;

    // payload
    void* const buf = this->writeInplace(pad_size(len));
    if (buf == NULL)
        return BAD_VALUE;

    int* fds = NULL;
    if (fd_count) {
        fds = new (std::nothrow) int[fd_count];
        if (fds == nullptr) {
            ALOGE("write: failed to allocate requested %zu fds", fd_count);
            return BAD_VALUE;
        }
    }

    err = val.flatten(buf, len, fds, fd_count);
    for (size_t i=0 ; i<fd_count && err==NO_ERROR ; i++) {
        err = this->writeDupFileDescriptor( fds[i] );
    }

    if (fd_count) {
        delete [] fds;
    }

    return err;
}

status_t Parcel::writeNoException()
{
    return 0;
}

void Parcel::remove(size_t /*start*/, size_t /*amt*/)
{
    LOG_ALWAYS_FATAL("Parcel::remove() not yet implemented!");
}

status_t Parcel::read(void* outData, size_t len) const
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return BAD_VALUE;
    }

    if ((mDataPos+pad_size(len)) >= mDataPos && (mDataPos+pad_size(len)) <= mDataSize
            && len <= pad_size(len)) {
        memcpy(outData, mData+mDataPos, len);
        mDataPos += pad_size(len);
        ALOGV("read Setting data pos of %p to %zu", this, mDataPos);
        return NO_ERROR;
    }
    return NOT_ENOUGH_DATA;
}

const void* Parcel::readInplace(size_t len) const
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return NULL;
    }

    if ((mDataPos+pad_size(len)) >= mDataPos && (mDataPos+pad_size(len)) <= mDataSize
            && len <= pad_size(len)) {
        const void* data = mData+mDataPos;
        mDataPos += pad_size(len);
        ALOGV("readInplace Setting data pos of %p to %zu", this, mDataPos);
        return data;
    }
    return NULL;
}

template<class T>
status_t Parcel::readAligned(T *pArg) const {
//    COMPILE_TIME_ASSERT_FUNCTION_SCOPE(PAD_SIZE_UNSAFE(sizeof(T)) == sizeof(T));

    if ((mDataPos+sizeof(T)) <= mDataSize) {
        const void* data = mData+mDataPos;
        mDataPos += sizeof(T);
        *pArg =  *reinterpret_cast<const T*>(data);
        return NO_ERROR;
    } else {
        return NOT_ENOUGH_DATA;
    }
}

template<class T>
T Parcel::readAligned() const {
    T result;
    if (readAligned(&result) != NO_ERROR) {
        result = 0;
    }

    return result;
}

template<class T>
status_t Parcel::writeAligned(T val) {
//    COMPILE_TIME_ASSERT_FUNCTION_SCOPE(PAD_SIZE_UNSAFE(sizeof(T)) == sizeof(T));

    if ((mDataPos+sizeof(val)) <= mDataCapacity) {
restart_write:
        *reinterpret_cast<T*>(mData+mDataPos) = val;
        return finishWrite(sizeof(val));
    }

    status_t err = growData(sizeof(val));
    if (err == NO_ERROR) goto restart_write;
    return err;
}

namespace {

template<typename T>
status_t readByteVectorInternal(const Parcel* parcel,
                                std::vector<T>* val) {
    val->clear();

    int32_t size;
    status_t status = parcel->readInt32(&size);

    if (status != OK) {
        return status;
    }

    if (size < 0) {
        status = UNEXPECTED_NULL;
        return status;
    }
    if (size_t(size) > parcel->dataAvail()) {
        status = BAD_VALUE;
        return status;
    }

    const void* data = parcel->readInplace(size);
    if (!data) {
        status = BAD_VALUE;
        return status;
    }
    val->resize(size);
    memcpy(val->data(), data, size);

    return status;
}

template<typename T>
status_t readByteVectorInternalPtr(
        const Parcel* parcel,
        std::unique_ptr<std::vector<T>>* val) {
    const int32_t start = parcel->dataPosition();
    int32_t size;
    status_t status = parcel->readInt32(&size);
    val->reset();

    if (status != OK || size < 0) {
        return status;
    }

    parcel->setDataPosition(start);
    val->reset(new (std::nothrow) std::vector<T>());

    status = readByteVectorInternal(parcel, val->get());

    if (status != OK) {
        val->reset();
    }

    return status;
}

}  // namespace

status_t Parcel::readByteVector(std::vector<int8_t>* val) const {
    return readByteVectorInternal(this, val);
}

status_t Parcel::readByteVector(std::vector<uint8_t>* val) const {
    return readByteVectorInternal(this, val);
}

status_t Parcel::readByteVector(std::unique_ptr<std::vector<int8_t>>* val) const {
    return readByteVectorInternalPtr(this, val);
}

status_t Parcel::readByteVector(std::unique_ptr<std::vector<uint8_t>>* val) const {
    return readByteVectorInternalPtr(this, val);
}

status_t Parcel::readInt32Vector(std::unique_ptr<std::vector<int32_t>>* val) const {
    return readNullableTypedVector(val, &Parcel::readInt32);
}

status_t Parcel::readInt32Vector(std::vector<int32_t>* val) const {
    return readTypedVector(val, &Parcel::readInt32);
}

status_t Parcel::readInt64Vector(std::unique_ptr<std::vector<int64_t>>* val) const {
    return readNullableTypedVector(val, &Parcel::readInt64);
}

status_t Parcel::readInt64Vector(std::vector<int64_t>* val) const {
    return readTypedVector(val, &Parcel::readInt64);
}

status_t Parcel::readFloatVector(std::unique_ptr<std::vector<float>>* val) const {
    return readNullableTypedVector(val, &Parcel::readFloat);
}

status_t Parcel::readFloatVector(std::vector<float>* val) const {
    return readTypedVector(val, &Parcel::readFloat);
}

status_t Parcel::readDoubleVector(std::unique_ptr<std::vector<double>>* val) const {
    return readNullableTypedVector(val, &Parcel::readDouble);
}

status_t Parcel::readDoubleVector(std::vector<double>* val) const {
    return readTypedVector(val, &Parcel::readDouble);
}

status_t Parcel::readBoolVector(std::unique_ptr<std::vector<bool>>* val) const {
    const int32_t start = dataPosition();
    int32_t size;
    status_t status = readInt32(&size);
    val->reset();

    if (status != OK || size < 0) {
        return status;
    }

    setDataPosition(start);
    val->reset(new (std::nothrow) std::vector<bool>());

    status = readBoolVector(val->get());

    if (status != OK) {
        val->reset();
    }

    return status;
}

status_t Parcel::readBoolVector(std::vector<bool>* val) const {
    int32_t size;
    status_t status = readInt32(&size);

    if (status != OK) {
        return status;
    }

    if (size < 0) {
        return UNEXPECTED_NULL;
    }

    val->resize(size);

    /* C++ bool handling means a vector of bools isn't necessarily addressable
     * (we might use individual bits)
     */
    bool data;
    for (int32_t i = 0; i < size; ++i) {
        status = readBool(&data);
        (*val)[i] = data;

        if (status != OK) {
            return status;
        }
    }

    return OK;
}

status_t Parcel::readCharVector(std::unique_ptr<std::vector<char16_t>>* val) const {
    return readNullableTypedVector(val, &Parcel::readChar);
}

status_t Parcel::readCharVector(std::vector<char16_t>* val) const {
    return readTypedVector(val, &Parcel::readChar);
}

status_t Parcel::readString16Vector(
        std::unique_ptr<std::vector<std::unique_ptr<String16>>>* val) const {
    return readNullableTypedVector(val, &Parcel::readString16);
}

status_t Parcel::readString16Vector(std::vector<String16>* val) const {
    return readTypedVector(val, &Parcel::readString16);
}

status_t Parcel::readUtf8VectorFromUtf16Vector(
        std::unique_ptr<std::vector<std::unique_ptr<std::string>>>* val) const {
    return readNullableTypedVector(val, &Parcel::readUtf8FromUtf16);
}

status_t Parcel::readUtf8VectorFromUtf16Vector(std::vector<std::string>* val) const {
    return readTypedVector(val, &Parcel::readUtf8FromUtf16);
}

status_t Parcel::readInt32(int32_t *pArg) const
{
    return readAligned(pArg);
}

int32_t Parcel::readInt32() const
{
    return readAligned<int32_t>();
}

status_t Parcel::readUint32(uint32_t *pArg) const
{
    return readAligned(pArg);
}

uint32_t Parcel::readUint32() const
{
    return readAligned<uint32_t>();
}

status_t Parcel::readInt64(int64_t *pArg) const
{
    return readAligned(pArg);
}


int64_t Parcel::readInt64() const
{
    return readAligned<int64_t>();
}

status_t Parcel::readUint64(uint64_t *pArg) const
{
    return readAligned(pArg);
}

uint64_t Parcel::readUint64() const
{
    return readAligned<uint64_t>();
}

status_t Parcel::readPointer(uintptr_t *pArg) const
{
    return 0;
}

uintptr_t Parcel::readPointer() const
{
    return 0;
}


status_t Parcel::readFloat(float *pArg) const
{
    return readAligned(pArg);
}


float Parcel::readFloat() const
{
    return readAligned<float>();
}

#if defined(__mips__) && defined(__mips_hard_float)

status_t Parcel::readDouble(double *pArg) const
{
    union {
      double d;
      unsigned long long ll;
    } u;
    u.d = 0;
    status_t status;
    status = readAligned(&u.ll);
    *pArg = u.d;
    return status;
}

double Parcel::readDouble() const
{
    union {
      double d;
      unsigned long long ll;
    } u;
    u.ll = readAligned<unsigned long long>();
    return u.d;
}

#else

status_t Parcel::readDouble(double *pArg) const
{
    return readAligned(pArg);
}

double Parcel::readDouble() const
{
    return readAligned<double>();
}

#endif

status_t Parcel::readIntPtr(intptr_t *pArg) const
{
    return readAligned(pArg);
}


intptr_t Parcel::readIntPtr() const
{
    return readAligned<intptr_t>();
}

status_t Parcel::readBool(bool *pArg) const
{
    int32_t tmp;
    status_t ret = readInt32(&tmp);
    *pArg = (tmp != 0);
    return ret;
}

bool Parcel::readBool() const
{
    return readInt32() != 0;
}

status_t Parcel::readChar(char16_t *pArg) const
{
    int32_t tmp;
    status_t ret = readInt32(&tmp);
    *pArg = char16_t(tmp);
    return ret;
}

char16_t Parcel::readChar() const
{
    return char16_t(readInt32());
}

status_t Parcel::readByte(int8_t *pArg) const
{
    int32_t tmp;
    status_t ret = readInt32(&tmp);
    *pArg = int8_t(tmp);
    return ret;
}

int8_t Parcel::readByte() const
{
    return int8_t(readInt32());
}

status_t Parcel::readUtf8FromUtf16(std::string* str) const {
    return NO_ERROR;
}

status_t Parcel::readUtf8FromUtf16(std::unique_ptr<std::string>* str) const {
    return readUtf8FromUtf16(str->get());
}

const char* Parcel::readCString() const
{
    return NULL;
}

String8 Parcel::readString8() const
{
    return String8();
}

String16 Parcel::readString16() const
{
    return String16();
}

status_t Parcel::readString16(std::unique_ptr<String16>* pArg) const
{
    return 0;
}

status_t Parcel::readString16(String16* pArg) const
{
    return 0;
}

const char16_t* Parcel::readString16Inplace(size_t* outLen) const
{
    return NULL;
}

status_t Parcel::readStrongBinder(sp<IBinder>* val) const
{
    return NO_ERROR;
}

sp<IBinder> Parcel::readStrongBinder() const
{
    sp<IBinder> val;
    return val;
}

wp<IBinder> Parcel::readWeakBinder() const
{
    wp<IBinder> val;
    return val;
}

int32_t Parcel::readExceptionCode() const
{
    return 0;
}

int Parcel::readFileDescriptor() const
{
    return BAD_TYPE;
}

status_t Parcel::readBlob(size_t len, ReadableBlob* outBlob) const
{
    return NO_ERROR;
}

status_t Parcel::read(FlattenableHelperInterface& val) const
{
    return NO_ERROR;    
}

void Parcel::closeFileDescriptors()
{
}

uintptr_t Parcel::ipcData() const
{
    return reinterpret_cast<uintptr_t>(mData);
}

size_t Parcel::ipcDataSize() const
{
    return (mDataSize > mDataPos ? mDataSize : mDataPos);
}

uintptr_t Parcel::ipcObjects() const
{
    return reinterpret_cast<uintptr_t>(mObjects);
}

size_t Parcel::ipcObjectsCount() const
{
    return mObjectsSize;
}

void Parcel::ipcSetDataReference(const uint8_t* data, size_t dataSize,
    const binder_size_t* objects, size_t objectsCount, release_func relFunc, void* relCookie)
{
}

void Parcel::print(TextOutput& to, uint32_t /*flags*/) const
{
}

void Parcel::releaseObjects()
{
}

void Parcel::acquireObjects()
{
}

void Parcel::freeData()
{
}

void Parcel::freeDataNoInit()
{
}

status_t Parcel::growData(size_t len)
{
    return 0;
}

status_t Parcel::restartWrite(size_t desired)
{
    return NO_ERROR;
}

status_t Parcel::continueWrite(size_t desired)
{
    return NO_ERROR;
}

void Parcel::initState()
{
 
}

void Parcel::scanForFds() const
{
}

size_t Parcel::getBlobAshmemSize() const
{
    // This used to return the size of all blobs that were written to ashmem, now we're returning
    // the ashmem currently referenced by this Parcel, which should be equivalent.
    // TODO: Remove method once ABI can be changed.
    return mOpenAshmemSize;
}

size_t Parcel::getOpenAshmemSize() const
{
    return mOpenAshmemSize;
}

// --- Parcel::Blob ---

Parcel::Blob::Blob() 
{
}

Parcel::Blob::~Blob() {
    release();
}

void Parcel::Blob::release() {
    clear();
}

void Parcel::Blob::init(int fd, void* data, size_t size, bool isMutable) {
}

void Parcel::Blob::clear() {
}

}; // namespace android
