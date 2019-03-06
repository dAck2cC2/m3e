
#include <vector>

#include <cutils/properties.h>

#include <binder/IPCThreadState.h>

#include <ui/DisplayInfo.h>

#include <gui/IDisplayEventConnection.h>

#include "Client.h"
#include "Layer.h"
#include "SurfaceFlinger.h"

#include "RenderEngine/RenderEngine.h"
#include "NativeWindow/NativeWindow.h"

#if ENABLE_ANGLE_TEST
#include "angle_test.hpp"
static sp<angle::MultiWindowSample> g_TestAngle;
#endif // ENABLE_ANGLE

namespace android {

SurfaceFlinger::SurfaceFlinger()
:   BnSurfaceComposer(),
    mRenderEngine(NULL),
    mBuiltinDisplays(),
    mNativeWindow(NULL)
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
#if 1
		/*
		* Not sure how to support such usage currently.
		* Where to keep the Binder Native(server) instance ?
		*/
		/*
		* Anyway, we have to keep the client for multi-window update.
		*/
		mClients.push_back(client);
#endif
    }

    return bclient;
}
    
sp<ISurfaceComposerClient> SurfaceFlinger::createScopedConnection(const sp<IGraphicBufferProducer>& gbp)
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
    if (uint32_t(id) >= DisplayDevice::NUM_BUILTIN_DISPLAY_TYPES) {
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

bool SurfaceFlinger::authenticateSurfaceTexture(
	const sp<IGraphicBufferProducer>& bufferProducer) const
{
    return false;
}

status_t SurfaceFlinger::getSupportedFrameTimestamps(
	std::vector<FrameEvent>* outSupported) const
{
	return NO_INIT;
}

sp<IDisplayEventConnection> SurfaceFlinger::createDisplayEventConnection(
	ISurfaceComposer::VsyncSource vsyncSource)
{
	return NULL;
}

status_t SurfaceFlinger::captureScreen(const sp<IBinder>& display,
	const sp<IGraphicBufferProducer>& producer,
	Rect sourceCrop, uint32_t reqWidth, uint32_t reqHeight,
	int32_t minLayerZ, int32_t maxLayerZ,
	bool useIdentityTransform, ISurfaceComposer::Rotation rotation)
{
	return NO_INIT;
}

status_t SurfaceFlinger::getDisplayStats(const sp<IBinder>& display,
	DisplayStatInfo* stats)
{
	return NO_INIT;
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
    for (int i=0 ; i<DisplayDevice::NUM_BUILTIN_DISPLAY_TYPES ; i++) {
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
        
        info.w = 800; //hwConfig->getWidth();
        info.h = 600; //hwConfig->getHeight();
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

int SurfaceFlinger::getActiveConfig(const sp<IBinder>& display)
{
    sp<DisplayDevice> device(getDisplayDevice(display));
    if (device != NULL) {
        return device->getActiveConfig();
    }
    return BAD_VALUE;
}

status_t SurfaceFlinger::getDisplayColorModes(const sp<IBinder>& display,
	Vector<android_color_mode_t>* configs)
{
	return NO_INIT;
}

android_color_mode_t SurfaceFlinger::getActiveColorMode(const sp<IBinder>& display)
{
	return HAL_COLOR_MODE_NATIVE;
}

status_t SurfaceFlinger::setActiveColorMode(const sp<IBinder>& display, android_color_mode_t colorMode)
{
	return NO_INIT;
}

void SurfaceFlinger::setPowerMode(const sp<IBinder>& display, int mode)
{
	return;
}

status_t SurfaceFlinger::setActiveConfig(const sp<IBinder>& display, int id)
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

status_t SurfaceFlinger::enableVSyncInjections(bool enable)
{
	return NO_INIT;
}

status_t SurfaceFlinger::injectVSync(nsecs_t when)
{
	return NO_INIT;
}

sp<NativeWindow> SurfaceFlinger::CreateOSWindow(const char* name, bool visible)
{
	sp<NativeWindow> nativeWindow = CreateNativeWindow();
	LOG_ALWAYS_FATAL_IF((nativeWindow == NULL), "Failed to create native window %s:%d", __FILE__, __LINE__);

    if (nativeWindow != NULL) {
        char defaultName[PROPERTY_VALUE_MAX];
        property_get("native.display.name", defaultName, "default");
		if (!name) {
			name = defaultName;
		}

        int32_t width  = property_get_int32("native.display.width",  400);
        int32_t height = property_get_int32("native.display.height", 300);
        
		bool check = nativeWindow->initialize(name, width, height);
		LOG_ALWAYS_FATAL_IF((check == false), "Failed to intialize native window %s:%d", __FILE__, __LINE__);

		nativeWindow->setVisible(visible);
    }

	return nativeWindow;
}

    
EGLDisplay SurfaceFlinger::initEGL()
{
	mNativeWindow = CreateOSWindow();

    EGLDisplay display = EGL_NO_DISPLAY;
    
    if (mNativeWindow == NULL) {
        return display;
    }

	// initializeDisplayAndSurface
#if ENABLE_ANGLE
    std::vector<EGLAttrib> displayAttributes;
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_TYPE_ANGLE);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE);
    displayAttributes.push_back(-1);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE);
    displayAttributes.push_back(-1);
    
    displayAttributes.push_back(EGL_NONE);
    
    display = eglGetPlatformDisplay(EGL_PLATFORM_ANGLE_ANGLE,
                                     reinterpret_cast<void *>(mNativeWindow->getNativeDisplay()),
                                     &displayAttributes[0]);
#else
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif

    return display;
}
    
