
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
    /*   0  A, */ {'A', GL_FALSE},
    /*   1  S, */ {'S', GL_FALSE},
    /*   2  D, */ {'D', GL_FALSE},
    /*   3  F, */ {'F', GL_FALSE},
    /*   4  H, */ {'H', GL_FALSE},
    /*   5  G, */ {'G', GL_FALSE},
    /*   6  Z, */ {'Z', GL_FALSE},
    /*   7  X, */ {'X', GL_FALSE},
    /*   8  C, */ {'C', GL_FALSE},
    /*   9  V, */ {'V', GL_FALSE},
    /*  10  NONUSBACKSLASH, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* NONUSBACKSLASH on ANSI and JIS keyboards (if this key would exist there), SDL_SCANCODE_GRAVE on ISO. (The USB keyboard driver actually translates these usage codes to different virtual key codes depending on whether the keyboard is ISO/ANSI/JIS. That's why you have to help it identify the keyboard type when you plug in a PC USB keyboard. It's a historical thing - ADB keyboards are wired this way.) */
    /*  11  B, */ {'B', GL_FALSE},
    /*  12  Q, */ {'Q', GL_FALSE},
    /*  13  W, */ {'W', GL_FALSE},
    /*  14  E, */ {'E', GL_FALSE},
    /*  15  R, */ {'R', GL_FALSE},
    /*  16  Y, */ {'Y', GL_FALSE},
    /*  17  T, */ {'T', GL_FALSE},
    /*  18  1, */ {'1', GL_FALSE},
    /*  19  2, */ {'2', GL_FALSE},
    /*  20  3, */ {'3', GL_FALSE},
    /*  21  4, */ {'4', GL_FALSE},
    /*  22  6, */ {'6', GL_FALSE},
    /*  23  5, */ {'5', GL_FALSE},
    /*  24  EQUALS, */ {'=', GL_FALSE},
    /*  25  9, */ {'9', GL_FALSE},
    /*  26  7, */ {'7', GL_FALSE},
    /*  27  MINUS, */ {'-', GL_FALSE},
    /*  28  8, */ {'8', GL_FALSE},
    /*  29  0, */ {'0', GL_FALSE},
    /*  30  RIGHTBRACKET, */ {'}', GL_FALSE},
    /*  31  O, */ {'O', GL_FALSE},
    /*  32  U, */ {'U', GL_FALSE},
    /*  33  LEFTBRACKET, */ {'{', GL_FALSE},
    /*  34  I, */ {'I', GL_FALSE},
    /*  35  P, */ {'P', GL_FALSE},
    /*  36  RETURN, */ {'\r', GL_FALSE},
    /*  37  L, */ {'L', GL_FALSE},
    /*  38  J, */ {'J', GL_FALSE},
    /*  39  APOSTROPHE, */ {'\'', GL_FALSE},
    /*  40  K, */ {'K', GL_FALSE},
    /*  41  SEMICOLON, */ {';', GL_FALSE},
    /*  42  BACKSLASH, */ {'\\', GL_FALSE},
    /*  43  COMMA, */ {',', GL_FALSE},
    /*  44  SLASH, */ {'/', GL_FALSE},
    /*  45  N, */ {'N', GL_FALSE},
    /*  46  M, */ {'M', GL_FALSE},
    /*  47  PERIOD, */ {'.', GL_FALSE},
    /*  48  TAB, */ {'\t', GL_FALSE},
    /*  49  SPACE, */ {' ', GL_FALSE},
    /*  50  GRAVE, */ {'`', GL_FALSE}, /* GRAVE on ANSI and JIS keyboards, SDL_SCANCODE_NONUSBACKSLASH on ISO (see comment about virtual key code 10 above) */
    /*  51  BACKSPACE, */ {8, GL_FALSE},
    /*  52  KP_ENTER, */  {13, GL_FALSE}, /* keyboard enter on portables */
    /*  53  ESCAPE, */ {27, GL_FALSE},
    /*  54  RGUI, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  55  LGUI, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  56  LSHIFT, */ {GLUT_KEY_SHIFT_L, GL_TRUE},
    /*  57  CAPSLOCK, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  58  LALT, */ {GLUT_KEY_ALT_L, GL_TRUE},
    /*  59  LCTRL, */ {GLUT_KEY_CTRL_L, GL_TRUE},
    /*  60  RSHIFT, */ {GLUT_KEY_SHIFT_R, GL_TRUE},
    /*  61  RALT, */ {GLUT_KEY_SHIFT_R, GL_TRUE},
    /*  62  RCTRL, */ {GLUT_KEY_CTRL_R, GL_TRUE},
    /*  63  RGUI, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE}, /* fn on portables, acts as a hardware-level modifier already, so we don't generate events for it, also XK_Meta_R */
    /*  64  F17, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  65  KP_PERIOD, */ {'~', GL_FALSE},
    /*  66  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  67  KP_MULTIPLY, */ {'*', GL_FALSE},
    /*  68  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  69  KP_PLUS, */ {'+', GL_FALSE},
    /*  70  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  71  NUMLOCKCLEAR, */ {GLUT_KEY_NUM_LOCK, GL_TRUE},
    /*  72  VOLUMEUP, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  73  VOLUMEDOWN, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  74  MUTE, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  75  KP_DIVIDE, */ {'%', GL_FALSE},
    /*  76  KP_ENTER, */  {13, GL_FALSE}, /* keypad enter on external keyboards, fn-return on portables */
    /*  77  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  78  KP_MINUS, */ {'-', GL_FALSE},
    /*  79  F18, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  80  F19, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  81  KP_EQUALS, */ {'=', GL_FALSE},
    /*  82  KP_0, */ {'0', GL_FALSE},
    /*  83  KP_1, */ {'1', GL_FALSE},
    /*  84  KP_2, */ {'2', GL_FALSE},
    /*  85  KP_3, */ {'3', GL_FALSE},
    /*  86  KP_4, */ {'4', GL_FALSE},
    /*  87  KP_5, */ {'5', GL_FALSE},
    /*  88  KP_6, */ {'6', GL_FALSE},
    /*  89  KP_7, */ {'7', GL_FALSE},
    /*  90  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  91  KP_8, */ {'8', GL_FALSE},
    /*  92  KP_9, */ {'9', GL_FALSE},
    /*  93  INTERNATIONAL3,  Cosmo_USB2ADB.c says "Yen (JIS)"  */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  94  INTERNATIONAL1,  Cosmo_USB2ADB.c says "Ro (JIS)"  */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /*  95  KP_COMMA,  Cosmo_USB2ADB.c says ", JIS only"  */ {',', GL_FALSE},
    /*  96  F5, */ {GLUT_KEY_F5, GL_TRUE},
    /*  97  F6, */ {GLUT_KEY_F6, GL_TRUE},
    /*  98  F7, */ {GLUT_KEY_F7, GL_TRUE},
    /*  99  F3, */ {GLUT_KEY_F3, GL_TRUE},
    /* 100  F8, */ {GLUT_KEY_F8, GL_TRUE},
    /* 101  F9, */ {GLUT_KEY_F9, GL_TRUE},
    /* 102  LANG2,  Cosmo_USB2ADB.c says "Eisu" */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 103  F11, */ {GLUT_KEY_F11, GL_TRUE},
    /* 104  LANG1,  Cosmo_USB2ADB.c says "Kana" */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 105  PRINTSCREEN,  On ADB keyboards, this key is labeled "F13/print screen". Problem: USB has different usage codes for these two functions. On Apple USB keyboards, the key is labeled "F13" and sends the F13 usage code (SDL_SCANCODE_F13). I decided to use SDL_SCANCODE_PRINTSCREEN here nevertheless since SDL applications are more likely to assume the presence of a print screen key than an F13 key. */
    {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 106  F16, */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 107  SCROLLLOCK,  F14/scroll lock, see comment about F13/print screen above */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 108  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 109  F10, */ {GLUT_KEY_F10, GL_TRUE},
    /* 110  APPLICATION, windows contextual menu key, fn-enter on portables */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 111  F12, */ {GLUT_KEY_F12, GL_TRUE},
    /* 112  UNKNOWN,  unknown (unused?) */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 113  PAUSE,  F15/pause, see comment about F13/print screen above */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
    /* 114  INSERT,  the key is actually labeled "help" on Apple keyboards, and works as such in Mac OS, but it sends the "insert" usage code even on Apple USB keyboards */
    {GLUT_KEY_INSERT, GL_TRUE},
    /* 115  HOME, */ {GLUT_KEY_HOME, GL_TRUE},
    /* 116  PAGEUP, */ {GLUT_KEY_PAGE_UP, GL_TRUE},
    /* 117  DELETE, */ {GLUT_KEY_DELETE, GL_TRUE},
    /* 118  F4, */ {GLUT_KEY_F4, GL_TRUE},
    /* 119  END, */ {GLUT_KEY_END, GL_TRUE},
    /* 120  F2, */ {GLUT_KEY_F2, GL_TRUE},
    /* 121  PAGEDOWN, */ {GLUT_KEY_PAGE_DOWN, GL_TRUE},
    /* 122  F1, */ {GLUT_KEY_F1, GL_TRUE},
    /* 123  LEFT, */ {GLUT_KEY_LEFT, GL_TRUE},
    /* 124  RIGHT, */ {GLUT_KEY_RIGHT, GL_TRUE},
    /* 125  DOWN, */ {GLUT_KEY_DOWN, GL_TRUE},
    /* 126  UP, */ {GLUT_KEY_UP, GL_TRUE},
    /* 127  POWER */ {GLUT_SCANCODE_UNKNOWN, GL_FALSE},
}; /* darwin_scancode_table */
#define SIZE_SCANCODE_TABLE  (sizeof(darwin_scancode_table) / sizeof(SFG_PlatformScancode))

