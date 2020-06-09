#ifndef HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_IMEMORY_H
#define HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_IMEMORY_H

#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hidl {
namespace memory {
namespace V1_0 {

struct IMemory : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    /**
     * Notify that you are about to use all of this memory.
     */
    virtual ::android::hardware::Return<void> update() = 0;

    /**
     * Notify that you are about to use the specific range.
     * 
     * start + length must be < size
     * 
     * @param start Offset from start of buffer about to be updated.
     * @param length Number of bytes to be updated.
     */
    virtual ::android::hardware::Return<void> updateRange(uint64_t start, uint64_t length) = 0;

    /**
     * Notify that you are about to start reading all of this memory.
     */
    virtual ::android::hardware::Return<void> read() = 0;

    /**
     * Notify that you are about to read the specific range.
     * 
     * @param start Offset from start of buffer about to be read.
     * @param length Number of bytes to be read.
     */
    virtual ::android::hardware::Return<void> readRange(uint64_t start, uint64_t length) = 0;

    /**
     * Notify that you are done reading and/or writing this memory.
     * 
     * Must commit all previous update's and updateAll's.
     */
    virtual ::android::hardware::Return<void> commit() = 0;

    /**
     * Must return the same value everytime it is called. Must be callable
     * at any point in or outside of the update/commit process.
     * 
     * @return ptr Actual pointer to underlying memory.
     */
    virtual ::android::hardware::Return<void*> getPointer() = 0;

    /**
     * @return size Size in bytes of underlying memory.
     */
    virtual ::android::hardware::Return<uint64_t> getSize() = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hidl::memory::V1_0::IMemory>> castFrom(const ::android::sp<::android::hidl::memory::V1_0::IMemory>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hidl::memory::V1_0::IMemory>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IMemory> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IMemory> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IMemory> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IMemory> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IMemory> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IMemory> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IMemory> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IMemory> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hidl::memory::V1_0::IMemory>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hidl::memory::V1_0::IMemory::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace memory
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_IMEMORY_H
