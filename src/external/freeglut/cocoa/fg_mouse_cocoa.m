
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

extern int  Cocoa_GetModifiers(void);
void fghPlatformGetCursorPos(const SFG_Window *window, GLboolean client, SFG_XYUse *mouse_pos);

@implementation NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor
{
    static NSCursor *invisibleCursor = NULL;
    if (!invisibleCursor) {
        /* RAW 16x16 transparent GIF */
        static unsigned char cursorBytes[] = {
            0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0xF9, 0x04,
            0x01, 0x00, 0x00, 0x01, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x10, 0x00, 0x00, 0x02, 0x0E, 0x8C, 0x8F, 0xA9, 0xCB, 0xED,
            0x0F, 0xA3, 0x9C, 0xB4, 0xDA, 0x8B, 0xB3, 0x3E, 0x05, 0x00, 0x3B
        };
        
        NSData *cursorData = [NSData dataWithBytesNoCopy:&cursorBytes[0]
                                                  length:sizeof(cursorBytes)
                                            freeWhenDone:NO];
        NSImage *cursorImage = [[[NSImage alloc] initWithData:cursorData] autorelease];
        invisibleCursor = [[NSCursor alloc] initWithImage:cursorImage
                                                  hotSpot:NSZeroPoint];
    }
    
    return invisibleCursor;
}
@end  /* InvisibleCursor */


static int
Cocoa_WarpMouseGlobal(int x, int y)
{
    const CGPoint point = CGPointMake((float)x, (float)y);
    
    CGWarpMouseCursorPosition(point);
    
    /* CGWarpMouse causes a short delay by default, which is preventable by
     * Calling this directly after. CGSetLocalEventsSuppressionInterval can also
     * prevent it, but it's deprecated as of OS X 10.6.
     */
    {
        CGAssociateMouseAndMouseCursorPosition(YES);
    }
    
    return 0;
}


static NSCursor *
Cocoa_CreateSystemCursor(int cursorid)
{ @autoreleasepool
    {
        NSCursor *nscursor = NULL;
        
        switch(cursorid) {
            case GLUT_CURSOR_RIGHT_ARROW:
            case GLUT_CURSOR_LEFT_ARROW:
            case GLUT_CURSOR_WAIT:
                nscursor = [NSCursor arrowCursor];
                break;
            case GLUT_CURSOR_INFO:
            case GLUT_CURSOR_HELP:
                nscursor = [NSCursor openHandCursor];
                break;
            case GLUT_CURSOR_DESTROY:
            case GLUT_CURSOR_SPRAY:
            case GLUT_CURSOR_CROSSHAIR:
            case GLUT_CURSOR_FULL_CROSSHAIR:
                nscursor = [NSCursor crosshairCursor];
                break;
            case GLUT_CURSOR_CYCLE:
            case GLUT_CURSOR_TOP_LEFT_CORNER:
            case GLUT_CURSOR_TOP_RIGHT_CORNER:
            case GLUT_CURSOR_BOTTOM_RIGHT_CORNER:
            case GLUT_CURSOR_BOTTOM_LEFT_CORNER:
                nscursor = [NSCursor closedHandCursor];
                break;
            case GLUT_CURSOR_TEXT:
                nscursor = [NSCursor IBeamCursor];
                break;
            case GLUT_CURSOR_UP_DOWN:
                nscursor = [NSCursor resizeUpDownCursor];
                break;
            case GLUT_CURSOR_LEFT_RIGHT:
                nscursor = [NSCursor resizeLeftRightCursor];
                break;
            case GLUT_CURSOR_TOP_SIDE:
                nscursor = [NSCursor resizeUpCursor];
                break;
            case GLUT_CURSOR_BOTTOM_SIDE:
                nscursor = [NSCursor resizeDownCursor];
                break;
            case GLUT_CURSOR_LEFT_SIDE:
                nscursor = [NSCursor resizeLeftCursor];
                break;
            case GLUT_CURSOR_RIGHT_SIDE:
                nscursor = [NSCursor resizeRightCursor];
                break;
            default:
                fgError(!"Unknown system cursor");
                return NULL;
        }
        
        if (nscursor) {
            /* We'll free it later, so retain it here */
            [nscursor retain];
        }
        
        return nscursor;
    }
}

static NSCursor *
Cocoa_CreateDefaultCursor()
{ @autoreleasepool
    {
        NSCursor *nscursor;
        nscursor = [NSCursor arrowCursor];
        if (nscursor) {
            /* We'll free it later, so retain it here */
            [nscursor retain];
        }
        
        return nscursor;
    }
}

static void
Cocoa_FreeCursor(NSCursor * cursor)
{ @autoreleasepool
    {
        [cursor release];
    }
}

