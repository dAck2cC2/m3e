#ifndef _RENDERER_GL_CGL_CONTEXTCOCOA_H_
#define _RENDERER_GL_CGL_CONTEXTCOCOA_H_

#import <Cocoa/Cocoa.h>
//#import <CoreGraphics/CGDirectDisplay.h>
#import <AppKit/NSWindow.h>


namespace rx
{

class WindowSurfaceCGL;
    
}  // namespace rx


@interface CGLOpenGLContext : NSOpenGLContext {
    int dirty;
    rx::WindowSurfaceCGL* window;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (void)scheduleUpdate;
- (void)updateIfNeeded;
- (void)setWindow:(rx::WindowSurfaceCGL *)window;

@end /* GLUTOpenGLContext */


CGLOpenGLContext* CreateOpenGLContext();
    
#endif //
