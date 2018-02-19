
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

/* -- PRIVATE FUNCTION DECLARATIONS ---------------------------------------- */

extern void Cocoa_InitMouse(SFG_Window* window);
extern void Cocoa_HandleMouseWheel(SFG_Window *window, NSEvent *event);
extern SFG_WindowContextType Cocoa_GL_CreateContext(SFG_Window * window);  /* fg_window_osx_gl.m */
extern int Cocoa_GL_MakeCurrent(SFG_Window * window, GLUTOpenGLContext* context);

extern void fghOnReshapeNotify(SFG_Window *window, int width, int height, GLboolean forceNotify);
extern void fghOnPositionNotify(SFG_Window *window, int x, int y, GLboolean forceNotify);

/* -- FUNCTION DEFINITION ---------------------------------------- */

void fghPlatformOnWindowStatusNotify(SFG_Window *window, GLboolean visState, GLboolean forceNotify)
{
    GLboolean notify = GL_FALSE;
    SFG_Window* child;
    
    if (window->State.Visible != visState)
    {
        window->State.Visible = visState;
#if 0
        /* If top level window (not a subwindow/child), and icon title text available, switch titles based on visibility state */
        if (!window->Parent && window->State.pWState.IconTitle)
        {
            if (visState)
            /* visible, set window title */
                SetWindowText( window->Window.Handle, window->State.pWState.WindowTitle );
            else
            /* not visible, set icon title */
                SetWindowText( window->Window.Handle, window->State.pWState.IconTitle );
        }
#endif
        notify = GL_TRUE;
    }
    
    if (notify || forceNotify)
    {
        SFG_Window *saved_window = fgStructure.CurrentWindow;
        
        /* On win32 we only have two states, window displayed and window not displayed (iconified)
         * We map these to GLUT_FULLY_RETAINED and GLUT_HIDDEN respectively.
         */
        INVOKE_WCB( *window, WindowStatus, ( visState ? GLUT_FULLY_RETAINED:GLUT_HIDDEN ) );
        fgSetWindow( saved_window );
    }
    
    /* Also set windowStatus/visibility state for children */
    for( child = ( SFG_Window * )window->Children.First;
        child;
        child = ( SFG_Window * )child->Node.Next )
    {
        fghPlatformOnWindowStatusNotify(child, visState, GL_FALSE); /* No need to propagate forceNotify. Childs get this from their own INIT_WORK */
    }
}

void
Cocoa_ShowWindow(SFG_Window * window)
{ @autoreleasepool
    {
        SFG_PlatformContext *windowData = (&window->Window.pContext);
        NSWindow *nswindow = windowData->nswindow;
        
        if (![nswindow isMiniaturized]) {
            [windowData->listener pauseVisibleObservation];
            [nswindow makeKeyAndOrderFront:nil];
            [windowData->listener resumeVisibleObservation];
        }
    }
}

void
Cocoa_HideWindow(SFG_Window * window)
{ @autoreleasepool
    {
        NSWindow *nswindow = window->Window.Handle;
        
        [nswindow orderOut:nil];
    }
}


@interface GLUTWindow : NSWindow <NSDraggingDestination>
/* These are needed for borderless/fullscreen windows */
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
- (void)sendEvent:(NSEvent *)event;
- (void)doCommandBySelector:(SEL)aSelector;

/* Handle drag-and-drop of files onto the SDL window. */
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (BOOL)wantsPeriodicDraggingUpdates;
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;

- (SFG_Window*)findWindow;
@end

@implementation GLUTWindow

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    /* Only allow using the macOS native fullscreen toggle menubar item if the
     * window is resizable and not in a SDL fullscreen mode.
     */
    if ([menuItem action] == @selector(toggleFullScreen:)) {
        SFG_Window *window = [self findWindow];
        if (window == NULL) {
            return NO;
            /*
             } else if ((window->flags & (SDL_WINDOW_FULLSCREEN|SDL_WINDOW_FULLSCREEN_DESKTOP)) != 0) {
             return NO;
             } else if ((window->flags & SDL_WINDOW_RESIZABLE) == 0) {
             return NO;
             */
        }
    }
    return [super validateMenuItem:menuItem];
}

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

- (void)sendEvent:(NSEvent *)event
{
    [super sendEvent:event];
    
    if ([event type] != NSEventTypeLeftMouseUp) {
        return;
    }
    
    id delegate = [self delegate];
    if (![delegate isKindOfClass:[Cocoa_WindowListener class]]) {
        return;
    }
    
    if ([delegate isMoving]) {
        [delegate windowDidFinishMoving];
    }
}

/* We'll respond to selectors by doing nothing so we don't beep.
 * The escape key gets converted to a "cancel" selector, etc.
 */
- (void)doCommandBySelector:(SEL)aSelector
{
    /*NSLog(@"doCommandBySelector: %@\n", NSStringFromSelector(aSelector));*/
}

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    if (([sender draggingSourceOperationMask] & NSDragOperationGeneric) == NSDragOperationGeneric) {
        return NSDragOperationGeneric;
    }
    
    return NSDragOperationNone; /* no idea what to do with this, reject it. */
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{ @autoreleasepool
    {
        NSPasteboard *pasteboard = [sender draggingPasteboard];
        NSArray *types = [NSArray arrayWithObject:NSFilenamesPboardType];
        NSString *desiredType = [pasteboard availableTypeFromArray:types];
        //SFG_Window *window = [self findWindow];
        
        if (desiredType == nil) {
            return NO;  /* can't accept anything that's being dropped here. */
        }
        
        NSData *data = [pasteboard dataForType:desiredType];
        if (data == nil) {
            return NO;
        }
        
        FREEGLUT_INTERNAL_ERROR_EXIT(([desiredType isEqualToString:NSFilenamesPboardType]), "desiredType is not PboardType", "performDragOperation");
        NSArray *array = [pasteboard propertyListForType:@"NSFilenamesPboardType"];
        
        for (NSString *path in array) {
            NSURL *fileURL = [NSURL fileURLWithPath:path];
            NSNumber *isAlias = nil;
            
            [fileURL getResourceValue:&isAlias forKey:NSURLIsAliasFileKey error:nil];
            
            /* If the URL is an alias, resolve it. */
            if ([isAlias boolValue]) {
                NSURLBookmarkResolutionOptions opts = NSURLBookmarkResolutionWithoutMounting | NSURLBookmarkResolutionWithoutUI;
                NSData *bookmark = [NSURL bookmarkDataWithContentsOfURL:fileURL error:nil];
                if (bookmark != nil) {
                    NSURL *resolvedURL = [NSURL URLByResolvingBookmarkData:bookmark
                                                                   options:opts
                                                             relativeToURL:nil
                                                       bookmarkDataIsStale:nil
                                                                     error:nil];
                    
                    if (resolvedURL != nil) {
                        fileURL = resolvedURL;
                    }
                }
            }
            
            //if (!SDL_SendDropFile(sdlwindow, [[fileURL path] UTF8String])) {
            //    return NO;
            //}
        }
        
        //SDL_SendDropComplete(sdlwindow);
        return YES;
    }}

