
//#define ENABLE_ADEBUG_EXT
#define LOG_TAG  "CEngineMonitor"
#include "utils/ADebugExt.h"
#include "media/stagefright/foundation/AString.h"
#include "media/stagefright/foundation/AMessage.h"
//#include "utils/String8.h"
#include "engine/EngineDefine.h"
#include "impl/CEngineMonitor.h"

ENGINE_BEGIN

CEngineMonitor::CEngineMonitor()
    : m_cMutex(),
      m_cDuration(),
      m_iOperationCnt(0),
      m_iCoreCnt(0),
      m_bIsOn(false)
{
    AUTO_LOG();

    begin();
}

CEngineMonitor::~CEngineMonitor()
{
    AUTO_LOG();

    end();
}

int
CEngineMonitor::begin()
{
    AUTO_LOG();

    m_iOperationCnt = 0;
    m_cDuration.start();

    RETURN(OK);
}

int
CEngineMonitor::end()
{
    AUTO_LOG();

    Mutex::Autolock lck(m_cMutex);

    m_cDuration.stop();

    if (!m_bIsOn) RETURN(OK);

    long long iTime = m_cDuration.durationUsecs();

    printf("=============================================\n");
    printf("[Core Count : %d ]\n", m_iCoreCnt);
    printf("[File Count : %d ]\n", m_iOperationCnt);
    printf("[Spend Time : %d ms]\n", (int)(iTime / 1000));
    printf("=============================================\n");

    RETURN(OK);
}


int
CEngineMonitor::publish(const sp<AMessage>& pInfo_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(pInfo_in, BAD_VALUE);

    Mutex::Autolock lck(m_cMutex);

    CHECK_IS_EXT((true == m_bIsOn), INVALID_OPERATION);

    AString cSourceFile;
    pInfo_in->findString(INFO_INPUT_FILE, &cSourceFile);

    if (false == cSourceFile.empty()) {
        m_iOperationCnt++;
        printf("[%s] done.\n", cSourceFile.c_str());
    }

    int32_t iCoreCnt = 0;
    bool chk = pInfo_in->findInt32(INFO_CORE_COUNT, &iCoreCnt);

    if (true == chk) {
        m_iCoreCnt = iCoreCnt;
    }

    RETURN(OK);
}

void 
CEngineMonitor::setOnOff(const bool isOn_in)
{
    AUTO_LOG();

    Mutex::Autolock lck(m_cMutex);

    m_bIsOn = isOn_in;

    return;
}

ENGINE_END

