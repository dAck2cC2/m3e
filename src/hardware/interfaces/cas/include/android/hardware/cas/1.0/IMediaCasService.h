#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_IMEDIACASSERVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_IMEDIACASSERVICE_H

#include <android/hardware/cas/1.0/ICas.h>
#include <android/hardware/cas/1.0/ICasListener.h>
#include <android/hardware/cas/1.0/IDescramblerBase.h>
#include <android/hardware/cas/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {

struct IMediaCasService : public ::android::hidl::base::V1_0::IBase {
    virtual bool isRemote() const override { return false; }


    using enumeratePlugins_cb = std::function<void(const ::android::hardware::hidl_vec<HidlCasPluginDescriptor>& descriptors)>;
    virtual ::android::hardware::Return<void> enumeratePlugins(enumeratePlugins_cb _hidl_cb) = 0;

    virtual ::android::hardware::Return<bool> isSystemIdSupported(int32_t CA_system_id) = 0;

    virtual ::android::hardware::Return<::android::sp<ICas>> createPlugin(int32_t CA_system_id, const ::android::sp<ICasListener>& listener) = 0;

    virtual ::android::hardware::Return<bool> isDescramblerSupported(int32_t CA_system_id) = 0;

    virtual ::android::hardware::Return<::android::sp<IDescramblerBase>> createDescrambler(int32_t CA_system_id) = 0;

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
    static ::android::hardware::Return<::android::sp<IMediaCasService>> castFrom(const ::android::sp<IMediaCasService>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<IMediaCasService>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IMediaCasService> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IMediaCasService> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IMediaCasService> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IMediaCasService> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IMediaCasService> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IMediaCasService> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IMediaCasService> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IMediaCasService> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

std::string toString(const ::android::sp<IMediaCasService>&);

}  // namespace V1_0
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_IMEDIACASSERVICE_H
