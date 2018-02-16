#ifndef  FREEGLUT_INTERNAL_OSX_H
#define  FREEGLUT_INTERNAL_OSX_H

#include <CoreGraphics/CGDirectDisplay.h>

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
#define TARGET_NO_CURSOR     1
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
typedef int    SFG_WindowHandleType;
typedef int   SFG_WindowContextType;
typedef struct tagSFG_PlatformContext SFG_PlatformContext;
struct tagSFG_PlatformContext
{
    int device;
};

/* Window's state description. This structure should be kept portable. */
typedef struct tagSFG_PlatformWindowState SFG_PlatformWindowState;
struct tagSFG_PlatformWindowState
{
    /* Need to store window titles to emulate
     * glutSetIconTitle/glutSetWindowTitle as Windows has only
     * one title associated with a window and we need to swap
     * them out based on the window's iconic state
     */
    char*           WindowTitle;
    char*           IconTitle;
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
