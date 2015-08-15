
#ifndef __IENGINE_SCANNER_CLIENT_H__
#define __IENGINE_SCANNER_CLIENT_H__

#include "engine/EngineDefine.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

ENGINE_BEGIN

class MediaExtractor;
class String8;
class AMessage;

class IEngineScannerClient : public RefBase
{
public:
    explicit IEngineScannerClient() {};
    virtual ~IEngineScannerClient() {};

    virtual int  init(const sp<AMessage>& pOption_in) = 0;

    virtual void setLocale(const char* locale) = 0;

    virtual int  scanFile(const char* path, long long lastModified,
                          long long fileSize, bool isDirectory, bool noMedia) = 0;

    virtual int  foundMediaFile(const char * pszPath_in, sp<MediaExtractor>& pExtractor_in) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineScannerClient);
};

ENGINE_END

#endif // __IENGINE_SCANNER_CLIENT_H__

