
#include <stdint.h>
#include <sys/types.h>

#include "Client.h"
#include "SurfaceFlinger.h"

namespace android {

// ---------------------------------------------------------------------------

Client::Client(const sp<SurfaceFlinger>& flinger)
    : mFlinger(flinger)
{
}

Client::~Client()
{
}

status_t Client::initCheck() const {
    return NO_ERROR;
}

status_t Client::createSurface(
        const String8& name,
        uint32_t w, uint32_t h, PixelFormat format, uint32_t flags,
        sp<IBinder>* handle,
        sp<IGraphicBufferProducer>* gbp)
{
    return NO_INIT;
}

status_t Client::destroySurface(const sp<IBinder>& handle) {
    return NO_INIT;
}

status_t Client::clearLayerFrameStats(const sp<IBinder>& handle) const {
    return NO_INIT;
}

status_t Client::getLayerFrameStats(const sp<IBinder>& handle, FrameStats* outStats) const {
    return NO_INIT;
}

status_t Client::getTransformToDisplayInverse(const sp<IBinder>& handle,
        bool* outTransformToDisplayInverse) const {
    return NO_INIT;
}

// ---------------------------------------------------------------------------
}; // namespace android
