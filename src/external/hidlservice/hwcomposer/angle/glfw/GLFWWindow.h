#ifndef SF_GLFW_WINDOW_H
#define SF_GLFW_WINDOW_H

#include "com/NativeWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GLFWWindow : public android::NativeWindow
{
public:
    GLFWWindow();
    ~GLFWWindow() override;

    bool initialize(const std::string &name, size_t width, size_t height) override;
    void destroy() override;

    EGLNativeWindowType getNativeWindow() const override;
    EGLNativeDisplayType getNativeDisplay() const override;

    void messageLoop() override;

    void setMousePosition(int x, int y) override;
    bool setPosition(int x, int y) override;
    bool resize(int width, int height) override;
    void setVisible(bool isVisible) override;

    void signalTestEvent() override;

private:
    GLFWwindow* mWindow;
};

#endif // SF_GLFW_WINDOW_H