- (BOOL)wantsPeriodicDraggingUpdates
{
    return NO;
}

- (SFG_Window*)findWindow
{
    SFG_Window *window = fgWindowByHandle(self);
    
    return window;
}

@end // GLUTWindow


static fg_time_t s_moveHack;

static void ConvertNSRect(NSScreen *screen, NSRect *r)
{
    r->origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - r->origin.y - r->size.height;
}

static void
ScheduleContextUpdates(SFG_Window *data)
{
    NSOpenGLContext *currentContext = [NSOpenGLContext currentContext];
    NSMutableArray *contexts = data->Window.pContext.nscontexts;
    @synchronized (contexts) {
        for (GLUTOpenGLContext *context in contexts) {
            if (context == currentContext) {
                [context update];
            } else {
                [context scheduleUpdate];
            }
        }
    }
}

static NSUInteger
GetWindowStyle(SFG_Window * window)
{
    NSUInteger style = 0;
    
    if (window->State.IsFullscreen) {
        style = NSWindowStyleMaskBorderless;
    } else {
        if (window->IsMenu) {
            style = NSWindowStyleMaskBorderless;
        } else {
            style = (NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable);
            
            style |= NSWindowStyleMaskResizable;
        }
    }
    return style;
}

static GLboolean
SetWindowStyle(SFG_Window * window, NSUInteger style)
{
    SFG_PlatformContext *data = &(window->Window.pContext);
    NSWindow *nswindow = data->nswindow;
    
    /* The view responder chain gets messed with during setStyleMask */
    if ([[nswindow contentView] nextResponder] == data->listener) {
        [[nswindow contentView] setNextResponder:nil];
    }
    
    [nswindow setStyleMask:style];
    
    /* The view responder chain gets messed with during setStyleMask */
    if ([[nswindow contentView] nextResponder] != data->listener) {
        [[nswindow contentView] setNextResponder:data->listener];
    }
    
    return GL_TRUE;
}


@implementation Cocoa_WindowListener

- (void)listen:(SFG_WindowHandleType)data
{
    NSNotificationCenter *center;
    NSWindow *window = data;
    NSView *view = [window contentView];
    
    _window = data;
    observingVisible = YES;
    wasCtrlLeft = NO;
    wasVisible = [window isVisible];
    isFullscreenSpace = NO;
    inFullscreenTransition = NO;
    pendingWindowOperation = PENDING_OPERATION_NONE;
    isMoving = NO;
    isDragAreaRunning = NO;
    
    center = [NSNotificationCenter defaultCenter];
    
    if ([window delegate] != nil) {
        [center addObserver:self selector:@selector(windowDidExpose:) name:NSWindowDidExposeNotification object:window];
        [center addObserver:self selector:@selector(windowDidMove:) name:NSWindowDidMoveNotification object:window];
        [center addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidMiniaturize:) name:NSWindowDidMiniaturizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidDeminiaturize:) name:NSWindowDidDeminiaturizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidBecomeKey:) name:NSWindowDidBecomeKeyNotification object:window];
        [center addObserver:self selector:@selector(windowDidResignKey:) name:NSWindowDidResignKeyNotification object:window];
        [center addObserver:self selector:@selector(windowDidChangeBackingProperties:) name:NSWindowDidChangeBackingPropertiesNotification object:window];
        [center addObserver:self selector:@selector(windowWillEnterFullScreen:) name:NSWindowWillEnterFullScreenNotification object:window];
        [center addObserver:self selector:@selector(windowDidEnterFullScreen:) name:NSWindowDidEnterFullScreenNotification object:window];
        [center addObserver:self selector:@selector(windowWillExitFullScreen:) name:NSWindowWillExitFullScreenNotification object:window];
        [center addObserver:self selector:@selector(windowDidExitFullScreen:) name:NSWindowDidExitFullScreenNotification object:window];
        [center addObserver:self selector:@selector(windowDidFailToEnterFullScreen:) name:@"NSWindowDidFailToEnterFullScreenNotification" object:window];
        [center addObserver:self selector:@selector(windowDidFailToExitFullScreen:) name:@"NSWindowDidFailToExitFullScreenNotification" object:window];
    } else {
        [window setDelegate:self];
    }
    
    /* Haven't found a delegate / notification that triggers when the window is
     * ordered out (is not visible any more). You can be ordered out without
     * minimizing, so DidMiniaturize doesn't work. (e.g. -[NSWindow orderOut:])
     */
    [window addObserver:self
             forKeyPath:@"visible"
                options:NSKeyValueObservingOptionNew
                context:NULL];
    
    [window setNextResponder:self];
    [window setAcceptsMouseMovedEvents:YES];
    
    [view setNextResponder:self];
    
    [view setAcceptsTouchEvents:YES];
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    SFG_Window *window = fgWindowByHandle(_window);

    if (!observingVisible) {
        return;
    }
    
    if (object == _window && [keyPath isEqualToString:@"visible"]) {
        int newVisibility = [[change objectForKey:@"new"] intValue];
        if (newVisibility) {
            fghPlatformOnWindowStatusNotify(window, GL_TRUE, GL_FALSE);
            window->State.WorkMask |= GLUT_DISPLAY_WORK;
        } else {
            fghPlatformOnWindowStatusNotify(window, GL_FALSE, GL_FALSE);
            window->State.WorkMask &= ~GLUT_DISPLAY_WORK;
        }
    }
}

-(void) pauseVisibleObservation
{
    observingVisible = NO;
    wasVisible = [_window isVisible];
}

-(void) resumeVisibleObservation
{
    SFG_Window *window = fgWindowByHandle(_window);

    BOOL isVisible = [_window isVisible];
    observingVisible = YES;
    if (wasVisible != isVisible) {
        if (isVisible) {
            fghPlatformOnWindowStatusNotify(window, GL_TRUE, GL_FALSE);
            window->State.WorkMask |= GLUT_DISPLAY_WORK;
        } else {
            fghPlatformOnWindowStatusNotify(window, GL_FALSE, GL_FALSE);
            window->State.WorkMask &= ~GLUT_DISPLAY_WORK;
        }
        
        wasVisible = isVisible;
    }
}

