
#ifndef SF_NATIVE_WIN32_WINDOW_H
#define SF_NATIVE_WIN32_WINDOW_H

#include <windows.h>
#include <string>

#include "com/NativeWindow.h"
#include "com/Timer.h"

namespace android {

class Win32Window : public NativeWindow
{
  public:
    Win32Window();
    ~Win32Window() override;

    bool initialize(const std::string &name, size_t width, size_t height) override;
    void destroy() override;

    bool takeScreenshot(uint8_t *pixelData) override;

    EGLNativeWindowType getNativeWindow() const override;
    EGLNativeDisplayType getNativeDisplay() const override;

    void messageLoop() override;

    void pushEvent(Event event) override;

    void setMousePosition(int x, int y) override;
    bool setPosition(int x, int y) override;
    bool resize(int width, int height) override;
    void setVisible(bool isVisible) override;

    void signalTestEvent() override;

  private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::string mParentClassName;
    std::string mChildClassName;

    bool mIsVisible;
    Timer *mSetVisibleTimer;

    bool mIsMouseInWindow;

    EGLNativeWindowType mNativeWindow;
    EGLNativeWindowType mParentWindow;
    EGLNativeDisplayType mNativeDisplay;
};

} /* namespace android */

#endif  // SF_NATIVE_WIN32_WINDOW_H
