
/* An example of the minimal Win32 & OpenGL program.  It only works in
   16 bit color modes or higher (since it doesn't create a
   palette). */

#define WGL_WGLEXT_PROTOTYPES 1

#include "NativeWindow/NativeWindow.h"

#include <windows.h>			/* must include this before GL/gl.h */
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */
#include <stdio.h>
#include <vector>

#include "wglext.h"

void
display()
{
    /* rotate a triangle around */
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(0,  1);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(-1, -1);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(1, -1);
    glEnd();
    glFlush();
}


LONG WINAPI
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    static PAINTSTRUCT ps;

    switch(uMsg) {
	case WM_CREATE: {
		}
		break;
    case WM_PAINT:
	display();
	BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
	return 0;

    case WM_SIZE:
	glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
	PostMessage(hWnd, WM_PAINT, 0, 0);
	return 0;

    case WM_CHAR:
	switch (wParam) {
	case 27:			/* ESC key */
	    PostQuitMessage(0);
	    break;
	}
	return 0;

    case WM_CLOSE:
	PostQuitMessage(0);
	return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam); 
} 

HWND
CreateOpenGLWindow(char* title, int x, int y, int width, int height, 
		   BYTE type, DWORD flags)
{
    int         pf;
    HDC         hDC;
    HWND        hWnd;
    WNDCLASS    wc;
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;

    /* only register the window class once - use hInstance as a flag. */
    if (!hInstance) {
	hInstance = GetModuleHandle(NULL);
	wc.style         = CS_OWNDC;
	wc.lpfnWndProc   = (WNDPROC)WindowProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc)) {
	    MessageBox(NULL, "RegisterClass() failed:  "
		       "Cannot register window class.", "Error", MB_OK);
	    return NULL;
	}
    }
#if 1
    hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW |
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			x, y, width, height, NULL, NULL, hInstance, NULL);
#else
	flags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

	hWnd = CreateWindowEx(
		0,
		"OpenGL",
		"MINI",
		flags,
		x, y, width, height,
		(HWND)NULL,
		(HMENU)NULL,
		GetModuleHandle(NULL),
		(LPVOID)NULL
	);
#endif
    if (hWnd == NULL) {
		DWORD error = GetLastError();
	MessageBox(NULL, "CreateWindow() failed:  Cannot create a window.",
		   "Error", MB_OK);
	return NULL;
    }

    hDC = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
    pfd.iPixelType   = type;
    pfd.cColorBits   = 32;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
	MessageBox(NULL, "ChoosePixelFormat() failed:  "
		   "Cannot find a suitable pixel format.", "Error", MB_OK); 
	return 0;
    } 
 
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
	MessageBox(NULL, "SetPixelFormat() failed:  "
		   "Cannot set format specified.", "Error", MB_OK);
	return 0;
    } 

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    ReleaseDC(hWnd, hDC);

    return hWnd;
}    

int APIENTRY
WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
    HDC hDC;				/* device context */
    HGLRC hRC;				/* opengl context */
    HWND  hWnd;				/* window */
    MSG   msg;				/* message */

    hWnd = CreateOpenGLWindow("minimal", 0, 0, 256, 256, PFD_TYPE_RGBA, 0);
    if (hWnd == NULL)
	exit(1);

    hDC = GetDC(hWnd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

	ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&msg, hWnd, 0, 0)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    wglMakeCurrent(NULL, NULL);
    ReleaseDC(hWnd, hDC);
    wglDeleteContext(hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}



PIXELFORMATDESCRIPTOR GetDefaultPixelFormatDescriptor()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };
	pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_GENERIC_ACCELERATED | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24;
	pixelFormatDescriptor.cAlphaBits = 8;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cStencilBits = 8;
	pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

	return pixelFormatDescriptor;
}

static HGLRC dummyWGLContext = 0;

