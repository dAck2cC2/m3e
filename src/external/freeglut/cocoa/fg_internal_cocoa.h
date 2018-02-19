#ifndef  FREEGLUT_INTERNAL_OSX_H
#define  FREEGLUT_INTERNAL_OSX_H

#import <Cocoa/Cocoa.h>
#import <CoreGraphics/CGDirectDisplay.h>
#import <AppKit/NSWindow.h>

/* Switch of unsupported feature */

#define TARGET_NO_MAIN       0
#define TARGET_NO_INIT       0
#define TARGET_NO_WINDOW     0
#define TARGET_NO_DISPLAY    1
#define TARGET_NO_JOYSTICK   1
#define TARGET_NO_SPACEBALL  1
#define TARGET_NO_GAMEMODE   1
#define TARGET_NO_STRUCTURE  1
#define TARGET_NO_EXT        1
#define TARGET_NO_MENU       1
#define TARGET_NO_STATE      1
#define TARGET_NO_CURSOR     0
#define TARGET_NO_SERIAL     0

/* Structure Definitions */

typedef struct tagSFG_PlatformDisplay SFG_PlatformDisplay;
struct tagSFG_PlatformDisplay
{
    CGDirectDisplayID  display;
    CGDisplayModeRef   moderef;
    int                refreshRate;
    int                bpp;         /* Bits Per Pixel */
    char*              name;        /* Display name for multi display support*/
};

/*
 * Make "freeglut" window handle and context types so that we don't need so
 * much conditionally-compiled code later in the library.
 */

typedef NSWindow * SFG_WindowHandleType;
typedef void *     SFG_WindowContextType;

typedef enum
{
    PENDING_OPERATION_NONE,
    PENDING_OPERATION_ENTER_FULLSCREEN,
    PENDING_OPERATION_LEAVE_FULLSCREEN,
    PENDING_OPERATION_MINIMIZE
} PendingWindowOperation;

@interface Cocoa_WindowListener : NSResponder <NSWindowDelegate> {
    SFG_WindowHandleType _window;
    BOOL observingVisible;
    BOOL wasCtrlLeft;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    int pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
}

-(void) listen:(SFG_WindowHandleType) data;
-(void) pauseVisibleObservation;
-(void) resumeVisibleObservation;
-(BOOL) setFullscreenSpace:(BOOL) state;
-(BOOL) isInFullscreenSpace;
-(BOOL) isInFullscreenSpaceTransition;
-(void) addPendingWindowOperation:(PendingWindowOperation) operation;
-(void) close;

-(BOOL) isMoving;
-(void) setPendingMoveX:(int)x Y:(int)y;
-(void) windowDidFinishMoving;

/* Window delegate functionality */
-(BOOL) windowShouldClose:(id) sender;
-(void) windowDidExpose:(NSNotification *) aNotification;
-(void) windowDidMove:(NSNotification *) aNotification;
-(void) windowDidResize:(NSNotification *) aNotification;
-(void) windowDidMiniaturize:(NSNotification *) aNotification;
-(void) windowDidDeminiaturize:(NSNotification *) aNotification;
-(void) windowDidBecomeKey:(NSNotification *) aNotification;
-(void) windowDidResignKey:(NSNotification *) aNotification;
-(void) windowDidChangeBackingProperties:(NSNotification *) aNotification;
-(void) windowWillEnterFullScreen:(NSNotification *) aNotification;
-(void) windowDidEnterFullScreen:(NSNotification *) aNotification;
-(void) windowWillExitFullScreen:(NSNotification *) aNotification;
-(void) windowDidExitFullScreen:(NSNotification *) aNotification;
-(NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

/* See if event is in a drag area, toggle on window dragging. */
-(BOOL) processHitTest:(NSEvent *)theEvent;

/* Window event handling */
-(void) mouseDown:(NSEvent *) theEvent;
-(void) rightMouseDown:(NSEvent *) theEvent;
-(void) otherMouseDown:(NSEvent *) theEvent;
-(void) mouseUp:(NSEvent *) theEvent;
-(void) rightMouseUp:(NSEvent *) theEvent;
-(void) otherMouseUp:(NSEvent *) theEvent;
-(void) mouseMoved:(NSEvent *) theEvent;
-(void) mouseDragged:(NSEvent *) theEvent;
-(void) rightMouseDragged:(NSEvent *) theEvent;
-(void) otherMouseDragged:(NSEvent *) theEvent;
-(void) scrollWheel:(NSEvent *) theEvent;
-(void) touchesBeganWithEvent:(NSEvent *) theEvent;
-(void) touchesMovedWithEvent:(NSEvent *) theEvent;
-(void) touchesEndedWithEvent:(NSEvent *) theEvent;
-(void) touchesCancelledWithEvent:(NSEvent *) theEvent;

/* Touch event handling */
-(void) handleTouches:(NSTouchPhase) phase withEvent:(NSEvent*) theEvent;

@end /* Cocoa_WindowListener */


@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@end /*InvisibleCursor*/


typedef struct tagSFG_PlatformContext SFG_PlatformContext;
struct tagSFG_PlatformContext
{
    SFG_WindowHandleType nswindow;
    NSMutableArray *nscontexts;
    GLboolean created;
    GLboolean is_destroying;
    Cocoa_WindowListener *listener;
    NSCursor * cursor;
};

@interface GLUTOpenGLContext : NSOpenGLContext {
    int dirty;
    SFG_PlatformContext* window;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (void)scheduleUpdate;
- (void)updateIfNeeded;
- (void)setWindow:(SFG_PlatformContext *)window;

@end /* GLUTOpenGLContext */


/* Window's state description. This structure should be kept portable. */
typedef struct tagSFG_PlatformWindowState SFG_PlatformWindowState;
struct tagSFG_PlatformWindowState
{
    unsigned long style;
    GLboolean isMaximized;
    GLboolean isMinimized;
    GLboolean isKeyWindow;
    
    /* Need to store window titles to emulate
     * glutSetIconTitle/glutSetWindowTitle as Windows has only
     * one title associated with a window and we need to swap
     * them out based on the window's iconic state
     */
    char*           title;
    char*           iconic;
};


#    define _JS_MAX_AXES 16
typedef struct tagSFG_PlatformJoystick SFG_PlatformJoystick;
struct tagSFG_PlatformJoystick
{
    char         fname [ 128 ];
    int          fd;
};


/* Menu font and color definitions */
#define  FREEGLUT_MENU_FONT    GLUT_BITMAP_8_BY_13

#define  FREEGLUT_MENU_PEN_FORE_COLORS   {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_BACK_COLORS   {0.85f, 0.85f, 0.85f, 1.0f}
#define  FREEGLUT_MENU_PEN_HFORE_COLORS  {1.0f,  1.0f,  1.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_HBACK_COLORS  {0.15f, 0.15f, 0.45f, 1.0f}


#endif // FREEGLUT_INTERNAL_OSX_H
