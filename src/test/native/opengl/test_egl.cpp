
#include <initrc.h>

#include <EGL/egl.h>

int main(int argc, char** argv)
{
    
    android::InitRC::getInstance().Entry(argc, argv);
    
	const EGLint attribs[] = {
		EGL_RED_SIZE,   8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE,  8,
		EGL_DEPTH_SIZE, 0,
		EGL_NONE
	};
	EGLint numConfigs;
	EGLConfig config;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, 0, 0);
	eglBindAPI(EGL_OPENGL_ES_API);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);


	return 0;
}
