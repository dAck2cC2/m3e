
//#define  ENABLE_ADEBUG_EXT
#define LOG_TAG   "CEncoderLame"
#include "utils/ADebugExt.h"
#include "media/stagefright/foundation/ADebug.h"
#include "media/stagefright/foundation/AMessage.h"
#include "media/stagefright/MediaSource.h"
#include "media/stagefright/MetaData.h"
#include "media/stagefright/MediaDefs.h"
#include "media/stagefright/MediaBuffer.h"

#include "IAudioSink.h"
#include "CEncoderLame.h"


ENGINE_BEGIN

CEncoderLame::CEncoderLame()
    : m_pGobalFlags(NULL)
{
    AUTO_LOG();
}

CEncoderLame::~CEncoderLame()
{
    AUTO_LOG();
}


int
CEncoderLame::syncEncode(
    const sp<IMediaSource>& pMediaSource_in,
    const sp<IAudioSink>&  pAudioSink_out,
    const sp<AMessage>&    pOption_in
)
{
    AUTO_LOG();

    CHECK_PTR_EXT(pMediaSource_in, BAD_VALUE);
    CHECK_PTR_EXT(pAudioSink_out,  BAD_VALUE);

    sp<MetaData> meta = pMediaSource_in->getFormat();

    const char *mime;
    CHECK(meta->findCString(kKeyMIMEType, &mime));

    if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_RAW)) {
        int ret = prepare(pMediaSource_in, pAudioSink_out, pOption_in);

        if (OK == ret) {
            ret = encode( pMediaSource_in, pAudioSink_out);
        }

        finish();

        CHECK_IS_EXT((OK == ret), ret);
    } else {
        RETURN(INVALID_OPERATION);
    }

    RETURN(OK);
}

void
CEncoderLame::errorf(const char *format, va_list ap)
{
    AUTO_LOG();

    // TO DO
    // notify monitor
}

void
CEncoderLame::debugf(const char *format, va_list ap)
{
    AUTO_LOG();

    // TO DO
    // notify monitor
}

void
CEncoderLame::msgf(const char *format, va_list ap)
{
    AUTO_LOG();

    // TO DO
    // notify monitor
}

int CEncoderLame::prepare(
    const sp<IMediaSource>& pMediaSource_in,
    const sp<IAudioSink>&  pAudioSink_out,
    const sp<AMessage>&    pOption_in
)
{
    AUTO_LOG();

    if (m_pGobalFlags != NULL) {
        RETURN(ALREADY_EXISTS);
    }

    CHECK_PTR_EXT(pMediaSource_in, BAD_VALUE);
    CHECK_PTR_EXT(pAudioSink_out,  BAD_VALUE);

    sp<MetaData>  pMeta = pMediaSource_in->getFormat();
    CHECK_PTR_EXT(pMeta,  BAD_VALUE);

    m_pGobalFlags = lame_init();
    CHECK_PTR_EXT(m_pGobalFlags, BAD_VALUE);

    lame_set_errorf(m_pGobalFlags, CEncoderLame::errorf);
    lame_set_debugf(m_pGobalFlags, CEncoderLame::debugf);
    lame_set_msgf(m_pGobalFlags, CEncoderLame::msgf);

    id3tag_init(m_pGobalFlags);

    // TO DO
    // pass the user option to encoder
    //if (pOption_in != NULL) {
    //}

    int  ret = OK;
    bool chk = false;

    int32_t iChannelNum = 0;
    chk = pMeta->findInt32(kKeyChannelCount, &iChannelNum);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    ret = lame_set_num_channels(m_pGobalFlags, iChannelNum);
    CHECK_IS_EXT((ret == OK), ret);

    int32_t iSampleRate = 0;
    chk = pMeta->findInt32(kKeySampleRate, &iSampleRate);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    ret = lame_set_in_samplerate(m_pGobalFlags, iSampleRate);
    CHECK_IS_EXT((ret == OK), ret);

    int32_t iBitsPerSample = 0;
    chk = pMeta->findInt32(kKeyBitsPerSample, &iBitsPerSample);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    int32_t iDataSize = 0;
    chk = pMeta->findInt32(kKeyDataSize, &iDataSize);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    ret = lame_set_num_samples(m_pGobalFlags, iDataSize / (iChannelNum * ((iBitsPerSample + 7) / 8)));
    CHECK_IS_EXT((ret == OK), ret);

    lame_set_write_id3tag_automatic(m_pGobalFlags, 0);
    ret = lame_init_params(m_pGobalFlags);
    CHECK_IS_EXT((ret == OK), ret);

    size_t id3v2_size = lame_get_id3v2_tag(m_pGobalFlags, 0, 0);

    if (id3v2_size > 0) {
        unsigned char *id3v2tag = new unsigned char[id3v2_size];

        if (id3v2tag != 0) {
            int iTagSz = lame_get_id3v2_tag(m_pGobalFlags, id3v2tag, id3v2_size);
            int iWrite = (int) pAudioSink_out->write(id3v2tag, iTagSz);
            delete(id3v2tag);
            CHECK_IS_EXT((iTagSz == iWrite), UNKNOWN_ERROR);
        }
    }

    RETURN(OK);
}

