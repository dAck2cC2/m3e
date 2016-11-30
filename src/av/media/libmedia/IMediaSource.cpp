//#define LOG_NDEBUG 0
#define LOG_TAG "BnMediaSource"
#include <utils/Log.h>

#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <media/IMediaSource.h>
#include <media/stagefright/MediaBuffer.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <media/stagefright/MediaSource.h>


namespace android {

IMPLEMENT_META_INTERFACE(MediaSource, "android.media.IMediaSource");

BnMediaSource::BnMediaSource()
    : mBuffersSinceStop(0)
    , mGroup(new MediaBufferGroup(kBinderMediaBuffers /* growthLimit */)) {
}

BnMediaSource::~BnMediaSource() {
}

status_t BnMediaSource::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    return NO_ERROR;
}

bool IMediaSource::ReadOptions::getSeekTo(
        int64_t *time_us, SeekMode *mode) const {
    *time_us = mSeekTimeUs;
    *mode = mSeekMode;
    return (mOptions & kSeekTo_Option) != 0;
}


}