static int
Cocoa_ShowCursor(SFG_Window* fgwindow_in)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(fgwindow_in, "FG window is nonexistent", __FUNCTION__);
        
        /* cursor could be set to GLUT_CURSOR_NONE */
        if (fgwindow_in->Window.pContext.cursor) {
            NSCursor* nscursor = fgwindow_in->Window.pContext.cursor;
            [nscursor set];
        }

        return 0;
    }
}

static GLboolean
Cocoa_IsInWindow(SFG_Window* fgwindow_in, int x_in, int y_in)
{
    FREEGLUT_INTERNAL_ERROR_EXIT(fgwindow_in, "FG window is nonexistent", __FUNCTION__);
    
    if (!fgwindow_in->State.Visible) {
        return GL_FALSE;
    }
    
    if ((x_in >= fgwindow_in->State.Xpos)
    &&  (x_in <= (fgwindow_in->State.Xpos + fgwindow_in->State.Width))
    &&  (y_in >= fgwindow_in->State.Ypos)
    &&  (y_in <= (fgwindow_in->State.Ypos + fgwindow_in->State.Height))) {
        return GL_TRUE;
    } else {
        return GL_FALSE;
    }

}

static SFG_Window*
Cocoa_FindFocusWindow(SFG_List* windowList, int x, int y)
{
    FREEGLUT_INTERNAL_ERROR_EXIT(windowList, "window list is nonexistent", __FUNCTION__);
    
    SFG_Window* window = NULL;
    
    /* Check every of the top-level windows */
    for(window = ( SFG_Window * )windowList->First;
        window;
        window = ( SFG_Window * )window->Node.Next )
    {
        if (Cocoa_IsInWindow(window, x, y)) {
            SFG_Window* subWindow = Cocoa_FindFocusWindow(&(window->Children), x, y);
            if (subWindow) {
                return subWindow;
            } else {
                return window;
            }
        }
    }
    
    return NULL;
}

void
Cocoa_MouseMoved(SFG_Window* window)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(window, "window is nonexistent", __FUNCTION__);
        
        if ( window->ActiveMenu ) {
            fgUpdateMenuHighlight( window->ActiveMenu );
            return;
        }
        
        fgState.Modifiers = Cocoa_GetModifiers();
        if (FETCH_WCB( *window, Passive )) {
            INVOKE_WCB( *window, Passive, ( window->State.MouseX,
                                            window->State.MouseY ));
        }
        fgState.Modifiers = INVALID_MODIFIERS;
    }
}

void
Cocoa_MouseDragged(SFG_Window* window)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(window, "window is nonexistent", __FUNCTION__);
        
        if ( window->ActiveMenu ) {
            fgUpdateMenuHighlight( window->ActiveMenu );
            return;
        }
        
        if (FETCH_WCB( *window, Motion )) {
            fgState.Modifiers = Cocoa_GetModifiers();
            INVOKE_WCB( *window, Motion, ( window->State.MouseX,
                                           window->State.MouseY ));
            fgState.Modifiers = INVALID_MODIFIERS;
        }
    }
}

void
Cocoa_MouseButton(SFG_Window* fgwindow_in, int button_in, int updown_in)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(fgwindow_in, "FG window is nonexistent", __FUNCTION__);
        
        /*
         * Do not execute the application's mouse callback if a menu
         * is hooked to this button.  In that case an appropriate
         * private call should be generated.
         */
        if( fgCheckActiveMenu( fgwindow_in, button_in, (updown_in == GLUT_DOWN ? GL_TRUE : GL_FALSE),
                               fgwindow_in->State.MouseX, fgwindow_in->State.MouseY ) ) {
            return;
        }
        
        if (FETCH_WCB( *fgwindow_in, Mouse )) {
            fgState.Modifiers = Cocoa_GetModifiers();
            INVOKE_WCB( *fgwindow_in, Mouse,
                       ( button_in,
                        updown_in,
                        fgwindow_in->State.MouseX,
                        fgwindow_in->State.MouseY
                        ));
            fgState.Modifiers = INVALID_MODIFIERS;
        }
    }
}

void
Cocoa_HandleMouseWheel(SFG_Window *window, NSEvent *event)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(window, "window is nonexistent", __FUNCTION__);
        FREEGLUT_INTERNAL_ERROR_EXIT(event, "event is nonexistent", __FUNCTION__);
    
        if ( ! FETCH_WCB( *window, MouseWheel )) {
            return;
        }
    
        CGFloat x = -[event deltaX];
        CGFloat y = [event deltaY];
        int direction = 1;
    
        if ([event respondsToSelector:@selector(isDirectionInvertedFromDevice)]) {
            if ([event isDirectionInvertedFromDevice] == YES) {
                direction = -1;
            }
        }
    
        fgState.Modifiers = Cocoa_GetModifiers();
        INVOKE_WCB( *window, MouseWheel, ( 0,
                                      direction,
                                      x,
                                      y ));
        fgState.Modifiers = INVALID_MODIFIERS;
    }
}

