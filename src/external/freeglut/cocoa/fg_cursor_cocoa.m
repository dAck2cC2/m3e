
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"


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
    
#if 0
    /* CGWarpMouseCursorPosition doesn't generate a window event, unlike our
     * other implementations' APIs. Send what's appropriate.
     */
    if (!mouse->relative_mode) {
        SDL_Window *win = SDL_FindWindowAtPoint(x, y);
        SDL_SetMouseFocus(win);
        if (win) {
            SDL_assert(win == mouse->focus);
            SDL_SendMouseMotion(win, mouse->mouseID, 0, x - win->x, y - win->y);
        }
    }
#endif
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

static void
Cocoa_MouseMove(NSEvent *event)
{ @autoreleasepool
    {
        SFG_Window* window = fgStructure.CurrentWindow;
        if (!window) {
            return;
        }
        
        if( window->ActiveMenu ) {
            fgUpdateMenuHighlight(window->ActiveMenu);
            return;
        }
        
        const NSPoint location =  [NSEvent mouseLocation];
        window->State.MouseX = location.x;
        window->State.MouseY = location.y;
        
        if( NSEventTypeMouseMoved == [event type] ) {
            INVOKE_WCB( *window, Motion, ( window->State.MouseX,
                                          window->State.MouseY ) );
        } else {
            INVOKE_WCB( *window, Passive, ( window->State.MouseX,
                                           window->State.MouseY ) );
        }
    }
}


void
Cocoa_InitMouse(SFG_Window* window)
{
    if (window) {
        window->Window.pContext.cursor = Cocoa_CreateDefaultCursor();
        
        const NSPoint location =  [NSEvent mouseLocation];
        window->State.MouseX = location.x;
        window->State.MouseY = location.y;
    }
}


void
Cocoa_HandleMouseEvent(NSEvent *event)
{
    switch ([event type]) {
        case NSEventTypeMouseMoved:
        case NSEventTypeLeftMouseDragged:
        case NSEventTypeRightMouseDragged:
        case NSEventTypeOtherMouseDragged:
            Cocoa_MouseMove(event);
            break;
        default:
            /* Ignore any other events. */
            return;
    }
}

void
Cocoa_HandleMouseWheel(SFG_Window *window, NSEvent *event)
{
    if (!window || !event) {
        return;
    }
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
    
    INVOKE_WCB( *window, MouseWheel, ( 0,
                                      direction,
                                      x,
                                      y ));
}

/*
 * cursor
 */
void fgPlatformSetCursor ( SFG_Window *window, int cursorID )
{
    if (!window) {
        return;
    }
    
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
