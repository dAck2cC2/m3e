
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

#include <IOKit/hid/IOHIDLib.h>


#define GLUT_SCANCODE_UNKNOWN   (-1)

typedef struct tagSFG_PlatformScancode SFG_PlatformScancode;
struct tagSFG_PlatformScancode {
    GLint     code;
    GLboolean isSpecial;
};

static const SFG_PlatformScancode darwin_scancode_table[] = {
    /*   0    SDL_SCANCODE_A, */ {'A', GL_FALSE},
    /*   1    SDL_SCANCODE_S, */ {'S', GL_FALSE},
    /*   2    SDL_SCANCODE_D, */ {'D', GL_FALSE},
    /*   3    SDL_SCANCODE_F, */ {'F', GL_FALSE},
    /*   4    SDL_SCANCODE_H, */ {'H', GL_FALSE},
    /*   5    SDL_SCANCODE_G, */ {'G', GL_FALSE},
    /*   6    SDL_SCANCODE_Z, */ {'Z', GL_FALSE},
    /*   7    SDL_SCANCODE_X, */ {'X', GL_FALSE},
    /*   8    SDL_SCANCODE_C, */ {'C', GL_FALSE},
    /*   9    SDL_SCANCODE_V, */ {'V', GL_FALSE},
    /*  10    SDL_SCANCODE_NONUSBACKSLASH,  SDL_SCANCODE_NONUSBACKSLASH on ANSI and JIS keyboards (if this key would exist there), SDL_SCANCODE_GRAVE on ISO. (The USB keyboard driver actually translates these usage codes to different virtual key codes depending on whether the keyboard is ISO/ANSI/JIS. That's why you have to help it identify the keyboard type when you plug in a PC USB keyboard. It's a historical thing - ADB keyboards are wired this way.) */
    {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  11    SDL_SCANCODE_B, */ {'B', GL_FALSE},
    /*  12    SDL_SCANCODE_Q, */ {'Q', GL_FALSE},
    /*  13    SDL_SCANCODE_W, */ {'W', GL_FALSE},
    /*  14    SDL_SCANCODE_E, */ {'E', GL_FALSE},
    /*  15    SDL_SCANCODE_R, */ {'R', GL_FALSE},
    /*  16    SDL_SCANCODE_Y, */ {'Y', GL_FALSE},
    /*  17    SDL_SCANCODE_T, */ {'T', GL_FALSE},
    /*  18    SDL_SCANCODE_1, */ {'1', GL_FALSE},
    /*  19    SDL_SCANCODE_2, */ {'2', GL_FALSE},
    /*  20    SDL_SCANCODE_3, */ {'3', GL_FALSE},
    /*  21    SDL_SCANCODE_4, */ {'4', GL_FALSE},
    /*  22    SDL_SCANCODE_6, */ {'6', GL_FALSE},
    /*  23    SDL_SCANCODE_5, */ {'5', GL_FALSE},
    /*  24    SDL_SCANCODE_EQUALS, */ {'=', GL_FALSE},
    /*  25    SDL_SCANCODE_9, */ {'9', GL_FALSE},
    /*  26    SDL_SCANCODE_7, */ {'7', GL_FALSE},
    /*  27    SDL_SCANCODE_MINUS, */ {'-', GL_FALSE},
    /*  28    SDL_SCANCODE_8, */ {'8', GL_FALSE},
    /*  29    SDL_SCANCODE_0, */ {'0', GL_FALSE},
    /*  30    SDL_SCANCODE_RIGHTBRACKET, */ {'}', GL_FALSE},
    /*  31    SDL_SCANCODE_O, */ {'O', GL_FALSE},
    /*  32    SDL_SCANCODE_U, */ {'U', GL_FALSE},
    /*  33    SDL_SCANCODE_LEFTBRACKET, */ {'{', GL_FALSE},
    /*  34    SDL_SCANCODE_I, */ {'I', GL_FALSE},
    /*  35    SDL_SCANCODE_P, */ {'P', GL_FALSE},
    /*  36    SDL_SCANCODE_RETURN, */ {'\r', GL_FALSE},
    /*  37    SDL_SCANCODE_L, */ {'L', GL_FALSE},
    /*  38    SDL_SCANCODE_J, */ {'J', GL_FALSE},
    /*  39    SDL_SCANCODE_APOSTROPHE, */ {'\'', GL_FALSE},
    /*  40    SDL_SCANCODE_K, */ {'K', GL_FALSE},
    /*  41    SDL_SCANCODE_SEMICOLON, */ {';', GL_FALSE},
    /*  42    SDL_SCANCODE_BACKSLASH, */ {'\\', GL_FALSE},
    /*  43    SDL_SCANCODE_COMMA, */ {',', GL_FALSE},
    /*  44    SDL_SCANCODE_SLASH, */ {'/', GL_FALSE},
    /*  45    SDL_SCANCODE_N, */ {'N', GL_FALSE},
    /*  46    SDL_SCANCODE_M, */ {'M', GL_FALSE},
    /*  47    SDL_SCANCODE_PERIOD, */ {'.', GL_FALSE},
    /*  48    SDL_SCANCODE_TAB, */ {'\t', GL_FALSE},
    /*  49    SDL_SCANCODE_SPACE, */ {' ', GL_FALSE},
    /*  50    SDL_SCANCODE_GRAVE,  SDL_SCANCODE_GRAVE on ANSI and JIS keyboards, SDL_SCANCODE_NONUSBACKSLASH on ISO (see comment about virtual key code 10 above) */
    {'`', GL_FALSE},
    /*  51    SDL_SCANCODE_BACKSPACE, */ {8, GL_FALSE},
    /*  52    SDL_SCANCODE_KP_ENTER,  keyboard enter on portables */
    {13, GL_FALSE},
    /*  53    SDL_SCANCODE_ESCAPE, */ {27, GL_FALSE},
    /*  54    SDL_SCANCODE_RGUI, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  55    SDL_SCANCODE_LGUI, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  56    SDL_SCANCODE_LSHIFT, */ {GLUT_KEY_SHIFT_L, GL_TRUE},
    /*  57    SDL_SCANCODE_CAPSLOCK, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  58    SDL_SCANCODE_LALT, */ {GLUT_KEY_ALT_L, GL_TRUE},
    /*  59    SDL_SCANCODE_LCTRL, */ {GLUT_KEY_CTRL_L, GL_TRUE},
    /*  60    SDL_SCANCODE_RSHIFT, */ {GLUT_KEY_SHIFT_R, GL_TRUE},
    /*  61    SDL_SCANCODE_RALT, */ {GLUT_KEY_SHIFT_R, GL_TRUE},
    /*  62    SDL_SCANCODE_RCTRL, */ {GLUT_KEY_CTRL_R, GL_TRUE},
    /*  63    SDL_SCANCODE_RGUI, fn on portables, acts as a hardware-level modifier already, so we don't generate events for it, also XK_Meta_R */
    {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  64    SDL_SCANCODE_F17, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  65    SDL_SCANCODE_KP_PERIOD, */ {'~', GL_FALSE},
    /*  66    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  67    SDL_SCANCODE_KP_MULTIPLY, */ {'*', GL_FALSE},
    /*  68    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  69    SDL_SCANCODE_KP_PLUS, */ {'+', GL_FALSE},
    /*  70    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  71    SDL_SCANCODE_NUMLOCKCLEAR, */ {GLUT_KEY_NUM_LOCK, GL_TRUE},
    /*  72    SDL_SCANCODE_VOLUMEUP, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  73    SDL_SCANCODE_VOLUMEDOWN, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  74    SDL_SCANCODE_MUTE, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  75    SDL_SCANCODE_KP_DIVIDE, */ {'%', GL_FALSE},
    /*  76    SDL_SCANCODE_KP_ENTER, keypad enter on external keyboards, fn-return on portables */ {13, GL_FALSE},
    /*  77    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  78    SDL_SCANCODE_KP_MINUS, */ {'-', GL_FALSE},
    /*  79    SDL_SCANCODE_F18, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  80    SDL_SCANCODE_F19, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  81    SDL_SCANCODE_KP_EQUALS, */ {'=', GL_FALSE},
    /*  82    SDL_SCANCODE_KP_0, */ {'0', GL_FALSE},
    /*  83    SDL_SCANCODE_KP_1, */ {'1', GL_FALSE},
    /*  84    SDL_SCANCODE_KP_2, */ {'2', GL_FALSE},
    /*  85    SDL_SCANCODE_KP_3, */ {'3', GL_FALSE},
    /*  86    SDL_SCANCODE_KP_4, */ {'4', GL_FALSE},
    /*  87    SDL_SCANCODE_KP_5, */ {'5', GL_FALSE},
    /*  88    SDL_SCANCODE_KP_6, */ {'6', GL_FALSE},
    /*  89    SDL_SCANCODE_KP_7, */ {'7', GL_FALSE},
    /*  90    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  91    SDL_SCANCODE_KP_8, */ {'8', GL_FALSE},
    /*  92    SDL_SCANCODE_KP_9, */ {'9', GL_FALSE},
    /*  93    SDL_SCANCODE_INTERNATIONAL3,  Cosmo_USB2ADB.c says "Yen (JIS)"  */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  94    SDL_SCANCODE_INTERNATIONAL1,  Cosmo_USB2ADB.c says "Ro (JIS)"  */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  95    SDL_SCANCODE_KP_COMMA,  Cosmo_USB2ADB.c says ", JIS only"  */ {',', GL_FALSE},
    /*  96    SDL_SCANCODE_F5, */ {GLUT_KEY_F5, GL_TRUE},
    /*  97    SDL_SCANCODE_F6, */ {GLUT_KEY_F6, GL_TRUE},
    /*  98    SDL_SCANCODE_F7, */ {GLUT_KEY_F7, GL_TRUE},
    /*  99    SDL_SCANCODE_F3, */ {GLUT_KEY_F3, GL_TRUE},
    /* 100    SDL_SCANCODE_F8, */ {GLUT_KEY_F8, GL_TRUE},
    /* 101    SDL_SCANCODE_F9, */ {GLUT_KEY_F9, GL_TRUE},
    /* 102    SDL_SCANCODE_LANG2,  Cosmo_USB2ADB.c says "Eisu" */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 103    SDL_SCANCODE_F11, */ {GLUT_KEY_F11, GL_TRUE},
    /* 104    SDL_SCANCODE_LANG1,  Cosmo_USB2ADB.c says "Kana" */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 105    SDL_SCANCODE_PRINTSCREEN,  On ADB keyboards, this key is labeled "F13/print screen". Problem: USB has different usage codes for these two functions. On Apple USB keyboards, the key is labeled "F13" and sends the F13 usage code (SDL_SCANCODE_F13). I decided to use SDL_SCANCODE_PRINTSCREEN here nevertheless since SDL applications are more likely to assume the presence of a print screen key than an F13 key. */
    {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 106    SDL_SCANCODE_F16, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 107    SDL_SCANCODE_SCROLLLOCK,  F14/scroll lock, see comment about F13/print screen above */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 108    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 109    SDL_SCANCODE_F10, */ {GLUT_KEY_F10, GL_TRUE},
    /* 110    SDL_SCANCODE_APPLICATION, windows contextual menu key, fn-enter on portables */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 111    SDL_SCANCODE_F12, */ {GLUT_KEY_F12, GL_TRUE},
    /* 112    SDL_SCANCODE_UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 113    SDL_SCANCODE_PAUSE,  F15/pause, see comment about F13/print screen above */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 114    SDL_SCANCODE_INSERT,  the key is actually labeled "help" on Apple keyboards, and works as such in Mac OS, but it sends the "insert" usage code even on Apple USB keyboards */
    {GLUT_KEY_INSERT, GL_TRUE},
    /* 115    SDL_SCANCODE_HOME, */ {GLUT_KEY_HOME, GL_TRUE},
    /* 116    SDL_SCANCODE_PAGEUP, */ {GLUT_KEY_PAGE_UP, GL_TRUE},
    /* 117    SDL_SCANCODE_DELETE, */ {GLUT_KEY_DELETE, GL_TRUE},
    /* 118    SDL_SCANCODE_F4, */ {GLUT_KEY_F4, GL_TRUE},
    /* 119    SDL_SCANCODE_END, */ {GLUT_KEY_END, GL_TRUE},
    /* 120    SDL_SCANCODE_F2, */ {GLUT_KEY_F2, GL_TRUE},
    /* 121    SDL_SCANCODE_PAGEDOWN, */ {GLUT_KEY_PAGE_DOWN, GL_TRUE},
    /* 122    SDL_SCANCODE_F1, */ {GLUT_KEY_F1, GL_TRUE},
    /* 123    SDL_SCANCODE_LEFT, */ {GLUT_KEY_LEFT, GL_TRUE},
    /* 124    SDL_SCANCODE_RIGHT, */ {GLUT_KEY_RIGHT, GL_TRUE},
    /* 125    SDL_SCANCODE_DOWN, */ {GLUT_KEY_DOWN, GL_TRUE},
    /* 126    SDL_SCANCODE_UP, */ {GLUT_KEY_UP, GL_TRUE},
    /* 127    SDL_SCANCODE_POWER */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
}; /* darwin_scancode_table */
#define SIZE_SCANCODE_TABLE  (sizeof(darwin_scancode_table) / sizeof(SFG_PlatformScancode))

static IOHIDManagerRef s_hidManager = NULL;

static void
HIDCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value)
{
    if (context != s_hidManager) {
        /* An old callback, ignore it (related to bug 2157 below) */
        return;
    }
    
    IOHIDElementRef elem = IOHIDValueGetElement(value);
    if (IOHIDElementGetUsagePage(elem) != kHIDPage_KeyboardOrKeypad
        || IOHIDElementGetUsage(elem) != kHIDUsage_KeyboardCapsLock) {
        return;
    }
    //CFIndex pressed = IOHIDValueGetIntegerValue(value);
    //SDL_SendKeyboardKey(pressed ? SDL_PRESSED : SDL_RELEASED, SDL_SCANCODE_CAPSLOCK);
}

static void
QuitHIDCallback()
{
    if (!s_hidManager) {
        return;
    }
    
#if 0 /* Releasing here causes a crash on Mac OS X 10.10 and earlier,
* so just leak it for now. See bug 2157 for details.
*/
    IOHIDManagerUnscheduleFromRunLoop(s_hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    IOHIDManagerRegisterInputValueCallback(s_hidManager, NULL, NULL);
    IOHIDManagerClose(s_hidManager, 0);
    
    CFRelease(s_hidManager);
#endif
    s_hidManager = NULL;
}

static CFDictionaryRef
CreateHIDDeviceMatchingDictionary(UInt32 usagePage, UInt32 usage)
{
    CFMutableDictionaryRef dict = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                                            0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    if (dict) {
        CFNumberRef number = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usagePage);
        if (number) {
            CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsagePageKey), number);
            CFRelease(number);
            number = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage);
            if (number) {
                CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsageKey), number);
                CFRelease(number);
                return dict;
            }
        }
        CFRelease(dict);
    }
    return NULL;
}