int
CEncoderLame::encode(const sp<IMediaSource>& pMediaSource_in, const sp<IAudioSink>& pAudioSink_out)
{
    AUTO_LOG();

    CHECK_PTR_EXT(m_pGobalFlags, BAD_VALUE);
    CHECK_PTR_EXT(pMediaSource_in, BAD_VALUE);
    CHECK_PTR_EXT(pAudioSink_out, BAD_VALUE);

    sp<MetaData>  pMeta = pMediaSource_in->getFormat();
    CHECK_PTR_EXT(pMeta,  BAD_VALUE);

    int32_t iChannelNum = 0;
    bool chk = pMeta->findInt32(kKeyChannelCount, &iChannelNum);
    CHECK_IS_EXT((true == chk), UNKNOWN_ERROR);
    int  ret = lame_set_num_channels(m_pGobalFlags, iChannelNum);
    CHECK_IS_EXT((ret == OK), ret);

    // only support one channel and two channels
    CHECK_IS_EXT(((1 == iChannelNum) || (2 == iChannelNum)), INVALID_OPERATION);

    ret = pMediaSource_in->start();
    CHECK_IS_EXT((ret == OK), ret);

    MediaBuffer* pBuf = NULL;

    while (OK == (pMediaSource_in->read(&pBuf, NULL))) {
        if (pBuf == NULL) {
            break;
        }

        if ((pBuf->data() == NULL) || (pBuf->range_length() == 0)) {
            pBuf->release();
            pBuf = NULL;
            continue;
        }

        int16_t *pOrg = (int16_t *)((const char *)pBuf->data() + pBuf->range_offset());
        ssize_t iSamplesRead = pBuf->range_length() / 2;
        pOrg += iSamplesRead;
        iSamplesRead /= iChannelNum;

        CHECK_NE(iSamplesRead, 0);

        int iMP3BufSize = 1.25 * iSamplesRead + 7200;
        short int*     pPCMBufL = new short int[iSamplesRead];
        short int*     pPCMBufR = new short int[iSamplesRead];
        unsigned char* pMP3Buf  = new unsigned char[iMP3BufSize];

        if (iChannelNum == 2) {
            for (ssize_t i = iSamplesRead; --i >= 0;) {
                pPCMBufR[i] = *--pOrg;
                pPCMBufL[i] = *--pOrg;
            }
        } else if (iChannelNum == 1) {
            memset(pPCMBufR, 0, iSamplesRead * sizeof(short int));

            for (ssize_t i = iSamplesRead; --i >= 0;) {
                pPCMBufL[i] = *--pOrg;
            }
        } else {
            // EMPTY
        }

        int iOutSize = lame_encode_buffer(m_pGobalFlags, pPCMBufL, pPCMBufR, iSamplesRead, pMP3Buf, iMP3BufSize);
        int iWriteSize = iOutSize;

        if (iOutSize > 0) {
            iWriteSize = pAudioSink_out->write(pMP3Buf, iOutSize);
        }

        delete (pMP3Buf);
        delete (pPCMBufR);
        delete (pPCMBufL);


        pBuf->release();
        pBuf = NULL;

        CHECK_IS_EXT((iOutSize == iWriteSize), UNKNOWN_ERROR);
    }

    // last frame may remain
    {
        unsigned char* pMP3Buf  = new unsigned char[LAME_MAXMP3BUFFER];
        int iOutSize = lame_encode_flush(m_pGobalFlags, pMP3Buf, sizeof(pMP3Buf));
        int iWriteSize = iOutSize;

        if (iOutSize > 0) {
            iWriteSize = pAudioSink_out->write(pMP3Buf, iOutSize);
        }

        delete (pMP3Buf);

        CHECK_IS_EXT((iOutSize == iWriteSize), UNKNOWN_ERROR);
    }

    // write the tag3v1
    {
        unsigned char* pMP3Buf = new unsigned char[128];
        int iOutSize = lame_get_id3v1_tag(m_pGobalFlags, pMP3Buf, sizeof(pMP3Buf));
        int iWriteSize = iOutSize;

        if ((iOutSize > 0) && (((size_t)iOutSize) <= sizeof(pMP3Buf))) {
            iWriteSize = pAudioSink_out->write(pMP3Buf, iOutSize);
        }

        delete (pMP3Buf);

        CHECK_IS_EXT((iOutSize == iWriteSize), UNKNOWN_ERROR);
    }

    RETURN(OK);
}

void
CEncoderLame::finish()
{
    AUTO_LOG();

    if (m_pGobalFlags != NULL) {
        lame_close(m_pGobalFlags);
        m_pGobalFlags = NULL;
    }
}

ENGINE_END

