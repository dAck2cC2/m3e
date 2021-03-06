
#ifndef __IENGINE_ENCODER_H__
#define __IENGINE_ENCODER_H__

#include "EngineDefine.h"
#include "utils/RefBase.h"
#include "media/stagefright/foundation/ABase.h"

ENGINE_BEGIN

struct IMediaSource;
class  IAudioSink;
struct  AMessage;

class IEngineEncoder : public RefBase
{
public:
    explicit IEngineEncoder() {};
    virtual ~IEngineEncoder() {};

    virtual int syncEncode(
        const sp<IMediaSource>& pMediaSource_in,
        const sp<IAudioSink>&  pAudioSink_out,
        const sp<AMessage>&    pOption_in = NULL
    ) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineEncoder);
};

ENGINE_END

#endif // __IENGINE_ENCODER_H__

