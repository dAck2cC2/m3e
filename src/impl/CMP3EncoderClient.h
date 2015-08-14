
#ifndef __CMP3_ENCODER_CLIENT_H__
#define __CMP3_ENCODER_CLIENT_H__

#include "engine/EngineDefine.h"
#include "engine/IEngineScannerClient.h"
#include "utils/ABase.h"

ENGINE_BEGIN

class String8;
class IEngineEncoder;
class CAsyncEncoderGroup;

class CMP3EncoderClient : public IEngineScannerClient
{
public:
    explicit CMP3EncoderClient();
    virtual ~CMP3EncoderClient();

    virtual int  init();

    virtual void setLocale(const char* locale);

    virtual int  scanFile(const char* path, long long lastModified,
                          long long fileSize, bool isDirectory, bool noMedia);

    virtual int  foundMediaFile(const char *path, sp<MediaExtractor>& pExtractor_in);

private:
    String8 getOutputFilePath(const String8& cInputFilePath_in);

private:
    CAsyncEncoderGroup*  m_pGroup;

    DISALLOW_EVIL_CONSTRUCTORS(CMP3EncoderClient);
};

ENGINE_END

#endif // __CMP3_ENCODER_CLIENT_H__

