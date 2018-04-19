
#include <initrc.h>

#include <ui/DisplayInfo.h>

#include <gui/ISurfaceComposer.h>
#include <gui/ISurfaceHandle.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>

#include <EGL/eglext.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


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
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        do {
            GLfloat vertices[] =
            {
                0.0f,  0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
            };
            
            // Set the viewport
            glViewport(0, 0, mWidth, mHeight);
            
            // Clear the color buffer
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Use the program object
            //glUseProgram(mProgram);
            
            // Load the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
            glEnableVertexAttribArray(0);
            
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            eglSwapBuffers(mDisplay, mSurface);
        } while (!exitPending());
        
        eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(mDisplay, mContext);
        eglDestroySurface(mDisplay, mSurface);
        mFlingerSurface.clear();
        mFlingerSurfaceControl.clear();
        eglTerminate(mDisplay);
        eglReleaseThread();

        return false;
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
        
        //SurfaceComposerClient::openGlobalTransaction();
        //control->setLayer(0x40000000);
        //SurfaceComposerClient::closeGlobalTransaction();
        
        sp<Surface> s = control->getSurface();
        sp<ISurfaceHandle> handle = interface_cast<ISurfaceHandle>(control->getHandle());

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
        eglBindAPI(EGL_OPENGL_ES_API);
        eglChooseConfig(display, attribs, &config, 1, &numConfigs);
        surface = eglCreateWindowSurface(display, config, handle->getNativeWindow(), NULL);
        context = eglCreateContext(display, config, NULL, attribs);
        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);
        
        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
            return NO_INIT;
        
        mDisplay = display;
        mContext = context;
        mSurface = surface;
        mWidth = w;
        mHeight = h;
        mFlingerSurfaceControl = control;
        mFlingerSurface = s;
        
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
    int         mWidth;
    int         mHeight;
    EGLDisplay  mDisplay;
    EGLDisplay  mContext;
    EGLDisplay  mSurface;
    sp<SurfaceControl> mFlingerSurfaceControl;
    sp<Surface> mFlingerSurface;
};

int main(int argc, char** argv)
{
    sp<Animation> animation = new Animation();
    
    while (1) ;
    
    return 0;
}
