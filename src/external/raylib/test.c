
#define TEST_EGL_GL 0

#include <string.h>
#include <pthread.h>

#include <initrc/initrc.h>
#include <OMXAL/OpenMAXAL_Android.h>

#if TEST_EGL_GL
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#endif // TEST_EGL_GL

#include "raylib.h"
#include "android_native_app_glue.h"

const int screenWidth = 800;
const int screenHeight = 600;

struct ANativeActivity mActivity;
struct android_app     mApp;

#include "test_case.h"

void* _threadLoopRay(void* user)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    mApp.window = xaAndroidCreateNativeWindow();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    mApp.onAppCmd(&mApp, APP_CMD_INIT_WINDOW);
    
    // TODO: Load resources / Initialize variables at this point
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            //hello_triangle();
            //example_hello_text();
            sharps_basic_sharps();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // TODO: Unload all loaded resources at this point
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return NULL;
}

#if TEST_EGL_GL
void* _threadLoopEGL(void* user)
{
    const EGLint attribs[] = {
            EGL_RED_SIZE,   8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE,  8,
            EGL_DEPTH_SIZE, 0,
            EGL_NONE
    };
    EGLint w, h;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display;
    
    mApp.window = xaAndroidCreateNativeWindow();

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);

    EGLint displayFormat;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &displayFormat);

    
    surface = eglCreateWindowSurface(display, config, mApp.window, NULL);
    //eglQuerySurface(display, surface, EGL_WIDTH, &w);
    //eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        return NULL;

    for (;;) {
        hello_triangle();
        //sharps_basic_sharps();
        EGLBoolean res = eglSwapBuffers(display, surface);
        if (res == EGL_FALSE)
            break;
    }
    
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    xaAndroidDisposeNativeWindow(mApp.window);
    mApp.window = NULL;
    eglTerminate(display);
    eglReleaseThread();

    return NULL;
}
#endif

int main(int argc, char** argv)
{
    InitRC_entry(argc, argv);

    memset(&mActivity, 0x00, sizeof(mActivity));
    memset(&mApp,      0x00, sizeof(mApp));
    
    mApp.activity = &mActivity;
    
    android_main(&mApp);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mApp.thread), &attr,
#if TEST_EGL_GL
                                _threadLoopEGL,
#else
                                _threadLoopRay,
#endif
                                NULL);
    pthread_attr_destroy(&attr);
    
    InitRC_run();

    return 0;
}