-(BOOL) setFullscreenSpace:(BOOL) state
{
    //SFG_Window *window = fgWindowByHandle(_window);
    NSWindow *nswindow = _window;
#if 0
    SDL_VideoData *videodata = ((SDL_WindowData *) window->driverdata)->videodata;
    
    if (!videodata->allow_spaces) {
        return NO;  /* Spaces are forcibly disabled. */
    } else if (state && ((window->flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        return NO;  /* we only allow you to make a Space on FULLSCREEN_DESKTOP windows. */
    } else if (!state && ((window->last_fullscreen_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        return NO;  /* we only handle leaving the Space on windows that were previously FULLSCREEN_DESKTOP. */
    } else
#endif
        if (state == isFullscreenSpace) {
        return YES;  /* already there. */
    }
    
    if (inFullscreenTransition) {
        if (state) {
            [self addPendingWindowOperation:PENDING_OPERATION_ENTER_FULLSCREEN];
        } else {
            [self addPendingWindowOperation:PENDING_OPERATION_LEAVE_FULLSCREEN];
        }
        return YES;
    }
    inFullscreenTransition = YES;
    
    /* you need to be FullScreenPrimary, or toggleFullScreen doesn't work. Unset it again in windowDidExitFullScreen. */
    [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
    [nswindow performSelectorOnMainThread: @selector(toggleFullScreen:) withObject:nswindow waitUntilDone:NO];
    return YES;
}

-(BOOL) isInFullscreenSpace
{
    return isFullscreenSpace;
}

-(BOOL) isInFullscreenSpaceTransition
{
    return inFullscreenTransition;
}

-(void) addPendingWindowOperation:(PendingWindowOperation) operation
{
    pendingWindowOperation = operation;
}

- (void)close
{
    NSNotificationCenter *center;
    NSWindow *window = _window;
    NSView *view = [window contentView];
    
    center = [NSNotificationCenter defaultCenter];
    
    if ([window delegate] != self) {
        [center removeObserver:self name:NSWindowDidExposeNotification object:window];
        [center removeObserver:self name:NSWindowDidMoveNotification object:window];
        [center removeObserver:self name:NSWindowDidResizeNotification object:window];
        [center removeObserver:self name:NSWindowDidMiniaturizeNotification object:window];
        [center removeObserver:self name:NSWindowDidDeminiaturizeNotification object:window];
        [center removeObserver:self name:NSWindowDidBecomeKeyNotification object:window];
        [center removeObserver:self name:NSWindowDidResignKeyNotification object:window];
        [center removeObserver:self name:NSWindowDidChangeBackingPropertiesNotification object:window];
        [center removeObserver:self name:NSWindowWillEnterFullScreenNotification object:window];
        [center removeObserver:self name:NSWindowDidEnterFullScreenNotification object:window];
        [center removeObserver:self name:NSWindowWillExitFullScreenNotification object:window];
        [center removeObserver:self name:NSWindowDidExitFullScreenNotification object:window];
        [center removeObserver:self name:@"NSWindowDidFailToEnterFullScreenNotification" object:window];
        [center removeObserver:self name:@"NSWindowDidFailToExitFullScreenNotification" object:window];
    } else {
        [window setDelegate:nil];
    }
    
    [window removeObserver:self forKeyPath:@"visible"];
    
    if ([window nextResponder] == self) {
        [window setNextResponder:nil];
    }
    if ([view nextResponder] == self) {
        [view setNextResponder:nil];
    }
}

- (BOOL)isMoving
{
    return isMoving;
}

-(void) setPendingMoveX:(int)x Y:(int)y
{
    pendingWindowWarpX = x;
    pendingWindowWarpY = y;
}

- (void)windowDidFinishMoving
{
    if ([self isMoving]) {
        isMoving = NO;
#if 0
        SDL_Mouse *mouse = SDL_GetMouse();
        if (pendingWindowWarpX != INT_MAX && pendingWindowWarpY != INT_MAX) {
            mouse->WarpMouseGlobal(pendingWindowWarpX, pendingWindowWarpY);
            pendingWindowWarpX = pendingWindowWarpY = INT_MAX;
        }
        if (mouse->relative_mode && !mouse->relative_mode_warp && mouse->focus == _data->window) {
            mouse->SetRelativeMouseMode(SDL_TRUE);
        }
#endif
    }
}

- (BOOL)windowShouldClose:(id)sender
{
    SFG_Window *window = fgWindowByHandle(_window);
    fgDestroyWindow(window);
    if ( fgState.ActionOnWindowClose != GLUT_ACTION_CONTINUE_EXECUTION ) {
        return YES;
    } else {
        return NO;
    }
}

- (void)windowDidExpose:(NSNotification *)aNotification
{
    //SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_EXPOSED, 0, 0);
}

- (void)windowWillMove:(NSNotification *)aNotification
{
    if ([_window isKindOfClass:[GLUTWindow class]]) {
        pendingWindowWarpX = pendingWindowWarpY = INT_MAX;
        isMoving = YES;
    }
}

- (void)windowDidMove:(NSNotification *)aNotification
{
    int x, y;
    SFG_Window *window = fgWindowByHandle(_window);
    NSWindow *nswindow = _window;
    NSRect rect = [nswindow contentRectForFrameRect:[nswindow frame]];
    ConvertNSRect([nswindow screen], &rect);
    
    if (inFullscreenTransition) {
        /* We'll take care of this at the end of the transition */
        return;
    }
    
    if (s_moveHack) {
        GLboolean blockMove = ((fgSystemTime() - fgState.Time - s_moveHack) < 500);
        
        s_moveHack = 0;
        
        if (blockMove) {
            /* Cocoa is adjusting the window in response to a mode change */
            rect.origin.x = window->State.Xpos;
            rect.origin.y = window->State.Ypos;
            ConvertNSRect([nswindow screen], &rect);
            [nswindow setFrameOrigin:rect.origin];
            return;
        }
    }
    
    x = (int)rect.origin.x;
    y = (int)rect.origin.y;
    
    ScheduleContextUpdates(window);
    
    fghOnPositionNotify(window, x, y, GL_FALSE);
}

- (void)windowDidResize:(NSNotification *)aNotification
{
    if (inFullscreenTransition) {
        /* We'll take care of this at the end of the transition */
        return;
    }
    
    SFG_Window *window = fgWindowByHandle(_window);
    NSWindow *nswindow = _window;
    int x, y, w, h;
    NSRect rect = [nswindow contentRectForFrameRect:[nswindow frame]];
    ConvertNSRect([nswindow screen], &rect);
    x = (int)rect.origin.x;
    y = (int)rect.origin.y;
    w = (int)rect.size.width;
    h = (int)rect.size.height;
    
    //if (SDL_IsShapedWindow(window)) {
    //    Cocoa_ResizeWindowShape(window);
    //}
    
    ScheduleContextUpdates(window);
    
    /* The window can move during a resize event, such as when maximizing
     or resizing from a corner */
    fghOnPositionNotify(window, x, y, GL_FALSE);
    fghOnReshapeNotify(window, w, h, GL_FALSE);
    
    const BOOL zoomed = [nswindow isZoomed];
    if (!zoomed && !window->State.Visible) {
        fghPlatformOnWindowStatusNotify(window,GL_TRUE,GL_FALSE);
    }
}

- (void)windowDidMiniaturize:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);
    fghPlatformOnWindowStatusNotify(window,GL_FALSE,GL_FALSE);
}

- (void)windowDidDeminiaturize:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);
    if (!window->State.Visible) {
        fghPlatformOnWindowStatusNotify(window,GL_TRUE,GL_FALSE);
    }
}

- (void)windowDidBecomeKey:(NSNotification *)aNotification
{
#if 0
    SFG_Window *window = fgWindowByHandle(_window);
    SDL_Mouse *mouse = SDL_GetMouse();
    
    /* We're going to get keyboard events, since we're key. */
    /* This needs to be done before restoring the relative mouse mode. */
    SDL_SetKeyboardFocus(window);
    
    if (mouse->relative_mode && !mouse->relative_mode_warp && ![self isMoving]) {
        mouse->SetRelativeMouseMode(SDL_TRUE);
    }
    
    /* If we just gained focus we need the updated mouse position */
    if (!mouse->relative_mode) {
        NSPoint point;
        int x, y;
        
        point = [_data->nswindow mouseLocationOutsideOfEventStream];
        x = (int)point.x;
        y = (int)(window->h - point.y);
        
        if (x >= 0 && x < window->w && y >= 0 && y < window->h) {
            SDL_SendMouseMotion(window, 0, 0, x, y);
        }
    }
    
    /* Check to see if someone updated the clipboard */
    Cocoa_CheckClipboardUpdate(_data->videodata);
    
    if ((isFullscreenSpace) && ((window->flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        [NSMenu setMenuBarVisible:NO];
    }
    
    const unsigned int newflags = [NSEvent modifierFlags] & NSEventModifierFlagCapsLock;
    _data->videodata->modifierFlags = (_data->videodata->modifierFlags & ~NSEventModifierFlagCapsLock) | newflags;
    SDL_ToggleModState(KMOD_CAPS, newflags != 0);
#endif
}

- (void)windowDidResignKey:(NSNotification *)aNotification
{
#if 0
    SDL_Mouse *mouse = SDL_GetMouse();
    if (mouse->relative_mode && !mouse->relative_mode_warp) {
        mouse->SetRelativeMouseMode(SDL_FALSE);
    }
    
    /* Some other window will get mouse events, since we're not key. */
    if (SDL_GetMouseFocus() == _data->window) {
        SDL_SetMouseFocus(NULL);
    }
    
    /* Some other window will get keyboard events, since we're not key. */
    if (SDL_GetKeyboardFocus() == _data->window) {
        SDL_SetKeyboardFocus(NULL);
    }
#endif
    if (isFullscreenSpace) {
        [NSMenu setMenuBarVisible:YES];
    }
}

- (void)windowDidChangeBackingProperties:(NSNotification *)aNotification
{
    NSNumber *oldscale = [[aNotification userInfo] objectForKey:NSBackingPropertyOldScaleFactorKey];
    
    if (inFullscreenTransition) {
        return;
    }
    
    if ([oldscale doubleValue] != [_window backingScaleFactor]) {
        /* Force a resize event when the backing scale factor changes. */
        SFG_Window *window = fgWindowByHandle(_window);
        window->State.Width = 0;
        window->State.Height = 0;
        [self windowDidResize:aNotification];
    }
}

- (void)windowWillEnterFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);

    SetWindowStyle(window, (NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskResizable));
    
    isFullscreenSpace = YES;
    inFullscreenTransition = YES;
}

- (void)windowDidFailToEnterFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);

    if (window->Window.pContext.is_destroying) {
        return;
    }
    
    SetWindowStyle(window, GetWindowStyle(window));
    
    isFullscreenSpace = NO;
    inFullscreenTransition = NO;
    
    [self windowDidExitFullScreen:nil];
}

