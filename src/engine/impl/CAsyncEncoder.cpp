
#//define ENABLE_ADEBUG_EXT
#define LOG_TAG   "CAsyncEncoder"
#include "utils/ADebugExt.h"
#include "media/stagefright/foundation/ADebug.h"
#include "media/stagefright/foundation/AMessage.h"
#include "cutils/atomic.h"
#include "media/stagefright/MediaSource.h"
#include "media/stagefright/MetaData.h"
#include "media/stagefright/MediaDefs.h"
#include "media/stagefright/MediaBuffer.h"
#include "media/IAudioSink.h"
#include "impl/CAsyncEncoder.h"
#include "engine/CEngineFactory.h"

ENGINE_BEGIN

CAsyncEncoder::CAsyncEncoder(const sp<IEngineEncoder>& pEncoder_in, const int32_t iAffinity_in)
    : m_iRefCount(0),
      m_pObserver(NULL),
      m_pNext(NULL),
      m_pEncoder(pEncoder_in),
      m_pThread(NULL),
      m_pOption(NULL),
      m_cSrcFile(),
      m_iAffinity(iAffinity_in)
{
    AUTO_LOG();
}

CAsyncEncoder::~CAsyncEncoder()
{
    AUTO_LOG();

    CHECK(m_pObserver == NULL);

    if (m_pThread != NULL) {
        m_pThread->requestExitAndWait();
        m_pThread.clear();
        m_pThread = NULL;
    }

    if (m_pEncoder != NULL) {
        m_pEncoder = NULL;
    }
}

int
CAsyncEncoder::asyncEncode(
    const sp<MediaSource>&     pMediaSource_in,
    const sp<IAudioSink>&      pAudioSink_out,
    const sp<AMessage>&        pOption_in,
    const String8&             cSrcFile_in
)
{
    AUTO_LOG();

    CHECK_PTR_EXT(m_pEncoder, BAD_VALUE);
    CHECK_PTR_EXT(pMediaSource_in, BAD_VALUE);
    CHECK_PTR_EXT(pAudioSink_out,  BAD_VALUE);

    sp<MetaData> meta = pMediaSource_in->getFormat();
    CHECK_PTR_EXT(meta, BAD_VALUE);

    const char *mime;
    CHECK(meta->findCString(kKeyMIMEType, &mime));

    if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_RAW)) {
        m_cSrcFile = cSrcFile_in;

        m_pThread = new CEncoderThread(
            *this,
            pMediaSource_in,
            pAudioSink_out,
            pOption_in,
            m_pEncoder,
            m_iAffinity
        );
        CHECK_PTR_EXT(m_pThread, NO_MEMORY);

        status_t ret = m_pThread->run();
        CHECK_IS_EXT((OK == ret), ret);
    } else {
        RETURN(INVALID_OPERATION);
    }

    RETURN(OK);
}


String8&
CAsyncEncoder::getSourceFile()
{
    return (m_cSrcFile);
}


void
CAsyncEncoder::release()
{
    AUTO_LOG();

    if (m_pObserver == NULL) {
        CHECK_EQ(m_iRefCount, 0);
        delete this;
        return;
    }

    int prevCount = android_atomic_dec(&m_iRefCount);

    if (prevCount == 1) {
        if (m_pObserver == NULL) {
            delete this;
            return;
        }

        m_pObserver->signalReturned(this);
    }

    CHECK(prevCount > 0);
}

void
CAsyncEncoder::add_ref()
{
    AUTO_LOG();

    (void) android_atomic_inc(&m_iRefCount);
}

int
CAsyncEncoder::refcount() const
{
    AUTO_LOG();

    return (m_iRefCount);
}

void
CAsyncEncoder::reset()
{
    AUTO_LOG();

    if (m_pThread != NULL) {
        m_pThread->requestExitAndWait();
        m_pThread.clear();
        m_pThread = NULL;
    }
}

void
CAsyncEncoder::setObserver(IAsyncEncoderObserver * pObserver_in)
{
    AUTO_LOG();

    CHECK((pObserver_in == NULL) || (m_pObserver == NULL));
    m_pObserver = pObserver_in;
}

void
CAsyncEncoder::setNext(CAsyncEncoder * pNext_in)
{
    AUTO_LOG();

    m_pNext = pNext_in;
}

CAsyncEncoder *
CAsyncEncoder::next()
{
    AUTO_LOG();

    return (m_pNext);
}

CAsyncEncoder::CEncoderThread::CEncoderThread(
    CAsyncEncoder&             cParent_in,
    const sp<MediaSource>&     pSrc_in,
    const sp<IAudioSink>&      pDst_in,
    const sp<AMessage>&        pOpt_in,
    const sp<IEngineEncoder>&  pEncoder_in,
    const int32_t              iAffinity_in

)
    : Thread(false, iAffinity_in),
      m_cParent(cParent_in),
      m_pMediaSource(pSrc_in),
      m_pAudioSink(pDst_in),
      m_pOption(pOpt_in),
      m_pEncoder(pEncoder_in)
{
    AUTO_LOG();
}

CAsyncEncoder::CEncoderThread::~CEncoderThread()
{
    AUTO_LOG();
}

bool
CAsyncEncoder::CEncoderThread::threadLoop()
{
    AUTO_LOG();

    if (m_pEncoder != NULL) {
        m_pEncoder->syncEncode(m_pMediaSource, m_pAudioSink, m_pOption);
    }

    m_pEncoder     = NULL;
    m_pMediaSource = NULL;
    m_pAudioSink   = NULL;
    m_pOption      = NULL;

    m_cParent.release();

    return (false);
}

ENGINE_END

