
#include <initrc.h>

#include <cutils/properties.h>

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

#if defined(ENABLE_ANGLE)
#include "shader_utils.h"
#endif

using namespace android;

class Sample : public Thread
{
public:
    Sample()
    :   Thread(false)
    {
        mSession = new SurfaceComposerClient();
    };
    
    ~Sample()
    {
        
    };
    
    virtual bool initialize()
    {
#if defined(ENABLE_ANGLE)
        const std::string vs =
        R"(attribute vec4 vPosition;
        void main()
        {
            gl_Position = vPosition;
        })";
        
        const std::string fs =
        R"(precision mediump float;
        void main()
        {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        })";
     
        mProgram = CompileProgram(vs, fs);
        if (!mProgram)
        {
            return false;
        }
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
#endif
        return true;
    }

    
    void draw()
    {
#if (ENABLE_DESKTOP_GL)
		static GLfloat r = 1.0f;
		static GLfloat g = 0.0f;
		static GLfloat b = 1.0f;

		r -= 0.01f;
		if (r < 0.0f) r = 1.0f;

		b += 0.01f;
		if (b > 1.0f) b = 0.0f;

		/* rotate a triangle around */
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3f(r, 0.0f, 0.0f);
		glVertex2i(0, 1);
		glColor3f(0.0f, g, 0.0f);
		glVertex2i(-1, -1);
		glColor3f(0.0f, 0.0f, b);
		glVertex2i(1, -1);
		glEnd();
		glFlush();
#else
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
        glUseProgram(mProgram);
        
        // Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
        eglSwapBuffers(mDisplay, mSurface);
    };

	void rotating()
	{

	};
    
private:
    virtual bool        threadLoop()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        do {
            draw();
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
        sp<SurfaceControl> control = session()->createSurface(String8("Sample"),
                                                              dinfo.w, dinfo.h, PIXEL_FORMAT_RGB_565);
        
        SurfaceComposerClient::openGlobalTransaction();
        control->setLayer(0x40000000);
        SurfaceComposerClient::closeGlobalTransaction();
        
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
		const EGLint attribsContext[] = {
			EGL_CONTEXT_MAJOR_VERSION_KHR, 2,
			EGL_NONE
		};
        EGLint w, h;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;

#if defined(__APPLE__)
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY + 1);
#else
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif
        
        eglInitialize(display, 0, 0);
        eglBindAPI(EGL_OPENGL_ES_API);
        eglChooseConfig(display, attribs, &config, 1, &numConfigs);
        surface = eglCreateWindowSurface(display, config, handle->getNativeWindow(), NULL);
        context = eglCreateContext(display, config, NULL, attribsContext);
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
        
        initialize();
        
        return NO_ERROR;
    };
    
    virtual void        onFirstRef()
    {
        run("Sample", PRIORITY_DISPLAY);
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
    GLuint mProgram;
	// Current rotation
	float mRotation;
};


int main(int argc, char** argv)
{
    InitRC::getInstance().Entry(argc, argv);
    
    sp<Sample> sample = new Sample();
    
	property_set("ctl.start", "");

    InitRC::getInstance().Run();
    
    return 0;
}