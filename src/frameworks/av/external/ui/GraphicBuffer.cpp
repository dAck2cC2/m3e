
#define LOG_TAG "GraphicBuffer"
#include <ui/GraphicBuffer.h>

namespace android {

GraphicBuffer::GraphicBuffer()
{
}

GraphicBuffer::GraphicBuffer(uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage, std::string requestorName)
{
}

GraphicBuffer::GraphicBuffer(uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage, uint32_t inStride,
        native_handle_t* inHandle, bool keepOwnership)
{
}

GraphicBuffer::GraphicBuffer(ANativeWindowBuffer* buffer, bool keepOwnership)
{
}

GraphicBuffer::~GraphicBuffer()
{
}

status_t GraphicBuffer::initCheck() const {
    return INVALID_OPERATION;
}

void GraphicBuffer::dumpAllocationsToSystemLog()
{
}


status_t GraphicBuffer::reallocate(uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage)
{
        return INVALID_OPERATION;
}

bool GraphicBuffer::needsReallocation(uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage)
{
    return false;
}

status_t GraphicBuffer::lock(uint32_t inUsage, void** vaddr)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lock(uint32_t inUsage, const Rect& rect, void** vaddr)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockYCbCr(uint32_t inUsage, android_ycbcr* ycbcr)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockYCbCr(uint32_t inUsage, const Rect& rect,
        android_ycbcr* ycbcr)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::unlock()
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockAsync(uint32_t inUsage, void** vaddr, int fenceFd)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockAsync(uint32_t inUsage, const Rect& rect,
        void** vaddr, int fenceFd)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockAsyncYCbCr(uint32_t inUsage, android_ycbcr* ycbcr,
        int fenceFd)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::lockAsyncYCbCr(uint32_t inUsage, const Rect& rect,
        android_ycbcr* ycbcr, int fenceFd)
{
        return INVALID_OPERATION;
}

status_t GraphicBuffer::unlockAsync(int *fenceFd)
{
        return INVALID_OPERATION;
}

size_t GraphicBuffer::getFlattenedSize() const {
    return 0;
}

size_t GraphicBuffer::getFdCount() const {
    return 0;
}

status_t GraphicBuffer::flatten(void*& buffer, size_t& size, int*& fds, size_t& count) const {
        return INVALID_OPERATION;
}

status_t GraphicBuffer::unflatten(
        void const*& buffer, size_t& size, int const*& fds, size_t& count) {
        return INVALID_OPERATION;
}

ANativeWindowBuffer* GraphicBuffer::getNativeBuffer() const
{
        return NULL;
}


// ---------------------------------------------------------------------------

}; // namespace android
