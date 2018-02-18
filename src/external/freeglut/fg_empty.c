
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

#if TARGET_NO_MAIN
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
    return 0;
    
}
#endif // TARGET_NO_MAIN

#if TARGET_NO_INIT
/*
 * init
 */
void fgPlatformCloseDisplay ( void )
{
}
void fgPlatformDeinitialiseInputDevices ( void )
{
}
void fgPlatformDestroyContext ( SFG_PlatformDisplay pDisplay, SFG_WindowContextType MContext )
{
}
void fgPlatformInitialize( const char* displayName )
{
}
#endif // TARGET_NO_INIT

#if TARGET_NO_WINDOW
/*
 * windows
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
#endif // TARGET_NO_WINDOW

#if TARGET_NO_DISPLAY
/*
 * display
 */
void fgPlatformGlutSwapBuffers( SFG_PlatformDisplay *pDisplayPtr, SFG_Window* CurrentWindow )
{
}
#endif // TARGET_NO_DISPLAY

#if TARGET_NO_JOYSTICK
/*
 * joystick
 */
void fgPlatformJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
}
void fgPlatformJoystickOpen( SFG_Joystick* joy )
{
}
void fgPlatformJoystickInit( SFG_Joystick *fgJoystick[], int ident )
{
}
void fgPlatformJoystickClose ( int ident )
{
}
#endif // TARGET_NO_JOYSTICK


#if TARGET_NO_SPACEBALL
/*
 * spaceball
 */
void fgPlatformInitializeSpaceball( void )
{
}
void fgPlatformSpaceballClose( void )
{
}
void fgPlatformSpaceballSetWindow( SFG_Window *window )
{
}
int fgPlatformHasSpaceball( void )
{
    return 0;
}
int fgPlatformSpaceballNumButtons( void )
{
    return 0;
}
#endif // TARGET_NO_SPACEBALL

#if TARGET_NO_GAMEMODE
/*
* gamemode
*/
GLboolean fgPlatformChangeDisplayMode( GLboolean haveToTest )
{
    return GL_FALSE;
}
void fgPlatformEnterGameMode( void )
{
}
void fgPlatformLeaveGameMode( void )
{
}
void fgPlatformRememberState( void )
{
}
void fgPlatformRestoreState( void )
{
}
#endif // TARGET_NO_GAMEMODE

#if TARGET_NO_STRUCTURE
/*
 * structure
 */
void fgPlatformCreateWindow ( SFG_Window *window )
{
    if (window) {
        memset(window, 0x00, sizeof(SFG_Window));
    }
}
#endif // TARGET_NO_STRUCTURE

#if TARGET_NO_EXT
/*
 * ext
 */
GLUTproc fgPlatformGetGLUTProcAddress( const char* procName )
{
    return NULL;
}
SFG_Proc fgPlatformGetProcAddress( const char *procName )
{
    return NULL;
}
#endif // TARGET_NO_EXT

#if TARGET_NO_MENU
/*
 * menu
 */
GLvoid fgPlatformGetGameModeVMaxExtent( SFG_Window* window, int* x, int* y )
{
}
#endif // TARGET_NO_MENU

#if TARGET_NO_STATE
/*
 * state
 */
int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
    return -1;
}
int fgPlatformGlutGet ( GLenum eWhat )
{
    return -1;
}
int *fgPlatformGlutGetModeValues(GLenum eWhat, int *size)
{
    *size = 0;
    return NULL;
}
#endif // TARGET_NO_STATE

#if TARGET_NO_CURSOR
/*
 * cursor
 */
void fgPlatformSetCursor ( SFG_Window *window, int cursorID )
{
}
void fgPlatformWarpPointer ( int x, int y )
{
}
void fghPlatformGetCursorPos(const SFG_Window *window, GLboolean client, SFG_XYUse *mouse_pos)
{
}
#endif // TARGET_NO_CURSOR

#if TARGET_NO_SERIAL
/*
 * input_devices
 */
typedef struct {
    int dummy;
} SERIALPORT;
void fgPlatformRegisterDialDevice ( const char *dial_device )
{
}
SERIALPORT *serial_open(const char *device)
{
    return NULL;
}
void serial_close(SERIALPORT *port)
{
}
int serial_getchar(SERIALPORT *port)
{
    return EOF;
}
int serial_putchar(SERIALPORT *port, unsigned char ch)
{
    return 0;
}
void serial_flush ( SERIALPORT *port )
{
}
#endif // TARGET_NO_SERIAL