void SurfaceFlinger::init()
{
    ALOGI(  "SurfaceFlinger's main thread ready to run. "
          "Initializing graphics H/W...");
    
    { // Autolock scope
        Mutex::Autolock _l(mStateLock);
        
        // initialize EGL for the default display
#if 0
		mEGLDisplay = initEGL();
#else
		mNativeWindow = CreateOSWindow();
        mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif 
        eglInitialize(mEGLDisplay, NULL, NULL);
        
        // Get a RenderEngine for the given display / config (can't fail)
        mRenderEngine = RenderEngine::create(mEGLDisplay,
                                             HAL_PIXEL_FORMAT_RGBA_8888);
    }
    
    // Drop the state lock while we initialize the hardware composer. We drop
    // the lock because on creation, it will call back into SurfaceFlinger to
    // initialize the primary display.
    onHotplugReceived(DisplayDevice::DISPLAY_PRIMARY, true);
    
    Mutex::Autolock _l(mStateLock);
    
    // retrieve the EGL context that was selected/created
    mEGLContext = mRenderEngine->getEGLContext();
    
    LOG_ALWAYS_FATAL_IF(mEGLContext == EGL_NO_CONTEXT,
                        "couldn't create EGLContext");
    
    // make the GLContext current so that we can create textures when creating
    // Layers (which may happens before we render something)
    getDefaultDisplayDevice()->makeCurrent(mEGLDisplay, mEGLContext);
    
    mRenderEngine->primeCache();

    // start boot animation
    startBootAnim();
    
    ALOGV("Done initializing");
}

void SurfaceFlinger::startBootAnim() {
    // start boot animation
    property_set("service.bootanim.exit", "0");
    property_set("ctl.start", "bootanim");
}

    
void SurfaceFlinger::onFirstRef()
{
    mEventQueue.init(this);    
}

void SurfaceFlinger::onHotplugReceived(int32_t disp, bool connected) {
    ALOGV("onHotplugReceived(%d, %s)", disp, connected ? "true" : "false");
    if (disp == DisplayDevice::DISPLAY_PRIMARY) {
        Mutex::Autolock lock(mStateLock);
        
        // All non-virtual displays are currently considered secure.
        //bool isSecure = true;
        
        int32_t type = DisplayDevice::DISPLAY_PRIMARY;
        createBuiltinDisplayLocked(DisplayDevice::DISPLAY_PRIMARY);
        wp<IBinder> token = mBuiltinDisplays[type];
        /*
        sp<IGraphicBufferProducer> producer;
        sp<IGraphicBufferConsumer> consumer;
        BufferQueue::createBufferQueue(&producer, &consumer,
                                       new GraphicBufferAlloc());
        
        sp<FramebufferSurface> fbs = new FramebufferSurface(*mHwc,
                                                            DisplayDevice::DISPLAY_PRIMARY, consumer);
        sp<DisplayDevice> hw = new DisplayDevice(this,
                                                 DisplayDevice::DISPLAY_PRIMARY, disp, isSecure, token, fbs,
                                                 producer, mRenderEngine->getEGLConfig());
        */
        sp<DisplayDevice> hw = new DisplayDevice(this,
                                                 DisplayDevice::DISPLAY_PRIMARY,
                                                 mRenderEngine->getEGLConfig(),
                                                 mEGLDisplay);

        mDisplays.add(token, hw);
    } else {
        auto type = DisplayDevice::DISPLAY_EXTERNAL;
        Mutex::Autolock _l(mStateLock);
        if (connected) {
            createBuiltinDisplayLocked(type);
        } else {
            //mCurrentState.displays.removeItem(mBuiltinDisplays[type]);
            mBuiltinDisplays[type].clear();
        }
        //setTransactionFlags(eDisplayTransactionNeeded);
        
        // Defer EventThread notification until SF has updated mDisplays.
    }
}
    
void SurfaceFlinger::createBuiltinDisplayLocked(int type)
{
    ALOGV("createBuiltinDisplayLocked(%d)", type);
    ALOGW_IF(mBuiltinDisplays[type],
             "Overwriting display token for display type %d", type);
    mBuiltinDisplays[type] = new BBinder();
}

