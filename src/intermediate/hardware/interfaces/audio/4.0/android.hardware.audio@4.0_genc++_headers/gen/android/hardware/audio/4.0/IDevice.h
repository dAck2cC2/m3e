#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICE_H

#include <android/hardware/audio/common/4.0/types.h>
#include <android/hardware/audio/4.0/IStreamIn.h>
#include <android/hardware/audio/4.0/IStreamOut.h>
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

struct IDevice : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    /**
     * Returns whether the audio hardware interface has been initialized.
     * 
     * @return retval OK on success, NOT_INITIALIZED on failure.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> initCheck() = 0;

    /**
     * Sets the audio volume for all audio activities other than voice call. If
     * NOT_SUPPORTED is returned, the software mixer will emulate this
     * capability.
     * 
     * @param volume 1.0f means unity, 0.0f is zero.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMasterVolume(float volume) = 0;

    using getMasterVolume_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, float volume)>;
    /**
     * Get the current master volume value for the HAL, if the HAL supports
     * master volume control. For example, AudioFlinger will query this value
     * from the primary audio HAL when the service starts and use the value for
     * setting the initial master volume across all HALs. HALs which do not
     * support this method must return NOT_SUPPORTED in 'retval'.
     * 
     * @return retval operation completion status.
     * @return volume 1.0f means unity, 0.0f is zero.
     */
    virtual ::android::hardware::Return<void> getMasterVolume(getMasterVolume_cb _hidl_cb) = 0;

    /**
     * Sets microphone muting state.
     * 
     * @param mute whether microphone is muted.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMicMute(bool mute) = 0;

    using getMicMute_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, bool mute)>;
    /**
     * Gets whether microphone is muted.
     * 
     * @return retval operation completion status.
     * @return mute whether microphone is muted.
     */
    virtual ::android::hardware::Return<void> getMicMute(getMicMute_cb _hidl_cb) = 0;

    /**
     * Set the audio mute status for all audio activities. If the return value
     * is NOT_SUPPORTED, the software mixer will emulate this capability.
     * 
     * @param mute whether audio is muted.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setMasterMute(bool mute) = 0;

    using getMasterMute_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, bool mute)>;
    /**
     * Get the current master mute status for the HAL, if the HAL supports
     * master mute control. AudioFlinger will query this value from the primary
     * audio HAL when the service starts and use the value for setting the
     * initial master mute across all HALs. HAL must indicate that the feature
     * is not supported by returning NOT_SUPPORTED status.
     * 
     * @return retval operation completion status.
     * @return mute whether audio is muted.
     */
    virtual ::android::hardware::Return<void> getMasterMute(getMasterMute_cb _hidl_cb) = 0;

    using getInputBufferSize_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, uint64_t bufferSize)>;
    /**
     * Returns audio input buffer size according to parameters passed or
     * INVALID_ARGUMENTS if one of the parameters is not supported.
     * 
     * @param config audio configuration.
     * @return retval operation completion status.
     * @return bufferSize input buffer size in bytes.
     */
    virtual ::android::hardware::Return<void> getInputBufferSize(const ::android::hardware::audio::common::V4_0::AudioConfig& config, getInputBufferSize_cb _hidl_cb) = 0;

    using openOutputStream_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::sp<::android::hardware::audio::V4_0::IStreamOut>& outStream, const ::android::hardware::audio::common::V4_0::AudioConfig& suggestedConfig)>;
    /**
     * This method creates and opens the audio hardware output stream.
     * If the stream can not be opened with the proposed audio config,
     * HAL must provide suggested values for the audio config.
     * 
     * @param ioHandle handle assigned by AudioFlinger.
     * @param device device type and (if needed) address.
     * @param config stream configuration.
     * @param flags additional flags.
     * @param sourceMetadata Description of the audio that will be played.
     * May be used by implementations to configure hardware effects.
     * @return retval operation completion status.
     * @return outStream created output stream.
     * @return suggestedConfig in case of invalid parameters, suggested config.
     */
    virtual ::android::hardware::Return<void> openOutputStream(int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioOutputFlag> flags, const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata, openOutputStream_cb _hidl_cb) = 0;

    using openInputStream_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::sp<::android::hardware::audio::V4_0::IStreamIn>& inStream, const ::android::hardware::audio::common::V4_0::AudioConfig& suggestedConfig)>;
    /**
     * This method creates and opens the audio hardware input stream.
     * If the stream can not be opened with the proposed audio config,
     * HAL must provide suggested values for the audio config.
     * 
     * @param ioHandle handle assigned by AudioFlinger.
     * @param device device type and (if needed) address.
     * @param config stream configuration.
     * @param flags additional flags.
     * @param sinkMetadata Description of the audio that is suggested by the client.
     *                     May be used by implementations to configure hardware effects.
     * @return retval operation completion status.
     * @return inStream in case of success, created input stream.
     * @return suggestedConfig in case of invalid parameters, suggested config.
     */
    virtual ::android::hardware::Return<void> openInputStream(int32_t ioHandle, const ::android::hardware::audio::V4_0::DeviceAddress& device, const ::android::hardware::audio::common::V4_0::AudioConfig& config, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioInputFlag> flags, const ::android::hardware::audio::V4_0::SinkMetadata& sinkMetadata, openInputStream_cb _hidl_cb) = 0;

    /**
     * Returns whether HAL supports audio patches.
     * 
     * @return supports true if audio patches are supported.
     */
    virtual ::android::hardware::Return<bool> supportsAudioPatches() = 0;

    using createAudioPatch_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, int32_t patch)>;
    /**
     * Creates an audio patch between several source and sink ports.  The handle
     * is allocated by the HAL and must be unique for this audio HAL module.
     * 
     * @param sources patch sources.
     * @param sinks patch sinks.
     * @return retval operation completion status.
     * @return patch created patch handle.
     */
    virtual ::android::hardware::Return<void> createAudioPatch(const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sources, const ::android::hardware::hidl_vec<::android::hardware::audio::common::V4_0::AudioPortConfig>& sinks, createAudioPatch_cb _hidl_cb) = 0;

    /**
     * Release an audio patch.
     * 
     * @param patch patch handle.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> releaseAudioPatch(int32_t patch) = 0;

    using getAudioPort_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::hardware::audio::common::V4_0::AudioPort& resultPort)>;
    /**
     * Returns the list of supported attributes for a given audio port.
     * 
     * As input, 'port' contains the information (type, role, address etc...)
     * needed by the HAL to identify the port.
     * 
     * As output, 'resultPort' contains possible attributes (sampling rates,
     * formats, channel masks, gain controllers...) for this port.
     * 
     * @param port port identifier.
     * @return retval operation completion status.
     * @return resultPort port descriptor with all parameters filled up.
     */
    virtual ::android::hardware::Return<void> getAudioPort(const ::android::hardware::audio::common::V4_0::AudioPort& port, getAudioPort_cb _hidl_cb) = 0;

    /**
     * Set audio port configuration.
     * 
     * @param config audio port configuration.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setAudioPortConfig(const ::android::hardware::audio::common::V4_0::AudioPortConfig& config) = 0;

    using getHwAvSync_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, uint32_t hwAvSync)>;
    /**
     * Gets the HW synchronization source of the device. Calling this method is
     * equivalent to getting AUDIO_PARAMETER_HW_AV_SYNC on the legacy HAL.
     * Optional method
     * 
     * @return retval operation completion status: OK or NOT_SUPPORTED.
     * @return hwAvSync HW synchronization source
     */
    virtual ::android::hardware::Return<void> getHwAvSync(getHwAvSync_cb _hidl_cb) = 0;

    /**
     * Sets whether the screen is on. Calling this method is equivalent to
     * setting AUDIO_PARAMETER_KEY_SCREEN_STATE on the legacy HAL.
     * Optional method
     * 
     * @param turnedOn whether the screen is turned on.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setScreenState(bool turnedOn) = 0;

    using getParameters_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters)>;
    /**
     * Generic method for retrieving vendor-specific parameter values.
     * The framework does not interpret the parameters, they are passed
     * in an opaque manner between a vendor application and HAL.
     * 
     * Multiple parameters can be retrieved at the same time.
     * The implementation should return as many requested parameters
     * as possible, even if one or more is not supported
     * 
     * @param context provides more information about the request
     * @param keys keys of the requested parameters
     * @return retval operation completion status.
     *         OK must be returned if keys is empty.
     *         NOT_SUPPORTED must be returned if at least one key is unknown.
     * @return parameters parameter key value pairs.
     *         Must contain the value of all requested keys if retval == OK
     */
    virtual ::android::hardware::Return<void> getParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb) = 0;

    /**
     * Generic method for setting vendor-specific parameter values.
     * The framework does not interpret the parameters, they are passed
     * in an opaque manner between a vendor application and HAL.
     * 
     * Multiple parameters can be set at the same time though this is
     * discouraged as it make failure analysis harder.
     * 
     * If possible, a failed setParameters should not impact the platform state.
     * 
     * @param context provides more information about the request
     * @param parameters parameter key value pairs.
     * @return retval operation completion status.
     *         All parameters must be successfully set for OK to be returned
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters) = 0;

    using getMicrophones_cb = std::function<void(::android::hardware::audio::V4_0::Result retval, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::MicrophoneInfo>& microphones)>;
    /**
     * Returns an array with available microphones in device.
     * 
     * @return retval INVALID_STATE if the call is not successful,
     *                OK otherwise.
     * 
     * @return microphones array with microphones info
     */
    virtual ::android::hardware::Return<void> getMicrophones(getMicrophones_cb _hidl_cb) = 0;

    /**
     * Notifies the device module about the connection state of an input/output
     * device attached to it. Calling this method is equivalent to setting
     * AUDIO_PARAMETER_DEVICE_[DIS]CONNECT on the legacy HAL.
     * 
     * @param address audio device specification.
     * @param connected whether the device is connected.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V4_0::Result> setConnectedState(const ::android::hardware::audio::V4_0::DeviceAddress& address, bool connected) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IDevice>> castFrom(const ::android::sp<::android::hardware::audio::V4_0::IDevice>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IDevice>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IDevice> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDevice> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IDevice> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IDevice> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IDevice> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDevice> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IDevice> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IDevice> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::audio::V4_0::IDevice>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::V4_0::IDevice::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V4_0
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V4_0_IDEVICE_H
