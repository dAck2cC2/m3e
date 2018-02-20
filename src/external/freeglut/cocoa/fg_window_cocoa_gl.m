
#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"

#include <dlfcn.h>


@implementation GLUTOpenGLContext : NSOpenGLContext

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share
{
    self = [super initWithFormat:format shareContext:share];
    if (self) {
        self->dirty = 0;
        self->window = NULL;
    }
    return self;
}

- (void)scheduleUpdate
{
    self->dirty += 1;
}

/* This should only be called on the thread on which a user is using the context. */
- (void)updateIfNeeded
{
    int value = self->dirty;
    self->dirty = 0;
    if (value > 0) {
        /* We call the real underlying update here, since -[SDLOpenGLContext update] just calls us. */
        [super update];
    }
}

/* This should only be called on the thread on which a user is using the context. */
- (void)update
{
    /* This ensures that regular 'update' calls clear the atomic dirty flag. */
    [self scheduleUpdate];
    [self updateIfNeeded];
}

/* Updates the drawable for the contexts and manages related state. */
- (void)setWindow:(SFG_PlatformContext *)newWindow
{
    if (self->window) {
        SFG_PlatformContext *oldwindowdata = self->window;
        
        /* Make sure to remove us from the old window's context list, or we'll get scheduled updates from it too. */
        NSMutableArray *contexts = oldwindowdata->nscontexts;
        @synchronized (contexts) {
            [contexts removeObject:self];
        }
    }
    
    self->window = newWindow;
    
    if (newWindow) {
        SFG_PlatformContext *windowdata = newWindow;
        
        /* Now sign up for scheduled updates for the new window. */
        NSMutableArray *contexts = windowdata->nscontexts;
        @synchronized (contexts) {
            [contexts addObject:self];
        }
        
        if ([self view] != [windowdata->nswindow contentView]) {
            [self setView:[windowdata->nswindow contentView]];
            if (self == [NSOpenGLContext currentContext]) {
                [self update];
            } else {
                [self scheduleUpdate];
            }
        }
    } else {
        [self clearDrawable];
        if (self == [NSOpenGLContext currentContext]) {
            [self update];
        } else {
            [self scheduleUpdate];
        }
    }
}

@end  /* GLUTOpenGLContext */

int
Cocoa_GL_MakeCurrent(SFG_Window * window, GLUTOpenGLContext* context)
{ @autoreleasepool
    {
        if (context) {
            [context setWindow:&window->Window.pContext];
            [context updateIfNeeded];
            [context makeCurrentContext];
        } else {
            [NSOpenGLContext clearCurrentContext];
        }
        
        return 0;
    }
}

void
Cocoa_GL_DeleteContext(GLUTOpenGLContext* context)
{ @autoreleasepool
    {
        [context setWindow:NULL];
        [context release];
    }
    
}

SFG_WindowContextType
Cocoa_GL_CreateContext(SFG_Window * window)
{ @autoreleasepool
    {
        GLboolean lion_or_later = floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6;
        NSOpenGLPixelFormatAttribute attr[32];
        NSOpenGLPixelFormat *fmt;
        GLUTOpenGLContext *context;
        NSOpenGLContext *share_context = nil;
        int i = 0;
        const char *glversion;
        int glversion_major;
        int glversion_minor;
        
        FREEGLUT_INTERNAL_ERROR_EXIT ( ( window->Window.Context == NULL ), "Context of window already exists.", "Cocoa_GL_CreateContext");
        
#if 0
        if (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) {
            SDL_SetError ("OpenGL ES is not supported on this platform");
            return NULL;
        }
        if ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_CORE) && !lion_or_later) {
            SDL_SetError ("OpenGL Core Profile is not supported on this platform version");
            return NULL;
        }
