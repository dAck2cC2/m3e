#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTSFACTORY_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTSFACTORY_H

#include <android/hardware/audio/common/2.0/types.h>
#include <android/hardware/audio/effect/2.0/IEffect.h>
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

struct IEffectsFactory : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    using getAllDescriptors_cb = std::function<void(::android::hardware::audio::effect::V2_0::Result retval, const ::android::hardware::hidl_vec<::android::hardware::audio::effect::V2_0::EffectDescriptor>& result)>;
    /**
     * Returns descriptors of different effects in all loaded libraries.
     * 
     * @return retval operation completion status.
     * @return result list of effect descriptors.
     */
    virtual ::android::hardware::Return<void> getAllDescriptors(getAllDescriptors_cb _hidl_cb) = 0;

    using getDescriptor_cb = std::function<void(::android::hardware::audio::effect::V2_0::Result retval, const ::android::hardware::audio::effect::V2_0::EffectDescriptor& result)>;
    /**
     * Returns a descriptor of a particular effect.
     * 
     * @return retval operation completion status.
     * @return result effect descriptor.
     */
    virtual ::android::hardware::Return<void> getDescriptor(const ::android::hardware::audio::common::V2_0::Uuid& uid, getDescriptor_cb _hidl_cb) = 0;

    using createEffect_cb = std::function<void(::android::hardware::audio::effect::V2_0::Result retval, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffect>& result, uint64_t effectId)>;
    /**
     * Creates an effect engine of the specified type.  To release the effect
     * engine, it is necessary to release references to the returned effect
     * object.
     * 
     * @param uid effect uuid.
     * @param session audio session to which this effect instance will be
     *                attached.  All effects created with the same session ID
     *                are connected in series and process the same signal
     *                stream.
     * @param ioHandle identifies the output or input stream this effect is
     *                 directed to in audio HAL.
     * @return retval operation completion status.
     * @return result the interface for the created effect.
     * @return effectId the unique ID of the effect to be used with
     *                  IStream::addEffect and IStream::removeEffect methods.
     */
    virtual ::android::hardware::Return<void> createEffect(const ::android::hardware::audio::common::V2_0::Uuid& uid, int32_t session, int32_t ioHandle, createEffect_cb _hidl_cb) = 0;

    /**
     * Dumps information about effects into the provided file descriptor.
     * This is used for the dumpsys facility.
     * 
     * @param fd dump file descriptor.
     */
    virtual ::android::hardware::Return<void> debugDump(const ::android::hardware::hidl_handle& fd) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IEffectsFactory>> castFrom(const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectsFactory>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IEffectsFactory>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IEffectsFactory> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IEffectsFactory> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IEffectsFactory> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IEffectsFactory> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IEffectsFactory> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IEffectsFactory> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IEffectsFactory> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IEffectsFactory> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectsFactory>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::effect::V2_0::IEffectsFactory::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_0
}  // namespace effect
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V2_0_IEFFECTSFACTORY_H
