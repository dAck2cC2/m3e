
#ifndef __CENGINE_ANALYZER_H__
#define __CENGINE_ANALYZER_H__

#include "EngineDefine.h"
#include "IEngineAnalyzer.h"
#include "media/stagefright/foundation/ABase.h"

ENGINE_BEGIN

class CEngineAnalyzer : public IEngineAnalyzer
{
public:
    explicit CEngineAnalyzer();
    virtual ~CEngineAnalyzer();

    virtual int  parse(int argc, char *argv[]);
    virtual sp<AMessage>  getOption();

private:
    void usage();

private:
    sp<AMessage> m_pData;

    DISALLOW_EVIL_CONSTRUCTORS(CEngineAnalyzer);
};

ENGINE_END

#endif // __CENGINE_ANALYZER_H__

