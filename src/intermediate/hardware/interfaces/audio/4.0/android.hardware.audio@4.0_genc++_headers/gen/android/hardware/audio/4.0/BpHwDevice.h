#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_BPHWDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_BPHWDEVICE_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/audio/4.0/IHwDevice.h>

namespace android {
namespace hardware {
namespace audio {
namespace V4_0 {

struct BpHwDevice : public ::android::hardware::BpInterface<IDevice>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwDevice(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef IDevice Pure;

    typedef android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    // Methods from ::android::hardware::audio::V4_0::IDevice follow.
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_initCheck(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setMasterVolume(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, float volume);
    static ::android::hardware::Return<void>  _hidl_getMasterVolume(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getMasterVolume_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setMicMute(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, bool mute);
    static ::android::hardware::Return<void>  _hidl_getMicMute(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getMicMute_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setMasterMute(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, bool mute);
    static ::android::hardware::Return<void>  _hidl_getMasterMute(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getMasterMute_cb _hidl_cb);
    static ::android::hardware::Return<void>  _hidl_getInputBufferSize(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::common::V4_0::AudioConfig& config, getInputBufferSize_cb _hidl_cb);
    static ::android::hardware::Return<void>  _hidl_openOutputStream(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioOutputFlag> flags, const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata, openOutputStream_cb _hidl_cb);
    static ::android::hardware::Return<void>  _hidl_openInputStream(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioInputFlag> flags, const ::android::hardware::audio::V4_0::SinkMetadata& sinkMetadata, openInputStream_cb _hidl_cb);
    static ::android::hardware::Return<bool>  _hidl_supportsAudioPatches(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor);
    static ::android::hardware::Return<void>  _hidl_createAudioPatch(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sources, const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sinks, createAudioPatch_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_releaseAudioPatch(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t patch);
    static ::android::hardware::Return<void>  _hidl_getAudioPort(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::common::V4_0::AudioPort& port, getAudioPort_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setAudioPortConfig(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::common::V4_0::AudioPortConfig& config);
    static ::android::hardware::Return<void>  _hidl_getHwAvSync(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getHwAvSync_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setScreenState(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, bool turnedOn);
    static ::android::hardware::Return<void>  _hidl_getParameters(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setParameters(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters);
    static ::android::hardware::Return<void>  _hidl_getMicrophones(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getMicrophones_cb _hidl_cb);
    static ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_setConnectedState(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::V4_0::DeviceAddress& address, bool connected);

    // Methods from ::android::hardware::audio::V4_0::IDevice follow.
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> initCheck() override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMasterVolume(float volume) override;
    ::android::hardware::Return<void> getMasterVolume(getMasterVolume_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMicMute(bool mute) override;
    ::android::hardware::Return<void> getMicMute(getMicMute_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMasterMute(bool mute) override;
    ::android::hardware::Return<void> getMasterMute(getMasterMute_cb _hidl_cb) override;
    ::android::hardware::Return<void> getInputBufferSize(const ::android::hardware::audio::common::V4_0::AudioConfig& config, getInputBufferSize_cb _hidl_cb) override;
    ::android::hardware::Return<void> openOutputStream(int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioOutputFlag> flags, const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata, openOutputStream_cb _hidl_cb) override;
    ::android::hardware::Return<void> openInputStream(int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioInputFlag> flags, const ::android::hardware::audio::V4_0::SinkMetadata& sinkMetadata, openInputStream_cb _hidl_cb) override;
    ::android::hardware::Return<bool> supportsAudioPatches() override;
    ::android::hardware::Return<void> createAudioPatch(const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sources, const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sinks, createAudioPatch_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> releaseAudioPatch(int32_t patch) override;
    ::android::hardware::Return<void> getAudioPort(const ::android::hardware::audio::common::V4_0::AudioPort& port, getAudioPort_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setAudioPortConfig(const ::android::hardware::audio::common::V4_0::AudioPortConfig& config) override;
    ::android::hardware::Return<void> getHwAvSync(getHwAvSync_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setScreenState(bool turnedOn) override;
    ::android::hardware::Return<void> getParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters) override;
    ::android::hardware::Return<void> getMicrophones(getMicrophones_cb _hidl_cb) override;
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setConnectedState(const ::android::hardware::audio::V4_0::DeviceAddress& address, bool connected) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V4_0
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_BPHWDEVICE_H
