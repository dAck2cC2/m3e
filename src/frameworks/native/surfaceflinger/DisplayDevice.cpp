
// #define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "DisplayDevice"

#include <cutils/properties.h>

#include <OSWindow.h>

#include "RenderEngine/RenderEngine.h"

#include "DisplayDevice.h"
#include "SurfaceFlinger.h"

// ----------------------------------------------------------------------------
using namespace android;
// ----------------------------------------------------------------------------

DisplayDevice::DisplayDevice(const sp<SurfaceFlinger>& flinger,
                             DisplayType type,
                             EGLConfig config,
                             OSWindow* osWindow)
:   mFlinger(flinger),
    mType(type),
    mActiveConfig(0),
    mOSWindow(osWindow),
    mName(),
    mDisplay(EGL_NO_DISPLAY),
    mSurface(EGL_NO_SURFACE),
    mDisplayWidth(),
    mDisplayHeight()
{
    EGLNativeWindowType const window = mOSWindow->getNativeWindow();
    
    EGLSurface eglSurface;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (config == EGL_NO_CONFIG) {
        config = RenderEngine::chooseEglConfig(display, PIXEL_FORMAT_RGBA_8888);
    }
    eglSurface = eglCreateWindowSurface(display, config, window, NULL);
    eglQuerySurface(display, eglSurface, EGL_WIDTH,  &mDisplayWidth);
    eglQuerySurface(display, eglSurface, EGL_HEIGHT, &mDisplayHeight);
    
    mConfig = config;
    mDisplay = display;
    mSurface = eglSurface;
    
    // Name the display.  The name will be replaced shortly if the display
    // was created with createDisplay().
    switch (mType) {
        case DISPLAY_PRIMARY:
            mDisplayName = "Built-in Screen";
            break;
        case DISPLAY_EXTERNAL:
            mDisplayName = "HDMI Screen";
            break;
        default:
            mDisplayName = "Virtual Screen";    // e.g. Overlay #n
            break;
    }
    
    // initialize the display orientation transform.
    //setProjection(DisplayState::eOrientationDefault, mViewport, mFrame);
}

DisplayDevice::~DisplayDevice() 
{
    if (mOSWindow) {
        mOSWindow->destroy();
        delete mOSWindow;
        mOSWindow = NULL;
    }
}

EGLBoolean DisplayDevice::makeCurrent(EGLDisplay dpy, EGLContext ctx) const {
    EGLBoolean result = EGL_TRUE;
    EGLSurface sur = eglGetCurrentSurface(EGL_DRAW);
    if (sur != mSurface) {
        result = eglMakeCurrent(dpy, mSurface, mSurface, ctx);
        if (result == EGL_TRUE) {
            if (mType >= DisplayDevice::DISPLAY_VIRTUAL)
                eglSwapInterval(dpy, 0);
        }
    }
    //setViewportAndProjection();
    return result;
}

// ----------------------------------------------------------------------------
void DisplayDevice::setActiveConfig(int mode) {
    mActiveConfig = mode;
}

int DisplayDevice::getActiveConfig()  const {
    return mActiveConfig;
}
