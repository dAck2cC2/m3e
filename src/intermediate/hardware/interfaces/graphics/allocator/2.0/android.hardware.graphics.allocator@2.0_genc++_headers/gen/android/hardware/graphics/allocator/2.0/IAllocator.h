#ifndef HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_V2_0_IALLOCATOR_H
#define HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_V2_0_IALLOCATOR_H

#include <android/hardware/graphics/mapper/2.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace graphics {
namespace allocator {
namespace V2_0 {

struct IAllocator : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    using dumpDebugInfo_cb = std::function<void(const ::android::hardware::hidl_string& debugInfo)>;
    // @entry @exit @callflow(next="*")
    /**
     * Retrieves implementation-defined debug information, which will be
     * displayed during, for example, `dumpsys SurfaceFlinger`.
     * 
     * @return debugInfo is a string of debug information.
     */
    virtual ::android::hardware::Return<void> dumpDebugInfo(dumpDebugInfo_cb _hidl_cb) = 0;

    using allocate_cb = std::function<void(::android::hardware::graphics::mapper::V2_0::Error error, uint32_t stride, const ::android::hardware::hidl_vec<::android::hardware::hidl_handle>& buffers)>;
    // @entry @exit @callflow(next="*")
    /**
     * Allocates buffers with the properties specified by the descriptor.
     * 
     * @param descriptor specifies the properties of the buffers to allocate.
     * @param count is the number of buffers to allocate.
     * @return error is NONE upon success. Otherwise,
     *         BAD_DESCRIPTOR when the descriptor is invalid.
     *         NO_RESOURCES when the allocation cannot be fulfilled at this
     *                      time.
     *         UNSUPPORTED when any of the property encoded in the descriptor
     *                     is not supported.
     * @return stride is the number of pixels between two consecutive rows of
     *         the buffers, when the concept of consecutive rows is defined.
     *         Otherwise, it has no meaning.
     * @return buffers is an array of raw handles to the newly allocated
     *         buffers.
     */
    virtual ::android::hardware::Return<void> allocate(const ::android::hardware::hidl_vec<uint32_t>& descriptor, uint32_t count, allocate_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::allocator::V2_0::IAllocator>> castFrom(const ::android::sp<::android::hardware::graphics::allocator::V2_0::IAllocator>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::allocator::V2_0::IAllocator>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

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

static inline std::string toString(const ::android::sp<::android::hardware::graphics::allocator::V2_0::IAllocator>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::graphics::allocator::V2_0::IAllocator::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_0
}  // namespace allocator
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_V2_0_IALLOCATOR_H
