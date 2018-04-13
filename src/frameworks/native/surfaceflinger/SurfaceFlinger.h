#ifndef ANDROID_SURFACE_FLINGER_H
#define ANDROID_SURFACE_FLINGER_H

#include <utils/threads.h>
#include <gui/ISurfaceComposer.h>
#include <hardware/hwcomposer_defs.h>

namespace android {
    
class SurfaceFlinger : public BnSurfaceComposer
{
public:
    static char const* getServiceName() {
        return "SurfaceFlinger";
    };
    
    SurfaceFlinger();
    ~SurfaceFlinger();
    
    virtual sp<ISurfaceComposerClient> createConnection();
    virtual sp<IGraphicBufferAlloc> createGraphicBufferAlloc();
    virtual sp<IDisplayEventConnection> createDisplayEventConnection();
    virtual sp<IBinder> createDisplay(const String8& displayName, bool secure);
    virtual void destroyDisplay(const sp<IBinder>& display);
    virtual sp<IBinder> getBuiltInDisplay(int32_t id);
    virtual void setTransactionState(const Vector<ComposerState>& state,
                                     const Vector<DisplayState>& displays, uint32_t flags);
    virtual void bootFinished();
    virtual bool authenticateSurfaceTexture(const sp<IGraphicBufferProducer>& surface) const;
    virtual void setPowerMode(const sp<IBinder>& display, int mode);
    virtual status_t getDisplayConfigs(const sp<IBinder>& display,
                                       Vector<DisplayInfo>* configs);
    virtual status_t getDisplayStats(const sp<IBinder>& display,
                                     DisplayStatInfo* stats);
    virtual int getActiveConfig(const sp<IBinder>& display);
    virtual status_t setActiveConfig(const sp<IBinder>& display, int id);
    virtual status_t getDisplayColorModes(const sp<IBinder>& display,
                                          Vector<android_color_mode_t>* outColorModes);
    virtual android_color_mode_t getActiveColorMode(const sp<IBinder>& display);
    virtual status_t setActiveColorMode(const sp<IBinder>& display,
                                        android_color_mode_t colorMode);
    virtual status_t captureScreen(const sp<IBinder>& display,
                                   const sp<IGraphicBufferProducer>& producer,
                                   Rect sourceCrop, uint32_t reqWidth, uint32_t reqHeight,
                                   uint32_t minLayerZ, uint32_t maxLayerZ,
                                   bool useIdentityTransform,
                                   Rotation rotation = eRotateNone);
    virtual status_t clearAnimationFrameStats();
    virtual status_t getAnimationFrameStats(FrameStats* outStats) const;
    virtual status_t getHdrCapabilities(const sp<IBinder>& display,
                                        HdrCapabilities* outCapabilities) const;
private:
    /* ------------------------------------------------------------------------
     * RefBase interface
     */
    virtual void onFirstRef();

    void createBuiltinDisplayLocked(int type);

private:
    sp<IBinder> mBuiltinDisplays[HWC_NUM_PHYSICAL_DISPLAY_TYPES];
};

};  // namespace android

#endif // ANDROID_SURFACE_FLINGER_H
