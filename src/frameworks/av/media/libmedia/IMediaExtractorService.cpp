
#define LOG_TAG "IMediaExtractorService"
//#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <media/IMediaExtractorService.h>

namespace android {

IMPLEMENT_META_INTERFACE(MediaExtractorService, "android.media.IMediaExtractorService");

status_t BnMediaExtractorService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    return NO_ERROR;
}

}