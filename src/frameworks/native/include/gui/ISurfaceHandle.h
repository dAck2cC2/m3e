
#ifndef ANDROID_GUI_ISURFACE_HANDLE_H
#define ANDROID_GUI_ISURFACE_HANDLE_H

#include <gui/compiler.h>

#include <stdint.h>
#include <sys/types.h>

#include <utils/Errors.h>
#include <utils/RefBase.h>

#include <binder/IInterface.h>

#include <EGL/egl.h>

namespace android {
// ----------------------------------------------------------------------------

class ANDROID_GUI_API ISurfaceHandle : public IInterface
{
public:
    DECLARE_META_INTERFACE(SurfaceHandle);

    virtual EGLNativeWindowType getNativeWindow() = 0;
};

// ----------------------------------------------------------------------------

class ANDROID_GUI_API BnSurfaceHandle: public BnInterface<ISurfaceHandle> {
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0);
};

// ----------------------------------------------------------------------------

}; // namespace android

#endif // ANDROID_GUI_ISURFACE_HANDLE_H
