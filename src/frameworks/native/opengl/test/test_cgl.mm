
#import <Cocoa/Cocoa.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <dlfcn.h>

const char *kDefaultOpenGLDylibName =
"/System/Library/Frameworks/OpenGL.framework/Libraries/libGL.dylib";

const char *kAngleEGLDylibName = "./libEGL_angle.dylib";

#define GL_VERSION                        0x1F02
typedef unsigned int GLenum;
typedef unsigned char  GLubyte;
typedef void(*PFNGLENABLEPROC)(GLenum);
typedef GLenum(*PFNGLGETERRORPROC)();
typedef const GLubyte *(*PFNGLGETSTRINGPROC)(GLenum);


typedef int EGLint;
typedef EGLint(* eglGetError)(void);


#define ASSIGN(NAME, FP, HANDLE) FP = reinterpret_cast<decltype(FP)>(loadProcAddress(NAME, HANDLE))


void * mDylibHandle = nullptr;
PFNGLENABLEPROC mglEnable = nullptr;
PFNGLGETERRORPROC mglGetError = nullptr;
PFNGLGETSTRINGPROC mglGetString = nullptr;

void * mDylibEGL = nullptr;
eglGetError meglGetError = nullptr;

void *loadProcAddress(const std::string &function, void* handle)
{
    return dlsym(handle, function.c_str());
}


CGLContextObj mContext = nullptr;
CGLPixelFormatObj mPixelFormat = nullptr;
void initCGL()
{
    std::vector<CGLPixelFormatAttribute> attribs;
    attribs.push_back(kCGLPFAOpenGLProfile);
    attribs.push_back(static_cast<CGLPixelFormatAttribute>(kCGLOGLPVersion_3_2_Core));
    attribs.push_back(kCGLPFAAllowOfflineRenderers);
    attribs.push_back(static_cast<CGLPixelFormatAttribute>(0));
    GLint nVirtualScreens = 0;
    CGLChoosePixelFormat(attribs.data(), &mPixelFormat, &nVirtualScreens);

    if (mPixelFormat == nullptr)
    {
        return;
    }

    CGLCreateContext(mPixelFormat, nullptr, &mContext);
    if (mContext == nullptr)
    {
        return;
    }

    CGLSetCurrentContext(mContext);
}



void* _threadLoop(void* user) 
{
    meglGetError();

    //mDylibHandle = dlopen(kDefaultOpenGLDylibName, RTLD_NOW);
    //ASSIGN("glEnable", mEnable);
    
    CGLSetCurrentContext(mContext);
    mglGetString(GL_VERSION);
    //mglGetError();
    //mglEnable(1);

    return nullptr;
}

int main(int argc, char** argv)
{
    initCGL();
    
    mDylibHandle = dlopen(kDefaultOpenGLDylibName, RTLD_NOW);
    
    ASSIGN("glGetString", mglGetString, mDylibHandle);
    mglGetString(GL_VERSION);
    char * error = dlerror();

    ASSIGN("glEnable", mglEnable, mDylibHandle);
    //mEnable(1);
    
    ASSIGN("glGetError", mglGetError, mDylibHandle);
    //mglGetError();
    
    mDylibEGL = dlopen(kAngleEGLDylibName, RTLD_NOW);
    ASSIGN("eglGetError", meglGetError, mDylibEGL);
    meglGetError();

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t thread;
    int result = pthread_create(&thread, &attr, _threadLoop, nullptr);
    pthread_attr_destroy(&attr);

    for (;;);

    return 0;
}
