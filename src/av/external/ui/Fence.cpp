
#define LOG_TAG "Fence"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS
//#define LOG_NDEBUG 0

// We would eliminate the non-conforming zero-length array, but we can't since
// this is effectively included from the Linux kernel
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wzero-length-array"
//#include <sync/sync.h>
//#pragma clang diagnostic pop

#include <ui/Fence.h>
//#include <unistd.h>
//#include <utils/Log.h>
//#include <utils/Trace.h>

namespace android {

const sp<Fence> Fence::NO_FENCE = sp<Fence>(new Fence);

Fence::Fence() {
}

Fence::Fence(int fenceFd) {
}

Fence::~Fence() {
}

status_t Fence::wait(int timeout) {
    return NO_ERROR;
}

status_t Fence::waitForever(const char* logname) {
    return NO_ERROR;
}

sp<Fence> Fence::merge(const String8& name, const sp<Fence>& f1,
        const sp<Fence>& f2) {
    return NULL;
}

int Fence::dup() const {
    return 0;
}

nsecs_t Fence::getSignalTime() const {
    return -1;
}

size_t Fence::getFlattenedSize() const {
    return 4;
}

size_t Fence::getFdCount() const {
    return 0;
}

status_t Fence::flatten(void*& buffer, size_t& size, int*& fds, size_t& count) const {
    return NO_ERROR;
}

status_t Fence::unflatten(void const*& buffer, size_t& size, int const*& fds, size_t& count) {
    return NO_ERROR;
}

} // namespace android
