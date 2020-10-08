#ifndef HIDL_ALLOCATOR_V1_0_IMPL_LOCAL_H
#define HIDL_ALLOCATOR_V1_0_IMPL_LOCAL_H

#include <android/hidl/allocator/1.0/IAllocator.h>

namespace android {
namespace hidl {
namespace allocator {
namespace V1_0 {
namespace implement {

using namespace ::android::hidl::allocator::V1_0;

struct Allocator : public IAllocator {
	virtual ::android::hardware::Return<void> allocate(uint64_t size, allocate_cb _hidl_cb) override 
	{
		LOG_ALWAYS_FATAL_IF((size == 0), "request empty allocate");

		android::hardware::hidl_memory* mem = new android::hardware::hidl_memory("local", nullptr, size);
		if (mem != NULL) {
			_hidl_cb(true, *mem);

			delete (mem);
		}

		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void> batchAllocate(uint64_t size, uint64_t count, batchAllocate_cb _hidl_cb) override
	{
		LOG_ALWAYS_FATAL_IF((size == 0),  "request empty size");
		LOG_ALWAYS_FATAL_IF((count == 0), "request empty batch");

		return ::android::hardware::Void();
	};
}; // Allocator

}  // namespace implement
}  // namespace V1_0
}  // namespace allocator
}  // namespace hidl
}  // namespace android

#endif // HIDL_ALLOCATOR_V1_0_IMPL_LOCAL_H
