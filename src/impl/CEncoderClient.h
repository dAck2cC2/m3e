
#ifndef __CENCODER_CLIENT_H__
#define __CENCODER_CLIENT_H__

#include "engine/EngineDefine.h"
#include "engine/IEngineScannerClient.h"
#include "utils/ABase.h"

ENGINE_BEGIN

class String8;
//class IEngineEncoder;
class CAsyncEncoderGroup;

class CEncoderClient : public IEngineScannerClient
{
public:
    explicit CEncoderClient();
    virtual ~CEncoderClient();

    virtual int  init(const sp<AMessage>& pOption_in);

    virtual void setLocale(const char* locale);

    virtual int  scanFile(const char* path, long long lastModified,
                          long long fileSize, bool isDirectory, bool noMedia);

    virtual int  foundMediaFile(const char *path, sp<MediaExtractor>& pExtractor_in);

private:
    String8 getOutputFile(const String8& cInputFile_in);

private:
    CAsyncEncoderGroup*  m_pGroup;
    sp<AMessage>         m_pOption;

    DISALLOW_EVIL_CONSTRUCTORS(CEncoderClient);
};

ENGINE_END

#endif // __CENCODER_CLIENT_H__

