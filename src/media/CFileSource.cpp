
#define LOG_TAG  "CFileSource"
#include "media/MediaDefine.h"
#include "media/CFileSource.h"
#include "utils/ADebug.h"
#include "utils/log.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

_MEDIA_BEGIN

CFileSource::CFileSource(const char *filename)
    : mFd(-1),
      mOffset(0),
      mLength(-1),
      mLock(),
      mFilename(),
      mDelete(false)
{
    mFd = open(filename, O_LARGEFILE | O_RDONLY);

    if (mFd >= 0) {
        mLength   = lseek64(mFd, 0, SEEK_END);

        mFilename = filename;

    } else {
        ALOGE("Failed to open file '%s'. (%s)", filename, strerror(errno));
    }
}

CFileSource::CFileSource(int fd, int64_t offset, int64_t length)
    : mFd(fd),
      mOffset(offset),
      mLength(length),
      mLock(),
      mFilename(),
      mDelete(false)
{
    CHECK(offset >= 0);
    CHECK(length >= 0);
}

CFileSource::~CFileSource()
{
    if (mFd >= 0) {
        close(mFd);
        mFd = -1;

        if ((mDelete) && (!mFilename.isEmpty())) {
            ::remove(mFilename.string());
        }
    }
}

status_t CFileSource::initCheck() const
{
    return mFd >= 0 ? OK : NO_INIT;
}

ssize_t CFileSource::readAt(off64_t offset, void *data, size_t size)
{
    if (mFd < 0) {
        return NO_INIT;
    }

    Mutex::Autolock autoLock(mLock);

    if (mLength >= 0) {
        if (offset >= mLength) {
            return 0;  // read beyond EOF.
        }

        int64_t numAvailable = mLength - offset;

        if ((int64_t)size > numAvailable) {
            size = numAvailable;
        }
    }

    off64_t result = lseek64(mFd, offset + mOffset, SEEK_SET);

    if (result == -1) {
        ALOGE("seek to %lld failed", offset + mOffset);
        return UNKNOWN_ERROR;
    }

    return ::read(mFd, data, size);
}

bool CFileSource::getUInt16(off64_t offset, uint16_t *x)
{
    *x = 0;

    uint8_t byte[2];

    if (readAt(offset, byte, 2) != 2) {
        return false;
    }

    *x = (byte[0] << 8) | byte[1];

    return true;
}


status_t CFileSource::getSize(off64_t *size)
{
    Mutex::Autolock autoLock(mLock);

    if (mFd < 0) {
        return NO_INIT;
    }

    *size = mLength;

    return OK;
}

void CFileSource::deleteFileAfter(const bool bDelete_in)
{
    mDelete = bDelete_in;
}

_MEDIA_END

