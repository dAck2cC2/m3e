
#include "media/MediaDefine.h"
#include "media/CFileRender.h"
#include "utils/Errors.h"
#include "utils/ADebug.h"
#include "utils/log.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

_MEDIA_BEGIN

CFileRender::CFileRender(const char *filename)
    : mFd(-1)
{
    mFd = open(filename, O_WRONLY | O_CREAT, 0777);

    if (mFd < 0) {
        ALOGE("Failed to create file '%s'. (%s)", filename, strerror(errno));
    }
}

CFileRender::~CFileRender()
{
    Mutex::Autolock autoLock(mLock);

    if (mFd >= 0) {
        close(mFd);
        mFd = -1;
    }
}

ssize_t
CFileRender::syncWrite(const void *data, const size_t size)
{
    if ((data == 0) || (size <= 0)) {
        return BAD_VALUE;
    }

    if (mFd < 0) {
        return NO_INIT;
    }

    Mutex::Autolock autoLock(mLock);

    size_t iSize = ::write(mFd, data, size);

    return (iSize);
}

_MEDIA_END

