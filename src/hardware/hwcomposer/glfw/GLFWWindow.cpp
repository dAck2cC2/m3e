
#include "glfw/GLFWWindow.h"

#include <utils/Mutex.h>
#include <glfw/glfw3native.h>

static android::Mutex gLckCnt("init count");
static uint64_t       gWndCnt = 0;

//extern "C" EGLNativeWindowType glfwGetNativeWindow(GLFWwindow* window);

GLFWWindow::GLFWWindow() :
    mWindow(NULL)
{
    android::AutoMutex _l(gLckCnt);
    
    if (gWndCnt == 0){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE, 0);
    }
    
    gWndCnt++;
}

GLFWWindow::~GLFWWindow()
{
    destroy();
    
    {
        android::AutoMutex _l(gLckCnt);
        
        --gWndCnt;
        
        if (gWndCnt == 0) {
            glfwTerminate();
        }
    }
}

bool GLFWWindow::initialize(const std::string &name, size_t width, size_t height)
{
    if (mWindow) {
        return true;
    }

    mWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    
    if (mWindow) {
        return true;
    } else {
        return false;
    }
}

void GLFWWindow::destroy()
{
    if (mWindow) {
        glfwDestroyWindow(mWindow);
        mWindow = NULL;
    }
}

EGLNativeWindowType GLFWWindow::getNativeWindow() const
{
    if (mWindow) {
#if defined(__APPLE__)
        return glfwGetCocoaLayer(mWindow);
#elif defined(_MSC_VER)
        return glfwGetWin32Window(mWindow);
#endif
    }
        
    return static_cast<EGLNativeWindowType>(0);
}

EGLNativeDisplayType GLFWWindow::getNativeDisplay() const
{
    // TODO(cwallez): implement it once we have defined what EGLNativeDisplayType is
    return static_cast<EGLNativeDisplayType>(0);
}

void GLFWWindow::messageLoop()
{
    glfwPollEvents();
}

void GLFWWindow::setMousePosition(int x, int y)
{
    //_glfwPlatformSetCursorPos(x, y);
}

bool GLFWWindow::setPosition(int x, int y)
{
    if (mWindow) {
        glfwSetWindowPos(mWindow, x, y);
        return true;
    } else {
        return false;
    }
}

bool GLFWWindow::resize(int width, int height)
{
    if (mWindow) {
        glfwSetWindowSize(mWindow, width, height);
        return true;
    } else {
        return false;
    }
}

void GLFWWindow::setVisible(bool isVisible)
{
    if (!mWindow) {
        return;
    }
    
    if (isVisible) {
        glfwShowWindow(mWindow);
    }
    else {
        glfwHideWindow(mWindow);
    }
}
void GLFWWindow::signalTestEvent()
{
}

android::sp<android::NativeWindow> android::CreateNativeWindow()
{
    return new GLFWWindow;
}
