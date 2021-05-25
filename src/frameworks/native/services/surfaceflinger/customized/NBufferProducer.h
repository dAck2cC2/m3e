#pragma once

#if defined(ENABLE_ANDROID_GL)

#ifndef NATIVE_BUFFER_PRODUCER_H
#define NATIVE_BUFFER_PRODUCER_H

#include "MonitoredProducer.h"
#include "DisplayHardware/HWComposer.h"

namespace android {

class IProducerListener;
class SurfaceFlinger;
class Layer;

namespace NATIVE {

class BufferProducer : public MonitoredProducer {
public:
    BufferProducer(const sp<IGraphicBufferProducer>& producer,
        const sp<SurfaceFlinger>& flinger,
        const wp<Layer>& layer);
    virtual ~BufferProducer();

    // From IGraphicBufferProducer
    virtual int query(int what, int* value) override;
    virtual status_t getConsumerUsage(uint64_t* outUsage) const override;

private:
    sp<SurfaceFlinger>         mSF;
    HWC2::Layer*               mNativeLayer;
    hwc2_layer_t               mEGLNativeWindow;
    int32_t                    mFBWidth;
    int32_t                    mFBHeight;
}; // BufferProducer

} // NATIVE
} // android

#endif // NATIVE_BUFFER_PRODUCER_H
#endif // ENABLE_ANDROID_GL
