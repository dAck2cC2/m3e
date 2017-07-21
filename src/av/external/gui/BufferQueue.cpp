
#define LOG_TAG "BufferQueue"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS
//#define LOG_NDEBUG 0

#include <gui/BufferQueue.h>
//#include <gui/BufferQueueConsumer.h>
//#include <gui/BufferQueueCore.h>
//#include <gui/BufferQueueProducer.h>

namespace android {

BufferQueue::ProxyConsumerListener::ProxyConsumerListener(
        const wp<ConsumerListener>& consumerListener)
{}

BufferQueue::ProxyConsumerListener::~ProxyConsumerListener() {}

void BufferQueue::ProxyConsumerListener::onFrameAvailable(
        const BufferItem& item) {
}

void BufferQueue::ProxyConsumerListener::onFrameReplaced(
        const BufferItem& item) {
}

void BufferQueue::ProxyConsumerListener::onBuffersReleased() {
}

void BufferQueue::ProxyConsumerListener::onSidebandStreamChanged() {
}

bool BufferQueue::ProxyConsumerListener::getFrameTimestamps(
        uint64_t frameNumber, FrameTimestamps* outTimestamps) const {
    return false;
}

void BufferQueue::createBufferQueue(sp<IGraphicBufferProducer>* outProducer,
        sp<IGraphicBufferConsumer>* outConsumer,
        const sp<IGraphicBufferAlloc>& allocator) {
}

}; // namespace android
