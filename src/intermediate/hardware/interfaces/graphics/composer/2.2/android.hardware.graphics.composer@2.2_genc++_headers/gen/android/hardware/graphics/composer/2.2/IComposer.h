#ifndef HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_2_ICOMPOSER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_2_ICOMPOSER_H

#include <android/hardware/graphics/composer/2.1/IComposer.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_2 {

struct IComposer : public ::android::hardware::graphics::composer::V2_1::IComposer {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    using getCapabilities_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::graphics::composer::V2_1::IComposer::Capability>& capabilities)>;
    // @entry @exit @callflow(next="*")
    /**
     * Provides a list of supported capabilities (as described in the
     * definition of Capability above). This list must not change after
     * initialization.
     * 
     * @return capabilities is a list of supported capabilities.
     */
    virtual ::android::hardware::Return<void> getCapabilities(getCapabilities_cb _hidl_cb) = 0;

    using dumpDebugInfo_cb = std::function<void(const ::android::hardware::hidl_string& debugInfo)>;
    // @entry @exit @callflow(next="*")
    /**
     * Retrieves implementation-defined debug information, which will be
     * displayed during, for example, `dumpsys SurfaceFlinger`.
     * 
     * @return debugInfo is a string of debug information.
     */
    virtual ::android::hardware::Return<void> dumpDebugInfo(dumpDebugInfo_cb _hidl_cb) = 0;

    using createClient_cb = std::function<void(::android::hardware::graphics::composer::V2_1::Error error, const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerClient>& client)>;
    // @entry @callflow(next="*")
    /**
     * Creates a client of the composer. All resources created by the client
     * are owned by the client and are only visible to the client.
     * 
     * There can only be one client at any time.
     * 
     * @return error is NONE upon success. Otherwise,
     *         NO_RESOURCES when no more client can be created currently.
     * @return client is the newly created client.
     */
    virtual ::android::hardware::Return<void> createClient(createClient_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>> castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>> castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IComposer> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposer> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IComposer> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IComposer> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IComposer> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposer> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IComposer> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IComposer> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::graphics::composer::V2_2::IComposer::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_2
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_2_ICOMPOSER_H
