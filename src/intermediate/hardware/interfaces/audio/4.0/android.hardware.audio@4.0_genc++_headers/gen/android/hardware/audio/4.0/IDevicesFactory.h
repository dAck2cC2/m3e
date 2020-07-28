#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICESFACTORY_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICESFACTORY_H

#include <android/hardware/audio/4.0/IDevice.h>
#include <android/hardware/audio/4.0/IPrimaryDevice.h>
#include <android/hardware/audio/4.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace audio {
namespace V4_0 {

struct IDevicesFactory : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * This factory allows a HAL implementation to be split in multiple independent
     *  devices (called module in the pre-treble API).
     *  Note that this division is arbitrary and implementation are free
     *  to only have a Primary.
     *  The framework will query the devices according to audio_policy_configuration.xml
     * 
     *  Each device name is arbitrary, provided by the vendor's audio_policy_configuration.xml
     *  and only used to identify a device in this factory.
     *  The framework must not interpret the name, treating it as a vendor opaque data
     *  with the following exception:
     *  - the "r_submix" device that must be present to support policyMixes (Eg: Android projected).
     *    Note that this Device is included by default in a build derived from AOSP.
     * 
     *  Note that on AOSP Oreo (including MR1) the "a2dp" module is not using this API
     *  but is loaded directly from the system partition using the legacy API
     *  due to limitations with the Bluetooth framework.
     */
    virtual bool isRemote() const override { return false; }


    using openDevice_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::sp<::android::hardware::audio::V4_0::IDevice>& result)>;
    /**
     * Opens an audio device. To close the device, it is necessary to release
     * references to the returned device object.
     * 
     * @param device device name.
     * @return retval operation completion status. Returns INVALID_ARGUMENTS
     *         if there is no corresponding hardware module found,
     *         NOT_INITIALIZED if an error occured while opening the hardware
     *         module.
     * @return result the interface for the created device.
     */
    virtual ::android::hardware::Return<void> openDevice(const ::android::hardware::hidl_string& device, openDevice_cb _hidl_cb) = 0;

    using openPrimaryDevice_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::sp<::android::hardware::audio::V4_0::IPrimaryDevice>& result)>;
    /**
     * Opens the Primary audio device that must be present.
     * This function is not optional and must return successfully the primary device.
     * 
     * This device must have the name "primary".
     * 
     * The telephony stack uses this device to control the audio during a voice call.
     * 
     * @return retval operation completion status. Must be SUCCESS.
     *         For debuging, return INVALID_ARGUMENTS if there is no corresponding
     *         hardware module found, NOT_INITIALIZED if an error occurred
     *         while opening the hardware module.
     * @return result the interface for the created device.
     */
    virtual ::android::hardware::Return<void> openPrimaryDevice(openPrimaryDevice_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IDevicesFactory>> castFrom(const ::android::sp<::android::hardware::audio::V4_0::IDevicesFactory>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IDevicesFactory>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IDevicesFactory> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDevicesFactory> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IDevicesFactory> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IDevicesFactory> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IDevicesFactory> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDevicesFactory> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IDevicesFactory> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IDevicesFactory> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::audio::V4_0::IDevicesFactory>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::V4_0::IDevicesFactory::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V4_0
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICESFACTORY_H
