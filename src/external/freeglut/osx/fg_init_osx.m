
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

//#include <ApplicationServices/ApplicationServices.h>
#include <Cocoa/Cocoa.h>


/* We need this for IODisplayCreateInfoDictionary and kIODisplayOnlyPreferredName */
#include <IOKit/graphics/IOGraphicsLib.h>

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVDisplayLink.h>


extern void Cocoa_RegisterApp(void);


static const char *
Cocoa_GetDisplayName(CGDirectDisplayID displayID)
{
    CFDictionaryRef deviceInfo = IODisplayCreateInfoDictionary(CGDisplayIOServicePort(displayID), kIODisplayOnlyPreferredName);
    NSDictionary *localizedNames = [(NSDictionary *)deviceInfo objectForKey:[NSString stringWithUTF8String:kDisplayProductName]];
    const char* displayName = NULL;
    
    if ([localizedNames count] > 0) {
        displayName = strdup([[localizedNames objectForKey:[[localizedNames allKeys] objectAtIndex:0]] UTF8String]);
    }
    CFRelease(deviceInfo);
    return displayName;
}

void
Cocoa_InitModes()
{ @autoreleasepool
    {
        CGDisplayErr result;
        CGDirectDisplayID *displays;
        CGDisplayCount numDisplays;
        int pass, i;
        
        result = CGGetOnlineDisplayList(0, NULL, &numDisplays);
        if (result != kCGErrorSuccess) {
            //CG_SetError("CGGetOnlineDisplayList()", result);
            return;
        }
        displays = malloc(sizeof(CGDirectDisplayID)*numDisplays);
        result = CGGetOnlineDisplayList(numDisplays, displays, &numDisplays);
        if (result != kCGErrorSuccess) {
            //CG_SetError("CGGetOnlineDisplayList()", result);
            free(displays);
            return;
        }
        
        /* Pick up the primary display in the first pass, then get the rest */
        for (pass = 0; pass < 2; ++pass) {
            for (i = 0; i < numDisplays; ++i) {
                //SDL_VideoDisplay display;
                //SDL_DisplayData *displaydata;
                //SDL_DisplayMode mode;
                CGDisplayModeRef moderef = NULL;
                CVDisplayLinkRef link = NULL;
                
                if (pass == 0) {
                    if (!CGDisplayIsMain(displays[i])) {
                        continue;
                    }
                } else {
                    if (CGDisplayIsMain(displays[i])) {
                        continue;
                    }
                }
                
                if (CGDisplayMirrorsDisplay(displays[i]) != kCGNullDirectDisplay) {
                    continue;
                }
                
                moderef = CGDisplayCopyDisplayMode(displays[i]);
                
                if (!moderef) {
                    continue;
                }
#if 0
                displaydata = (SDL_DisplayData *) SDL_malloc(sizeof(*displaydata));
                if (!displaydata) {
                    CGDisplayModeRelease(moderef);
                    continue;
                }
                displaydata->display = displays[i];
                
                CVDisplayLinkCreateWithCGDisplay(displays[i], &link);
                
                SDL_zero(display);
                /* this returns a stddup'ed string */
                display.name = (char *)Cocoa_GetDisplayName(displays[i]);
                if (!GetDisplayMode(_this, moderef, NULL, link, &mode)) {
                    CVDisplayLinkRelease(link);
                    CGDisplayModeRelease(moderef);
                    SDL_free(display.name);
                    SDL_free(displaydata);
                    continue;
                }
                
                CVDisplayLinkRelease(link);
                
                display.desktop_mode = mode;
                display.current_mode = mode;
                display.driverdata = displaydata;
                SDL_AddVideoDisplay(&display);
                SDL_free(display.name);
#endif
            }
        }
        free(displays);
    }
}



void
Cocoa_VideoInit()
{
    Cocoa_InitModes();
    
}

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
    Cocoa_RegisterApp();
    Cocoa_VideoInit();
}
