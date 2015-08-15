#ifndef __CFILE_SINK_H__
#define __CFILE_SINK_H__

#include "media/MediaDefine.h"
#include "media/IAudioSink.h"
#include "utils/Mutex.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class CFileSink : public IAudioSink
{
public:
    explicit CFileSink(const char *filename);
    virtual ~CFileSink();

    virtual ssize_t write(const void *data, size_t size);

private:
    Mutex mLock;
    int mFd;

    DISALLOW_EVIL_CONSTRUCTORS(CFileSink);
};

_MEDIA_END

#endif // __CFILE_SINK_H__

