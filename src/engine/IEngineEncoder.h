
#ifndef __IENGINE_ENCODER_H__
#define __IENGINE_ENCODER_H__

#include "engine/EngineDefine.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

ENGINE_BEGIN

struct MediaSource;
class  IDataRender;

class IEngineEncoder : public RefBase
{
public:
    explicit IEngineEncoder() {};
    virtual ~IEngineEncoder() {};

    virtual int syncEncode(const sp<MediaSource>& pMediaSource_in, const sp<IDataRender>& pDataRender_out) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineEncoder);
};

ENGINE_END

#endif // __IENGINE_ENCODER_H__

