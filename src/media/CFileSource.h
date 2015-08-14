#ifndef __CFILE_SOURCE_H__
#define __CFILE_SOURCE_H__

#include "media/MediaDefine.h"
#include "media/CDataSource.h"
#include "utils/String8.h"
#include "utils/Mutex.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class CFileSource : public CDataSource
{
public:
    explicit CFileSource(const char *filename);
    explicit CFileSource(int fd, int64_t offset, int64_t length);

    virtual status_t initCheck() const;
    virtual ssize_t  readAt(off64_t offset, void *data, size_t size);
    virtual bool     getUInt16(off64_t offset, uint16_t *x);
    // May return ERROR_UNSUPPORTED.
    virtual status_t getSize(off64_t *size);

    virtual void     deleteFileAfter(const bool bDelete_in);

protected:
    virtual ~CFileSource();

private:
    int     mFd;
    int64_t mOffset;
    int64_t mLength;
    Mutex   mLock;
    String8 mFilename;
    bool    mDelete;

    DISALLOW_EVIL_CONSTRUCTORS(CFileSource);
};

_MEDIA_END

#endif // __CFILE_SOURCE_H__

