
//#define  ENABLE_ADEBUG_EXT
#define LOG_TAG   "CEncoderClient"
#include "utils/ADebugExt.h"
#include "utils/String8.h"
#include "utils/Errors.h"
#include "media/stagefright/foundation/ADebug.h"
#include "media/stagefright/foundation/AString.h"
#include "media/stagefright/foundation/AMessage.h"
#include "media/stagefright/MediaExtractor.h"
#include "media/stagefright/MediaSource.h"
#include "media/stagefright/MetaData.h"
#include "CEngineFactory.h"

#include "CAsyncEncoderGroup.h"
#include "CEncoderClient.h"
#include "CFileSink.h"

#include <stdio.h>

ENGINE_BEGIN

CEncoderClient::CEncoderClient()
    : m_pGroup(NULL),
      m_pOption(NULL)
{
    AUTO_LOG();
}

CEncoderClient::~CEncoderClient()
{
    AUTO_LOG();

    if (m_pGroup != NULL) {
        delete (m_pGroup);
        m_pGroup = NULL;
    }
}

int
CEncoderClient::init(const sp<AMessage>& pOption_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(pOption_in, BAD_VALUE);

    m_pOption = pOption_in;

    AString cEncoder;
    bool chk = m_pOption->findString(OPTION_ENCODER_NAME, &cEncoder);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    CHECK_IS_EXT((false == cEncoder.empty()), UNKNOWN_ERROR);

    if (m_pGroup == NULL) {
        m_pGroup = new CAsyncEncoderGroup();
        CHECK_PTR_EXT(m_pGroup, NO_MEMORY);

        // get the core count of CPU
        int iCoreCnt = sysconf(_SC_NPROCESSORS_ONLN);

        sp<AMessage> pInfo = new AMessage();

        if (pInfo != NULL) {
            pInfo->setInt32(INFO_CORE_COUNT, iCoreCnt);
            CEngineFactory::getInstance().getMonitor()->publish(pInfo);
        }

        if (iCoreCnt <= 0) {
            iCoreCnt = 1;
        }

        // create a encoder for each core
        for (int i = 0; i < iCoreCnt; ++i) {
            sp<IEngineEncoder> pSyncEncoder = CEngineFactory::getInstance().createEncoder(cEncoder.c_str());
            CHECK_PTR_EXT(pSyncEncoder, NO_MEMORY);

            CAsyncEncoder* pAsyncEncoder = new CAsyncEncoder(pSyncEncoder, i);
            CHECK_PTR_EXT(pAsyncEncoder, NO_MEMORY);

            m_pGroup->add(pAsyncEncoder);
        }
    }

    RETURN(OK);
}

void
CEncoderClient::setLocale(const char* locale)
{
    AUTO_LOG();
}

int
CEncoderClient::scanFile(const char* path, long long lastModified,
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
CEncoderClient::foundMediaFile(const char *path, sp<IMediaExtractor>& pExtractor_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(path, BAD_VALUE);
    CHECK_PTR_EXT(pExtractor_in, BAD_VALUE);
    CHECK_PTR_EXT(m_pGroup,  BAD_VALUE);
    CHECK_PTR_EXT(m_pOption, BAD_VALUE);

    for (size_t i = 0; i < pExtractor_in->countTracks(); ++i) {
        sp<MetaData> meta = pExtractor_in->getTrackMetaData(i);

        const char *_mime;
        CHECK(meta->findCString(kKeyMIMEType, &_mime));

        String8 mime = String8(_mime);

        if (!strncasecmp(mime.string(), "audio/", 6)) {
            CAsyncEncoder* pEncoder = NULL;
            status_t chk = m_pGroup->acquire(&pEncoder);
            CHECK_IS_EXT((OK == chk), chk);
            CHECK_PTR_EXT(pEncoder, UNKNOWN_ERROR);

            String8 out = getOutputFile(String8(path));
            sp<IAudioSink> pAudioSink = new CFileSink(out.string());
            CHECK_PTR_EXT(pAudioSink, UNKNOWN_ERROR);

            chk = pEncoder->asyncEncode(pExtractor_in->getTrack(i), pAudioSink, m_pOption, String8(path));

            if (OK == chk) {
                int32_t bNeedDeleteFile = 0;
                m_pOption->findInt32(OPTION_REMOVE_SOURCE_FILE, &bNeedDeleteFile);
                //pExtractor_in->getTrack(i)->deleteFileAfter(bNeedDeleteFile);
            }
        }
    }

    RETURN(OK);
}

String8
CEncoderClient::getOutputFile(const String8& cInputFile_in)
{
    AUTO_LOG();

    const char* pszIn  = cInputFile_in.string();
    const char* pszExt = cInputFile_in.find_extension();

    CHECK_PTR_EXT(m_pOption, String8(pszIn));

    // TO DO
    // change the output path
    //AString cOutPath;
    //m_pOption->findString(OPTION_OUTPUT_PATH, &cOutPath);

    AString cOutType;
    m_pOption->findString(OPTION_ENCODER_TYPE, &cOutType);

    if (!strcasecmp(cOutType.c_str(), ENCODER_TYPE_MP3)) {
        int iOut = pszExt - pszIn + 1;
        char* pszOut = new char [iOut + 4];
        memset(pszOut, 0x00, sizeof(iOut + 4));
        memcpy(pszOut, pszIn, iOut);
        pszOut[iOut++] = 'm';
        pszOut[iOut++] = 'p';
        pszOut[iOut++] = '3';
        pszOut[iOut]   = '\0';

        String8 cOut(pszOut);
        delete(pszOut);

        return (cOut);
    }

    return (String8(pszIn));
}

ENGINE_END

