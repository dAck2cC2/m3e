
//#define  ENABLE_ADEBUG_EXT
#define LOG_TAG   "CMP3EncoderClient"
#include "utils/ADebugExt.h"
#include "utils/ADebug.h"
#include "utils/String8.h"
#include "utils/Errors.h"
#include "impl/CAsyncEncoderGroup.h"
#include "impl/CMP3EncoderClient.h"
#include "engine/CEngineFactory.h"
#include "media/MediaExtractor.h"
#include "media/MediaSource.h"
#include "media/MetaData.h"
#include "media/CFileRender.h"

#include <stdio.h>

ENGINE_BEGIN

CMP3EncoderClient::CMP3EncoderClient()
    : m_pGroup(NULL)
{
    AUTO_LOG();
}

CMP3EncoderClient::~CMP3EncoderClient()
{
    AUTO_LOG();

    if (m_pGroup != NULL) {
        delete (m_pGroup);
        m_pGroup = NULL;
    }
}

int
CMP3EncoderClient::init()
{
    AUTO_LOG();

    if (m_pGroup == NULL) {
        m_pGroup = new CAsyncEncoderGroup();
        CHECK_PTR_EXT(m_pGroup, NO_MEMORY);

        // get the core count of CPU
        int iCoreCnt = sysconf(_SC_NPROCESSORS_ONLN);

        //printf("[Core][%d] \n", iCoreCnt);
        if (iCoreCnt <= 0) {
            iCoreCnt = 1;
        }

        // create a encoder for each core
        for (int i = 0; i < iCoreCnt; ++i) {
            sp<IEngineEncoder> pMP3Encoder = CEngineFactory::getInstance().createMP3Encoder();
            CHECK_PTR_EXT(pMP3Encoder, NO_MEMORY);

            CAsyncEncoder* pEncoder = new CAsyncEncoder(pMP3Encoder, i);
            CHECK_PTR_EXT(pEncoder, NO_MEMORY);

            m_pGroup->add(pEncoder);
        }
    }

    RETURN(OK);
}

void
CMP3EncoderClient::setLocale(const char* locale)
{
    AUTO_LOG();
}

int
CMP3EncoderClient::scanFile(const char* path, long long lastModified,
                            long long fileSize, bool isDirectory, bool noMedia)
{
    AUTO_LOG();

    if (path && !isDirectory) {
        //printf("%s \n", path);

        sp<IEngineScanner> pFileScanner = CEngineFactory::getInstance().createMediaScanner();
        CHECK_PTR_EXT(pFileScanner, BAD_VALUE);
        pFileScanner->processFile(path, 0, this);
    }

    RETURN(OK);
}

int
CMP3EncoderClient::foundMediaFile(const char *path, sp<MediaExtractor>& pExtractor_in)
{
    AUTO_LOG();

    CHECK_PTR_EXT(path, BAD_VALUE);
    CHECK_PTR_EXT(pExtractor_in, BAD_VALUE);
    CHECK_PTR_EXT(m_pGroup, BAD_VALUE);

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
            CHECK_PTR_EXT(pEncoder->get(), UNKNOWN_ERROR);

            String8 out = getOutputFilePath(String8(path));
            sp<IDataRender> pRender = new CFileRender(out.string());
            chk = pEncoder->asyncEncode(pExtractor_in->getTrack(i), pRender, String8(path));

            if (OK == chk) {
                //pExtractor_in->getTrack(i)->deleteFileAfter();
            }
        }
    }

    RETURN(OK);
}

String8
CMP3EncoderClient::getOutputFilePath(const String8& cInputFilePath_in)
{
    AUTO_LOG();

    const char* pszIn  = cInputFilePath_in.string();
    const char* pszExt = cInputFilePath_in.find_extension();

    String8 cOut;

    int iOut = pszExt - pszIn + 1;
    char* pszOut = new char [iOut + 4];
    memset(pszOut, 0x00, sizeof(iOut + 4));
    memcpy(pszOut, pszIn, iOut);
    pszOut[iOut++] = 'm';
    pszOut[iOut++] = 'p';
    pszOut[iOut++] = '3';
    pszOut[iOut]   = '\0';

    cOut = pszOut;
    delete(pszOut);

    return (cOut);
}

ENGINE_END

