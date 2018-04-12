
#include "SurfaceFlinger.h"
#include <gui/IDisplayEventConnection.h>

namespace android {

SurfaceFlinger::SurfaceFlinger()
{

}

SurfaceFlinger::~SurfaceFlinger()
{

}

sp<ISurfaceComposerClient> SurfaceFlinger::createConnection()
{
    return NULL;
}
    
sp<IGraphicBufferAlloc> SurfaceFlinger::createGraphicBufferAlloc()
{
    return NULL;
}

sp<IDisplayEventConnection> SurfaceFlinger::createDisplayEventConnection()
{
    return NULL;
}

sp<IBinder> SurfaceFlinger::createDisplay(const String8& displayName, bool secure)
{
    return NULL;
}

void SurfaceFlinger::destroyDisplay(const sp<IBinder>& display)
{
    return;
}
    
sp<IBinder> SurfaceFlinger::getBuiltInDisplay(int32_t id)
{
    return NULL;
}

void SurfaceFlinger::setTransactionState(const Vector<ComposerState>& state,
                                     const Vector<DisplayState>& displays, uint32_t flags)
{
    return;
}

void SurfaceFlinger::bootFinished()
{
    return;
}

bool SurfaceFlinger::authenticateSurfaceTexture(const sp<IGraphicBufferProducer>& surface) const
{
    return false;
}

void SurfaceFlinger::setPowerMode(const sp<IBinder>& display, int mode)
{
    return;
}

status_t SurfaceFlinger::getDisplayConfigs(const sp<IBinder>& display,
                                       Vector<DisplayInfo>* configs)
{
    return NO_INIT;
}

status_t SurfaceFlinger::getDisplayStats(const sp<IBinder>& display,
                             DisplayStatInfo* stats)
{
    return NO_INIT;
}

int SurfaceFlinger::getActiveConfig(const sp<IBinder>& display)
{
    return -1;
}

status_t SurfaceFlinger::setActiveConfig(const sp<IBinder>& display, int id)
{
    return NO_INIT;
}

status_t SurfaceFlinger::getDisplayColorModes(const sp<IBinder>& display,
                                              Vector<android_color_mode_t>* outColorModes)
{
    return NO_INIT;
}

android_color_mode_t SurfaceFlinger::getActiveColorMode(const sp<IBinder>& display)
{
    return HAL_COLOR_MODE_NATIVE;
}

status_t SurfaceFlinger::setActiveColorMode(const sp<IBinder>& display,
                                android_color_mode_t colorMode)
{
    return NO_INIT;
}

status_t SurfaceFlinger::captureScreen(const sp<IBinder>& display,
                                   const sp<IGraphicBufferProducer>& producer,
                                   Rect sourceCrop, uint32_t reqWidth, uint32_t reqHeight,
                                   uint32_t minLayerZ, uint32_t maxLayerZ,
                                   bool useIdentityTransform,
                                   Rotation rotation)
{
    return NO_INIT;
}

status_t SurfaceFlinger::clearAnimationFrameStats()
{
    return NO_INIT;
}
    
status_t SurfaceFlinger::getAnimationFrameStats(FrameStats* outStats) const
{
    return NO_INIT;
}

status_t SurfaceFlinger::getHdrCapabilities(const sp<IBinder>& display,
                                    HdrCapabilities* outCapabilities) const
{
    return NO_INIT;
}

}; // namespace android