void
Cocoa_MouseIn(SFG_Window * fgwindow_in)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(fgwindow_in, "FG window is nonexistent", __FUNCTION__);
        
        fgSetWindow(fgwindow_in);
        Cocoa_ShowCursor(fgwindow_in);
        
        if (FETCH_WCB( *fgwindow_in, Entry )) {
            INVOKE_WCB( *fgwindow_in, Entry, ( GLUT_ENTERED ) );
        }
    }
}

void
Cocoa_MouseOut(SFG_Window * fgwindow_in)
{ @autoreleasepool
    {
        FREEGLUT_INTERNAL_ERROR_EXIT(fgwindow_in, "FG window is nonexistent", __FUNCTION__);
        
        if (FETCH_WCB(*fgwindow_in, Entry)) {
            INVOKE_WCB( *fgwindow_in, Entry, ( GLUT_LEFT ) );
        }
        
        /* give the focus back to root window */
        if (fgwindow_in->Parent) {
            SFG_Window* parent = fgwindow_in->Parent;
            while (parent->Parent) {
                parent = parent->Parent;
            }
            fgSetWindow(parent);
        }
    }
}

void
Cocoa_InitCursor(SFG_Window* window)
{
    if (window) {
        window->Window.pContext.cursor = Cocoa_CreateDefaultCursor();
        
        SFG_XYUse mouse;
        fghPlatformGetCursorPos(NULL, GL_FALSE, &mouse);
        if (Cocoa_IsInWindow(window, mouse.X, mouse.Y)) {
            window->State.MouseX = mouse.X;
            window->State.MouseY = mouse.Y;
        } else {
            window->State.MouseX = 0;
            window->State.MouseY = 0;
        }
    }
}

void
Cocoa_HandleMouseEvent(NSEvent *event)
{
    static GLboolean s_hasLeft = GL_FALSE;
    
    /* Only handle the focus change here, so ignore other event. */
    switch ([event type]) {
        case NSEventTypeMouseMoved:
        case NSEventTypeLeftMouseDragged:
        case NSEventTypeRightMouseDragged:
        case NSEventTypeOtherMouseDragged:
            break;
        default:
            return;
    }
    
    SFG_XYUse mouse;
    fghPlatformGetCursorPos(NULL, GL_FALSE, &mouse);
    
    SFG_Window* window = Cocoa_FindFocusWindow(&(fgStructure.Windows), mouse.X, mouse.Y);
    
    if (window) {
        s_hasLeft = GL_FALSE;
        SFG_Window* saved_window = fgStructure.CurrentWindow;
        if ((window != saved_window) && saved_window) {
            if (FETCH_WCB(*saved_window, Entry)) {
                INVOKE_WCB( *saved_window, Entry, ( GLUT_LEFT ) );
            }
        }
        fgSetWindow(window);
        window->State.MouseX = mouse.X - window->State.Xpos;
        window->State.MouseY = mouse.Y - window->State.Ypos;
        if ((window != saved_window)) {
            Cocoa_ShowCursor(window);
            
            if (FETCH_WCB( *window, Entry )) {
                INVOKE_WCB( *window, Entry, ( GLUT_ENTERED ) );
            }
        }
    } else {
        if (fgStructure.CurrentWindow && !s_hasLeft) {
            s_hasLeft = GL_TRUE;
            Cocoa_MouseOut(fgStructure.CurrentWindow);
        }
    }
}


/*
 * cursor
 */
void fgPlatformSetCursor ( SFG_Window *window, int cursorID )
{
    FREEGLUT_INTERNAL_ERROR_EXIT(window, "window is nonexistent", __FUNCTION__);
    
    if (window->Window.pContext.cursor) {
        Cocoa_FreeCursor(window->Window.pContext.cursor);
        window->Window.pContext.cursor = NULL;
    }
    
    switch (cursorID) {
        case GLUT_CURSOR_NONE:
            break;
        case GLUT_CURSOR_INHERIT:
            if( window->Parent ) {
                window->Window.pContext.cursor =
                window->Parent->Window.pContext.cursor;
            }
            break;
        default:
            window->Window.pContext.cursor = Cocoa_CreateSystemCursor(cursorID);
            break;
    }
}

void fgPlatformWarpPointer ( int x, int y )
{
    Cocoa_WarpMouseGlobal(x, y);
}

void fghPlatformGetCursorPos(const SFG_Window *window, GLboolean client, SFG_XYUse *mouse_pos)
{
    if (client && window) {
        mouse_pos->X = window->State.MouseX;
        mouse_pos->Y = window->State.MouseY;
    } else {
        const NSPoint cocoaLocation = [NSEvent mouseLocation];
        for (NSScreen *screen in [NSScreen screens]) {
            NSRect frame = [screen frame];
            if (NSMouseInRect(cocoaLocation, frame, NO)) {
                mouse_pos->X = (int) cocoaLocation.x;
                mouse_pos->Y  = (int) ((frame.origin.y + frame.size.height) - cocoaLocation.y);
                break;
            }
        }
    }
}
