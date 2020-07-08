
#define TEST_EGL_GL 0

#include <string.h>
#include <pthread.h>

#include <initrc/initrc.h>

#if TEST_EGL_GL
#include <OMXAL/OpenMAXAL_Android.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#endif // TEST_EGL_GL

#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 600;

static pthread_t mGUIThread = NULL;

#include "test_case.h"

void* _threadLoopRay(void* user)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
        
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
            //sharps_basic_sharps();
        
            hello_rectangle();

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
    
    XANativeHandle window = xaAndroidCreateNativeWindow();

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);

    EGLint displayFormat;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &displayFormat);

    
    surface = eglCreateWindowSurface(display, config, window, NULL);
    //eglQuerySurface(display, surface, EGL_WIDTH, &w);
    //eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        return NULL;

    // clear screen
    /*
    glShadeModel(GL_FLAT);
    glDisable(GL_DITHER);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(display, surface);
     */
    
    for (;;) {
        
        //hello_triangle();
        colored_rect(-0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
        
        
        EGLBoolean res = eglSwapBuffers(display, surface);
        if (res == EGL_FALSE)
            break;
    }
    
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
    eglReleaseThread();
    
    xaAndroidDisposeNativeWindow(window);

    return NULL;
}
#endif

int main(int argc, char** argv)
{
    InitRC_set(M_PROPERTY_DISPLAY_NAME,   "test raylib");
    InitRC_set(M_PROPERTY_DISPLAY_WIDTH,  "800");
    InitRC_set(M_PROPERTY_DISPLAY_HEIGHT, "600");
    
    InitRC_entry(argc, argv);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mGUIThread), &attr,
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
