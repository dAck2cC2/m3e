#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

#include <Cocoa/Cocoa.h>


@interface GLUTApplication : NSApplication

- (void)terminate:(id)sender;
- (void)sendEvent:(NSEvent *)theEvent;

@end

@implementation GLUTApplication

// Override terminate to handle Quit and System Shutdown smoothly.
- (void)terminate:(id)sender
{
    //fgDestroyWindow ( window );
}

static GLboolean s_bShouldHandleEventsInApplication = GL_FALSE;

static void Cocoa_DispatchEvent(NSEvent *theEvent)
{
    //DL_VideoDevice *_this = SDL_GetVideoDevice();
    
    switch ([theEvent type]) {
        case NSEventTypeLeftMouseDown:
        case NSEventTypeOtherMouseDown:
        case NSEventTypeRightMouseDown:
        case NSEventTypeLeftMouseUp:
        case NSEventTypeOtherMouseUp:
        case NSEventTypeRightMouseUp:
        case NSEventTypeLeftMouseDragged:
        case NSEventTypeRightMouseDragged:
        case NSEventTypeOtherMouseDragged: /* usually middle mouse dragged */
        case NSEventTypeMouseMoved:
        case NSEventTypeScrollWheel:
            //Cocoa_HandleMouseEvent(_this, theEvent);
            break;
        case NSEventTypeKeyDown:
        case NSEventTypeKeyUp:
        case NSEventTypeFlagsChanged:
            //Cocoa_HandleKeyEvent(_this, theEvent);
            break;
        default:
            break;
    }
}

// Dispatch events here so that we can handle events caught by
// nextEventMatchingMask in SDL, as well as events caught by other
// processes (such as CEF) that are passed down to NSApp.
- (void)sendEvent:(NSEvent *)theEvent
{
    if (s_bShouldHandleEventsInApplication) {
        Cocoa_DispatchEvent(theEvent);
    }
    
    [super sendEvent:theEvent];
}

@end // GLUTApplication

/* setAppleMenu disappeared from the headers in 10.4 */
@interface NSApplication(NSAppleMenu)
- (void)setAppleMenu:(NSMenu *)menu;
@end

@interface GLUTAppDelegate : NSObject <NSApplicationDelegate> {
@public
    BOOL seenFirstActivate;
}

- (id)init;
@end

@implementation GLUTAppDelegate : NSObject
- (id)init
{
    self = [super init];
    if (self) {
        NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
        
        seenFirstActivate = NO;
        
        [center addObserver:self
                   selector:@selector(windowWillClose:)
                       name:NSWindowWillCloseNotification
                     object:nil];
        
        [center addObserver:self
                   selector:@selector(focusSomeWindow:)
                       name:NSApplicationDidBecomeActiveNotification
                     object:nil];
    }
    
    return self;
}

- (void)dealloc
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    
    [center removeObserver:self name:NSWindowWillCloseNotification object:nil];
    [center removeObserver:self name:NSApplicationDidBecomeActiveNotification object:nil];
    
    [super dealloc];
}

- (void)windowWillClose:(NSNotification *)notification;
{
    NSWindow *win = (NSWindow*)[notification object];
    
    if (![win isKeyWindow]) {
        return;
    }
    
    /* HACK: Make the next window in the z-order key when the key window is
     * closed. The custom event loop and/or windowing code we have seems to
     * prevent the normal behavior: https://bugzilla.libsdl.org/show_bug.cgi?id=1825
     */
    
    /* +[NSApp orderedWindows] never includes the 'About' window, but we still
     * want to try its list first since the behavior in other apps is to only
     * make the 'About' window key if no other windows are on-screen.
     */
    for (NSWindow *window in [NSApp orderedWindows]) {
        if (window != win && [window canBecomeKeyWindow]) {
            if (![window isOnActiveSpace]) {
                continue;
            }
            [window makeKeyAndOrderFront:self];
            return;
        }
    }
    
    /* If a window wasn't found above, iterate through all visible windows in
     * the active Space in z-order (including the 'About' window, if it's shown)
     * and make the first one key.
     */
    for (NSNumber *num in [NSWindow windowNumbersWithOptions:0]) {
        NSWindow *window = [NSApp windowWithWindowNumber:[num integerValue]];
        if (window && window != win && [window canBecomeKeyWindow]) {
            [window makeKeyAndOrderFront:self];
            return;
        }
    }
}

- (void)focusSomeWindow:(NSNotification *)aNotification
{
    /* HACK: Ignore the first call. The application gets a
     * applicationDidBecomeActive: a little bit after the first window is
     * created, and if we don't ignore it, a window that has been created with
     * SDL_WINDOW_MINIMIZED will ~immediately be restored.
     */
    if (!seenFirstActivate) {
        seenFirstActivate = YES;
        return;
    }
    
    /*
     SDL_VideoDevice *device = SDL_GetVideoDevice();
     if (device && device->windows) {
     SDL_Window *window = device->windows;
     int i;
     for (i = 0; i < device->num_displays; ++i) {
     SDL_Window *fullscreen_window = device->displays[i].fullscreen_window;
     if (fullscreen_window) {
     if (fullscreen_window->flags & SDL_WINDOW_MINIMIZED) {
     SDL_RestoreWindow(fullscreen_window);
     }
     return;
     }
     }
     
     if (window->flags & SDL_WINDOW_MINIMIZED) {
     SDL_RestoreWindow(window);
     } else {
     SDL_RaiseWindow(window);
     }
     }
     */
}

- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
{
    //return (BOOL)SDL_SendDropFile(NULL, [filename UTF8String]) && SDL_SendDropComplete(NULL);
    return FALSE;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    /* The menu bar of SDL apps which don't have the typical .app bundle
     * structure fails to work the first time a window is created (until it's
     * de-focused and re-focused), if this call is in Cocoa_RegisterApp instead
     * of here. https://bugzilla.libsdl.org/show_bug.cgi?id=3051
     */
    //if (!SDL_GetHintBoolean(SDL_HINT_MAC_BACKGROUND_APP, SDL_FALSE))
    {
        [NSApp activateIgnoringOtherApps:YES];
    }
}
@end // GLUTAppDelegate

static GLUTAppDelegate *appDelegate = nil;

static NSString *
GetApplicationName(void)
{
    NSString *appName;
    
    /* Determine the application name */
    appName = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"];
    if (!appName) {
        appName = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleName"];
    }
    
    if (![appName length]) {
        appName = [[NSProcessInfo processInfo] processName];
    }
    
    return appName;
}

static void
CreateApplicationMenus(void)
{
    NSString *appName;
    NSString *title;
    NSMenu *appleMenu;
    NSMenu *serviceMenu;
    NSMenu *windowMenu;
    NSMenu *viewMenu;
    NSMenuItem *menuItem;
    NSMenu *mainMenu;
    
    if (NSApp == nil) {
        return;
    }
    
    mainMenu = [[NSMenu alloc] init];
    
    /* Create the main menu bar */
    [NSApp setMainMenu:mainMenu];
    
    [mainMenu release];  /* we're done with it, let NSApp own it. */
    mainMenu = nil;
    
    /* Create the application menu */
    appName = GetApplicationName();
    appleMenu = [[NSMenu alloc] initWithTitle:@""];
    
    /* Add menu items */
    title = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    [appleMenu addItemWithTitle:@"Preferences…" action:nil keyEquivalent:@","];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    serviceMenu = [[NSMenu alloc] initWithTitle:@""];
    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Services" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:serviceMenu];
    
    [NSApp setServicesMenu:serviceMenu];
    [serviceMenu release];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSEventModifierFlagOption|NSEventModifierFlagCommand)];
    
    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    
    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];
    [menuItem release];
    
    /* Tell the application object that this is now the application menu */
    [NSApp setAppleMenu:appleMenu];
    [appleMenu release];
    
    
    /* Create the window menu */
    windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    
    /* Add menu items */
    [windowMenu addItemWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    
    [windowMenu addItemWithTitle:@"Zoom" action:@selector(performZoom:) keyEquivalent:@""];
    
    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:menuItem];
    [menuItem release];
    
    /* Tell the application object that this is now the window menu */
    [NSApp setWindowsMenu:windowMenu];
    [windowMenu release];
    
    
    /* Add the fullscreen view toggle menu option, if supported */
    if (floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6) {
        /* Create the view menu */
        viewMenu = [[NSMenu alloc] initWithTitle:@"View"];
        
        /* Add menu items */
        menuItem = [viewMenu addItemWithTitle:@"Toggle Full Screen" action:@selector(toggleFullScreen:) keyEquivalent:@"f"];
        [menuItem setKeyEquivalentModifierMask:NSEventModifierFlagControl | NSEventModifierFlagCommand];
        
        /* Put menu into the menubar */
        menuItem = [[NSMenuItem alloc] initWithTitle:@"View" action:nil keyEquivalent:@""];
        [menuItem setSubmenu:viewMenu];
        [[NSApp mainMenu] addItem:menuItem];
        [menuItem release];
        
        [viewMenu release];
    }
}

void
Cocoa_RegisterApp(void)
{ @autoreleasepool
    {
        /* This can get called more than once! Be careful what you initialize! */
        
        if (NSApp == nil) {
            [GLUTApplication sharedApplication];
            //SDL_assert(NSApp != nil);
            
            s_bShouldHandleEventsInApplication = GL_TRUE;
            
            //if (!SDL_GetHintBoolean(SDL_HINT_MAC_BACKGROUND_APP, SDL_FALSE))
            {
                [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
            }
            
            if ([NSApp mainMenu] == nil) {
                CreateApplicationMenus();
            }
            [NSApp finishLaunching];
            NSDictionary *appDefaults = [[NSDictionary alloc] initWithObjectsAndKeys:
                                         [NSNumber numberWithBool:NO], @"AppleMomentumScrollSupported",
                                         [NSNumber numberWithBool:NO], @"ApplePressAndHoldEnabled",
                                         [NSNumber numberWithBool:YES], @"ApplePersistenceIgnoreState",
                                         nil];
            [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaults];
            [appDefaults release];
        }
        if (NSApp && !appDelegate) {
            appDelegate = [[GLUTAppDelegate alloc] init];
            
            /* If someone else has an app delegate, it means we can't turn a
             * termination into SDL_Quit, and we can't handle application:openFile:
             */
            if (![NSApp delegate]) {
                [(NSApplication *)NSApp setDelegate:appDelegate];
            } else {
                appDelegate->seenFirstActivate = YES;
            }
        }
    }
}

/*
 * main
 */
void fgPlatformInitWork(SFG_Window* window)
{
}
void fgPlatformMainLoopPreliminaryWork ( void )
{
}
void fgPlatformPosResZordWork(SFG_Window* window, unsigned int workMask)
{
}
void fgPlatformProcessSingleEvent ( void )
{
}
void fgPlatformSleepForEvents( fg_time_t msec )
{
}
void fgPlatformVisibilityWork(SFG_Window* window)
{
}

fg_time_t fgPlatformSystemTime ( void )
{
#ifdef CLOCK_MONOTONIC
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_nsec/1000000 + now.tv_sec*1000;
#elif defined(HAVE_GETTIMEOFDAY)
    struct timeval now;
    gettimeofday( &now, NULL );
    return now.tv_usec/1000 + now.tv_sec*1000;
#endif
}
