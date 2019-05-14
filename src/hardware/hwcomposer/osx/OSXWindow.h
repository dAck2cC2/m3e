
#ifndef SF_NATIVE_OSX_WINDOW_H_
#define SF_NATIVE_OSX_WINDOW_H_

#import <Cocoa/Cocoa.h>

#include "NativeWindow/NativeWindow.h"

class OSXWindow;

@interface WindowDelegate : NSObject
{
    OSXWindow *mWindow;
}
- (id) initWithWindow: (OSXWindow*) window;
@end

@interface ContentView : NSView
{
    OSXWindow *mWindow;
    NSTrackingArea *mTrackingArea;
    int mCurrentModifier;
}
- (id) initWithWindow: (OSXWindow*) window;
@end
    
class OSXWindow : public android::NativeWindow
{
  public:
    OSXWindow();
    ~OSXWindow();

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

    NSWindow *getNSWindow() const;

  private:
    NSWindow *mWindow;
    WindowDelegate *mDelegate;
    ContentView *mView;
};


#endif // SF_NATIVE_OSX_WINDOW_H_