static IOHIDManagerRef s_hidManager = NULL;
static int             s_iModifiersOS   = 0;
static int             s_iModifiersGLUT = 0;
static GLboolean       s_isCapsLockOn = GL_FALSE;

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
    CFIndex pressed = IOHIDValueGetIntegerValue(value);
    if (!pressed) {
        s_isCapsLockOn = !s_isCapsLockOn;
    }
#if 0
    SFG_Window* window = fgStructure.CurrentWindow;
    freeglut_return_if_fail(window);
    
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData  special_ud = NULL;
    if (pressed) {
        special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, Special  ));
        special_ud  = FETCH_USER_DATA_WCB( *window, Special  );
    } else {
        special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
        special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
    }
    if (special_cb) {
        //special_cb(CAPSLOCK_KEY, window->State.MouseX, window->State.MouseY, special_ud );
    }
#endif
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

static void
HandleNonDeviceModifier(unsigned int device_independent_mask,
                        unsigned int oldMods,
                        unsigned int newMods,
                        int scancode,
                        int bit_map)
{
    unsigned int oldMask, newMask;
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData  special_ud = NULL;
    SFG_Window* window = fgStructure.CurrentWindow;
    
    /* Isolate just the bits we care about in the depedent bits so we can
     * figure out what changed
     */
    oldMask = oldMods & device_independent_mask;
    newMask = newMods & device_independent_mask;
    
    if (oldMask && oldMask != newMask) {
        s_iModifiersGLUT &= ~bit_map;
        if (window) {
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
            special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
        }
    } else if (newMask && oldMask != newMask) {
        s_iModifiersGLUT |= bit_map;
        if (window) {
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, Special  ));
            special_ud  = FETCH_USER_DATA_WCB( *window, Special  );
        }
    }
    
    if (special_cb) {
        special_cb(scancode, window->State.MouseX, window->State.MouseY, special_ud );
    }
}