- (void)windowDidEnterFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);
    SFG_PlatformContext *data = (&window->Window.pContext);
    NSWindow *nswindow = data->nswindow;
    
    inFullscreenTransition = NO;
    
    if (pendingWindowOperation == PENDING_OPERATION_LEAVE_FULLSCREEN) {
        pendingWindowOperation = PENDING_OPERATION_NONE;
        [self setFullscreenSpace:NO];
    } else {
        /* Unset the resizable flag.
         This is a workaround for https://bugzilla.libsdl.org/show_bug.cgi?id=3697
         */
        SetWindowStyle(window, [nswindow styleMask] & (~NSWindowStyleMaskResizable));
        /*
        if ((window->flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
            [NSMenu setMenuBarVisible:NO];
        }
        */
        pendingWindowOperation = PENDING_OPERATION_NONE;
        /* Force the size change event in case it was delivered earlier
         while the window was still animating into place.
         */
        window->State.Width = 0;
        window->State.Height = 0;
        [self windowDidMove:aNotification];
        [self windowDidResize:aNotification];
    }
}

- (void)windowWillExitFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);

    isFullscreenSpace = NO;
    inFullscreenTransition = YES;
    
    /* As of OS X 10.11, the window seems to need to be resizable when exiting
     a Space, in order for it to resize back to its windowed-mode size.
     */
    SetWindowStyle(window, GetWindowStyle(window) | NSWindowStyleMaskResizable);
}

- (void)windowDidFailToExitFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);

    if (window->Window.pContext.is_destroying) {
        return;
    }
    
    SetWindowStyle(window, (NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskResizable));
    
    isFullscreenSpace = YES;
    inFullscreenTransition = NO;
    
    [self windowDidEnterFullScreen:nil];
}

