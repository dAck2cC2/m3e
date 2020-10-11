#ifndef HIDL_MEMORY_MAPPER_V1_0_IMPL_LOCAL_H
#define HIDL_MEMORY_MAPPER_V1_0_IMPL_LOCAL_H

#include <android/hidl/memory/1.0/IMapper.h>
#include <hidl/memory/1.0/memory.h>

namespace android {
namespace hidl {
namespace memory {
namespace V1_0 {
namespace implement {

using namespace ::android::hidl::memory::V1_0;
using ImplMemory1_0 = ::android::hidl::memory::V1_0::implement::Memory;

struct Mapper : public IMapper {
    virtual ::android::hardware::Return<::android::sp<::android::hidl::memory::V1_0::IMemory>> mapMemory(const ::android::hardware::hidl_memory& mem) override
    {
        return new ImplMemory1_0(mem);
    };
}; // Mapper

}  // implement
}  // namespace V1_0
}  // namespace memory
}  // namespace hidl
}  // namespace android

#endif // HIDL_MEMORY_MAPPER_V1_0_IMPL_LOCAL_H