void
initialGLWindow(void)
{
	const LPSTR idcArrow = MAKEINTRESOURCEA(32512);

	//std::ostringstream stream;
	//stream << "ANGLE DisplayWGL " << std::internal << std::setw(10) << std::setfill('0') << mDisplay
	//	<< " Intermediate Window Class";
	//std::string className = stream.str();
	std::string className = "ANGLE DisplayWGL ";

	WNDCLASSA intermediateClassDesc = { 0 };
	intermediateClassDesc.style = CS_OWNDC;
	intermediateClassDesc.lpfnWndProc = DefWindowProc;
	intermediateClassDesc.cbClsExtra = 0;
	intermediateClassDesc.cbWndExtra = 0;
	intermediateClassDesc.hInstance = GetModuleHandle(nullptr);
	intermediateClassDesc.hIcon = nullptr;
	intermediateClassDesc.hCursor = LoadCursorA(nullptr, idcArrow);
	intermediateClassDesc.hbrBackground = 0;
	intermediateClassDesc.lpszMenuName = nullptr;
	intermediateClassDesc.lpszClassName = className.c_str();
	ATOM mWindowClass = RegisterClassA(&intermediateClassDesc);
	if (!mWindowClass)
	{
		return;
	}

	HWND dummyWindow = CreateWindowExA(0,
		reinterpret_cast<const char *>(mWindowClass),
		"ANGLE Dummy Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		nullptr,
		nullptr);
	if (!dummyWindow)
	{
		return;
	}

	HDC dummyDeviceContext = GetDC(dummyWindow);
	if (!dummyDeviceContext)
	{
		return;
	}

	const PIXELFORMATDESCRIPTOR pixelFormatDescriptor = GetDefaultPixelFormatDescriptor();

	int dummyPixelFormat = ChoosePixelFormat(dummyDeviceContext, &pixelFormatDescriptor);
	if (dummyPixelFormat == 0)
	{
		return;
	}

	if (!SetPixelFormat(dummyDeviceContext, dummyPixelFormat, &pixelFormatDescriptor))
	{
		return;
	}

	{
		std::vector<int> attribs;

		attribs.push_back(WGL_CONTEXT_MAJOR_VERSION_ARB);
		attribs.push_back(1);

		attribs.push_back(WGL_CONTEXT_MINOR_VERSION_ARB);
		attribs.push_back(0);

		attribs.push_back(0);
		attribs.push_back(0);

		//dummyWGLContext = wglCreateContextAttribsARB(dummyDeviceContext, nullptr, &attribs[0]);
	}

	if (!dummyWGLContext) {
		dummyWGLContext = wglCreateContext(dummyDeviceContext);
		if (!dummyDeviceContext)
		{
			return;
		}
	}

	if (!wglMakeCurrent(dummyDeviceContext, dummyWGLContext))
	{
		return;
	}

	// Destroy the dummy window and context
	wglMakeCurrent(dummyDeviceContext, nullptr);
	wglDeleteContext(dummyWGLContext);
	ReleaseDC(dummyWindow, dummyDeviceContext);
	DestroyWindow(dummyWindow);
}

int main(int argc, char** argv)
{
	android::NativeWindow* pWin = android::CreateNativeWindow();
	pWin->initialize("test_wgl", 720, 480);
	pWin->setVisible(true);

	HWND  hWnd = pWin->getNativeWindow();
	HDC   hDC  = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
	PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;

    int pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
	MessageBox(NULL, "ChoosePixelFormat() failed:  "
		   "Cannot find a suitable pixel format.", "Error", MB_OK); 
	return 0;
    } 
 
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
	MessageBox(NULL, "SetPixelFormat() failed:  "
		   "Cannot set format specified.", "Error", MB_OK);
	return 0;
    } 

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	HGLRC hRC  = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	//initialGLWindow();
	//wglMakeCurrent(hDC, dummyWGLContext);

	display();

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

			pWin->messageLoop();

			// OpenGL draw
			//display();

		} // while (mRunning)
	} // if (pWin)

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hWnd, hDC);
	wglDeleteContext(hRC);

	pWin->destroy();

	return 0;
}