- (void)windowDidExitFullScreen:(NSNotification *)aNotification
{
    SFG_Window *window = fgWindowByHandle(_window);
    NSWindow *nswindow = _window;
    
    inFullscreenTransition = NO;
    
    SetWindowStyle(window, GetWindowStyle(window));
    
    [nswindow setLevel:kCGNormalWindowLevel];
    
    if (pendingWindowOperation == PENDING_OPERATION_ENTER_FULLSCREEN) {
        pendingWindowOperation = PENDING_OPERATION_NONE;
        [self setFullscreenSpace:YES];
    } else if (pendingWindowOperation == PENDING_OPERATION_MINIMIZE) {
        pendingWindowOperation = PENDING_OPERATION_NONE;
        [nswindow miniaturize:nil];
    } else {
        /* Adjust the fullscreen toggle button and readd menu now that we're here. */
        //if (window->flags & SDL_WINDOW_RESIZABLE)
        {
            /* resizable windows are Spaces-friendly: they get the "go fullscreen" toggle button on their titlebar. */
            [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
        } /* else {
            [nswindow setCollectionBehavior:NSWindowCollectionBehaviorManaged];
        } */
        [NSMenu setMenuBarVisible:YES];
        
        pendingWindowOperation = PENDING_OPERATION_NONE;
        
#if 0
        /* This fixed bug 3719, which is that changing window size while fullscreen
         doesn't take effect when leaving fullscreen, but introduces bug 3809,
         which is that a maximized window doesn't go back to normal size when
         restored, so this code is disabled until we can properly handle the
         beginning and end of maximize and restore.
         */
        /* Restore windowed size and position in case it changed while fullscreen */
        {
            NSRect rect;
            rect.origin.x = window->windowed.x;
            rect.origin.y = window->windowed.y;
            rect.size.width = window->windowed.w;
            rect.size.height = window->windowed.h;
            ConvertNSRect([nswindow screen], NO, &rect);
            
            s_moveHack = 0;
            [nswindow setContentSize:rect.size];
            [nswindow setFrameOrigin:rect.origin];
            s_moveHack = fgSystemTime() - fgState.Time;
        }
#endif /* 0 */
        
        /* Force the size change event in case it was delivered earlier
         while the window was still animating into place.
         */
        window->State.Width = 0;
        window->State.Height = 0;
        [self windowDidMove:aNotification];
        [self windowDidResize:aNotification];
        
        /* FIXME: Why does the window get hidden? */
        if (window->State.Visible) {
            Cocoa_ShowWindow(window);
        }
    }
}

-(NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions
{
    /*
    if ((_data->window->flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
        return NSApplicationPresentationFullScreen | NSApplicationPresentationHideDock | NSApplicationPresentationHideMenuBar;
    } else */ {
        return proposedOptions;
    }
}


/* We'll respond to key events by doing nothing so we don't beep.
 * We could handle key messages here, but we lose some in the NSApp dispatch,
 * where they get converted to action messages, etc.
 */
- (void)flagsChanged:(NSEvent *)theEvent
{
    /*Cocoa_HandleKeyEvent(SDL_GetVideoDevice(), theEvent);*/
}
- (void)keyDown:(NSEvent *)theEvent
{
    /*Cocoa_HandleKeyEvent(SDL_GetVideoDevice(), theEvent);*/
}
- (void)keyUp:(NSEvent *)theEvent
{
    /*Cocoa_HandleKeyEvent(SDL_GetVideoDevice(), theEvent);*/
}

/* We'll respond to selectors by doing nothing so we don't beep.
 * The escape key gets converted to a "cancel" selector, etc.
 */
- (void)doCommandBySelector:(SEL)aSelector
{
    /*NSLog(@"doCommandBySelector: %@\n", NSStringFromSelector(aSelector));*/
}

- (BOOL)processHitTest:(NSEvent *)theEvent
{
    FREEGLUT_INTERNAL_ERROR_EXIT((isDragAreaRunning == [_window isMovableByWindowBackground]), "Drag Area is not running", "processHitTest");
#if 0
    if (_data->window->hit_test) {  /* if no hit-test, skip this. */
        const NSPoint location = [theEvent locationInWindow];
        const SDL_Point point = { (int) location.x, _data->window->h - (((int) location.y)-1) };
        const SDL_HitTestResult rc = _data->window->hit_test(_data->window, &point, _data->window->hit_test_data);
        if (rc == SDL_HITTEST_DRAGGABLE) {
            if (!isDragAreaRunning) {
                isDragAreaRunning = YES;
                [_data->nswindow setMovableByWindowBackground:YES];
            }
            return YES;  /* dragging! */
        }
    }
#endif
    if (isDragAreaRunning) {
        isDragAreaRunning = NO;
        [_window setMovableByWindowBackground:NO];
        return YES;  /* was dragging, drop event. */
    }
    
    return NO;  /* not a special area, carry on. */
}

- (void)mouseDown:(NSEvent *)theEvent
{
#if 0
    int button;
    int clicks;
    
    /* Ignore events that aren't inside the client area (i.e. title bar.) */
    if ([theEvent window]) {
        NSRect windowRect = [[[theEvent window] contentView] frame];
        if (!NSMouseInRect([theEvent locationInWindow], windowRect, NO)) {
            return;
        }
    }
    
    if ([self processHitTest:theEvent]) {
        //SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_HIT_TEST, 0, 0);
        return;  /* dragging, drop event. */
    }

    switch ([theEvent buttonNumber]) {
        case 0:
            if (([theEvent modifierFlags] & NSEventModifierFlagControl) &&
                GetHintCtrlClickEmulateRightClick()) {
                wasCtrlLeft = YES;
                button = SDL_BUTTON_RIGHT;
            } else {
                wasCtrlLeft = NO;
                button = SDL_BUTTON_LEFT;
            }
            break;
        case 1:
            button = SDL_BUTTON_RIGHT;
            break;
        case 2:
            button = SDL_BUTTON_MIDDLE;
            break;
        default:
            button = (int) [theEvent buttonNumber] + 1;
            break;
    }
    
    clicks = (int) [theEvent clickCount];
    SDL_SendMouseButtonClicks(_data->window, 0, SDL_PRESSED, button, clicks);
#endif
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    [self mouseDown:theEvent];
}

- (void)otherMouseDown:(NSEvent *)theEvent
{
    [self mouseDown:theEvent];
}

- (void)mouseUp:(NSEvent *)theEvent
{
#if 0
    int button;
    int clicks;
    
    if ([self processHitTest:theEvent]) {
        //SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_HIT_TEST, 0, 0);
        return;  /* stopped dragging, drop event. */
    }

    switch ([theEvent buttonNumber]) {
        case 0:
            if (wasCtrlLeft) {
                button = SDL_BUTTON_RIGHT;
                wasCtrlLeft = NO;
            } else {
                button = SDL_BUTTON_LEFT;
            }
            break;
        case 1:
            button = SDL_BUTTON_RIGHT;
            break;
        case 2:
            button = SDL_BUTTON_MIDDLE;
            break;
        default:
            button = (int) [theEvent buttonNumber] + 1;
            break;
    }
    
    clicks = (int) [theEvent clickCount];
    SDL_SendMouseButtonClicks(_data->window, 0, SDL_RELEASED, button, clicks);
#endif
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    [self mouseUp:theEvent];
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
    [self mouseUp:theEvent];
}

- (void)mouseMoved:(NSEvent *)theEvent
{
#if 0
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Window *window = _data->window;
    NSPoint point;
    int x, y;
    
    if ([self processHitTest:theEvent]) {
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_HIT_TEST, 0, 0);
        return;  /* dragging, drop event. */
    }
    
    if (mouse->relative_mode) {
        return;
    }
    
    point = [theEvent locationInWindow];
    x = (int)point.x;
    y = (int)(window->h - point.y);
    
    if (window->flags & SDL_WINDOW_INPUT_GRABBED) {
        if (x < 0 || x >= window->w || y < 0 || y >= window->h) {
            if (x < 0) {
                x = 0;
            } else if (x >= window->w) {
                x = window->w - 1;
            }
            if (y < 0) {
                y = 0;
            } else if (y >= window->h) {
                y = window->h - 1;
            }
            
#if !SDL_MAC_NO_SANDBOX
            CGPoint cgpoint;
            
            /* When SDL_MAC_NO_SANDBOX is set, this is handled by
             * SDL_cocoamousetap.m.
             */
            
            cgpoint.x = window->x + x;
            cgpoint.y = window->y + y;
            
            CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, cgpoint);
            CGAssociateMouseAndMouseCursorPosition(YES);
            
            Cocoa_HandleMouseWarp(cgpoint.x, cgpoint.y);
#endif
        }
    }
    SDL_SendMouseMotion(window, 0, 0, x, y);
#endif
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    Cocoa_HandleMouseWheel(fgWindowByHandle(_window), theEvent);
}

