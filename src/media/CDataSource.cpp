
#include "media/MediaDefine.h"
#include "media/CDataSource.h"
#include "media/WAVExtractor.h"

_MEDIA_BEGIN

// The sniffer can optionally fill in "meta" with an AMessage containing
// a dictionary of values that helps the corresponding extractor initialize
// its state without duplicating effort already exerted by the sniffer.
typedef bool (*SnifferFunc)(
    const sp<IDataSource> &source, String8 *mimeType,
    float *confidence
#ifdef ENABLE_AMESSAGE
    , sp<AMessage> *meta
#endif // ENABLE_AMESSAGE
);

CDataSource::CDataSource()
{
}

CDataSource::~CDataSource()
{
}

bool
CDataSource::sniff(String8 *mimeType, float *confidence
#ifdef ENABLE_AMESSAGE
                   , sp<AMessage> *meta
#endif // ENABLE_AMESSAGE
                  )
{
    static const SnifferFunc s_apfnSnifferFunc[] = {
        SniffWAV
    };
#define SNIFFER_FUNC_MAX   (sizeof(s_apfnSnifferFunc)/sizeof(SnifferFunc))


    *mimeType = "";
    *confidence = 0.0f;
#ifdef ENABLE_AMESSAGE
    meta->clear();
#endif // ENABLE_AMESSAGE

    for (unsigned int i = 0; i < SNIFFER_FUNC_MAX; ++i) {
        String8 newMimeType;
        float newConfidence;
#ifdef ENABLE_AMESSAGE
        sp<AMessage> newMeta;
#endif // ENABLE_AMESSAGE

        if ((s_apfnSnifferFunc[i](this, &newMimeType, &newConfidence
#ifdef ENABLE_AMESSAGE
                                  , &newMeta
#endif // ENABLE_AMESSAGE
                                 ))) {
            *mimeType = newMimeType;
            *confidence = newConfidence;
#ifdef ENABLE_AMESSAGE
            *meta = newMeta;
#endif // ENABLE_AMESSAGE
        }
    }

    return (*confidence > 0.0);
}

_MEDIA_END

