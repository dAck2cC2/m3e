#pragma once

#if defined(ENABLE_ANDROID_GL)

#ifndef NATIVE_BUFFER_PRODUCER_H
#define NATIVE_BUFFER_PRODUCER_H

#include <gui/IGraphicBufferProducer.h>
#include "Layer.h"

namespace android {

class IProducerListener;
//class NativeHandle;
class SurfaceFlinger;
//class Layer;

namespace NATIVE {

class BufferProducer : public BnGraphicBufferProducer {
public:
    BufferProducer(const sp<IGraphicBufferProducer>& producer,
            const sp<SurfaceFlinger>& flinger);
    virtual ~BufferProducer();

    // From IGraphicBufferProducer
    virtual status_t requestBuffer(int slot, sp<GraphicBuffer>* buf);
    virtual status_t setMaxDequeuedBufferCount(int maxDequeuedBuffers);
    virtual status_t setAsyncMode(bool async);
    virtual status_t dequeueBuffer(int* slot, sp<Fence>* fence, uint32_t w, uint32_t h,
                                   PixelFormat format, uint64_t usage, uint64_t* outBufferAge,
                                   FrameEventHistoryDelta* outTimestamps);
    virtual status_t detachBuffer(int slot);
    virtual status_t detachNextBuffer(sp<GraphicBuffer>* outBuffer,
            sp<Fence>* outFence);
    virtual status_t attachBuffer(int* outSlot,
            const sp<GraphicBuffer>& buffer);
    virtual status_t queueBuffer(int slot, const QueueBufferInput& input,
            QueueBufferOutput* output);
    virtual status_t cancelBuffer(int slot, const sp<Fence>& fence);
    virtual int query(int what, int* value);
    virtual status_t connect(const sp<IProducerListener>& token, int api,
            bool producerControlledByApp, QueueBufferOutput* output);
    virtual status_t disconnect(int api, DisconnectMode mode);
    virtual status_t setSidebandStream(const sp<NativeHandle>& stream);
    virtual void allocateBuffers(uint32_t width, uint32_t height,
            PixelFormat format, uint64_t usage);
    virtual status_t allowAllocation(bool allow);
    virtual status_t setGenerationNumber(uint32_t generationNumber);
    virtual String8 getConsumerName() const override;
    virtual status_t setDequeueTimeout(nsecs_t timeout) override;
    virtual status_t getLastQueuedBuffer(sp<GraphicBuffer>* outBuffer,
            sp<Fence>* outFence, float outTransformMatrix[16]) override;
    virtual IBinder* onAsBinder();
    virtual status_t setSharedBufferMode(bool sharedBufferMode) override;
    virtual status_t setAutoRefresh(bool autoRefresh) override;
    virtual void getFrameTimestamps(FrameEventHistoryDelta *outDelta) override;
    virtual status_t getUniqueId(uint64_t* outId) const override;
    virtual status_t getConsumerUsage(uint64_t* outUsage) const override;

private:
    sp<IGraphicBufferProducer> mProducer;
    sp<SurfaceFlinger>         mFlinger;
    HWC2::Layer*               mNativeLayer;
    hwc2_layer_t               mEGLNativeWindow;
    int32_t                    mFBWidth;
    int32_t                    mFBHeight;
}; // BufferProducer

} // NATIVE
} // android

#endif // NATIVE_BUFFER_PRODUCER_H
#endif // ENABLE_ANDROID_GL
