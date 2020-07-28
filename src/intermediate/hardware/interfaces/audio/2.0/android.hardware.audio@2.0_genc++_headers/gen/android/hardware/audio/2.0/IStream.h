#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAM_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAM_H

#include <android/hardware/audio/common/2.0/types.h>
#include <android/hardware/audio/2.0/types.h>
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
namespace V2_0 {

struct IStream : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    // Forward declaration for forward reference support:

    typedef ::android::hardware::audio::V2_0::Result Result;

    virtual bool isRemote() const override { return false; }


    /**
     * Return the frame size (number of bytes per sample).
     * 
     * @return frameSize frame size in bytes.
     */
    virtual ::android::hardware::Return<uint64_t> getFrameSize() = 0;

    /**
     * Return the frame count of the buffer. Calling this method is equivalent
     * to getting AUDIO_PARAMETER_STREAM_FRAME_COUNT on the legacy HAL.
     * 
     * @return count frame count.
     */
    virtual ::android::hardware::Return<uint64_t> getFrameCount() = 0;

    /**
     * Return the size of input/output buffer in bytes for this stream.
     * It must be a multiple of the frame size.
     * 
     * @return buffer buffer size in bytes.
     */
    virtual ::android::hardware::Return<uint64_t> getBufferSize() = 0;

    /**
     * Return the sampling rate in Hz.
     * 
     * @return sampleRateHz sample rate in Hz.
     */
    virtual ::android::hardware::Return<uint32_t> getSampleRate() = 0;

    using getSupportedSampleRates_cb = std::function<void(const ::android::hardware::hidl_vec<uint32_t>& sampleRates)>;
    /**
     * Return supported sampling rates of the stream. Calling this method is
     * equivalent to getting AUDIO_PARAMETER_STREAM_SUP_SAMPLING_RATES on the
     * legacy HAL.
     * 
     * @return sampleRateHz supported sample rates.
     */
    virtual ::android::hardware::Return<void> getSupportedSampleRates(getSupportedSampleRates_cb _hidl_cb) = 0;

    /**
     * Sets the sampling rate of the stream. Calling this method is equivalent
     * to setting AUDIO_PARAMETER_STREAM_SAMPLING_RATE on the legacy HAL.
     * 
     * @param sampleRateHz sample rate in Hz.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setSampleRate(uint32_t sampleRateHz) = 0;

    /**
     * Return the channel mask of the stream.
     * 
     * @return mask channel mask.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioChannelMask> getChannelMask() = 0;

    using getSupportedChannelMasks_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::audio::common::V2_0::AudioChannelMask>& masks)>;
    /**
     * Return supported channel masks of the stream. Calling this method is
     * equivalent to getting AUDIO_PARAMETER_STREAM_SUP_CHANNELS on the legacy
     * HAL.
     * 
     * @return masks supported audio masks.
     */
    virtual ::android::hardware::Return<void> getSupportedChannelMasks(getSupportedChannelMasks_cb _hidl_cb) = 0;

    /**
     * Sets the channel mask of the stream. Calling this method is equivalent to
     * setting AUDIO_PARAMETER_STREAM_CHANNELS on the legacy HAL.
     * 
     * @param format audio format.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setChannelMask(::android::hardware::audio::common::V2_0::AudioChannelMask mask) = 0;

    /**
     * Return the audio format of the stream.
     * 
     * @return format audio format.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioFormat> getFormat() = 0;

    using getSupportedFormats_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::audio::common::V2_0::AudioFormat>& formats)>;
    /**
     * Return supported audio formats of the stream. Calling this method is
     * equivalent to getting AUDIO_PARAMETER_STREAM_SUP_FORMATS on the legacy
     * HAL.
     * 
     * @return formats supported audio formats.
     */
    virtual ::android::hardware::Return<void> getSupportedFormats(getSupportedFormats_cb _hidl_cb) = 0;

    /**
     * Sets the audio format of the stream. Calling this method is equivalent to
     * setting AUDIO_PARAMETER_STREAM_FORMAT on the legacy HAL.
     * 
     * @param format audio format.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setFormat(::android::hardware::audio::common::V2_0::AudioFormat format) = 0;

    using getAudioProperties_cb = std::function<void(uint32_t sampleRateHz, ::android::hardware::audio::common::V2_0::AudioChannelMask mask, ::android::hardware::audio::common::V2_0::AudioFormat format)>;
    /**
     * Convenience method for retrieving several stream parameters in
     * one transaction.
     * 
     * @return sampleRateHz sample rate in Hz.
     * @return mask channel mask.
     * @return format audio format.
     */
    virtual ::android::hardware::Return<void> getAudioProperties(getAudioProperties_cb _hidl_cb) = 0;