- (void)touchesBeganWithEvent:(NSEvent *) theEvent
{
    NSSet *touches = [theEvent touchesMatchingPhase:NSTouchPhaseAny inView:nil];
    int existingTouchCount = 0;
    
    for (NSTouch* touch in touches) {
        if ([touch phase] != NSTouchPhaseBegan) {
            existingTouchCount++;
        }
    }

    [self handleTouches:NSTouchPhaseBegan withEvent:theEvent];
}

- (void)touchesMovedWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:NSTouchPhaseMoved withEvent:theEvent];
}

- (void)touchesEndedWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:NSTouchPhaseEnded withEvent:theEvent];
}

- (void)touchesCancelledWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:NSTouchPhaseCancelled withEvent:theEvent];
}

- (void)handleTouches:(NSTouchPhase) phase withEvent:(NSEvent *) theEvent
{
    SFG_Window *window = fgWindowByHandle(_window);
    if (!window) {
        return;
    }
    
    NSSet *touches = [theEvent touchesMatchingPhase:phase inView:nil];
    
    for (NSTouch *touch in touches) {
        int touchID = [touch device];
        float x = [touch normalizedPosition].x;
        float y = [touch normalizedPosition].y;
        /* Make the origin the upper left instead of the lower left */
        y = 1.0f - y;
        
        switch (phase) {
            case NSTouchPhaseMoved:
                INVOKE_WCB( *window, MultiMotion, ( touchID, x, y ) );
                break;
            case NSTouchPhaseBegan:
                INVOKE_WCB( *window, MultiEntry,  ( touchID, GLUT_ENTERED ) );
                INVOKE_WCB( *window, MultiButton, ( touchID, x, y, 0, GLUT_DOWN ) );
                break;
            case NSTouchPhaseEnded:
                INVOKE_WCB( *window, MultiButton, ( touchID, x, y, 0, GLUT_UP ) );
                INVOKE_WCB( *window, MultiEntry,  ( touchID, GLUT_LEFT ) );
                break;
            case NSTouchPhaseCancelled:
            default:
                break;
        }
    }
}

@end  // Cocoa_WindowListener


@interface GLUTView : NSView {
    SFG_Window *_Window;
}

- (void)setWindow:(SFG_Window*)window;

/* The default implementation doesn't pass rightMouseDown to responder chain */
- (void)rightMouseDown:(NSEvent *)theEvent;
- (BOOL)mouseDownCanMoveWindow;
- (void)drawRect:(NSRect)dirtyRect;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;
@end

@implementation GLUTView
- (void)setWindow:(SFG_Window*)window
{
    _Window = window;
}

- (void)drawRect:(NSRect)dirtyRect
{
    //SDL_SendWindowEvent(_sdlWindow, SDL_WINDOWEVENT_EXPOSED, 0, 0);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    [[self nextResponder] rightMouseDown:theEvent];
}

- (BOOL)mouseDownCanMoveWindow
{
    /* Always say YES, but this doesn't do anything until we call
     -[NSWindow setMovableByWindowBackground:YES], which we ninja-toggle
     during mouse events when we're using a drag area. */
    return YES;
}

- (void)resetCursorRects
{
    [super resetCursorRects];
    if (_Window->Window.pContext.cursor) {
        [self addCursorRect:[self bounds]
                     cursor:_Window->Window.pContext.cursor];
    } else {
        [self addCursorRect:[self bounds]
                     cursor:[NSCursor invisibleCursor]];
    }
}

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent
{
    return NO;
}
@end // GLUTView

