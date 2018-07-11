#ifndef __CENCODER_LAME__
#define __CENCODER_LAME__

#include "IEngineEncoder.h"
#include "media/stagefright/foundation/ABase.h"

#include "lame.h"

ENGINE_BEGIN

class CEncoderLame : public IEngineEncoder
{
public:
    explicit CEncoderLame();
    virtual ~CEncoderLame();

    virtual int syncEncode(
        const sp<IMediaSource>& pMediaSource_in,
        const sp<IAudioSink>&  pAudioSink_out,
        const sp<AMessage>&    pOption_in = NULL);

public:
    static void errorf(const char *format, va_list ap);
    static void debugf(const char *format, va_list ap);
    static void msgf(const char *format, va_list ap);

private:
    virtual int  prepare(
        const sp<IMediaSource>& pMediaSource_in,
        const sp<IAudioSink>&  pAudioSink_out,
        const sp<AMessage>&    pOption_in
    );

    virtual int  encode( const sp<IMediaSource>& pMediaSource_in, const sp<IAudioSink>& pAudioSink_out);
    virtual void finish( );

private:
    lame_t   m_pGobalFlags;

    DISALLOW_EVIL_CONSTRUCTORS(CEncoderLame);
};

ENGINE_END

#endif // __CENCODER_LAME__

