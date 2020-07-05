#include <string.h>
#include <pthread.h>

#include <initrc/initrc.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again
#define GUI_TEXTBOX_EXTENDED_IMPLEMENTATION
#define RAYGUIDEF 
#include "gui_textbox_extended.h"


const int screenWidth = 800;
const int screenHeight = 600;

static pthread_t mGUIThread = NULL;

#include "text_editor.h"
#if !defined(_MSC_VER)
#include "textbox_extended_demo.h"
#endif
#include "scroll_panel.h"
#include "portable_window.h"

void* _threadLoopRay(void* user)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    //text_editor();
    //textbox_extended_demo();
    scroll_panel();
    //portable_window();

    return NULL;
}

int main(int argc, char** argv)
{
    InitRC_set(M_PROPERTY_DISPLAY_NAME,   "test raygui");
    InitRC_set(M_PROPERTY_DISPLAY_WIDTH,  "800");
    InitRC_set(M_PROPERTY_DISPLAY_HEIGHT, "450");
    
    InitRC_entry(argc, argv);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mGUIThread), &attr,
                                _threadLoopRay,
                                NULL);
    pthread_attr_destroy(&attr);
    
    InitRC_run();

    return 0;
}
