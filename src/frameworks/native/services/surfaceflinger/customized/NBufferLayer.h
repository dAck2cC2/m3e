#pragma once

#ifndef NATIVE_BUFFER_LAYER_H
#define NATIVE_BUFFER_LAYER_H

#include <private/binder/binder_module.h>
#include <gui/customized/ISurfaceHandle.h>
#include "BufferLayer.h"
#include "DisplayHardware/ComposerHal.h"

namespace android {
namespace NATIVE {

class BufferLayer : public android::BufferLayer {
public:
    class Handle : public android::Layer::Handle {
    public:
        Handle(const sp<SurfaceFlinger>& flinger, const sp<BufferLayer>& layer) :
        android::Layer::Handle(flinger, layer),
        mLayer(layer)
        { };
        
        virtual status_t    transact(uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags) override
        {
            switch (code) {
            case GET_NATIVE_WINDOW: {
                if (!data.enforceInterface(String16(ISURFACE_HANDLE_NAME))) return PERMISSION_DENIED;

                flat_binder_object obj = {};
                obj.hdr.type = BINDER_TYPE_PTR;

                sp<BufferLayer> layer = mLayer.promote();
                if (layer == NULL) {
                    // garbage data to catch improper use
                    obj.cookie = static_cast<uintptr_t>(0xDEADBEEF);
                }
                else {
                    obj.cookie = static_cast<uintptr_t>(layer->getEGLNativeWindow());
                }

                reply->writeObject(obj, true);
                return NO_ERROR;
            }
            default:
                return BBinder::transact(code, data, reply, flags);
                break;
            }
        };
        
    private:
        wp<BufferLayer> mLayer;
    }; // class Handle
    
public:
    BufferLayer(SurfaceFlinger* flinger, const sp<Client>& client, const String8& name, uint32_t w,
                uint32_t h, uint32_t flags) :
    android::BufferLayer(flinger, client, name, w, h, flags),
    mNativeLayer(nullptr),
    mEGLNativeWindow(0)
    {
        //flinger->getBE().mHwc->getComposer()->createLayer(0, reinterpret_cast<uint64_t *>(&mEGLNativeWindow));
        mNativeLayer = mFlinger->getBE().mHwc->createLayer(0);
        if (mNativeLayer) {
            mEGLNativeWindow = mNativeLayer->getId();
        }
    };
    
    virtual ~BufferLayer()
    {
        if (mNativeLayer) {
            mFlinger->getBE().mHwc->destroyLayer(0, mNativeLayer);
            mNativeLayer = nullptr;
            mEGLNativeWindow = 0;
        }
    };
    
    sp<IBinder> getHandle() override {
        return (new Handle(mFlinger, this));
    };
    
    
    hwc2_layer_t getEGLNativeWindow() {
        return mEGLNativeWindow;
    }

private:
    HWC2::Layer* mNativeLayer;
    hwc2_layer_t mEGLNativeWindow;
    
}; // class BufferLayer

} // NATIVE
} // android

#endif // NATIVE_BUFFER_LAYER_H
