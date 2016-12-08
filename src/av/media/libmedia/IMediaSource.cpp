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

////////////////////////////////////////////////////////////////////////////////

IMediaSource::ReadOptions::ReadOptions() {
    reset();
}

void IMediaSource::ReadOptions::reset() {
    mOptions = 0;
    mSeekTimeUs = 0;
    mLatenessUs = 0;
    mNonBlocking = false;
}

void IMediaSource::ReadOptions::setNonBlocking() {
    mNonBlocking = true;
}

void IMediaSource::ReadOptions::clearNonBlocking() {
    mNonBlocking = false;
}

bool IMediaSource::ReadOptions::getNonBlocking() const {
    return mNonBlocking;
}

void IMediaSource::ReadOptions::setSeekTo(int64_t time_us, SeekMode mode) {
    mOptions |= kSeekTo_Option;
    mSeekTimeUs = time_us;
    mSeekMode = mode;
}

void IMediaSource::ReadOptions::clearSeekTo() {
    mOptions &= ~kSeekTo_Option;
    mSeekTimeUs = 0;
    mSeekMode = SEEK_CLOSEST_SYNC;
}

bool IMediaSource::ReadOptions::getSeekTo(
        int64_t *time_us, SeekMode *mode) const {
    *time_us = mSeekTimeUs;
    *mode = mSeekMode;
    return (mOptions & kSeekTo_Option) != 0;
}

void IMediaSource::ReadOptions::setLateBy(int64_t lateness_us) {
    mLatenessUs = lateness_us;
}

int64_t IMediaSource::ReadOptions::getLateBy() const {
    return mLatenessUs;
}

}
