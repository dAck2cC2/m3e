#ifndef HIDL_MEMORY_MEMROY_V1_0_IMPL_LOCAL_H
#define HIDL_MEMORY_MEMROY_V1_0_IMPL_LOCAL_H

#include <android/hidl/memory/1.0/IMemory.h>

namespace android {
namespace hidl {
namespace memory {
namespace V1_0 {
namespace implement {

using namespace ::android::hidl::memory::V1_0;

struct Memory : public IMemory {
public:
	explicit Memory(uint64_t size) : mSize(size) , mPointer(nullptr)
	{
		if (mSize > 0) {
			mPointer = new uint8_t[mSize];
			memset(mPointer, 0x00, mSize);
		}
	};

	virtual ~Memory()
	{
		if (mPointer) {
			delete[] mPointer;
			mPointer = nullptr;
		}
	};

	virtual ::android::hardware::Return<void> update() override 
	{
		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void> updateRange(uint64_t start, uint64_t length) override
	{
		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void> read() override
	{
		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void> readRange(uint64_t start, uint64_t length) override 
	{
		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void> commit() override 
	{
		return ::android::hardware::Void();
	};

	virtual ::android::hardware::Return<void*> getPointer() override 
	{
		return mPointer;
	};

	virtual ::android::hardware::Return<uint64_t> getSize() override 
	{
		return mSize;
	};
private:
	uint64_t mSize;
	void* mPointer;
}; // Memory

}  // namespace implement
}  // namespace V1_0
}  // namespace memory
}  // namespace hidl
}  // namespace android

#endif // HIDL_MEMORY_MEMROY_V1_0_IMPL_LOCAL_H
