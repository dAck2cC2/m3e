#ifndef __IAUDIO_SINK_H__
#define __IAUDIO_SINK_H__

#include "media/MediaDefine.h"
#include "utils/RefBase.h"
#include "media/stagefright/foundation/ABase.h"

_MEDIA_BEGIN

class IAudioSink : public RefBase
{
public:
    explicit IAudioSink() {};
    virtual ~IAudioSink() {};

    virtual ssize_t  write(const void* buffer, size_t size) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IAudioSink);
};

_MEDIA_END

#endif //__IAUDIO_SINK_H__

