#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_ISURFACEFLINGERCONFIGS_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_ISURFACEFLINGERCONFIGS_H

#include <android/hardware/configstore/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace configstore {
namespace V1_0 {

struct ISurfaceFlingerConfigs : public ::android::hidl::base::V1_0::IBase {
    virtual bool isRemote() const override { return false; }


    using vsyncEventPhaseOffsetNs_cb = std::function<void(const OptionalInt64& value)>;
    virtual ::android::hardware::Return<void> vsyncEventPhaseOffsetNs(vsyncEventPhaseOffsetNs_cb _hidl_cb) = 0;

    using vsyncSfEventPhaseOffsetNs_cb = std::function<void(const OptionalInt64& value)>;
    virtual ::android::hardware::Return<void> vsyncSfEventPhaseOffsetNs(vsyncSfEventPhaseOffsetNs_cb _hidl_cb) = 0;

    using useContextPriority_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> useContextPriority(useContextPriority_cb _hidl_cb) = 0;

    using hasWideColorDisplay_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> hasWideColorDisplay(hasWideColorDisplay_cb _hidl_cb) = 0;

    using hasHDRDisplay_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> hasHDRDisplay(hasHDRDisplay_cb _hidl_cb) = 0;

    using presentTimeOffsetFromVSyncNs_cb = std::function<void(const OptionalInt64& value)>;
    virtual ::android::hardware::Return<void> presentTimeOffsetFromVSyncNs(presentTimeOffsetFromVSyncNs_cb _hidl_cb) = 0;

    using useHwcForRGBtoYUV_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> useHwcForRGBtoYUV(useHwcForRGBtoYUV_cb _hidl_cb) = 0;

    using maxVirtualDisplaySize_cb = std::function<void(const OptionalUInt64& value)>;
    virtual ::android::hardware::Return<void> maxVirtualDisplaySize(maxVirtualDisplaySize_cb _hidl_cb) = 0;

    using hasSyncFramework_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> hasSyncFramework(hasSyncFramework_cb _hidl_cb) = 0;

    using useVrFlinger_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> useVrFlinger(useVrFlinger_cb _hidl_cb) = 0;

    using maxFrameBufferAcquiredBuffers_cb = std::function<void(const OptionalInt64& value)>;
    virtual ::android::hardware::Return<void> maxFrameBufferAcquiredBuffers(maxFrameBufferAcquiredBuffers_cb _hidl_cb) = 0;

    using startGraphicsAllocatorService_cb = std::function<void(const OptionalBool& value)>;
    virtual ::android::hardware::Return<void> startGraphicsAllocatorService(startGraphicsAllocatorService_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<ISurfaceFlingerConfigs>> castFrom(const ::android::sp<ISurfaceFlingerConfigs>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<ISurfaceFlingerConfigs>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

	static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const std::string &serviceName = "default", bool getStub = false) { return NULL; };
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(bool getStub) { return tryGetService("default", getStub); }
	static ::android::sp<ISurfaceFlingerConfigs> getService(const std::string &serviceName = "default", bool getStub = false) { return NULL; };
    static ::android::sp<ISurfaceFlingerConfigs> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

std::string toString(const ::android::sp<ISurfaceFlingerConfigs>&);

}  // namespace V1_0
}  // namespace configstore
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_ISURFACEFLINGERCONFIGS_H
