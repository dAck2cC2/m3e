
#include <utils/Mutex.h>
#include <utils/KeyedVector.h>

#include <hidl/memory/1.0/memory.h>

namespace android {
namespace hidl {
namespace memory {
namespace V1_0 {
namespace implement {

struct Ashmem {
    int       ref;
    uint64_t  size;
    void*     addr;
};

static ::android::Mutex gMutex("ashmem");
static ::android::KeyedVector<int, Ashmem> gMemory;

Memory::Memory(android::hardware::hidl_memory hidlmem) :
    mToken(0),
	mSize(0), 
	mPointer(nullptr)
{
	::android::AutoMutex _l(gMutex);

	mSize = hidlmem.size();
	LOG_ALWAYS_FATAL_IF((mSize == 0), "Invalid memory size");

    const native_handle_t* pNativeHandle = hidlmem.handle();
	LOG_ALWAYS_FATAL_IF((pNativeHandle == nullptr), "No native handle");
    LOG_ALWAYS_FATAL_IF((pNativeHandle->numInts != 1), "Invalid native handle");
    
    mToken = pNativeHandle->data[0];
	if (gMemory.indexOfKey(mToken) < 0) {
        mPointer = new uint8_t[mSize];
        LOG_ALWAYS_FATAL_IF((mPointer == nullptr), "No memroy");

        Ashmem mem = {0};
        mem.ref = 1;
        mem.size = mSize;
        mem.addr = mPointer;
        gMemory.add(mToken, mem);
	}
	else {
        LOG_ALWAYS_FATAL_IF((gMemory.valueFor(mToken).size != mSize), "memory size doesn't match");
        
        gMemory.editValueFor(mToken).ref++;
        mPointer = gMemory.valueFor(mToken).addr;
	}
    
    ALOGD("Ashmem create token: %d, refcnt: %d", mToken, gMemory.valueFor(mToken).ref);
}

Memory::~Memory()
{
	::android::AutoMutex _l(gMutex);
    
	LOG_ALWAYS_FATAL_IF((mSize == 0), "How it can become Zero ?");
	LOG_ALWAYS_FATAL_IF((mPointer == nullptr), "How it can become NULL ?");

    LOG_ALWAYS_FATAL_IF((gMemory.indexOfKey(mToken) < 0), "Where is memory token ?");
    
    ALOGD("Ashmem release token: %d, refcnt: %d", mToken, gMemory.valueFor(mToken).ref);
    
	if ((--(gMemory.editValueFor(mToken).ref)) == 0) {
        gMemory.removeItem(mToken);

		delete[] static_cast<uint8_t*>(mPointer);
	}
    
    mPointer = nullptr;
    mSize = 0;
}

}  // namespace implement
}  // namespace V1_0
}  // namespace memory
}  // namespace hidl
}  // namespace android
