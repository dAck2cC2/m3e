#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"


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



