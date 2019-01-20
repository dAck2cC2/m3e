
// tag as surfaceflinger
#define LOG_TAG "SurfaceFlinger"

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <private/binder/binder_module.h>

#include <gui/ISurfaceHandle.h>

// ---------------------------------------------------------------------------

namespace android {

enum {
    GET_NATIVE_WINDOW = IBinder::FIRST_CALL_TRANSACTION,
};

class BpSurfaceHandle : public BpInterface<ISurfaceHandle>
{
public:
    BpSurfaceHandle(const sp<IBinder>& impl)
        : BpInterface<ISurfaceHandle>(impl) {
    }
    virtual ~BpSurfaceHandle();

    virtual EGLNativeWindowType getNativeWindow()
    {
        EGLNativeWindowType win = 0;
        Parcel data, reply;
        data.writeInterfaceToken(ISurfaceHandle::getInterfaceDescriptor());
        remote()->transact(GET_NATIVE_WINDOW, data, &reply);
        const flat_binder_object* obj = reply.readObject(true);
        if ((obj) && (obj->type == BINDER_TYPE_POINTER)) {
            win = (EGLNativeWindowType)(obj->cookie);
        }
        return (win);
    };
};

// Out-of-line virtual method definition to trigger vtable emission in this
// translation unit (see clang warning -Wweak-vtables)
BpSurfaceHandle::~BpSurfaceHandle() {}

IMPLEMENT_META_INTERFACE(SurfaceHandle, "android.ui.ISurfaceHandle");

// ----------------------------------------------------------------------

status_t BnSurfaceHandle::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
     switch(code) {
        case GET_NATIVE_WINDOW: {
            CHECK_INTERFACE(ISurfaceHandle, data, reply);
            flat_binder_object obj = {};
            obj.type   = BINDER_TYPE_POINTER;
            obj.cookie = (uintptr_t)(getNativeWindow());
            reply->writeObject(obj, true);
            return NO_ERROR;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
     }
};

}; // namespace android