static void
InitHIDCallback()
{
    s_hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    if (!s_hidManager) {
        return;
    }
    CFDictionaryRef keyboard = NULL, keypad = NULL;
    CFArrayRef matches = NULL;
    keyboard = CreateHIDDeviceMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
    if (!keyboard) {
        goto fail;
    }
    keypad = CreateHIDDeviceMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Keypad);
    if (!keypad) {
        goto fail;
    }
    CFDictionaryRef matchesList[] = { keyboard, keypad };
    matches = CFArrayCreate(kCFAllocatorDefault, (const void **)matchesList, 2, NULL);
    if (!matches) {
        goto fail;
    }
    IOHIDManagerSetDeviceMatchingMultiple(s_hidManager, matches);
    IOHIDManagerRegisterInputValueCallback(s_hidManager, HIDCallback, s_hidManager);
    IOHIDManagerScheduleWithRunLoop(s_hidManager, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
    if (IOHIDManagerOpen(s_hidManager, kIOHIDOptionsTypeNone) == kIOReturnSuccess) {
        goto cleanup;
    }
    
fail:
    QuitHIDCallback();
    
cleanup:
    if (matches) {
        CFRelease(matches);
    }
    if (keypad) {
        CFRelease(keypad);
    }
    if (keyboard) {
        CFRelease(keyboard);
    }
}


