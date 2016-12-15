
#ifndef __CPLAYER_CLIENT_H__
#define __CPLAYER_CLIENT_H__

#include "engine/EngineDefine.h"
#include "engine/IEngineScannerClient.h"
#include "media/stagefright/foundation/ABase.h"
#include "audio/AudioSinkFactory.h"

ENGINE_BEGIN

class  String8;
struct AMessage;
class  AudioPlayer;

class CPlayerClient : public IEngineScannerClient
{
public:
    explicit CPlayerClient();
    virtual ~CPlayerClient();

    virtual int  init(const sp<AMessage>& pOption_in);

    virtual void setLocale(const char* locale);

    virtual int  scanFile(const char* path, long long lastModified,
                          long long fileSize, bool isDirectory, bool noMedia);

    virtual int  foundMediaFile(const char *path, sp<IMediaExtractor>& pExtractor_in);

private:
    String8 getOutputFile(const String8& cInputFile_in);

private:
    sp<AMessage>                   m_pOption;
    sp<MediaPlayerBase::AudioSink> m_pSink;
    AudioPlayer*                   m_pPlayer;

    DISALLOW_EVIL_CONSTRUCTORS(CPlayerClient);
};

ENGINE_END

#endif // __CPLAYER_CLIENT_H__

