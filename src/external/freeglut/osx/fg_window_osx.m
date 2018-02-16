#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

#include <Cocoa/Cocoa.h>

#if 0
int
Cocoa_CreateWindow(SFG_Window * window)
{ @autoreleasepool
    {
        //SDL_VideoData *videodata = (SDL_VideoData *) _this->driverdata;
        NSWindow *nswindow;
        //SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
        NSRect rect;
        SDL_Rect bounds;
        NSUInteger style;
        NSArray *screens = [NSScreen screens];
        
        Cocoa_GetDisplayBounds(_this, display, &bounds);
        rect.origin.x = window->x;
        rect.origin.y = window->y;
        rect.size.width = window->w;
        rect.size.height = window->h;
        ConvertNSRect([screens objectAtIndex:0], (window->flags & FULLSCREEN_MASK), &rect);
        
        style = GetWindowStyle(window);
        
        /* Figure out which screen to place this window */
        NSScreen *screen = nil;
        for (NSScreen *candidate in screens) {
            NSRect screenRect = [candidate frame];
            if (rect.origin.x >= screenRect.origin.x &&
                rect.origin.x < screenRect.origin.x + screenRect.size.width &&
                rect.origin.y >= screenRect.origin.y &&
                rect.origin.y < screenRect.origin.y + screenRect.size.height) {
                screen = candidate;
                rect.origin.x -= screenRect.origin.x;
                rect.origin.y -= screenRect.origin.y;
            }
        }
        
        @try {
            nswindow = [[SDLWindow alloc] initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:NO screen:screen];
        }
        @catch (NSException *e) {
            return SDL_SetError("%s", [[e reason] UTF8String]);
        }
        [nswindow setBackgroundColor:[NSColor blackColor]];
        
        if (videodata->allow_spaces) {
            SDL_assert(floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6);
            SDL_assert([nswindow respondsToSelector:@selector(toggleFullScreen:)]);
            /* we put FULLSCREEN_DESKTOP windows in their own Space, without a toggle button or menubar, later */
            if (window->flags & SDL_WINDOW_RESIZABLE) {
                /* resizable windows are Spaces-friendly: they get the "go fullscreen" toggle button on their titlebar. */
                [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
            }
        }
        
        /* Create a default view for this window */
        rect = [nswindow contentRectForFrameRect:[nswindow frame]];
        SDLView *contentView = [[SDLView alloc] initWithFrame:rect];
        [contentView setSDLWindow:window];
        
        if (window->flags & SDL_WINDOW_ALLOW_HIGHDPI) {
            if ([contentView respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)]) {
                [contentView setWantsBestResolutionOpenGLSurface:YES];
            }
        }
        
        [nswindow setContentView:contentView];
        [contentView release];
        
        /* Allow files and folders to be dragged onto the window by users */
        [nswindow registerForDraggedTypes:[NSArray arrayWithObject:(NSString *)kUTTypeFileURL]];
        
        if (SetupWindowData(_this, window, nswindow, SDL_TRUE) < 0) {
            [nswindow release];
            return -1;
        }
        return 0;
    }
}
#endif 


/*
 * window
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
}
void fgPlatformGlutSetIconTitle( const char* title )
{
}
void fgPlatformGlutSetWindowTitle( const char* title )
{
}
void fgPlatformHideWindow( SFG_Window* window )
{
}
void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                          GLboolean positionUse, int x, int y,
                          GLboolean sizeUse, int w, int h,
                          GLboolean gameMode, GLboolean isSubWindow )
{
    
}
void fgPlatformSetWindow ( SFG_Window *window )
{
}

