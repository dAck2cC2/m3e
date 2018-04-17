
#ifndef ANDROID_DISPLAY_DEVICE_H
#define ANDROID_DISPLAY_DEVICE_H

#include <utils/RefBase.h>
#include <utils/String8.h>

#include <hardware/hwcomposer_defs.h>

class OSWindow;

namespace android {

class SurfaceFlinger;

class DisplayDevice : public LightRefBase<DisplayDevice>
{
public:
    enum DisplayType {
        DISPLAY_ID_INVALID = -1,
        DISPLAY_PRIMARY     = HWC_DISPLAY_PRIMARY,
        DISPLAY_EXTERNAL    = HWC_DISPLAY_EXTERNAL,
        DISPLAY_VIRTUAL     = HWC_DISPLAY_VIRTUAL,
        NUM_BUILTIN_DISPLAY_TYPES = HWC_NUM_PHYSICAL_DISPLAY_TYPES,
    };

    DisplayDevice(const sp<SurfaceFlinger>& flinger,
                  DisplayType type,
                  EGLConfig config,
                  OSWindow* osWindow);

    ~DisplayDevice();

    EGLBoolean makeCurrent(EGLDisplay dpy, EGLContext ctx) const;
   
    /* ------------------------------------------------------------------------
     * Display active config management.
     */
    int getActiveConfig() const;
    void setActiveConfig(int mode);
    
private:
    /*
     *  Constants, set during initialization
     */
    sp<SurfaceFlinger> mFlinger;
    DisplayType mType;
    
    // Current active config
    int mActiveConfig;
    
    // Window of operation system
    OSWindow*   mOSWindow;
    std::string mName;
    
    EGLConfig       mConfig;
    EGLDisplay      mDisplay;
    EGLSurface      mSurface;
    int             mDisplayWidth;
    int             mDisplayHeight;
    String8         mDisplayName;
};

}; // namespace android

#endif // ANDROID_DISPLAY_DEVICE_H
