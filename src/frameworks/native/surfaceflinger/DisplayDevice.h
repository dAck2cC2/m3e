
#ifndef ANDROID_DISPLAY_DEVICE_H
#define ANDROID_DISPLAY_DEVICE_H

#include "Transform.h"

#include <cutils/compiler.h>
#include <utils/RefBase.h>
#include <utils/String8.h>

#include <hardware/hwcomposer_defs.h>

namespace android {

class NativeWindow;
class SurfaceFlinger;

class ANDROID_API DisplayDevice : public LightRefBase<DisplayDevice>
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
		          EGLDisplay display);

    ~DisplayDevice();

    EGLBoolean makeCurrent(EGLDisplay dpy, EGLContext ctx) const;
    void setViewportAndProjection() const;

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
	NativeWindow*   mNativeWindow;
    EGLConfig       mConfig;
    EGLDisplay      mDisplay;
    EGLSurface      mSurface;
    int             mDisplayWidth;
    int             mDisplayHeight;
    String8         mDisplayName;
    
    /*
     * Transaction state
     */
    static status_t orientationToTransfrom(int orientation,
                                           int w, int h, Transform* tr);
};

}; // namespace android

#endif // ANDROID_DISPLAY_DEVICE_H
