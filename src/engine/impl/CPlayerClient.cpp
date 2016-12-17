
//#define  ENABLE_ADEBUG_EXT
#define LOG_TAG   "CPlayerClient"
#include "utils/ADebugExt.h"
#include "utils/String8.h"
#include "utils/Errors.h"
#include "media/stagefright/foundation/ADebug.h"
#include "media/stagefright/foundation/AString.h"
#include "media/stagefright/foundation/AMessage.h"
#include "media/stagefright/MediaExtractor.h"
#include "media/stagefright/MediaSource.h"
#include "media/stagefright/MetaData.h"
#include "media/stagefright/AudioPlayer.h"
#include "CEngineFactory.h"

#include "CPlayerClient.h"

#include <stdio.h>

ENGINE_BEGIN

CPlayerClient::CPlayerClient() :
    m_pPlayer(NULL)
{
    AUTO_LOG();
}

CPlayerClient::~CPlayerClient()
{
    AUTO_LOG();

    if (m_pPlayer) {
        delete (m_pPlayer);
    }
}

int
CPlayerClient::init(const sp<AMessage>& pOption_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(pOption_in, BAD_VALUE);

    m_pOption = pOption_in;

    int type  = AudioSinkFactory::getInstance().getAudioSinkType("default");
    m_pSink   = AudioSinkFactory::getInstance().createSink(type);
    CHECK_PTR_EXT(m_pSink, NAME_NOT_FOUND);

    RETURN(OK);
}

void
CPlayerClient::setLocale(const char* locale)
{
    AUTO_LOG();
}

int
CPlayerClient::scanFile(const char* path, long long lastModified,
                         long long fileSize, bool isDirectory, bool noMedia)
{
    AUTO_LOG();

    if (path && !isDirectory) {
        sp<IEngineScanner> pFileScanner = CEngineFactory::getInstance().createScanner();
        CHECK_PTR_EXT(pFileScanner, BAD_VALUE);
        pFileScanner->processFile(path, 0, this);
    }

    RETURN(OK);
}

int
CPlayerClient::foundMediaFile(const char *path, sp<IMediaExtractor>& pExtractor_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(path, BAD_VALUE);
    CHECK_PTR_EXT(pExtractor_in, BAD_VALUE);
    CHECK_PTR_EXT(m_pSink, BAD_VALUE);

    for (size_t i = 0; i < pExtractor_in->countTracks(); ++i) {
        sp<MetaData> meta = pExtractor_in->getTrackMetaData(i);
        CHECK_PTR_EXT(meta, BAD_VALUE);

        const char *_mime;
        CHECK(meta->findCString(kKeyMIMEType, &_mime));
        CHECK_PTR_EXT(_mime, BAD_VALUE);

        String8 mime = String8(_mime);

        if (!strncasecmp(mime.string(), "audio/", 6)) {
            AudioPlayer *player = new AudioPlayer(m_pSink);
            CHECK_PTR_EXT(player, BAD_VALUE);
                        
            player->setSource(pExtractor_in->getTrack(i));
            player->start(false /* sourceAlreadyStarted */);

            //status_t finalStatus;
            //while (!player->reachedEOS(&finalStatus)) {
            //    usleep(100000ll);
            //}

            delete player;
            player = NULL;            
        }
    }

    RETURN(OK);
}

ENGINE_END