static void
HandleModifierOneSide(unsigned int oldMods, unsigned int newMods,
                      int scancode,
                      unsigned int sided_device_dependent_mask,
                      int bit_map)
{
    unsigned int old_dep_mask, new_dep_mask;
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData  special_ud = NULL;
    SFG_Window* window = fgStructure.CurrentWindow;
    
    /* Isolate just the bits we care about in the depedent bits so we can
     * figure out what changed
     */
    old_dep_mask = oldMods & sided_device_dependent_mask;
    new_dep_mask = newMods & sided_device_dependent_mask;
    
    /* We now know that this side bit flipped. But we don't know if
     * it went pressed to released or released to pressed, so we must
     * find out which it is.
     */
    if (new_dep_mask && old_dep_mask != new_dep_mask) {
        s_iModifiersGLUT |= bit_map;
        if (window) {
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, Special  ));
            special_ud  = FETCH_USER_DATA_WCB( *window, Special  );
        }
    } else {
        s_iModifiersGLUT &= ~bit_map;
        if (window) {
            special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
            special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
        }
    }
    
    if (special_cb) {
        special_cb(scancode, window->State.MouseX, window->State.MouseY, special_ud );
    }
}

static void
HandleModifierSide(int device_independent_mask,
                   unsigned int oldMods, unsigned int newMods,
                   int left_scancode,
                   int right_scancode,
                   unsigned int left_device_dependent_mask,
                   unsigned int right_device_dependent_mask,
                   int bit_map)
{
    unsigned int device_dependent_mask = (left_device_dependent_mask |
                                          right_device_dependent_mask);
    unsigned int diff_mod;
    
    /* On the basis that the device independent mask is set, but there are
     * no device dependent flags set, we'll assume that we can't detect this
     * keyboard and revert to the unsided behavior.
     */
    if ((device_dependent_mask & newMods) == 0) {
        /* Revert to the old behavior */
        HandleNonDeviceModifier(device_independent_mask, oldMods, newMods, left_scancode, bit_map);
        return;
    }
    
    /* XOR the previous state against the new state to see if there's a change */
    diff_mod = (device_dependent_mask & oldMods) ^
    (device_dependent_mask & newMods);
    if (diff_mod) {
        /* A change in state was found. Isolate the left and right bits
         * to handle them separately just in case the values can simulataneously
         * change or if the bits don't both exist.
         */
        if (left_device_dependent_mask & diff_mod) {
            HandleModifierOneSide(oldMods, newMods, left_scancode, left_device_dependent_mask, bit_map);
        }
        if (right_device_dependent_mask & diff_mod) {
            HandleModifierOneSide(oldMods, newMods, right_scancode, right_device_dependent_mask, bit_map);
        }
    }
}

