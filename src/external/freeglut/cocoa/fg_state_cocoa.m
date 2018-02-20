
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

extern GLboolean Cocoa_HasKeyboard(void);
extern int Cocoa_GL_GetAtrr(int what);

/*
 * state
 */
int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
    switch( eWhat )
    {
        case GLUT_HAS_KEYBOARD:
            return (Cocoa_HasKeyboard() ? 1 : -1);
            
            /* Mac OSX should always has a mouse ? */
        case GLUT_HAS_MOUSE:
            return 1 ;
            
            /* Mac OSX normally has 2 buttons ? */
        case GLUT_NUM_MOUSE_BUTTONS:
            return 2;
            
        default:
            fgWarning( "glutDeviceGet(): missing enum handle %d", eWhat );
            break;
    }
    
    /* And now -- the failure. */
    return -1;
}

int fgPlatformGlutGet ( GLenum eWhat )
{
    switch( eWhat )
    {
            
            /*
             * Those calls are pointless under Wayland, so inform the user
             */
        case GLUT_WINDOW_X:
        case GLUT_WINDOW_Y:
        {
            if( fgStructure.CurrentWindow == NULL )
                return 0;
            
            switch ( eWhat )
            {
                case GLUT_WINDOW_WIDTH:
                    return fgStructure.CurrentWindow->State.Xpos;
                case GLUT_WINDOW_HEIGHT:
                    return fgStructure.CurrentWindow->State.Ypos;
            }
        }
            
            /*
             * TODO : support this correctly once we will start drawing
             *  client-side decorations
             */
        case GLUT_WINDOW_BORDER_WIDTH:
        case GLUT_WINDOW_HEADER_HEIGHT:
        {
            if( fgStructure.CurrentWindow == NULL ||
               fgStructure.CurrentWindow->Parent )
            /* can't get widths/heights if no current window
             * and child windows don't have borders */
                return 0;
            
            return 0;
        }
            
        case GLUT_WINDOW_WIDTH:
        case GLUT_WINDOW_HEIGHT:
        {
            if( fgStructure.CurrentWindow == NULL )
                return 0;
            
            switch ( eWhat )
            {
                case GLUT_WINDOW_WIDTH:
                    return fgStructure.CurrentWindow->State.Width;
                case GLUT_WINDOW_HEIGHT:
                    return fgStructure.CurrentWindow->State.Height;
            }
        }
    
        default:
            return Cocoa_GL_GetAtrr( eWhat );
    }
}

int *fgPlatformGlutGetModeValues(GLenum eWhat, int *size)
{
    *size = 0;
    return NULL;
}

