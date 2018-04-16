
// #define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "DisplayDevice"

#include <OSWindow.h>

#include "DisplayDevice.h"
#include "SurfaceFlinger.h"

// ----------------------------------------------------------------------------
using namespace android;
// ----------------------------------------------------------------------------

DisplayDevice::DisplayDevice(
        const sp<SurfaceFlinger>& flinger,
        DisplayType type
)
:   mFlinger(flinger),
    mType(type),
    mActiveConfig(0),
    mWindow(0)
{
    mWindow = CreateOSWindow();
}

DisplayDevice::~DisplayDevice() 
{
    
}

// ----------------------------------------------------------------------------
void DisplayDevice::setActiveConfig(int mode) {
    mActiveConfig = mode;
}

int DisplayDevice::getActiveConfig()  const {
    return mActiveConfig;
}
