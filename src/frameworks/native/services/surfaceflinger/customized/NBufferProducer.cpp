
#if defined(ENABLE_ANDROID_GL)

#include "Scheduler/MessageQueue.h"
#include "NBufferProducer.h"
#include "SurfaceFlinger.h"
#include "DisplayHardware/ComposerHal.h"

#include <system/window.h>

#include <gui/BufferItem.h>

namespace android {
namespace NATIVE {

using namespace hardware::graphics::composer::V2_1;

BufferProducer::BufferProducer(const sp<IGraphicBufferProducer>& producer,
        const sp<SurfaceFlinger>& flinger) :
    mProducer(producer),
    mFlinger(flinger),
    mNativeLayer(nullptr),
    mEGLNativeWindow(0),
    mFBWidth(0),
    mFBHeight(0)
{
    auto displayId = mFlinger->getHwComposer().toPhysicalDisplayId(0);
    mNativeLayer = mFlinger->getHwComposer().createLayer(displayId.value_or(getFallbackDisplayId(0)));
    if (mNativeLayer) {
        mEGLNativeWindow = mNativeLayer->getId();
        
        mFlinger->getHwComposer().getComposer()->getDisplayAttribute(mEGLNativeWindow, 0, IComposerClient::Attribute::WIDTH, &mFBWidth);
        mFlinger->getHwComposer().getComposer()->getDisplayAttribute(mEGLNativeWindow, 0, IComposerClient::Attribute::HEIGHT, &mFBHeight);
    }
}

BufferProducer::~BufferProducer() {
    if (mNativeLayer) {
        auto displayId = mFlinger->getHwComposer().toPhysicalDisplayId(0);
        mFlinger->getHwComposer().destroyLayer(displayId.value_or(getFallbackDisplayId(0)), mNativeLayer);
        mNativeLayer = nullptr;
        mEGLNativeWindow = 0;
    }
    
    // Remove ourselves from SurfaceFlinger's list. We do this asynchronously
    // because we don't know where this destructor is called from. It could be
    // called with the mStateLock held, leading to a dead-lock (it actually
    // happens).
    sp<LambdaMessage> cleanUpListMessage =
            new LambdaMessage([flinger = mFlinger, asBinder = wp<IBinder>(onAsBinder())]() {
                Mutex::Autolock lock(flinger->mStateLock);
                flinger->mGraphicBufferProducerList.erase(asBinder);
            });

    mFlinger->postMessageAsync(cleanUpListMessage);
}

status_t BufferProducer::requestBuffer(int slot, sp<GraphicBuffer>* buf) {
    return mProducer->requestBuffer(slot, buf);
}

status_t BufferProducer::setMaxDequeuedBufferCount(
        int maxDequeuedBuffers) {
    return mProducer->setMaxDequeuedBufferCount(maxDequeuedBuffers);
}

status_t BufferProducer::setAsyncMode(bool async) {
    return mProducer->setAsyncMode(async);
}

status_t BufferProducer::dequeueBuffer(int* slot, sp<Fence>* fence, uint32_t w, uint32_t h,
                                          PixelFormat format, uint64_t usage,
                                          uint64_t* outBufferAge,
                                          FrameEventHistoryDelta* outTimestamps) {
    return mProducer->dequeueBuffer(slot, fence, w, h, format, usage, outBufferAge, outTimestamps);
}

status_t BufferProducer::detachBuffer(int slot) {
    return mProducer->detachBuffer(slot);
}

status_t BufferProducer::detachNextBuffer(sp<GraphicBuffer>* outBuffer,
        sp<Fence>* outFence) {
    return mProducer->detachNextBuffer(outBuffer, outFence);
}

status_t BufferProducer::attachBuffer(int* outSlot,
        const sp<GraphicBuffer>& buffer) {
    return mProducer->attachBuffer(outSlot, buffer);
}

status_t BufferProducer::queueBuffer(int slot, const QueueBufferInput& input,
        QueueBufferOutput* output) {
    return mProducer->queueBuffer(slot, input, output);
}

status_t BufferProducer::cancelBuffer(int slot, const sp<Fence>& fence) {
    return mProducer->cancelBuffer(slot, fence);
}

int BufferProducer::query(int what, int* value) {
    switch(what) {
        case NATIVE_WINDOW_DEFAULT_WIDTH:
            *value = mFBWidth;
            return 0;
        case NATIVE_WINDOW_DEFAULT_HEIGHT:
            *value = mFBHeight;
            return 0;
        default:
            return mProducer->query(what, value);
    }
}

status_t BufferProducer::connect(const sp<IProducerListener>& listener,
        int api, bool producerControlledByApp, QueueBufferOutput* output) {
    return mProducer->connect(listener, api, producerControlledByApp, output);
}

status_t BufferProducer::disconnect(int api, DisconnectMode mode) {
    return mProducer->disconnect(api, mode);
}

status_t BufferProducer::setSidebandStream(const sp<NativeHandle>& stream) {
    return mProducer->setSidebandStream(stream);
}

void BufferProducer::allocateBuffers(uint32_t width, uint32_t height,
        PixelFormat format, uint64_t usage) {
    mProducer->allocateBuffers(width, height, format, usage);
}

status_t BufferProducer::allowAllocation(bool allow) {
    return mProducer->allowAllocation(allow);
}

status_t BufferProducer::setGenerationNumber(uint32_t generationNumber) {
    return mProducer->setGenerationNumber(generationNumber);
}

String8 BufferProducer::getConsumerName() const {
    return mProducer->getConsumerName();
}

status_t BufferProducer::setSharedBufferMode(bool sharedBufferMode) {
    return mProducer->setSharedBufferMode(sharedBufferMode);
}

status_t BufferProducer::setAutoRefresh(bool autoRefresh) {
    return mProducer->setAutoRefresh(autoRefresh);
}

status_t BufferProducer::setDequeueTimeout(nsecs_t timeout) {
    return mProducer->setDequeueTimeout(timeout);
}

status_t BufferProducer::setLegacyBufferDrop(bool drop) {
    return mProducer->setLegacyBufferDrop(drop);
}

status_t BufferProducer::getLastQueuedBuffer(sp<GraphicBuffer>* outBuffer,
        sp<Fence>* outFence, float outTransformMatrix[16]) {
    return mProducer->getLastQueuedBuffer(outBuffer, outFence,
            outTransformMatrix);
}

void BufferProducer::getFrameTimestamps(FrameEventHistoryDelta* outDelta) {
    mProducer->getFrameTimestamps(outDelta);
}

status_t BufferProducer::getUniqueId(uint64_t* outId) const {
    return mProducer->getUniqueId(outId);
}

status_t BufferProducer::getConsumerUsage(uint64_t* outUsage) const {
    //return mProducer->getConsumerUsage(outUsage);
    if (outUsage) {
        (*outUsage) = mEGLNativeWindow;
    }
    return OK;
}

IBinder* BufferProducer::onAsBinder() {
    return this;
}

// ---------------------------------------------------------------------------
}; // namespace NATIVE
}; // namespace android

#endif // ENABLE_ANDROID_GL
