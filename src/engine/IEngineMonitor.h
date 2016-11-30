
#ifndef __IENGINE_MONITOR_H__
#define __IENGINE_MONITOR_H__

#include "engine/EngineDefine.h"
#include "utils/RefBase.h"
#include "media/stagefright/foundation/ABase.h"

ENGINE_BEGIN

extern const char *INFO_INPUT_FILE;
extern const char *INFO_OUTPUT_FILE;
extern const char *INFO_OPERATION;
extern const char *INFO_CORE_COUNT;

struct AMessage;

class IEngineMonitor : public RefBase
{
public:
    explicit IEngineMonitor() {};
    virtual ~IEngineMonitor() {};

    virtual int publish(const sp<AMessage>& pInfo_in) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineMonitor);
};

ENGINE_END

#endif // __IENGINE_MONITOR_H__

