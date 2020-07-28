#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTBUFFERPROVIDERCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTBUFFERPROVIDERCALLBACK_H

#include <android/hardware/audio/effect/2.0/types.h>
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
namespace effect {
namespace V2_0 {

struct IEffectBufferProviderCallback : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * This callback interface contains functions that can be used by the effect
     * engine 'process' function to exchange input and output audio buffers.
     */
    virtual bool isRemote() const override { return false; }


    using getBuffer_cb = std::function<void(const ::android::hardware::audio::effect::V2_0::AudioBuffer& buffer)>;
    /**
     * Called to retrieve a buffer where data should read from by 'process'
     * function.
     * 
     * @return buffer audio buffer for processing
     */
    virtual ::android::hardware::Return<void> getBuffer(getBuffer_cb _hidl_cb) = 0;

    /**
     * Called to provide a buffer with the data written by 'process' function.
     * 
     * @param buffer audio buffer for processing
     */
    virtual ::android::hardware::Return<void> putBuffer(const ::android::hardware::audio::effect::V2_0::AudioBuffer& buffer) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>> castFrom(const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IEffectBufferProviderCallback> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IEffectBufferProviderCallback> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IEffectBufferProviderCallback> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IEffectBufferProviderCallback> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IEffectBufferProviderCallback> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IEffectBufferProviderCallback> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IEffectBufferProviderCallback> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IEffectBufferProviderCallback> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_0
}  // namespace effect
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTBUFFERPROVIDERCALLBACK_H
