
#define LOG_TAG "Surface"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS
//#define LOG_NDEBUG 0

#include <gui/Surface.h>

namespace android {

Surface::Surface(
        const sp<IGraphicBufferProducer>& bufferProducer,
        bool controlledByApp)
{
}

Surface::~Surface() {
}

sp<IGraphicBufferProducer> Surface::getIGraphicBufferProducer() const {
    return nullptr;
}

void Surface::setSidebandStream(const sp<NativeHandle>& stream) {
}

void Surface::allocateBuffers() {
}

status_t Surface::setGenerationNumber(uint32_t generation) {
    return NO_ERROR;
}

uint64_t Surface::getNextFrameNumber() const {
    return 0;
}

String8 Surface::getConsumerName() const {
    return String8();
}

status_t Surface::setDequeueTimeout(nsecs_t timeout) {
    return NO_ERROR;
}

status_t Surface::getLastQueuedBuffer(sp<GraphicBuffer>* outBuffer,
        sp<Fence>* outFence, float outTransformMatrix[16]) {
    return NO_ERROR;
}

bool Surface::getFrameTimestamps(uint64_t frameNumber, nsecs_t* outPostedTime,
        nsecs_t* outAcquireTime, nsecs_t* outRefreshStartTime,
        nsecs_t* outGlCompositionDoneTime, nsecs_t* outDisplayRetireTime,
        nsecs_t* outReleaseTime) {
    return false;
}
int Surface::setSwapInterval(int interval) {
    return 0;
}

int Surface::dequeueBuffer(android_native_buffer_t** buffer, int* fenceFd) {
    return OK;
}

int Surface::cancelBuffer(android_native_buffer_t* buffer,
        int fenceFd) {
    return OK;
}

int Surface::lockBuffer_DEPRECATED(android_native_buffer_t* buffer __attribute__((unused))) {
    return OK;
}

int Surface::queueBuffer(android_native_buffer_t* buffer, int fenceFd) {
    return OK;
}

int Surface::query(int what, int* value) const {
    return OK;
}

int Surface::perform(int operation, va_list args)
{
    return OK;
}

int Surface::connect(int api) {
    return OK;
}

int Surface::connect(int api, const sp<IProducerListener>& listener) {
    return OK;
}


int Surface::disconnect(int api) {
    return OK;
}

int Surface::detachNextBuffer(sp<GraphicBuffer>* outBuffer,
        sp<Fence>* outFence) {
    return OK;
}

int Surface::attachBuffer(ANativeWindowBuffer* buffer)
{
    return OK;
}

int Surface::setUsage(uint32_t reqUsage)
{
    return OK;
}

int Surface::setCrop(Rect const* rect)
{
    return NO_ERROR;
}

int Surface::setBufferCount(int bufferCount)
{
    return OK;
}

int Surface::setMaxDequeuedBufferCount(int maxDequeuedBuffers) {
    return OK;
}

int Surface::setAsyncMode(bool async) {
    return OK;
}

int Surface::setSharedBufferMode(bool sharedBufferMode) {
    return OK;
}

int Surface::setAutoRefresh(bool autoRefresh) {
    return OK;
}

int Surface::setBuffersDimensions(uint32_t width, uint32_t height)
{
    return NO_ERROR;
}

int Surface::setBuffersUserDimensions(uint32_t width, uint32_t height)
{
    return NO_ERROR;
}

int Surface::setBuffersFormat(PixelFormat format)
{
    return NO_ERROR;
}

int Surface::setScalingMode(int mode)
{
    return NO_ERROR;
}

int Surface::setBuffersTransform(uint32_t transform)
{
    return NO_ERROR;
}

int Surface::setBuffersStickyTransform(uint32_t transform)
{
    return NO_ERROR;
}

int Surface::setBuffersTimestamp(int64_t timestamp)
{
    return NO_ERROR;
}

int Surface::setBuffersDataSpace(android_dataspace dataSpace)
{
    return NO_ERROR;
}

void Surface::setSurfaceDamage(android_native_rect_t* rects, size_t numRects) {
}

// ----------------------------------------------------------------------------

status_t Surface::lock(
        ANativeWindow_Buffer* outBuffer, ARect* inOutDirtyBounds)
{
        return INVALID_OPERATION;
}

status_t Surface::unlockAndPost()
{
        return INVALID_OPERATION;
}

bool Surface::waitForNextFrame(uint64_t lastFrame, nsecs_t timeout) {
      return true;
}

status_t Surface::getUniqueId(uint64_t* outId) const {
    return OK;
}

}; // namespace android
