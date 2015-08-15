#ifndef __CENCODER_LAME__
#define __CENCODER_LAME__

#include "engine/IEngineEncoder.h"
#include "utils/ABase.h"

#include "lame.h"

ENGINE_BEGIN

class CEncoderLame : public IEngineEncoder
{
public:
    explicit CEncoderLame();
    virtual ~CEncoderLame();

    virtual int syncEncode(
        const sp<MediaSource>& pMediaSource_in,
        const sp<IDataRender>& pDataRender_out,
        const sp<AMessage>&    pOption_in = NULL);

public:
    static void errorf(const char *format, va_list ap);
    static void debugf(const char *format, va_list ap);
    static void msgf(const char *format, va_list ap);

private:
    virtual int  prepare(
        const sp<MediaSource>& pMediaSource_in,
        const sp<IDataRender>& pDataRender_out,
        const sp<AMessage>&    pOption_in
    );

    virtual int  encode( const sp<MediaSource>& pMediaSource_in, const sp<IDataRender>& pDataRender_out);
    virtual void finish( );

private:
    lame_t           m_pGobalFlags;

    DISALLOW_EVIL_CONSTRUCTORS(CEncoderLame);
};

ENGINE_END

#endif // __CENCODER_LAME__