static void
ReleaseModifierSide(unsigned int device_independent_mask,
                    unsigned int oldMods, unsigned int newMods,
                    int left_scancode,
                    int right_scancode,
                    unsigned int left_device_dependent_mask,
                    unsigned int right_device_dependent_mask,
                    int bit_map)
{
    
    s_iModifiersGLUT &= ~bit_map;
    
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData  special_ud = NULL;
    SFG_Window* window = fgStructure.CurrentWindow;
    if (window) {
        special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
        special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
    }
    if (!special_cb) {
        return;
    }
    
    
    unsigned int device_dependent_mask = (left_device_dependent_mask |
                                          right_device_dependent_mask);
    
    /* On the basis that the device independent mask is set, but there are
     * no device dependent flags set, we'll assume that we can't detect this
     * keyboard and revert to the unsided behavior.
     */
    if ((device_dependent_mask & oldMods) == 0) {
        /* In this case, we can't detect the keyboard, so use the left side
         * to represent both, and release it.
         */
        special_cb(left_scancode, window->State.MouseX, window->State.MouseY, special_ud );
        return;
    }
    
    /*
     * This could have been done in an if-else case because at this point,
     * we know that all keys have been released when calling this function.
     * But I'm being paranoid so I want to handle each separately,
     * so I hope this doesn't cause other problems.
     */
    if ( left_device_dependent_mask & oldMods ) {
        special_cb(left_scancode, window->State.MouseX, window->State.MouseY, special_ud );
    }
    if ( right_device_dependent_mask & oldMods ) {
        special_cb(right_scancode, window->State.MouseX, window->State.MouseY, special_ud );
    }
}