#endif
        attr[i++] = NSOpenGLPFAAllowOfflineRenderers;
        
        /* specify a profile if we're on Lion (10.7) or later. */
        if (lion_or_later) {
            NSOpenGLPixelFormatAttribute profile = NSOpenGLProfileVersionLegacy;
            //if (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_CORE) {
            //    profile = NSOpenGLProfileVersion3_2Core;
            //}
            attr[i++] = NSOpenGLPFAOpenGLProfile;
            attr[i++] = profile;
        }
        
        attr[i++] = NSOpenGLPFAColorSize;
        attr[i++] = 32;
        
        if (fgState.ContextFlags & GLUT_DEPTH) {
            attr[i++] = NSOpenGLPFADepthSize;
            attr[i++] = 16;
        }
        
        if (fgState.ContextFlags & GLUT_DOUBLE) {
            attr[i++] = NSOpenGLPFADoubleBuffer;
        }
        
        if (fgState.ContextFlags & GLUT_STEREO) {
            attr[i++] = NSOpenGLPFAStereo;
        }
        
        if (fgState.DisplayMode & GLUT_STENCIL) {
            attr[i++] = NSOpenGLPFAStencilSize;
            attr[i++] = 1;
        }
        
        if ((fgState.DisplayMode & GLUT_ACCUM) && (fgState.DisplayMode & GLUT_ALPHA)) {
            attr[i++] = NSOpenGLPFAAccumSize;
            attr[i++] = 32;
        } else if (fgState.DisplayMode & GLUT_ACCUM) {
            attr[i++] = NSOpenGLPFAAccumSize;
            attr[i++] = 24;
        } 
        
        if (fgState.DisplayMode & GLUT_MULTISAMPLE) {
            attr[i++] = NSOpenGLPFASampleBuffers;
            attr[i++] = 1;
            attr[i++] = NSOpenGLPFASamples;
            attr[i++] = fgState.SampleNumber;
            attr[i++] = NSOpenGLPFANoRecovery;
        }
#if 0
        if (_this->gl_config.accelerated >= 0)
        {
            if (_this->gl_config.accelerated)
            {
                attr[i++] = NSOpenGLPFAAccelerated;
            } else {
                attr[i++] = NSOpenGLPFARendererID;
                attr[i++] = kCGLRendererGenericFloatID;
            }
        }
#endif
        attr[i++] = NSOpenGLPFAScreenMask;
        attr[i++] = CGDisplayIDToOpenGLDisplayMask(fgDisplay.pDisplay.display);
        attr[i] = 0;
        
        fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
        if (fmt == nil) {
            fgError("Failed creating OpenGL pixel format");
            return NULL;
        }
        
        //if (_this->gl_config.share_with_current_context) {
        //    share_context = (NSOpenGLContext*)SDL_GL_GetCurrentContext();
        //}
        
        context = [[GLUTOpenGLContext alloc] initWithFormat:fmt shareContext:share_context];
        
        [fmt release];
        
        if (context == nil) {
            fgError("Failed creating OpenGL context");
            return NULL;
        }
        
        if ( Cocoa_GL_MakeCurrent(window, context) < 0 ) {
            Cocoa_GL_DeleteContext(context);
            fgError("Failed making OpenGL context current");
            return NULL;
        }
        
        if (fgState.MajorVersion < 3 &&
            fgState.ContextProfile == 0 &&
            fgState.ContextFlags == 0) {
            /* This is a legacy profile, so to match other backends, we're done. */
        } else {
            glversion = (const char *)glGetString(GL_VERSION);
            if (glversion == NULL) {
                Cocoa_GL_DeleteContext(context);
                fgError ("Failed getting OpenGL context version");
                return NULL;
            }
            
            if (sscanf(glversion, "%d.%d", &glversion_major, &glversion_minor) != 2) {
                Cocoa_GL_DeleteContext(context);
                fgError ("Failed parsing OpenGL context version");
                return NULL;
            }
            
            if ((glversion_major < fgState.MajorVersion) ||
                ((glversion_major == fgState.MajorVersion) && (glversion_minor < fgState.MinorVersion))) {
                Cocoa_GL_DeleteContext(context);
                fgError ("Failed creating OpenGL context at version requested");
                return NULL;
            }
            
            /* In the future we'll want to do this, but to match other platforms
             we'll leave the OpenGL version the way it is for now
             */
            /*fgState.MajorVersion = glversion_major;*/
            /*fgState.MinorVersion = glversion_minor;*/
        }
        
        window->Window.Context = context;
        
        return context;
    }
}

