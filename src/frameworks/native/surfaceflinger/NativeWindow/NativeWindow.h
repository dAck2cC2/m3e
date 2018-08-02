

#ifndef SF_NATIVE_WINDOW_H
#define SF_NATIVE_WINDOW_H

#include <list>
#include <stdint.h>
#include <string>

#include <EGL/egl.h>

#include <utils/RefBase.h>

#include "NativeWindow/Event.h"

namespace android {

class NativeWindow : public RefBase
{
  public:
    NativeWindow();
    virtual ~NativeWindow();

    virtual bool initialize(const std::string &name, size_t width, size_t height) = 0;
    virtual void destroy() = 0;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    // Takes a screenshot of the window, returning the result as a mWidth * mHeight * 4
    // normalized unsigned byte BGRA array. Note that it will be used to test the window
    // manager's behavior so it needs to take an actual screenshot of the screen and not
    // just grab the pixels of the window. Returns if it was successful.
    virtual bool takeScreenshot(uint8_t *pixelData);

    virtual EGLNativeWindowType getNativeWindow() const = 0;
    virtual EGLNativeDisplayType getNativeDisplay() const = 0;

    virtual void messageLoop() = 0;

    bool popEvent(Event *event);
    virtual void pushEvent(Event event);

    virtual void setMousePosition(int x, int y) = 0;
    virtual bool setPosition(int x, int y) = 0;
    virtual bool resize(int width, int height) = 0;
    virtual void setVisible(bool isVisible) = 0;

    virtual void signalTestEvent() = 0;

    // Pops events look for the test event
    bool didTestEventFire();

  protected:
    int mX;
    int mY;
    int mWidth;
    int mHeight;

    std::list<Event> mEvents;
};

sp<NativeWindow> CreateNativeWindow();

} /* namespace android */

#endif // SF_NATIVE_WINDOW_H
