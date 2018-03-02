
#define LOG_TAG "MemoryHeapBase"

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>

#ifdef _MSC_VER
extern "C" int getpagesize(void);
#endif // _MSC_VER

#include <binder/MemoryHeapBase.h>

namespace android {

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
    mapfd(-1, size, 0);
}

MemoryHeapBase::MemoryHeapBase(const char* device, size_t size, uint32_t flags)
    : mFD(-1), mSize(0), mBase(MAP_FAILED), mFlags(flags),
      mDevice(0), mNeedUnmap(false), mOffset(0)
{
    mapfd(-1, size, 0);
}

MemoryHeapBase::MemoryHeapBase(int fd, size_t size, uint32_t flags, uint32_t offset)
    : mFD(-1), mSize(0), mBase(MAP_FAILED), mFlags(flags),
      mDevice(0), mNeedUnmap(false), mOffset(0)
{
    mapfd(fd, size, offset);
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
