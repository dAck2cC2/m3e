
#ifndef __CENGINE_MONITOR_H__
#define __CENGINE_MONITOR_H__

#include "EngineDefine.h"
#include "IEngineMonitor.h"
#include "utils/Mutex.h"
#include "utils/Timers.h"
#include "media/stagefright/foundation/ABase.h"

ENGINE_BEGIN

class CEngineMonitor : public IEngineMonitor
{
public:
    explicit CEngineMonitor();
    virtual ~CEngineMonitor();

    virtual int  publish(const sp<AMessage>& pInfo_in);
    virtual void setOnOff(const bool isOn_in);

private:
    int  begin();
    int  end();

private:
    Mutex          m_cMutex;
    DurationTimer  m_cDuration;
    int            m_iOperationCnt;
    int32_t        m_iCoreCnt;
    bool           m_bIsOn;

    DISALLOW_EVIL_CONSTRUCTORS(CEngineMonitor);
};

ENGINE_END

#endif // __CENGINE_MONITOR_H__

