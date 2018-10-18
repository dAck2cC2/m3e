
#include "NativeWindow/NativeWindow.h"
#include <EGL/egl.h>
#include <GLES/gl.h>


static EGLDisplay  mDisplay;
static EGLDisplay  mContext;
static EGLDisplay  mSurface;
static EGLint mWidth  = 0;
static EGLint mHeight = 0;

void display_gl()
{
	/* rotate a triangle around */
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2i(-1, -1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(1, -1);
	glEnd();
	glFlush();
}

void draw()
{
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
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	//glEnableVertexAttribArray(0);

	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	eglSwapBuffers(mDisplay, mSurface);
};

void
redraw(void)
{
#if 0
	static GLfloat r = 0.0f;
	r += 0.1f;
	if (r >= 1.0f) r = 0.0f;
	glClearColor(r, 0.0f, 0.0f, 0.0f);
#endif
	// Set the viewport
	glViewport(0, 0, mWidth, mHeight);

	/* clear color and depth buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glLoadIdentity();

	//glTranslatef(-1.5f, 0.0f, -6.0f);                 // Move Left 1.5 Units And Into The Screen 6.0

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);  /* blue */
	glVertex2i(0, 0);
	glColor3f(0.0, 1.0, 0.0);  /* green */
	glVertex2i(2, 2);
	glColor3f(1.0, 0.0, 0.0);  /* red */
	glVertex2i(-2, 2);
	glEnd();
	glFlush();  /* Single buffered, so needs a flush. */

	//glTranslatef(3.0f, 0.0f, 0.0f);                   // Move Right 3 Units

	eglSwapBuffers(mDisplay, mSurface);
}

int main(int argc, char** argv)
{
	android::NativeWindow* pWin = android::CreateNativeWindow();
	pWin->initialize("test_egl", 720, 480);
	pWin->setVisible(true);

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
	surface = eglCreateWindowSurface(display, config, pWin->getNativeWindow(), NULL);
	context = eglCreateContext(display, config, NULL, attribs);
	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
		return 0;

	mDisplay = display;
	mContext = context;
	mSurface = surface;
	mWidth = w;
	mHeight = h;

	//display_gl();

	if (pWin) {
		bool mRunning = true;

		while (mRunning) {
			// Clear events that the application did not process from this frame
			Event event;
			while (pWin->popEvent(&event)) {
				// If the application did not catch a close event, close now
				if (event.Type == Event::EVENT_CLOSED) {
					mRunning = false;
				}
			}

			if (!mRunning) {
				break;
			}

			// OpenGL draw
			//draw();
			redraw();

			pWin->messageLoop();

		} // while (mRunning)
	} // if (pWin)

	return 0;
}