status_t SurfaceFlinger::createLayer(
                                     const String8& name,
                                     const sp<Client>& client,
                                     uint32_t w, uint32_t h, PixelFormat format, uint32_t flags,
                                     sp<IBinder>* handle, sp<IGraphicBufferProducer>* gbp)
{
    //ALOGD("createLayer for (%d x %d), name=%s", w, h, name.string());
    if (int32_t(w|h) < 0) {
        ALOGE("createLayer() failed, w or h is negative (w=%d, h=%d)",
              int(w), int(h));
        return BAD_VALUE;
    }
    
    status_t result = NO_ERROR;
    
    sp<Layer> layer;
    
    switch (flags & ISurfaceComposerClient::eFXSurfaceMask) {
        case ISurfaceComposerClient::eFXSurfaceNormal:
            result = createNormalLayer(client,
                                       name, w, h, flags, format,
                                       handle, gbp, &layer);
            break;
        case ISurfaceComposerClient::eFXSurfaceDim:
            result = createDimLayer(client,
                                    name, w, h, flags,
                                    handle, gbp, &layer);
            break;
        default:
            result = BAD_VALUE;
            break;
    }
    
    if (result != NO_ERROR) {
        return result;
    }
    
    result = addClientLayer(client, *handle, *gbp, layer);
    if (result != NO_ERROR) {
        return result;
    }
    
    //setTransactionFlags(eTransactionNeeded);
    return result;
}

status_t SurfaceFlinger::createNormalLayer(const sp<Client>& client,
                                           const String8& name, uint32_t w, uint32_t h, uint32_t flags, PixelFormat& format,
                                           sp<IBinder>* handle, sp<IGraphicBufferProducer>* gbp, sp<Layer>* outLayer)
{
    // initialize the surfaces
    switch (format) {
        case PIXEL_FORMAT_TRANSPARENT:
        case PIXEL_FORMAT_TRANSLUCENT:
            format = PIXEL_FORMAT_RGBA_8888;
            break;
        case PIXEL_FORMAT_OPAQUE:
            format = PIXEL_FORMAT_RGBX_8888;
            break;
    }
    
    *outLayer = new Layer(this, client, name, w, h, flags);
    status_t err = (*outLayer)->setBuffers(w, h, format, flags);
    if (err == NO_ERROR) {
        *handle = (*outLayer)->getHandle();
    //    *gbp = (*outLayer)->getProducer();
    }
    
    ALOGE_IF(err, "createNormalLayer() failed (%s)", strerror(-err));
    return err;
}

status_t SurfaceFlinger::createDimLayer(const sp<Client>& client,
                                        const String8& name, uint32_t w, uint32_t h, uint32_t flags,
                                        sp<IBinder>* handle, sp<IGraphicBufferProducer>* gbp, sp<Layer>* outLayer)
{
    return NO_INIT;
}

status_t SurfaceFlinger::addClientLayer(const sp<Client>& client,
                                        const sp<IBinder>& handle,
                                        const sp<IGraphicBufferProducer>& gbc,
                                        const sp<Layer>& lbc)
{
    /*
    // add this layer to the current state list
    {
        Mutex::Autolock _l(mStateLock);
        if (mCurrentState.layersSortedByZ.size() >= MAX_LAYERS) {
            return NO_MEMORY;
        }
        mCurrentState.layersSortedByZ.add(lbc);
        mGraphicBufferProducerList.add(IInterface::asBinder(gbc));
    }
    */
    
    // attach this layer to the client
    client->attachLayer(handle, lbc);
    
    return NO_ERROR;
}

status_t SurfaceFlinger::postMessageAsync(const sp<MessageBase>& msg,
                                          nsecs_t reltime, uint32_t /* flags */) {
    return mEventQueue.postMessage(msg, reltime);
}

status_t SurfaceFlinger::postMessageSync(const sp<MessageBase>& msg,
                                         nsecs_t reltime, uint32_t /* flags */) {
    status_t res = mEventQueue.postMessage(msg, reltime);
    if (res == NO_ERROR) {
        msg->wait();
    }
    return res;
}

void SurfaceFlinger::run() {
    if (mNativeWindow != NULL){
        bool mRunning = true;
        
        while (mRunning) {
#if ENABLE_ANGLE_TEST
			if (g_TestAngle == NULL) {
				g_TestAngle = new angle::MultiWindowSample(mNativeWindow, mEGLDisplay, mRenderEngine->getEGLConfig(), mDisplays.valueAt(0)->getEGLSurface(), mRenderEngine->getEGLContext());
				g_TestAngle->initialize();
			}
			if (g_TestAngle != NULL) {
				g_TestAngle->step();
				g_TestAngle->draw();
			}
#endif // ENABLE_ANGLE_TEST

			// message loop of sub window
			const size_t count = mClients.size();
			for (size_t i = 0; i<count; i++) {
				mClients[i]->updateLayer();
			}

            // Clear events that the application did not process from this frame
            Event event;
            while (mNativeWindow->popEvent(&event)) {
                // If the application did not catch a close event, close now
                if (event.Type == Event::EVENT_CLOSED) {
                    mRunning = false;
                }
            }
            
            if (!mRunning) {
                break;
            }

			// The message which is used to create surface must be executed in main thread.
            waitForEvent(1000/60);
            
			//IPCThreadState::self()->handlePolledCommands();
            
            mNativeWindow->messageLoop();
        } // while (mRunning)
    } // if (mNativeWindow)
}
    
void SurfaceFlinger::waitForEvent(int timeoutMillis) {
    mEventQueue.waitMessage(timeoutMillis);
}

}; // namespace android
