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

using namespace android;

GLuint CreateSimpleTexture2D()
{
	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	GLuint texture;
	glGenTextures(1, &texture);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture);

	// Load the texture: 2x2 Image, 3 bytes per pixel (R, G, B)
	const size_t width = 2;
	const size_t height = 2;
	GLubyte pixels[width * height * 3] =
	{
		255,   0,   0, // Red
		0, 255,   0, // Green
		0,   0, 255, // Blue
		255, 255,   0, // Yellow
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

class Sample : public Thread
{
public:
	Sample()
		: Thread(false)
	{
		mSession = new SurfaceComposerClient();
	};

	~Sample()
	{

	};

	virtual bool initialize()
	{
		// Load the texture
		mTexture = CreateSimpleTexture2D();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glActiveTexture(GL_TEXTURE0);
		//glEnable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		GLint crop[4] = { 0, 0, 2, 2 };
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, crop);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glViewport(0, 0, mWindowWidth, mWindowHeight);

		return true;
	};

	void draw()
	{
#if 1
		glDrawTexiOES(mX, mY, 0, mWindowWidth, mWindowHeight);
#else
		glClear(GL_COLOR_BUFFER_BIT);

		GLint windowWidth = mWindowWidth;
		GLint windowHeight = mWindowHeight;

		glDrawTexiOES(mX, mY, 0, mWidth, mHeight);
		glDrawTexiOES(windowWidth - mX, mY, 0, mWidth, mHeight);
		glDrawTexiOES(mX, windowHeight - mY, 0, mWidth, mHeight);
		glDrawTexiOES(windowWidth - mX, windowHeight - mY, 0, mWidth, mHeight);

		mX += mReverseX ? -1 : 1;
		mY += mReverseY ? -1 : 1;

		if (mX + mWidth >= windowWidth)
			mReverseX = true;
		if (mX < 0)
			mReverseX = false;

		if (mY + mHeight >= windowHeight)
			mReverseY = true;
		if (mY < 0)
			mReverseY = false;

		++mWidth;
		++mHeight;
		if (mWidth >= windowWidth)
			mWidth = 0;
		if (mHeight >= windowHeight)
			mHeight = 0;
#endif
	};

private:
	virtual bool        threadLoop()
	{
		initialize();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		do {
			draw();
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
		sp<SurfaceControl> control = session()->createSurface(String8("BootAnimation"),
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
		eglChooseConfig(display, attribs, &config, 1, &numConfigs);
		surface = eglCreateWindowSurface(display, config, handle->getNativeWindow(), NULL);
		context = eglCreateContext(display, config, NULL, NULL);
		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
			return NO_INIT;

		mDisplay = display;
		mContext = context;
		mSurface = surface;
		mWindowWidth = w;
		mWindowHeight = h;
		mFlingerSurfaceControl = control;
		mFlingerSurface = s;

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
	int         mWindowWidth;
	int         mWindowHeight;
	EGLDisplay  mDisplay;
	EGLDisplay  mContext;
	EGLDisplay  mSurface;
	sp<SurfaceControl> mFlingerSurfaceControl;
	sp<Surface> mFlingerSurface;

	// Texture handle
	GLuint mTexture = 0;

	// Draw texture coordinates and dimensions to loop through
	GLint mX = 0;
	GLint mY = 0;
	GLint mWidth = 0;
	GLint mHeight = 0;

	bool mReverseX = false;
	bool mReverseY = false;
};

int main(int argc, char** argv)
{
	InitRC::getInstance().Entry(argc, argv);

	sp<Sample> sample = new Sample();

	property_set("ctl.start", "");

	InitRC::getInstance().Run();

	return 0;
}

