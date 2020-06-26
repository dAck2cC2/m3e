#include <string.h>
#include <pthread.h>

#include <initrc/initrc.h>
#include <OMXAL/OpenMAXAL_Android.h>

#include "raylib.h"
#include "android_native_app_glue.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again
#define GUI_TEXTBOX_EXTENDED_IMPLEMENTATION
#include "gui_textbox_extended.h"


const int screenWidth = 800;
const int screenHeight = 600;

struct ANativeActivity mActivity;
struct android_app     mApp;

#include "text_editor.h"
#include "textbox_extended_demo.h"
#include "scroll_panel.h"
#include "portable_window.h"

void* _threadLoopRay(void* user)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    mApp.window = xaAndroidCreateNativeWindow();
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    mApp.onAppCmd(&mApp, APP_CMD_INIT_WINDOW);
    
    //text_editor();
    //textbox_extended_demo();
    //scroll_panel();
    portable_window();

    return NULL;
}

int main(int argc, char** argv)
{
    InitRC_set(M_PROPERTY_DISPLAY_NAME,   "test raygui");
    InitRC_set(M_PROPERTY_DISPLAY_WIDTH,  "800");
    InitRC_set(M_PROPERTY_DISPLAY_HEIGHT, "450");
    
    InitRC_entry(argc, argv);

    memset(&mActivity, 0x00, sizeof(mActivity));
    memset(&mApp,      0x00, sizeof(mApp));
    
    mApp.activity = &mActivity;
    
    android_main(&mApp);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mApp.thread), &attr,
                                _threadLoopRay,
                                NULL);
    pthread_attr_destroy(&attr);
    
    InitRC_run();

    return 0;
}