int
Cocoa_GL_GetAtrr(int what)
{
    int returnValue = (-1);
    GLboolean boolValue = GL_FALSE;
    
    switch( what )
    {
            /* The same as NSOpenGLPFAColorSize in Cocoa_GL_CreateContext */
        case GLUT_WINDOW_COLORMAP_SIZE:
        case GLUT_WINDOW_BUFFER_SIZE:
            return 32;
            /* Handle the OpenGL inquiries */
        case GLUT_WINDOW_NUM_SAMPLES:
            glGetIntegerv(GL_SAMPLES, &returnValue);
            return returnValue;
        case GLUT_WINDOW_RGBA:
            glGetBooleanv ( GL_RGBA_MODE, &boolValue );
            return (boolValue ? 1 : 0);
        case GLUT_WINDOW_DOUBLEBUFFER:
            glGetBooleanv ( GL_DOUBLEBUFFER, &boolValue );
            return (boolValue ? 1 : 0);
        case GLUT_WINDOW_STEREO:
            glGetBooleanv ( GL_STEREO, &boolValue );
            return (boolValue ? 1 : 0);
        case GLUT_WINDOW_RED_SIZE:
            glGetIntegerv ( GL_RED_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_GREEN_SIZE:
            glGetIntegerv ( GL_GREEN_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_BLUE_SIZE:
            glGetIntegerv ( GL_BLUE_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_ALPHA_SIZE:
            glGetIntegerv ( GL_ALPHA_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_ACCUM_RED_SIZE:
            glGetIntegerv ( GL_ACCUM_RED_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_ACCUM_GREEN_SIZE:
            glGetIntegerv ( GL_ACCUM_GREEN_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_ACCUM_BLUE_SIZE:
            glGetIntegerv ( GL_ACCUM_BLUE_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_ACCUM_ALPHA_SIZE:
            glGetIntegerv ( GL_ACCUM_ALPHA_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_DEPTH_SIZE:
            glGetIntegerv ( GL_DEPTH_BITS, &returnValue );
            return returnValue;
        case GLUT_WINDOW_STENCIL_SIZE:
            glGetIntegerv ( GL_STENCIL_BITS, &returnValue );
            return returnValue;
        default:
            fgWarning( "glutGet(): missing enum handle %d", what );
            break;
    }
    
    return -1;
}

/*
 * ext
 */
#define DEFAULT_OPENGL  "/System/Library/Frameworks/OpenGL.framework/Libraries/libGL.dylib"
static void * gl_dll_handle = NULL;

void
Cocoa_GL_LoadLibrary(void)
{
    const char *loaderror;
    gl_dll_handle = dlopen(DEFAULT_OPENGL, RTLD_NOW|RTLD_LOCAL);
    loaderror = (char *) dlerror();
    if (gl_dll_handle == NULL) {
        fgError("Failed loading %s: %s", DEFAULT_OPENGL, loaderror);
    }
}

GLUTproc fgPlatformGetGLUTProcAddress( const char* procName )
{
    if (!procName) {
        return NULL;
    }
    
    /* optimization: quick initial check */
    if( strncmp( procName, "glut", 4 ) != 0 )
        return NULL;
    
#define CHECK_NAME(x) if( strcmp( procName, #x ) == 0) return (GLUTproc)x;
    CHECK_NAME(glutJoystickFunc);
    CHECK_NAME(glutForceJoystickFunc);
    CHECK_NAME(glutGameModeString);
    CHECK_NAME(glutEnterGameMode);
    CHECK_NAME(glutLeaveGameMode);
    CHECK_NAME(glutGameModeGet);
#undef CHECK_NAME
    
    return NULL;
}

SFG_Proc fgPlatformGetProcAddress( const char *procName )
{
    if (gl_dll_handle && procName) {
        return dlsym(gl_dll_handle, procName);
    } else {
        return NULL;
    }
}

/*
 * display
 */
int
Cocoa_GL_SwapWindow(GLUTOpenGLContext* nscontext)
{ @autoreleasepool
    {
        if (nscontext) {
            [nscontext flushBuffer];
            [nscontext updateIfNeeded];
        }
        return 0;
    }
}

void fgPlatformGlutSwapBuffers( SFG_PlatformDisplay *pDisplayPtr, SFG_Window* CurrentWindow )
{
    if (CurrentWindow) {
        Cocoa_GL_SwapWindow((GLUTOpenGLContext* )(CurrentWindow->Window.Context));
    }
}