void
Cocoa_InitKeyboard(void)
{
    InitHIDCallback();
}

void
Cocoa_QuitKeyboard(void)
{
    QuitHIDCallback();
}

GLboolean
Cocoa_HasKeyboard(void)
{
    if (s_hidManager) {
        return GL_TRUE;
    } else {
        return GL_FALSE;
    }
}

void
Cocoa_HandleKeyEvent(NSEvent *event)
{
    FGCBKeyboardUC keyboard_cb = NULL;
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData keyboard_ud = NULL;
    FGCBUserData special_ud = NULL;
    
    SFG_Window* window = fgStructure.CurrentWindow;
    if (!window) {
        return;
    }
    
    switch ([event type]) {
        case NSEventTypeKeyDown:
            if (( fgState.KeyRepeat==GLUT_KEY_REPEAT_OFF || window->State.IgnoreKeyRepeat==GL_TRUE ) && ![event isARepeat]) {
                return;
            }
            keyboard_cb = (FGCBKeyboardUC)( FETCH_WCB( *window, Keyboard ));
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, Special  ));
            keyboard_ud = FETCH_USER_DATA_WCB( *window, Keyboard );
            special_ud  = FETCH_USER_DATA_WCB( *window, Special  );
            break;
        case NSEventTypeKeyUp:
            keyboard_cb = (FGCBKeyboardUC)( FETCH_WCB( *window, KeyboardUp ));
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
            keyboard_ud = FETCH_USER_DATA_WCB( *window, KeyboardUp );
            special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
            break;
        case NSEventTypeFlagsChanged:
            /* FIXME CW 2007-08-14: check if this whole mess that takes up half of this file is really necessary */
            //HandleModifiers(_this, scancode, [event modifierFlags]);
            break;
        default: /* just to avoid compiler warnings */
            break;
    }
    
    unsigned short scancode = [event keyCode];
    if ((scancode >= SIZE_SCANCODE_TABLE)
    ||  (darwin_scancode_table[scancode].code == GLUT_SCANCODE_UNKNOWN)) {
        return;
    }
    
    if (darwin_scancode_table[scancode].isSpecial && special_cb) {
        special_cb( darwin_scancode_table[scancode].code, window->State.MouseX, window->State.MouseY, special_ud );
    }
    else if (!darwin_scancode_table[scancode].isSpecial && keyboard_cb) {
        keyboard_cb( darwin_scancode_table[scancode].code, window->State.MouseX, window->State.MouseY, keyboard_ud );
    }
}

