#ifndef __CFILE_RENDER_H__
#define __CFILE_RENDER_H__

#include "media/MediaDefine.h"
#include "media/IDataRender.h"
#include "utils/Mutex.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class CFileRender : public IDataRender
{
public:
    explicit CFileRender(const char *filename);
    virtual ~CFileRender();

    virtual ssize_t syncWrite(const void *data, const size_t size);

private:
    Mutex mLock;
    int mFd;

    DISALLOW_EVIL_CONSTRUCTORS(CFileRender);
};

_MEDIA_END

#endif // __CFILE_RENDER_H__

