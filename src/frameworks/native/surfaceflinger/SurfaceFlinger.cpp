
#include <cutils/properties.h>

#include <ui/DisplayInfo.h>

#include <gui/IDisplayEventConnection.h>

#include "Client.h"
#include "SurfaceFlinger.h"

namespace android {

SurfaceFlinger::SurfaceFlinger()
:   BnSurfaceComposer(),
    mBuiltinDisplays()
{

}

SurfaceFlinger::~SurfaceFlinger()
{

}

sp<ISurfaceComposerClient> SurfaceFlinger::createConnection()
{
    sp<ISurfaceComposerClient> bclient;
    sp<Client> client(new Client(this));
    status_t err = client->initCheck();
    if (err == NO_ERROR) {
        bclient = client;
    }
    return bclient;
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
    if (uint32_t(id) >= HWC_NUM_PHYSICAL_DISPLAY_TYPES) {
        ALOGE("getDefaultDisplay: id=%d is not a valid default display id", id);
        return NULL;
    }
    return mBuiltinDisplays[id];
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
    if ((configs == NULL) || (display.get() == NULL)) {
        return BAD_VALUE;
    }
    
    if (!display.get())
        return NAME_NOT_FOUND;
    
    int32_t type = NAME_NOT_FOUND;
    for (int i=0 ; i<HWC_NUM_PHYSICAL_DISPLAY_TYPES ; i++) {
        if (display == mBuiltinDisplays[i]) {
            type = i;
            break;
        }
    }
    
    if (type < 0) {
        return type;
    }
    
    // TODO: Not sure if display density should handled by SF any longer
    class Density {
        static int getDensityFromProperty(char const* propName) {
            char property[PROPERTY_VALUE_MAX];
            int density = 0;
            if (property_get(propName, property, NULL) > 0) {
                density = atoi(property);
            }
            return density;
        }
    public:
        static int getEmuDensity() {
            return getDensityFromProperty("qemu.sf.lcd_density"); }
        static int getBuildDensity()  {
            return getDensityFromProperty("ro.sf.lcd_density"); }
    };
    
    configs->clear();

    {
        DisplayInfo info = DisplayInfo();
        
        float xdpi = 1; //hwConfig->getDpiX();
        float ydpi = 1; //hwConfig->getDpiY();
        
        if (type == HWC_DISPLAY_PRIMARY) {
            // The density of the device is provided by a build property
            float density = Density::getBuildDensity() / 160.0f;
            if (density == 0) {
                // the build doesn't provide a density -- this is wrong!
                // use xdpi instead
                ALOGE("ro.sf.lcd_density must be defined as a build property");
                density = xdpi / 160.0f;
            }
            if (Density::getEmuDensity()) {
                // if "qemu.sf.lcd_density" is specified, it overrides everything
                xdpi = ydpi = density = Density::getEmuDensity();
                density /= 160.0f;
            }
            info.density = density;
        } else {
            // TODO: where should this value come from?
            static const int TV_DENSITY = 213;
            info.density = TV_DENSITY / 160.0f;
            info.orientation = 0;
        }
        
        //info.w = hwConfig->getWidth();
        //info.h = hwConfig->getHeight();
        info.xdpi = xdpi;
        info.ydpi = ydpi;
        //info.fps = 1e9 / hwConfig->getVsyncPeriod();
        //info.appVsyncOffset = VSYNC_EVENT_PHASE_OFFSET_NS;
        
        // This is how far in advance a buffer must be queued for
        // presentation at a given time.  If you want a buffer to appear
        // on the screen at time N, you must submit the buffer before
        // (N - presentationDeadline).
        //
        // Normally it's one full refresh period (to give SF a chance to
        // latch the buffer), but this can be reduced by configuring a
        // DispSync offset.  Any additional delays introduced by the hardware
        // composer or panel must be accounted for here.
        //
        // We add an additional 1ms to allow for processing time and
        // differences between the ideal and actual refresh rate.
        //info.presentationDeadline = hwConfig->getVsyncPeriod() -
        //SF_VSYNC_EVENT_PHASE_OFFSET_NS + 1000000;
        
        // All non-virtual displays are currently considered secure.
        info.secure = true;
        
        configs->push_back(info);
    }
    
    return NO_ERROR;
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

void SurfaceFlinger::onFirstRef()
{
    createBuiltinDisplayLocked(HWC_DISPLAY_PRIMARY);
}

void SurfaceFlinger::createBuiltinDisplayLocked(int type)
{
    ALOGV("createBuiltinDisplayLocked(%d)", type);
    ALOGW_IF(mBuiltinDisplays[type],
             "Overwriting display token for display type %d", type);
    mBuiltinDisplays[type] = new BBinder();
}

    
}; // namespace android
