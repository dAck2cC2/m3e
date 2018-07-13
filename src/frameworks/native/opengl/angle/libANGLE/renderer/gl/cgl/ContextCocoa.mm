
#include "libANGLE/renderer/gl/cgl/ContextCocoa.h"
#include "libANGLE/renderer/gl/cgl/WindowSurfaceCGL.h"

@implementation CGLOpenGLContext : NSOpenGLContext

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
- (void)setWindow:(rx::WindowSurfaceCGL *)newWindow
{
    
    if (self->window) {
        rx::WindowSurfaceCGL *oldwindowdata = self->window;
        
        /* Make sure to remove us from the old window's context list, or we'll get scheduled updates from it too. */
        //NSMutableArray *contexts = oldwindowdata->nscontexts;
        //@synchronized (contexts) {
        //    [contexts removeObject:self];
        //}
    }
    
    self->window = newWindow;
    
    if (newWindow) {
        rx::WindowSurfaceCGL *windowdata = newWindow;
        
        /* Now sign up for scheduled updates for the new window. */
        //NSMutableArray *contexts = windowdata->nscontexts;
        //@synchronized (contexts) {
        //    [contexts addObject:self];
        //}
        
        if ([self view] != [windowdata->getNSWindow() contentView]) {
            [self setView:[windowdata->getNSWindow() contentView]];
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


CGLOpenGLContext* CreateOpenGLContext()
{
    GLboolean lion_or_later = floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6;
    NSOpenGLPixelFormatAttribute attr[32];
    CGLOpenGLContext* context = nil;
    NSOpenGLPixelFormat *fmt;
    NSOpenGLContext *share_context = nil;
    int i = 0;
    const char *glversion;
    int glversion_major;
    int glversion_minor;
    
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
        
    
    
    fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    if (fmt == nil) {
        return NULL;
    }
    context = [[CGLOpenGLContext alloc] initWithFormat:fmt shareContext:share_context];
    
    [fmt release];
    
    if (context == nil) {
        return NULL;
    }
    
    return context;
}
