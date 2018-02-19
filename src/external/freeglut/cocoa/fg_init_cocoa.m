
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

/* We need this for IODisplayCreateInfoDictionary and kIODisplayOnlyPreferredName */
#include <IOKit/graphics/IOGraphicsLib.h>

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVDisplayLink.h>

/* -- PRIVATE FUNCTION DECLARATIONS ---------------------------------------- */

extern void Cocoa_RegisterApp(void);  /* fg_main_osx.m */
extern void Cocoa_InitKeyboard(void);

/* -- FUNCTION DEFINITION ---------------------------------------- */

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

static GLboolean
GetDisplayMode(CGDisplayModeRef vidmode, CFArrayRef modelist, CVDisplayLinkRef link, SFG_Display * disp)
{
    int width = (int) CGDisplayModeGetWidth(vidmode);
    int height = (int) CGDisplayModeGetHeight(vidmode);
    int bpp = 0;
    int refreshRate = 0;
    CFStringRef fmt;
    
    /* Ignore this mode if it's low-dpi (@1x) and we have a high-dpi mode in the
     * list with the same size in points.
     */
#ifdef MAC_OS_X_VERSION_10_8
    if (modelist != NULL && floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_7) {
        int pixelW = (int) CGDisplayModeGetPixelWidth(vidmode);
        int pixelH = (int) CGDisplayModeGetPixelHeight(vidmode);
        
        if (width == pixelW && height == pixelH) {
            CFIndex modescount = CFArrayGetCount(modelist);
            
            for (int i = 0; i < modescount; i++) {
                CGDisplayModeRef othermode = (CGDisplayModeRef) CFArrayGetValueAtIndex(modelist, i);
                
                if (CFEqual(vidmode, othermode)) {
                    continue;
                }
                
                int otherW = (int) CGDisplayModeGetWidth(othermode);
                int otherH = (int) CGDisplayModeGetHeight(othermode);
                
                int otherpixelW = (int) CGDisplayModeGetPixelWidth(othermode);
                int otherpixelH = (int) CGDisplayModeGetPixelHeight(othermode);
                
                if (width == otherW && height == otherH && (otherpixelW != otherW || otherpixelH != otherH)) {
                    return GL_FALSE;
                }
            }
        }
    }
#endif
    
    if (!disp) {
        return GL_FALSE;
    }
    disp->pDisplay.moderef = vidmode;
    
    fmt = CGDisplayModeCopyPixelEncoding(vidmode);
    refreshRate = (int) (CGDisplayModeGetRefreshRate(vidmode) + 0.5);
    
    if (CFStringCompare(fmt, CFSTR(IO32BitDirectPixels),
                        kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
        bpp = 32;
    } else if (CFStringCompare(fmt, CFSTR(IO16BitDirectPixels),
                               kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
        bpp = 16;
    } else if (CFStringCompare(fmt, CFSTR(kIO30BitDirectPixels),
                               kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
        bpp = 30;
    } else {
        bpp = 0;  /* ignore 8-bit and such for now. */
    }
    
    CFRelease(fmt);
    
    /* CGDisplayModeGetRefreshRate returns 0 for many non-CRT displays. */
    if (refreshRate == 0 && link != NULL) {
        CVTime time = CVDisplayLinkGetNominalOutputVideoRefreshPeriod(link);
        if ((time.flags & kCVTimeIsIndefinite) == 0 && time.timeValue != 0) {
            refreshRate = (int) ((time.timeScale / (double) time.timeValue) + 0.5);
        }
    }
    
    switch (bpp) {
        case 16:
        case 30:
        case 32:
            disp->pDisplay.bpp = bpp;
            break;
        case 8: /* We don't support palettized modes now */
        default: /* Totally unrecognizable bit depth. */
            return GL_FALSE;
    }
    
    CGSize physicalSize = CGDisplayScreenSize(disp->pDisplay.display);
    
    disp->ScreenWidth    = width;
    disp->ScreenHeight   = height;
    disp->ScreenWidthMM  = physicalSize.width;
    disp->ScreenHeightMM = physicalSize.height;
    disp->pDisplay.refreshRate = refreshRate;
    
    return GL_TRUE;
}


void
Cocoa_InitModes()
{ @autoreleasepool
    {
        CGDisplayErr result;
        CGDirectDisplayID *displays;
        CGDisplayCount numDisplays;
        int pass = 0, i = 0;
        
        result = CGGetOnlineDisplayList(0, NULL, &numDisplays);
        if (result != kCGErrorSuccess) {
            fgError("CGGetOnlineDisplayList() return:%d", result);
            return;
        }
        displays = malloc(sizeof(CGDirectDisplayID)*numDisplays);
        result = CGGetOnlineDisplayList(numDisplays, displays, &numDisplays);
        if (result != kCGErrorSuccess) {
            fgError("CGGetOnlineDisplayList() return:%d", result);
            free(displays);
            return;
        }
        
        /* Pick up the primary display in the first pass, then get the rest */
        //for (pass = 0; pass < 2; ++pass)
        // Only support the primary display currently.
        {
            for (i = 0; i < numDisplays; ++i) {
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
                
                memset(&fgDisplay, 0x00, sizeof(fgDisplay));
                fgDisplay.pDisplay.display = displays[i];
                CVDisplayLinkCreateWithCGDisplay(displays[i], &link);
                
                /* this returns a stddup'ed string */
                fgDisplay.pDisplay.name = (char *)Cocoa_GetDisplayName(displays[i]);
                
                if (!GetDisplayMode(moderef, NULL, link, &fgDisplay)) {
                    CVDisplayLinkRelease(link);
                    CGDisplayModeRelease(moderef);
                    free(fgDisplay.pDisplay.name);
                    continue;
                }
                
                CVDisplayLinkRelease(link);
            }
        }
        free(displays);
    }
}

void
Cocoa_VideoInit()
{
    Cocoa_InitModes();
    Cocoa_InitKeyboard();
}

/*
 * init
 */
void fgPlatformCloseDisplay ( void )
{
}

void fgPlatformDeinitialiseInputDevices ( void )
{
    fgInputDeviceClose();
    
    fgState.InputDevsInitialised = GL_FALSE;
}

void fgPlatformDestroyContext ( SFG_PlatformDisplay pDisplay, SFG_WindowContextType MContext )
{
}

void fgPlatformInitialize( const char* displayName )
{
    Cocoa_RegisterApp();
    Cocoa_VideoInit();
    
    /* Get start time */
    fgState.Time = fgSystemTime();
    fgState.Initialised = GL_TRUE;
    
    atexit(fgDeinitialize);
    
    /* InputDevice uses GlutTimerFunc(), so fgState.Initialised must be TRUE */
    fgInitialiseInputDevices();
}