static int
SetupWindowData(SFG_Window * window, NSWindow *nswindow, GLboolean created)
{ @autoreleasepool
    {
        if (!window) {
            return -1;
        }
        
        SFG_PlatformContext *context = (SFG_PlatformContext *) &(window->Window.pContext);
        
        window->Window.Handle = nswindow;
        context->nswindow = nswindow;
        context->created = created;
        context->is_destroying = GL_FALSE;
        context->nscontexts = [[NSMutableArray alloc] init];
        
        /* Create an event listener for the window */
        context->listener = [[Cocoa_WindowListener alloc] init];
        
        /* Fill in the SDL window with the window data */
        {
            NSRect rect = [nswindow contentRectForFrameRect:[nswindow frame]];
            ConvertNSRect([nswindow screen], &rect);
            window->State.Xpos = (int)rect.origin.x;
            window->State.Ypos = (int)rect.origin.y;
            window->State.Width = (int)rect.size.width;
            window->State.Height = (int)rect.size.height;
        }
        
        /* Set up the listener after we create the view */
        [context->listener listen:nswindow];
        
        if ([nswindow isVisible]) {
            window->State.Visible = GL_TRUE;
        } else {
            window->State.Visible = GL_FALSE;
        }
        
        {
            unsigned long style = [nswindow styleMask];
            window->State.pWState.style = style;
        }
        
        /* isZoomed always returns true if the window is not resizable */
        if ([nswindow isZoomed]) {
            window->State.pWState.isMaximized = GL_TRUE;
        } else {
            window->State.pWState.isMaximized = GL_FALSE;
        }
        
        if ([nswindow isMiniaturized]) {
            window->State.pWState.isMinimized = GL_TRUE;
        } else {
            window->State.pWState.isMinimized = GL_FALSE;
        }
        
        if ([nswindow isKeyWindow]) {
            window->State.pWState.isKeyWindow = GL_TRUE;
            //SDL_SetKeyboardFocus(data->window);
        }
        
        /* Prevents the window's "window device" from being destroyed when it is
         * hidden. See http://www.mikeash.com/pyblog/nsopenglcontext-and-one-shot.html
         */
        [nswindow setOneShot:NO];
        
        /* All done! */
        return 0;
    }
}

int
Cocoa_CreateWindow(SFG_Window * window,
                  GLboolean positionUse, int x, int y,
                  GLboolean sizeUse, int w, int h,
                  GLboolean gameMode, GLboolean isSubWindow)
{ @autoreleasepool
    {
        if (!window) {
            return -1;
        }
        
        NSWindow *nswindow;
        NSRect rect;
        NSUInteger style;
        NSArray *screens = [NSScreen screens];
        
        if( ! positionUse )
            x = y = -1; /* default window position */
        if( ! sizeUse )
            w = h = 300; /* default window size */

        if( gameMode ) {
            window->State.IsFullscreen = GL_TRUE;
        }

        rect.origin.x = x;
        rect.origin.y = y;
        rect.size.width = w;
        rect.size.height = h;
        ConvertNSRect([screens objectAtIndex:0], &rect);
        
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
            nswindow = [[GLUTWindow alloc] initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:NO screen:screen];
        }
        @catch (NSException *e) {
            fgError("%s", [[e reason] UTF8String]);
            return -1;
        }
        [nswindow setBackgroundColor:[NSColor blackColor]];
#if 0
        if (videodata->allow_spaces) {
            FREEGLUT_INTERNAL_ERROR_EXIT((floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6), "AppKit Version is too low", "Cocoa_CreateWindow");
            FREEGLUT_INTERNAL_ERROR_EXIT(([nswindow respondsToSelector:@selector(toggleFullScreen:)], "respondsToSelector is failed", "Cocoa_CreateWindow"));
            /* we put FULLSCREEN_DESKTOP windows in their own Space, without a toggle button or menubar, later */
            if (window->flags & SDL_WINDOW_RESIZABLE) {
                /* resizable windows are Spaces-friendly: they get the "go fullscreen" toggle button on their titlebar. */
                [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
            }
        }
#endif
        /* Create a default view for this window */
        rect = [nswindow contentRectForFrameRect:[nswindow frame]];
        GLUTView *contentView = [[GLUTView alloc] initWithFrame:rect];
        [contentView setWindow:window];
        
        //if (window->flags & SDL_WINDOW_ALLOW_HIGHDPI)
        {
            if ([contentView respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)]) {
                [contentView setWantsBestResolutionOpenGLSurface:YES];
            }
        }
        
        [nswindow setContentView:contentView];
        [contentView release];
        
        /* Allow files and folders to be dragged onto the window by users */
        [nswindow registerForDraggedTypes:[NSArray arrayWithObject:(NSString *)kUTTypeFileURL]];
        
        if (SetupWindowData(window, nswindow, GL_TRUE) < 0) {
            [nswindow release];
            return -1;
        }
        return 0;
    }
} 

void
Cocoa_DestroyWindow(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        SFG_PlatformContext *data = (&window->Window.pContext);
        
        if (data) {
            if ([data->listener isInFullscreenSpace]) {
                [NSMenu setMenuBarVisible:YES];
            }
            [data->listener close];
            [data->listener release];
            if (data->created) {
                [data->nswindow close];
            }
            
            NSArray *contexts = [[data->nscontexts copy] autorelease];
            for (GLUTOpenGLContext *context in contexts) {
                /* Calling setWindow:NULL causes the context to remove itself from the context list. */
                [context setWindow:NULL];
            }
            [data->nscontexts release];
        }
    }
}


void
Cocoa_SetWindowTitle(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        const char *title = window->State.pWState.title ? window->State.pWState.title : "";
        NSWindow *nswindow = window->Window.Handle;
        NSString *string = [[NSString alloc] initWithUTF8String:title];
        [nswindow setTitle:string];
        [string release];
    }
    
}

void
Cocoa_SetWindowPosition(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        NSRect rect;
        fg_time_t moveHack;
        
        rect.origin.x = window->State.DesiredXpos;
        rect.origin.y = window->State.DesiredYpos;
        rect.size.width = window->State.Width;
        rect.size.height = window->State.Height;
        ConvertNSRect([nswindow screen], &rect);
        
        moveHack = s_moveHack;
        s_moveHack = 0;
        [nswindow setFrameOrigin:rect.origin];
        s_moveHack = moveHack;
        
        ScheduleContextUpdates(window);
    }}

void
Cocoa_SetWindowSize(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        NSRect rect;
        fg_time_t moveHack;
        
        /* Cocoa will resize the window from the bottom-left rather than the
         * top-left when -[nswindow setContentSize:] is used, so we must set the
         * entire frame based on the new size, in order to preserve the position.
         */
        rect.origin.x = window->State.Xpos;
        rect.origin.y = window->State.Ypos;
        rect.size.width = window->State.DesiredWidth;
        rect.size.height = window->State.DesiredHeight;
        ConvertNSRect([nswindow screen], &rect);
        
        moveHack = s_moveHack;
        s_moveHack = 0;
        [nswindow setFrame:[nswindow frameRectForContentRect:rect] display:YES];
        s_moveHack = moveHack;
        
        ScheduleContextUpdates(window);
    }
}



