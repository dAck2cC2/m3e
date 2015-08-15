
#ifndef __IENGINE_ENCODER_H__
#define __IENGINE_ENCODER_H__

#include "engine/EngineDefine.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

ENGINE_BEGIN

struct MediaSource;
class  IAudioSink;
class  AMessage;

class IEngineEncoder : public RefBase
{
public:
    explicit IEngineEncoder() {};
    virtual ~IEngineEncoder() {};

    virtual int syncEncode(
        const sp<MediaSource>& pMediaSource_in,
        const sp<IAudioSink>&  pAudioSink_out,
        const sp<AMessage>&    pOption_in = NULL
    ) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineEncoder);
};

ENGINE_END

#endif // __IENGINE_ENCODER_H__