static void
Ccocoa_HandleModifiers(unsigned int modifierFlags)
{
    
    if (modifierFlags == s_iModifiersOS) {
        return;
    }
    
    /* Set up arrays for the key syms for the left and right side. */
    const int left_mapping[]  = {
        GLUT_KEY_SHIFT_L,
        GLUT_KEY_CTRL_L,
        GLUT_KEY_ALT_L
    };
    const int right_mapping[] = {
        GLUT_KEY_SHIFT_R,
        GLUT_KEY_CTRL_R,
        GLUT_KEY_ALT_R
    };
    const int bits_mapping[] = {
        GLUT_ACTIVE_SHIFT,
        GLUT_ACTIVE_CTRL,
        GLUT_ACTIVE_ALT
    };
    /* Set up arrays for the device dependent masks with indices that
     * correspond to the _mapping arrays
     */
    const unsigned int left_device_mapping[]  = { NX_DEVICELSHIFTKEYMASK, NX_DEVICELCTLKEYMASK, NX_DEVICELALTKEYMASK, NX_DEVICELCMDKEYMASK };
    const unsigned int right_device_mapping[] = { NX_DEVICERSHIFTKEYMASK, NX_DEVICERCTLKEYMASK, NX_DEVICERALTKEYMASK, NX_DEVICERCMDKEYMASK };
    
    unsigned int i, bit;
    
    /* Iterate through the bits, testing each against the old modifiers */
    for (i = 0, bit = NSEventModifierFlagShift; bit <= NSEventModifierFlagOption; bit <<= 1, ++i) {
        unsigned int oldMask, newMask;
        
        oldMask = s_iModifiersOS  & bit;
        newMask = modifierFlags & bit;
        
        /* If the bit is set, we must always examine it because the left
         * and right side keys may alternate or both may be pressed.
         */
        if (newMask) {
            HandleModifierSide(bit, s_iModifiersOS, modifierFlags,
                               left_mapping[i], right_mapping[i],
                               left_device_mapping[i], right_device_mapping[i], bits_mapping[i]);
        }
        /* If the state changed from pressed to unpressed, we must examine
         * the device dependent bits to release the correct keys.
         */
        else if (oldMask && oldMask != newMask) {
            ReleaseModifierSide(bit, s_iModifiersOS, modifierFlags,
                                left_mapping[i], right_mapping[i],
                                left_device_mapping[i], right_device_mapping[i], bits_mapping[i]);
        }
    }
    
    s_iModifiersOS = modifierFlags;
}

int
Cocoa_GetModifiers(void)
{
    return s_iModifiersGLUT;
}

void
Cocoa_HandleKeyEvent(NSEvent *event)
{
    FGCBKeyboardUC keyboard_cb = NULL;
    FGCBSpecialUC special_cb = NULL;
    FGCBUserData keyboard_ud = NULL;
    FGCBUserData special_ud = NULL;
    
    SFG_Window* window = fgStructure.CurrentWindow;
    freeglut_return_if_fail(window);
    
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
            fgState.Modifiers = Cocoa_GetModifiers();
            Ccocoa_HandleModifiers([event modifierFlags]);
            fgState.Modifiers = INVALID_MODIFIERS;
            break;
        default: /* just to avoid compiler warnings */
            break;
    }
    
    unsigned short scancode = [event keyCode];
    if ((scancode >= SIZE_SCANCODE_TABLE)
    ||  (darwin_scancode_table[scancode].code == GLUT_SCANCODE_UNKNOWN)) {
        return;
    }
    
    fgState.Modifiers = Cocoa_GetModifiers();
    if (darwin_scancode_table[scancode].isSpecial && special_cb) {
        special_cb( darwin_scancode_table[scancode].code, window->State.MouseX, window->State.MouseY, special_ud );
    }
    else if (!darwin_scancode_table[scancode].isSpecial && keyboard_cb) {
        keyboard_cb( darwin_scancode_table[scancode].code, window->State.MouseX, window->State.MouseY, keyboard_ud );
    }
    fgState.Modifiers = INVALID_MODIFIERS;
}

