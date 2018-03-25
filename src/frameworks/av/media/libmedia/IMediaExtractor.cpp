//#define LOG_NDEBUG 0
#define LOG_TAG "BpMediaExtractor"
#include <utils/Log.h>

#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <media/IMediaExtractor.h>

namespace android {

IMPLEMENT_META_INTERFACE(MediaExtractor, "android.media.IMediaExtractor");

status_t BnMediaExtractor::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    return NO_ERROR;
}

}
