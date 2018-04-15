
#include <initrc.h>

#include <ui/DisplayInfo.h>

#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/eglext.h>

using namespace android;

static InitRC&   gInitrc = InitRC::getInstance();

class Animation : public Thread
{
public:
    Animation()
    :   Thread(false)
    {
        mSession = new SurfaceComposerClient();
    };
    
    ~Animation()
    {
        
    };
    
private:
    virtual bool        threadLoop()
    {
        return true;
    };
    
    virtual status_t    readyToRun()
    {
        sp<IBinder> dtoken(SurfaceComposerClient::getBuiltInDisplay(
                                                                    ISurfaceComposer::eDisplayIdMain));
        DisplayInfo dinfo;
        status_t status = SurfaceComposerClient::getDisplayInfo(dtoken, &dinfo);
        if (status)
            return -1;

        // create the native surface
        sp<SurfaceControl> control = session()->createSurface(String8("Animation"),
                                                              dinfo.w, dinfo.h, PIXEL_FORMAT_RGB_565);
        
        SurfaceComposerClient::openGlobalTransaction();
        control->setLayer(0x40000000);
        SurfaceComposerClient::closeGlobalTransaction();
        
        sp<Surface> s = control->getSurface();

        // initialize opengl and egl
        const EGLint attribs[] = {
            EGL_RED_SIZE,   8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE,  8,
            EGL_DEPTH_SIZE, 0,
            EGL_NONE
        };
        EGLint w, h;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;
        
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        
        eglInitialize(display, 0, 0);
        eglChooseConfig(display, attribs, &config, 1, &numConfigs);
        surface = eglCreateWindowSurface(display, config, s.get(), NULL);
        context = eglCreateContext(display, config, NULL, NULL);
        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);
        
        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
            return NO_INIT;
        
        return NO_ERROR;
    };
    
    virtual void        onFirstRef()
    {
        run("BootAnimation", PRIORITY_DISPLAY);
    };

    sp<SurfaceComposerClient> session() const
    {
        return mSession;
    }
    
private:
    sp<SurfaceComposerClient> mSession;
};

int main(int argc, char** argv)
{
    sp<Animation> animation = new Animation();
    
    while (1) ;
    
    return 0;
}
