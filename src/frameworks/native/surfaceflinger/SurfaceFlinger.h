
#ifndef ANDROID_SURFACE_FLINGER_H
#define ANDROID_SURFACE_FLINGER_H

#include <stdint.h>
#include <sys/types.h>

#include <EGL/egl.h>

#include <cutils/compiler.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/threads.h>
#include <gui/ISurfaceComposer.h>

#include "DisplayDevice.h"
#include "MessageQueue.h"

class OSWindow;

namespace android {
// ---------------------------------------------------------------------------

class Client;
class Layer;
class RenderEngine;

// ---------------------------------------------------------------------------

class ANDROID_API SurfaceFlinger : public BnSurfaceComposer
{
public:
    static char const* getServiceName() {
        return "SurfaceFlinger";
    };
    
    SurfaceFlinger();
    
    // must be called before clients can connect
    void init();
    
    // starts SurfaceFlinger main loop in the current thread
    void run();
    
    // post an asynchronous message to the main thread
    status_t postMessageAsync(const sp<MessageBase>& msg, nsecs_t reltime = 0, uint32_t flags = 0);
    
    // post a synchronous message to the main thread
    status_t postMessageSync(const sp<MessageBase>& msg, nsecs_t reltime = 0, uint32_t flags = 0);

    // returns the default Display
    sp<const DisplayDevice> getDefaultDisplayDevice() const {
        return getDisplayDevice(mBuiltinDisplays[DisplayDevice::DISPLAY_PRIMARY]);
    }

    RenderEngine& getRenderEngine() const {
        return *mRenderEngine;
    }
    
    OSWindow* getOSWindow() const {
        return mOSWindow;
    }
    
private:
    friend class Client;
    
    // We're reference counted, never destroy SurfaceFlinger directly
    virtual ~SurfaceFlinger();
    
    /* ------------------------------------------------------------------------
     * ISurfaceComposer interface
     */
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
    
    /* ------------------------------------------------------------------------
     * RefBase interface
     */
    virtual void onFirstRef();
    
    virtual void CreateNativeWindow();
    virtual EGLDisplay initEGL();
    
    virtual void onHotplugReceived(int disp, bool connected);
    
public:
    /* ------------------------------------------------------------------------
     * Message handling
     */
    void waitForEvent(int timeoutMillis);

private:
    /* ------------------------------------------------------------------------
     * Display and layer stack management
     */
    // called when starting, or restarting after system_server death
    //void initializeDisplays();

    void createBuiltinDisplayLocked(int type);
    
    // NOTE: can only be called from the main thread or with mStateLock held
    sp<const DisplayDevice> getDisplayDevice(const wp<IBinder>& dpy) const {
        return mDisplays.valueFor(dpy);
    }
    
    // NOTE: can only be called from the main thread or with mStateLock held
    sp<DisplayDevice> getDisplayDevice(const wp<IBinder>& dpy) {
        return mDisplays.valueFor(dpy);
    }
    
    int32_t getDisplayType(const sp<IBinder>& display) {
        if (!display.get()) return NAME_NOT_FOUND;
        for (int i = 0; i < DisplayDevice::NUM_BUILTIN_DISPLAY_TYPES; ++i) {
            if (display == mBuiltinDisplays[i]) {
                return i;
            }
        }
        return NAME_NOT_FOUND;
    }

    /* ------------------------------------------------------------------------
     * Layer management
     */
    status_t createLayer(const String8& name, const sp<Client>& client,
                         uint32_t w, uint32_t h, PixelFormat format, uint32_t flags,
                         sp<IBinder>* handle, sp<IGraphicBufferProducer>* gbp);
    
    status_t createNormalLayer(const sp<Client>& client, const String8& name,
                               uint32_t w, uint32_t h, uint32_t flags, PixelFormat& format,
                               sp<IBinder>* outHandle, sp<IGraphicBufferProducer>* outGbp,
                               sp<Layer>* outLayer);
    
    status_t createDimLayer(const sp<Client>& client, const String8& name,
                            uint32_t w, uint32_t h, uint32_t flags, sp<IBinder>* outHandle,
                            sp<IGraphicBufferProducer>* outGbp, sp<Layer>* outLayer);
    
    // add a layer to SurfaceFlinger
    status_t addClientLayer(const sp<Client>& client,
                            const sp<IBinder>& handle,
                            const sp<IGraphicBufferProducer>& gbc,
                            const sp<Layer>& lbc);
    
    /* ------------------------------------------------------------------------
     * Boot animation, on/off animations and screen capture
     */
    void startBootAnim();
    
private:
    /* ------------------------------------------------------------------------
     * Attributes
     */
    
    // access must be protected by mStateLock
    mutable Mutex mStateLock;

    RenderEngine* mRenderEngine;
    EGLContext mEGLContext;
    EGLDisplay mEGLDisplay;
    sp<IBinder> mBuiltinDisplays[DisplayDevice::NUM_BUILTIN_DISPLAY_TYPES];
    
    // this may only be written from the main thread with mStateLock held
    // it may be read from other threads with mStateLock held
    DefaultKeyedVector< wp<IBinder>, sp<DisplayDevice> > mDisplays;
    
    // these are thread safe
    mutable MessageQueue mEventQueue;
    
    // OS window
    OSWindow* mOSWindow;
};

};  // namespace android

#endif // ANDROID_SURFACE_FLINGER_H