    /**
     * Applies audio effect to the stream.
     * 
     * @param effectId effect ID (obtained from IEffectsFactory.createEffect) of
     *                 the effect to apply.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> addEffect(uint64_t effectId) = 0;

    /**
     * Stops application of the effect to the stream.
     * 
     * @param effectId effect ID (obtained from IEffectsFactory.createEffect) of
     *                 the effect to remove.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> removeEffect(uint64_t effectId) = 0;

    /**
     * Put the audio hardware input/output into standby mode.
     * Driver must exit from standby mode at the next I/O operation.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> standby() = 0;

    /**
     * Return the set of device(s) which this stream is connected to.
     * 
     * @return device set of device(s) which this stream is connected to.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioDevice> getDevice() = 0;

    /**
     * Connects the stream to the device.
     * 
     * This method must only be used for HALs that do not support
     * 'IDevice.createAudioPatch' method. Calling this method is
     * equivalent to setting AUDIO_PARAMETER_STREAM_ROUTING in the legacy HAL
     * interface.
     * 
     * @param address device to connect the stream to.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setDevice(const ::android::hardware::audio::V2_0::DeviceAddress& address) = 0;

    /**
     * Notifies the stream about device connection state. Calling this method is
     * equivalent to setting AUDIO_PARAMETER_DEVICE_[DIS]CONNECT on the legacy
     * HAL.
     * 
     * @param address audio device specification.
     * @param connected whether the device is connected.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setConnectedState(const ::android::hardware::audio::V2_0::DeviceAddress& address, bool connected) = 0;

    /**
     * Sets the HW synchronization source. Calling this method is equivalent to
     * setting AUDIO_PARAMETER_STREAM_HW_AV_SYNC on the legacy HAL.
     * 
     * @param hwAvSync HW synchronization source
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setHwAvSync(uint32_t hwAvSync) = 0;

    using getParameters_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, const ::android::hardware::hidl_vec<::android::hardware::audio::V2_0::ParameterValue>& parameters)>;
    /**
     * Generic method for retrieving vendor-specific parameter values.
     * The framework does not interpret the parameters, they are passed
     * in an opaque manner between a vendor application and HAL.
     * 
     * @param keys parameter keys.
     * @return retval operation completion status.
     * @return parameters parameter key value pairs.
     */
    virtual ::android::hardware::Return<void> getParameters(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb) = 0;

    /**
     * Generic method for setting vendor-specific parameter values.
     * The framework does not interpret the parameters, they are passed
     * in an opaque manner between a vendor application and HAL.
     * 
     * @param parameters parameter key value pairs.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V2_0::ParameterValue>& parameters) = 0;

    /**
     * Dumps information about the stream into the provided file descriptor.
     * This is used for the dumpsys facility.
     * 
     * @param fd dump file descriptor.
     */
    virtual ::android::hardware::Return<void> debugDump(const ::android::hardware::hidl_handle& fd) = 0;

    /**
     * Called by the framework to start a stream operating in mmap mode.
     * createMmapBuffer() must be called before calling start().
     * Function only implemented by streams operating in mmap mode.
     * 
     * @return retval OK in case the success.
     *                NOT_SUPPORTED on non mmap mode streams
     *                INVALID_STATE if called out of sequence
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> start() = 0;

    /**
     * Called by the framework to stop a stream operating in mmap mode.
     * Function only implemented by streams operating in mmap mode.
     * 
     * @return retval OK in case the succes.
     *                NOT_SUPPORTED on non mmap mode streams
     *                INVALID_STATE if called out of sequence
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> stop() = 0;

    using createMmapBuffer_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, const ::android::hardware::audio::V2_0::MmapBufferInfo& info)>;
    /**
     * Called by the framework to retrieve information on the mmap buffer used for audio
     * samples transfer.
     * Function only implemented by streams operating in mmap mode.
     * 
     * @param minSizeFrames minimum buffer size requested. The actual buffer
     *                     size returned in struct MmapBufferInfo can be larger.
     * @return retval OK in case the success.
     *                NOT_SUPPORTED on non mmap mode streams
     *                NOT_INITIALIZED in case of memory allocation error
     *                INVALID_ARGUMENTS if the requested buffer size is too large
     *                INVALID_STATE if called out of sequence
     * @return info    a MmapBufferInfo struct containing information on the MMMAP buffer created.
     */
    virtual ::android::hardware::Return<void> createMmapBuffer(int32_t minSizeFrames, createMmapBuffer_cb _hidl_cb) = 0;

    using getMmapPosition_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, const ::android::hardware::audio::V2_0::MmapPosition& position)>;
    /**
     * Called by the framework to read current read/write position in the mmap buffer
     * with associated time stamp.
     * Function only implemented by streams operating in mmap mode.
     * 
     * @return retval OK in case the success.
     *                NOT_SUPPORTED on non mmap mode streams
     *                INVALID_STATE if called out of sequence
     * @return position a MmapPosition struct containing current HW read/write position in frames
     *                  with associated time stamp.
     */
    virtual ::android::hardware::Return<void> getMmapPosition(getMmapPosition_cb _hidl_cb) = 0;

    /**
     * Called by the framework to deinitialize the stream and free up
     * all the currently allocated resources. It is recommended to close
     * the stream on the client side as soon as it is becomes unused.
     * 
     * @return retval OK in case the success.
     *                NOT_SUPPORTED if called on IStream instead of input or
     *                              output stream interface.
     *                INVALID_STATE if the stream was already closed.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> close() = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStream>> castFrom(const ::android::sp<::android::hardware::audio::V2_0::IStream>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStream>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IStream> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IStream> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IStream> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IStream> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IStream> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IStream> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IStream> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IStream> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::audio::V2_0::IStream>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::V2_0::IStream::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_0
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAM_H
