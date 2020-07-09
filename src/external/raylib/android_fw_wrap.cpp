
#include "android_fw_wrap.h"

#include <system/window.h>

//#include <ui/DisplayInfo.h>
//#include <gui/ISurfaceComposer.h>
//#include <gui/SurfaceComposerClient.h>
//using namespace android;

int AndroidFW_getFramebufferSize(ANativeWindow* win, int* w, int* h)
{
    if (!win || !w || !h) {
        return -1;
    }
    
    int valid = 0;
    win->query(win, NATIVE_WINDOW_IS_VALID, &valid);
    if (!valid) {
        return -2;
    }

    win->query(win, NATIVE_WINDOW_DEFAULT_WIDTH,  w);
    win->query(win, NATIVE_WINDOW_DEFAULT_HEIGHT, h);
    
    return 0;
}
