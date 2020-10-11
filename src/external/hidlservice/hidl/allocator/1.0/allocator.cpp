
#include <log/log.h>
#include <utils/Mutex.h>

#include <hidl/allocator/1.0/allocator.h>

namespace android {
namespace hidl {
namespace allocator {
namespace V1_0 {
namespace implement {

static const int MEM_TOKEN_MAX = INT_MAX;
static int gMemToken = 0;
static ::android::Mutex gMemMtx("MemToken");

::android::hardware::Return<void> Allocator::allocate(uint64_t size, allocate_cb _hidl_cb)
{
	LOG_ALWAYS_FATAL_IF((size == 0), "request empty allocate");

    native_handle_t* pNativeHandle = native_handle_create(0, 1);
    LOG_ALWAYS_FATAL_IF((pNativeHandle == nullptr), "failed to create natve handle");

    {
        ::android::AutoMutex _l(gMemMtx);
        
        // Negative value may also work.
        // Keeping it postive for debugging convenience
        if (gMemToken < MEM_TOKEN_MAX - 1) {
            gMemToken++;
        } else {
            gMemToken = 0;
        }
        
        pNativeHandle->data[0] = gMemToken;
    }
    
	android::hardware::hidl_memory mem = android::hardware::hidl_memory("ashmem", pNativeHandle, size);
	_hidl_cb(true, mem);
    
    // Native Handle should be cloned in callback.
    // It is safe to remove it then.
    native_handle_delete(pNativeHandle);
    
	return ::android::hardware::Void();
};

::android::hardware::Return<void> Allocator::batchAllocate(uint64_t size, uint64_t count, batchAllocate_cb _hidl_cb)
{
	LOG_ALWAYS_FATAL_IF((size == 0),  "request empty size");
	LOG_ALWAYS_FATAL_IF((count == 0), "request empty batch");

	LOG_ALWAYS_FATAL("DEBUG: Not supported yet");

	return ::android::hardware::Void();
};

}  // namespace implement
}  // namespace V1_0
}  // namespace allocator
}  // namespace hidl
}  // namespace android
