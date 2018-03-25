
#define LOG_TAG "GraphicBufferMapper"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS
//#define LOG_NDEBUG 0

#include <stdint.h>
#include <errno.h>

#include <system/window.h>
#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>

namespace android {
// ---------------------------------------------------------------------------

ANDROID_SINGLETON_STATIC_INSTANCE( GraphicBufferMapper )

GraphicBufferMapper::GraphicBufferMapper()
{}

status_t GraphicBufferMapper::registerBuffer(buffer_handle_t handle)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::registerBuffer(const GraphicBuffer* buffer)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::unregisterBuffer(buffer_handle_t handle)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::lock(buffer_handle_t handle, uint32_t usage,
        const Rect& bounds, void** vaddr)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::lockYCbCr(buffer_handle_t handle, uint32_t usage,
        const Rect& bounds, android_ycbcr *ycbcr)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::unlock(buffer_handle_t handle)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::lockAsync(buffer_handle_t handle,
        uint32_t usage, const Rect& bounds, void** vaddr, int fenceFd)
{
    return INVALID_OPERATION;
}

static inline bool isValidYCbCrPlane(const android_flex_plane_t& plane) {
    return false;
}

status_t GraphicBufferMapper::lockAsyncYCbCr(buffer_handle_t handle,
        uint32_t usage, const Rect& bounds, android_ycbcr *ycbcr, int fenceFd)
{
    return INVALID_OPERATION;
}

status_t GraphicBufferMapper::unlockAsync(buffer_handle_t handle, int *fenceFd)
{
    return INVALID_OPERATION;
}

// ---------------------------------------------------------------------------
}; // namespace android
