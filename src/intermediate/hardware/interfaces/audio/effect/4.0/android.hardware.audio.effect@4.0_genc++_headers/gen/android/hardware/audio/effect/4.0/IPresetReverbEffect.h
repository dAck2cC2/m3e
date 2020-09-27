#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V4_0_IPRESETREVERBEFFECT_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V4_0_IPRESETREVERBEFFECT_H

#include <android/hardware/audio/effect/4.0/IEffect.h>
#include <android/hardware/audio/effect/4.0/types.h>

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
namespace V4_0 {

struct IPresetReverbEffect : public ::android::hardware::audio::effect::V4_0::IEffect {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    // Forward declaration for forward reference support:
    enum class Preset : int32_t;

    enum class Preset : int32_t {
        NONE = 0,
        SMALLROOM = 1, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.NONE implicitly + 1)
        MEDIUMROOM = 2, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.SMALLROOM implicitly + 1)
        LARGEROOM = 3, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.MEDIUMROOM implicitly + 1)
        MEDIUMHALL = 4, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.LARGEROOM implicitly + 1)
        LARGEHALL = 5, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.MEDIUMHALL implicitly + 1)
        PLATE = 6, // (::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset.LARGEHALL implicitly + 1)
        LAST = 6, // PLATE
    };

    virtual bool isRemote() const override { return false; }


    // @entry
    /**
     * Initialize effect engine--all configurations return to default.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> init() = 0;

    /**
     * Apply new audio parameters configurations for input and output buffers.
     * The provider callbacks may be empty, but in this case the buffer
     * must be provided in the EffectConfig structure.
     * 
     * @param config configuration descriptor.
     * @param inputBufferProvider optional buffer provider reference.
     * @param outputBufferProvider optional buffer provider reference.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setConfig(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider) = 0;

    /**
     * Reset the effect engine. Keep configuration but resets state and buffer
     * content.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> reset() = 0;

    // @callflow(next="prepareForProcessing")
    /**
     * Enable processing.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> enable() = 0;

    // @callflow(next="close")
    /**
     * Disable processing.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> disable() = 0;

    /**
     * Set the rendering device the audio output path is connected to.  The
     * effect implementation must set EFFECT_FLAG_DEVICE_IND flag in its
     * descriptor to receive this command when the device changes.
     * 
     * Note: this method is only supported for effects inserted into
     *       the output chain.
     * 
     * @param device output device specification.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device) = 0;

    using setAndGetVolume_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::hidl_vec<uint32_t>& result)>;
    /**
     * Set and get volume. Used by audio framework to delegate volume control to
     * effect engine. The effect implementation must set EFFECT_FLAG_VOLUME_CTRL
     * flag in its descriptor to receive this command. The effect engine must
     * return the volume that should be applied before the effect is
     * processed. The overall volume (the volume actually applied by the effect
     * engine multiplied by the returned value) should match the value indicated
     * in the command.
     * 
     * @param volumes vector containing volume for each channel defined in
     *                EffectConfig for output buffer expressed in 8.24 fixed
     *                point format.
     * @return result updated volume values.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<void> setAndGetVolume(const ::android::hardware::hidl_vec<uint32_t>& volumes, setAndGetVolume_cb _hidl_cb) = 0;

    /**
     * Notify the effect of the volume change. The effect implementation must
     * set EFFECT_FLAG_VOLUME_IND flag in its descriptor to receive this
     * command.
     * 
     * @param volumes vector containing volume for each channel defined in
     *                EffectConfig for output buffer expressed in 8.24 fixed
     *                point format.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> volumeChangeNotification(const ::android::hardware::hidl_vec<uint32_t>& volumes) = 0;

    /**
     * Set the audio mode. The effect implementation must set
     * EFFECT_FLAG_AUDIO_MODE_IND flag in its descriptor to receive this command
     * when the audio mode changes.
     * 
     * @param mode desired audio mode.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setAudioMode(::android::hardware::audio::common::V4_0::AudioMode mode) = 0;

    /**
     * Apply new audio parameters configurations for input and output buffers of
     * reverse stream.  An example of reverse stream is the echo reference
     * supplied to an Acoustic Echo Canceler.
     * 
     * @param config configuration descriptor.
     * @param inputBufferProvider optional buffer provider reference.
     * @param outputBufferProvider optional buffer provider reference.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setConfigReverse(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider) = 0;

    /**
     * Set the capture device the audio input path is connected to. The effect
     * implementation must set EFFECT_FLAG_DEVICE_IND flag in its descriptor to
     * receive this command when the device changes.
     * 
     * Note: this method is only supported for effects inserted into
     *       the input chain.
     * 
     * @param device input device specification.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setInputDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device) = 0;

    using getConfig_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::audio::effect::V4_0::EffectConfig& config)>;
    /**
     * Read audio parameters configurations for input and output buffers.
     * 
     * @return retval operation completion status.
     * @return config configuration descriptor.
     */
    virtual ::android::hardware::Return<void> getConfig(getConfig_cb _hidl_cb) = 0;

    using getConfigReverse_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::audio::effect::V4_0::EffectConfig& config)>;
    /**
     * Read audio parameters configurations for input and output buffers of
     * reverse stream.
     * 
     * @return retval operation completion status.
     * @return config configuration descriptor.
     */
    virtual ::android::hardware::Return<void> getConfigReverse(getConfigReverse_cb _hidl_cb) = 0;

    using getSupportedAuxChannelsConfigs_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::hidl_vec<::android::hardware::audio::effect::V4_0::EffectAuxChannelsConfig>& result)>;
    /**
     * Queries for supported combinations of main and auxiliary channels
     * (e.g. for a multi-microphone noise suppressor).
     * 
     * @param maxConfigs maximum number of the combinations to return.
     * @return retval absence of the feature support is indicated using
     *                NOT_SUPPORTED code. RESULT_TOO_BIG is returned if
     *                the number of supported combinations exceeds 'maxConfigs'.
     * @return result list of configuration descriptors.
     */
    virtual ::android::hardware::Return<void> getSupportedAuxChannelsConfigs(uint32_t maxConfigs, getSupportedAuxChannelsConfigs_cb _hidl_cb) = 0;

    using getAuxChannelsConfig_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::audio::effect::V4_0::EffectAuxChannelsConfig& result)>;
    /**
     * Retrieves the current configuration of main and auxiliary channels.
     * 
     * @return retval absence of the feature support is indicated using
     *                NOT_SUPPORTED code.
     * @return result configuration descriptor.
     */
    virtual ::android::hardware::Return<void> getAuxChannelsConfig(getAuxChannelsConfig_cb _hidl_cb) = 0;

    /**
     * Sets the current configuration of main and auxiliary channels.
     * 
     * @return retval operation completion status; absence of the feature
     *                support is indicated using NOT_SUPPORTED code.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setAuxChannelsConfig(const ::android::hardware::audio::effect::V4_0::EffectAuxChannelsConfig& config) = 0;

    /**
     * Set the audio source the capture path is configured for (Camcorder, voice
     * recognition...).
     * 
     * Note: this method is only supported for effects inserted into
     *       the input chain.
     * 
     * @param source source descriptor.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setAudioSource(::android::hardware::audio::common::V4_0::AudioSource source) = 0;

    /**
     * This command indicates if the playback thread the effect is attached to
     * is offloaded or not, and updates the I/O handle of the playback thread
     * the effect is attached to.
     * 
     * @param param effect offload descriptor.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> offload(const ::android::hardware::audio::effect::V4_0::EffectOffloadParameter& param) = 0;

    using getDescriptor_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::audio::effect::V4_0::EffectDescriptor& descriptor)>;
    /**
     * Returns the effect descriptor.
     * 
     * @return retval operation completion status.
     * @return descriptor effect descriptor.
     */
    virtual ::android::hardware::Return<void> getDescriptor(getDescriptor_cb _hidl_cb) = 0;

    using prepareForProcessing_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::MQDescriptorSync<::android::hardware::audio::effect::V4_0::Result>& statusMQ)>;
    // @callflow(next="setProcessBuffers")
    /**
     * Set up required transports for passing audio buffers to the effect.
     * 
     * The transport consists of shared memory and a message queue for reporting
     * effect processing operation status. The shared memory is set up
     * separately using 'setProcessBuffers' method.
     * 
     * Processing is requested by setting 'REQUEST_PROCESS' or
     * 'REQUEST_PROCESS_REVERSE' EventFlags associated with the status message
     * queue. The result of processing may be one of the following:
     *   OK if there were no errors during processing;
     *   INVALID_ARGUMENTS if audio buffers are invalid;
     *   INVALID_STATE if the engine has finished the disable phase;
     *   NOT_INITIALIZED if the audio buffers were not set;
     *   NOT_SUPPORTED if the requested processing type is not supported by
     *                 the effect.
     * 
     * @return retval OK if both message queues were created successfully.
     *                INVALID_STATE if the method was already called.
     *                INVALID_ARGUMENTS if there was a problem setting up
     *                                  the queue.
     * @return statusMQ a message queue used for passing status from the effect.
     */
    virtual ::android::hardware::Return<void> prepareForProcessing(prepareForProcessing_cb _hidl_cb) = 0;

    /**
     * Set up input and output buffers for processing audio data. The effect
     * may modify both the input and the output buffer during the operation.
     * Buffers may be set multiple times during effect lifetime.
     * 
     * The input and the output buffer may be reused between different effects,
     * and the input buffer may be used as an output buffer. Buffers are
     * distinguished using 'AudioBuffer.id' field.
     * 
     * @param inBuffer input audio buffer.
     * @param outBuffer output audio buffer.
     * @return retval OK if both buffers were mapped successfully.
     *                INVALID_ARGUMENTS if there was a problem with mapping
     *                                  any of the buffers.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setProcessBuffers(const ::android::hardware::audio::effect::V4_0::AudioBuffer& inBuffer, const ::android::hardware::audio::effect::V4_0::AudioBuffer& outBuffer) = 0;

    using command_cb = std::function<void(int32_t status, const ::android::hardware::hidl_vec<uint8_t>& result)>;
    /**
     * Execute a vendor specific command on the effect. The command code
     * and data, as well as result data are not interpreted by Android
     * Framework and are passed as-is between the application and the effect.
     * 
     * The effect must use standard POSIX.1-2001 error codes for the operation
     * completion status.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it. This method only works for effects
     * implemented in software.
     * 
     * @param commandId the ID of the command.
     * @param data command data.
     * @param resultMaxSize maximum size in bytes of the result; can be 0.
     * @return status command completion status.
     * @return result result data.
     */
    virtual ::android::hardware::Return<void> command(uint32_t commandId, const ::android::hardware::hidl_vec<uint8_t>& data, uint32_t resultMaxSize, command_cb _hidl_cb) = 0;

    /**
     * Set a vendor-specific parameter and apply it immediately. The parameter
     * code and data are not interpreted by Android Framework and are passed
     * as-is between the application and the effect.
     * 
     * The effect must use INVALID_ARGUMENTS return code if the parameter ID is
     * unknown or if provided parameter data is invalid. If the effect does not
     * support setting vendor-specific parameters, it must return NOT_SUPPORTED.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it. This method only works for effects
     * implemented in software.
     * 
     * @param parameter identifying data of the parameter.
     * @param value the value of the parameter.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, const ::android::hardware::hidl_vec<uint8_t>& value) = 0;

    using getParameter_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::hidl_vec<uint8_t>& value)>;
    /**
     * Get a vendor-specific parameter value. The parameter code and returned
     * data are not interpreted by Android Framework and are passed as-is
     * between the application and the effect.
     * 
     * The effect must use INVALID_ARGUMENTS return code if the parameter ID is
     * unknown. If the effect does not support setting vendor-specific
     * parameters, it must return NOT_SUPPORTED.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it.  This method only works for effects
     * implemented in software.
     * 
     * @param parameter identifying data of the parameter.
     * @param valueMaxSize maximum size in bytes of the value.
     * @return retval operation completion status.
     * @return result the value of the parameter.
     */
    virtual ::android::hardware::Return<void> getParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, uint32_t valueMaxSize, getParameter_cb _hidl_cb) = 0;

    using getSupportedConfigsForFeature_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, uint32_t configsCount, const ::android::hardware::hidl_vec<uint8_t>& configsData)>;
    /**
     * Get supported configs for a vendor-specific feature. The configs returned
     * are not interpreted by Android Framework and are passed as-is between the
     * application and the effect.
     * 
     * The effect must use INVALID_ARGUMENTS return code if the feature ID is
     * unknown. If the effect does not support getting vendor-specific feature
     * configs, it must return NOT_SUPPORTED. If the feature is supported but
     * the total number of supported configurations exceeds the maximum number
     * indicated by the caller, the method must return RESULT_TOO_BIG.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it.  This method only works for effects
     * implemented in software.
     * 
     * @param featureId feature identifier.
     * @param maxConfigs maximum number of configs to return.
     * @param configSize size of each config in bytes.
     * @return retval operation completion status.
     * @return configsCount number of configs returned.
     * @return configsData data for all the configs returned.
     */
    virtual ::android::hardware::Return<void> getSupportedConfigsForFeature(uint32_t featureId, uint32_t maxConfigs, uint32_t configSize, getSupportedConfigsForFeature_cb _hidl_cb) = 0;

    using getCurrentConfigForFeature_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, const ::android::hardware::hidl_vec<uint8_t>& configData)>;
    /**
     * Get the current config for a vendor-specific feature. The config returned
     * is not interpreted by Android Framework and is passed as-is between the
     * application and the effect.
     * 
     * The effect must use INVALID_ARGUMENTS return code if the feature ID is
     * unknown. If the effect does not support getting vendor-specific
     * feature configs, it must return NOT_SUPPORTED.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it.  This method only works for effects
     * implemented in software.
     * 
     * @param featureId feature identifier.
     * @param configSize size of the config in bytes.
     * @return retval operation completion status.
     * @return configData config data.
     */
    virtual ::android::hardware::Return<void> getCurrentConfigForFeature(uint32_t featureId, uint32_t configSize, getCurrentConfigForFeature_cb _hidl_cb) = 0;

    /**
     * Set the current config for a vendor-specific feature. The config data
     * is not interpreted by Android Framework and is passed as-is between the
     * application and the effect.
     * 
     * The effect must use INVALID_ARGUMENTS return code if the feature ID is
     * unknown. If the effect does not support getting vendor-specific
     * feature configs, it must return NOT_SUPPORTED.
     * 
     * Use this method only if the effect is provided by a third party, and
     * there is no interface defined for it.  This method only works for effects
     * implemented in software.
     * 
     * @param featureId feature identifier.
     * @param configData config data.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setCurrentConfigForFeature(uint32_t featureId, const ::android::hardware::hidl_vec<uint8_t>& configData) = 0;

    // @exit
    /**
     * Called by the framework to deinitialize the effect and free up
     * all the currently allocated resources. It is recommended to close
     * the effect on the client side as soon as it is becomes unused.
     * 
     * @return retval OK in case the success.
     *                INVALID_STATE if the effect was already closed.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> close() = 0;

    /**
     * Sets the current preset.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> setPreset(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset preset) = 0;

    using getPreset_cb = std::function<void(::android::hardware::audio::effect::V4_0::Result retval, ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset preset)>;
    /**
     * Gets the current preset.
     */
    virtual ::android::hardware::Return<void> getPreset(getPreset_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IPresetReverbEffect>> castFrom(const ::android::sp<::android::hardware::audio::effect::V4_0::IPresetReverbEffect>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IPresetReverbEffect>> castFrom(const ::android::sp<::android::hardware::audio::effect::V4_0::IEffect>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IPresetReverbEffect>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IPresetReverbEffect> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IPresetReverbEffect> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IPresetReverbEffect> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IPresetReverbEffect> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IPresetReverbEffect> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IPresetReverbEffect> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IPresetReverbEffect> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IPresetReverbEffect> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

constexpr int32_t operator|(const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset lhs, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset lhs, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::NONE) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::NONE)) {
        os += (first ? "" : " | ");
        os += "NONE";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::NONE;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::SMALLROOM) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::SMALLROOM)) {
        os += (first ? "" : " | ");
        os += "SMALLROOM";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::SMALLROOM;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMROOM) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMROOM)) {
        os += (first ? "" : " | ");
        os += "MEDIUMROOM";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMROOM;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEROOM) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEROOM)) {
        os += (first ? "" : " | ");
        os += "LARGEROOM";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEROOM;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMHALL) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMHALL)) {
        os += (first ? "" : " | ");
        os += "MEDIUMHALL";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMHALL;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEHALL) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEHALL)) {
        os += (first ? "" : " | ");
        os += "LARGEHALL";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEHALL;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::PLATE) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::PLATE)) {
        os += (first ? "" : " | ");
        os += "PLATE";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::PLATE;
    }
    if ((o & ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LAST) == static_cast<int32_t>(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LAST)) {
        os += (first ? "" : " | ");
        os += "LAST";
        first = false;
        flipped |= ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LAST;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::NONE) {
        return "NONE";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::SMALLROOM) {
        return "SMALLROOM";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMROOM) {
        return "MEDIUMROOM";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEROOM) {
        return "LARGEROOM";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMHALL) {
        return "MEDIUMHALL";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEHALL) {
        return "LARGEHALL";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::PLATE) {
        return "PLATE";
    }
    if (o == ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LAST) {
        return "LAST";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

static inline std::string toString(const ::android::sp<::android::hardware::audio::effect::V4_0::IPresetReverbEffect>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V4_0
}  // namespace effect
}  // namespace audio
}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset>
{
    const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset* begin() { return static_begin(); }
    const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset* end() { return begin() + 8; }
    private:
    static const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset* static_begin() {
        static const ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset kVals[8] {
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::NONE,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::SMALLROOM,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMROOM,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEROOM,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::MEDIUMHALL,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LARGEHALL,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::PLATE,
            ::android::hardware::audio::effect::V4_0::IPresetReverbEffect::Preset::LAST,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V4_0_IPRESETREVERBEFFECT_H