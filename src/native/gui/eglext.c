
#include <EGL/egl.h>
#include <EGL/eglext.h>

EGLAPI EGLSyncKHR eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, const EGLint *attrib_list)
{
    return EGL_NO_SYNC_KHR;
}

EGLAPI EGLBoolean eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync)
{
    return (EGL_FALSE);
}

EGLAPI EGLint eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags)
{
    return (EGL_FALSE);
}

EGLAPI EGLint eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout)
{
    return (EGL_FALSE);
}

EGLAPI EGLint eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync)
{
    return (EGL_FALSE);
}
