
#include <gui/BufferItem.h>

#include <ui/Fence.h>
#include <ui/GraphicBuffer.h>

//#include <system/window.h>

namespace android {

BufferItem::BufferItem() {}

BufferItem::~BufferItem() {}

template <typename T>
static void addAligned(size_t& size, T /* value */) {
}

size_t BufferItem::getPodSize() const {
    return 0;
}

size_t BufferItem::getFlattenedSize() const {
    return 0;
}

size_t BufferItem::getFdCount() const {
    return 0;
}

template <typename T>
static void writeAligned(void*& buffer, size_t& size, T value) {
}

status_t BufferItem::flatten(
        void*& buffer, size_t& size, int*& fds, size_t& count) const {
    return NO_ERROR;
}

template <typename T>
static void readAligned(const void*& buffer, size_t& size, T& value) {
}

status_t BufferItem::unflatten(
        void const*& buffer, size_t& size, int const*& fds, size_t& count) {
    return NO_ERROR;
}

const char* BufferItem::scalingModeName(uint32_t scalingMode) {
    return "Unknown";
}

} // namespace android