void
Cocoa_RaiseWindow(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        SFG_PlatformContext *windowData = &window->Window.pContext;
        NSWindow *nswindow = windowData->nswindow;
        
        /* makeKeyAndOrderFront: has the side-effect of deminiaturizing and showing
         a minimized or hidden window, so check for that before showing it.
         */
        [windowData->listener pauseVisibleObservation];
        if (![nswindow isMiniaturized] && [nswindow isVisible]) {
            [NSApp activateIgnoringOtherApps:YES];
            [nswindow makeKeyAndOrderFront:nil];
        }
        [windowData->listener resumeVisibleObservation];
    }
}

void
Cocoa_MaximizeWindow(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        
        [nswindow zoom:nil];
        
        ScheduleContextUpdates(window);
    }
}

void
Cocoa_MinimizeWindow(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        SFG_PlatformContext *data = &window->Window.pContext;
        NSWindow *nswindow = data->nswindow;
        
        if ([data->listener isInFullscreenSpaceTransition]) {
            [data->listener addPendingWindowOperation:PENDING_OPERATION_MINIMIZE];
        } else {
            [nswindow miniaturize:nil];
        }
    }
}

void
Cocoa_RestoreWindow(SFG_Window * window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        
        if ([nswindow isMiniaturized]) {
            [nswindow deminiaturize:nil];
        } else if ([nswindow isZoomed]) {
            [nswindow zoom:nil];
        }
    }
}

void
Cocoa_SetWindowFullscreen(SFG_Window * window, SFG_PlatformDisplay * display, GLboolean fullscreen)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        SFG_PlatformContext *data = &window->Window.pContext;
        NSWindow *nswindow = data->nswindow;
        NSRect rect;
        
        /* The view responder chain gets messed with during setStyleMask */
        if ([[nswindow contentView] nextResponder] == data->listener) {
            [[nswindow contentView] setNextResponder:nil];
        }
        
        if (fullscreen) {
            CGRect cgrect;
            cgrect = CGDisplayBounds(fgDisplay.pDisplay.display);
            rect.origin.x = cgrect.origin.x;
            rect.origin.y = cgrect.origin.y;
            rect.size.width = cgrect.size.width;
            rect.size.height = cgrect.size.width;
            ConvertNSRect([nswindow screen], &rect);
            
            /* Hack to fix origin on Mac OS X 10.4 */
            NSRect screenRect = [[nswindow screen] frame];
            if (screenRect.size.height >= 1.0f) {
                rect.origin.y += (screenRect.size.height - rect.size.height);
            }
            
            [nswindow setStyleMask:NSWindowStyleMaskBorderless];
        } else {
            rect.origin.x = window->State.Xpos;
            rect.origin.y = window->State.Ypos;
            rect.size.width = window->State.Width;
            rect.size.height = window->State.Height;
            ConvertNSRect([nswindow screen], &rect);
            
            [nswindow setStyleMask:GetWindowStyle(window)];
            
            /* Hack to restore window decorations on Mac OS X 10.10 */
            NSRect frameRect = [nswindow frame];
            [nswindow setFrame:NSMakeRect(frameRect.origin.x, frameRect.origin.y, frameRect.size.width + 1, frameRect.size.height) display:NO];
            [nswindow setFrame:frameRect display:NO];
        }
        
        /* The view responder chain gets messed with during setStyleMask */
        if ([[nswindow contentView] nextResponder] != data->listener) {
            [[nswindow contentView] setNextResponder:data->listener];
        }
        
        s_moveHack = 0;
        [nswindow setContentSize:rect.size];
        [nswindow setFrameOrigin:rect.origin];
        s_moveHack = fgSystemTime() - fgState.Time;
        
        /* When the window style changes the title is cleared */
        if (!fullscreen) {
            Cocoa_SetWindowTitle(window);
        }
        
        if (fullscreen) {
            /* OpenGL is rendering to the window, so make it visible! */
            [nswindow setLevel:CGShieldingWindowLevel()];
        } else {
            [nswindow setLevel:kCGNormalWindowLevel];
        }
        
        if ([nswindow isVisible] || fullscreen) {
            [data->listener pauseVisibleObservation];
            [nswindow makeKeyAndOrderFront:nil];
            [data->listener resumeVisibleObservation];
        }
        
        ScheduleContextUpdates(window);
    }
}

GLboolean Cocoa_IsWindowVisible(SFG_Window* window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        if ([nswindow isVisible]) {
            return GL_TRUE;
        } else {
            return GL_FALSE;
        }
    }
}

void Cocoa_PushWindow(SFG_Window* window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        [nswindow orderBack:nil];
    }
}

void Cocoa_PopWindow(SFG_Window* window)
{ @autoreleasepool
    {
        if (!window) {
            return;
        }
        
        NSWindow *nswindow = window->Window.Handle;
        [nswindow orderFront:nil];
    }
}

/*
 * window
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
    if (!window) {
        return;
    }
    
    Cocoa_DestroyWindow(window);
}

void fgPlatformGlutSetIconTitle( const char* title )
{
    if (fgStructure.CurrentWindow->State.pWState.iconic) {
        free(fgStructure.CurrentWindow->State.pWState.iconic);
    }
    fgStructure.CurrentWindow->State.pWState.iconic = strdup(title ? title : "");
}

void fgPlatformGlutSetWindowTitle( const char* title )
{
    if (fgStructure.CurrentWindow->State.pWState.title) {
        free(fgStructure.CurrentWindow->State.pWState.title);
    }
    fgStructure.CurrentWindow->State.pWState.title = strdup(title ? title : "");
    
    Cocoa_SetWindowTitle(fgStructure.CurrentWindow);
}

void fgPlatformHideWindow( SFG_Window* window )
{
    Cocoa_HideWindow(window);
}

void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                          GLboolean positionUse, int x, int y,
                          GLboolean sizeUse, int w, int h,
                          GLboolean gameMode, GLboolean isSubWindow )
{
    if (!window) {
        return;
    }
    
    /* Create Window */
    Cocoa_CreateWindow(window, positionUse, x, y, sizeUse, w, h, gameMode, isSubWindow);
    
    /* Set Title */
    window->State.pWState.title  = strdup(title ? title : "");
    window->State.pWState.iconic = NULL;
    Cocoa_SetWindowTitle(window);
    
    /* Show Window */
    Cocoa_ShowWindow(window);
    
    /* Create OpenGL Context */
    Cocoa_GL_CreateContext(window);
    
    /* Create default cursor */
    Cocoa_InitMouse(window);
}

void fgPlatformSetWindow ( SFG_Window *window )
{
    if ( window != fgStructure.CurrentWindow && window) {
        Cocoa_GL_MakeCurrent(window, window->Window.Context);
    }
}

