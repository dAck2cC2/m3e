#ifndef HIDL_GENERATED_ANDROID_HIDL_ALLOCATOR_V1_0_IALLOCATOR_H
#define HIDL_GENERATED_ANDROID_HIDL_ALLOCATOR_V1_0_IALLOCATOR_H

#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hidl {
namespace allocator {
namespace V1_0 {

struct IAllocator : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * Interface which allocates the required memory.
     */
    virtual bool isRemote() const override { return false; }


    using allocate_cb = std::function<void(bool success, const ::android::hardware::hidl_memory& mem)>;
    /**
     * Return memory must have instance name corresponding to this type of memory.
     * 
     * @param size Size of memory to allocate in bytes.
     * @return success Whether allocation succeeded.
     * @return memory Unmapped memory object.
     */
    virtual ::android::hardware::Return<void> allocate(uint64_t size, allocate_cb _hidl_cb) = 0;

    using batchAllocate_cb = std::function<void(bool success, const ::android::hardware::hidl_vec<::android::hardware::hidl_memory>& batch)>;
    /**
     * Return memory must have instance name corresponding to this type of memory.
     * 
     * @param size Size of memory to allocate in bytes.
     * @param count Number of memory instances to allocate.
     * @return success Whether allocation succeeded (returns false if any allocation failed).
     * @return batch Unmapped memory objects.
     */
    virtual ::android::hardware::Return<void> batchAllocate(uint64_t size, uint64_t count, batchAllocate_cb _hidl_cb) = 0;

    using interfaceChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)>;
    virtual ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;

    using interfaceDescriptor_cb = std::function<void(const ::android::hardware::hidl_string& descriptor)>;
    virtual ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;

    using getHashChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_array<uint8_t, 32>>& hashchain)>;
    virtual ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> setHALInstrumentation() override;

    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;

    virtual ::android::hardware::Return<void> ping() override;

    using getDebugInfo_cb = std::function<void(const ::android::hidl::base::V1_0::DebugInfo& info)>;
    virtual ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> notifySyspropsChanged() override;

    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;
    // cast static functions
    static ::android::hardware::Return<::android::sp<::android::hidl::allocator::V1_0::IAllocator>> castFrom(const ::android::sp<::android::hidl::allocator::V1_0::IAllocator>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hidl::allocator::V1_0::IAllocator>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IAllocator> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IAllocator> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IAllocator> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IAllocator> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IAllocator> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IAllocator> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IAllocator> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IAllocator> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hidl::allocator::V1_0::IAllocator>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hidl::allocator::V1_0::IAllocator::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace allocator
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_ALLOCATOR_V1_0_IALLOCATOR_H
