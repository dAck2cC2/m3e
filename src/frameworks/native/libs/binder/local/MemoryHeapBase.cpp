/*
 * Copyright (C) 2008 The Android Open Source Project
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

#define LOG_TAG "MemoryHeapBase"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
//#include <sys/ioctl.h> /* M3E: */
//#include <sys/stat.h>  /* M3E: */
//#include <sys/types.h> /* M3E: */
#include <unistd.h>

#include <binder/MemoryHeapBase.h>
#include <cutils/ashmem.h>
#include <cutils/atomic.h>
#include <log/log.h>

namespace android {

/* M3E: Implmentation */

static int gHeapCount = 0;
    
// ---------------------------------------------------------------------------

MemoryHeapBase::MemoryHeapBase()
    : mFD(-1), mSize(0), mBase(MAP_FAILED),
      mDevice(NULL), mNeedUnmap(false), mOffset(0)
{
}

MemoryHeapBase::MemoryHeapBase(size_t size, uint32_t flags, char const * name)
    : mFD(-1), mSize(0), mBase(MAP_FAILED), mFlags(flags),
      mDevice(0), mNeedUnmap(false), mOffset(0)
{
    mapfd(gHeapCount++, size, 0);
}

MemoryHeapBase::MemoryHeapBase(const char* device, size_t size, uint32_t flags)
    : mFD(-1), mSize(0), mBase(MAP_FAILED), mFlags(flags),
      mDevice(0), mNeedUnmap(false), mOffset(0)
{
    mapfd(gHeapCount++, size, 0);
}

MemoryHeapBase::MemoryHeapBase(int fd, size_t size, uint32_t flags, uint32_t offset)
    : mFD(-1), mSize(0), mBase(MAP_FAILED), mFlags(flags),
      mDevice(0), mNeedUnmap(false), mOffset(0)
{
    mapfd(gHeapCount++, size, offset);
}

status_t MemoryHeapBase::init(int fd, void *base, int size, int flags, const char* device)
{
    if (mFD != -1) {
        return INVALID_OPERATION;
    }
    mFD = fd;
    mBase = base;
    mSize = size;
    mFlags = flags;
    mDevice = device;
    return NO_ERROR;
}

status_t MemoryHeapBase::mapfd(int fd, size_t size, uint32_t offset)
{
    const size_t pagesize = getpagesize();
    mSize = ((size + pagesize - 1) & ~(pagesize - 1));
    mBase = malloc(mSize);
    if (NULL == mBase) { mBase = MAP_FAILED; mSize = 0; }

    if (!mBase) {
        return NO_MEMORY;
    }
    
    mFD = fd;
    mOffset = offset;

    return NO_ERROR;
}

MemoryHeapBase::~MemoryHeapBase()
{
    dispose();
}

void MemoryHeapBase::dispose()
{
    if ((mBase != NULL) && (mBase != MAP_FAILED)) {
        free(mBase);
        mBase = MAP_FAILED;
        mSize = 0;
    }
}

int MemoryHeapBase::getHeapID() const {
    return mFD;
}

void* MemoryHeapBase::getBase() const {
    return mBase;
}

size_t MemoryHeapBase::getSize() const {
    return mSize;
}

uint32_t MemoryHeapBase::getFlags() const {
    return mFlags;
}

const char* MemoryHeapBase::getDevice() const {
    return mDevice;
}

uint32_t MemoryHeapBase::getOffset() const {
    return mOffset;
}

// ---------------------------------------------------------------------------
}; // namespace android
