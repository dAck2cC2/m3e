#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAMOUT_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAMOUT_H

#include <android/hardware/audio/common/2.0/types.h>
#include <android/hardware/audio/2.0/IStream.h>
#include <android/hardware/audio/2.0/IStreamOutCallback.h>
#include <android/hardware/audio/2.0/types.h>

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

struct IStreamOut : public ::android::hardware::audio::V2_0::IStream {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    // Forward declaration for forward reference support:
    enum class WriteCommand : int32_t;
    struct WriteStatus;

    typedef ::android::hardware::audio::V2_0::Result Result;

    /**
     * Commands that can be executed on the driver writer thread.
     */
    enum class WriteCommand : int32_t {
        WRITE = 0,
        GET_PRESENTATION_POSITION = 1, // (::android::hardware::audio::V2_0::IStreamOut::WriteCommand.WRITE implicitly + 1)
        GET_LATENCY = 2, // (::android::hardware::audio::V2_0::IStreamOut::WriteCommand.GET_PRESENTATION_POSITION implicitly + 1)
    };

    /**
     * Data structure passed back to the client via status message queue
     * of 'write' operation.
     * 
     * Possible values of 'retval' field:
     *  - OK, write operation was successful;
     *  - INVALID_ARGUMENTS, stream was not configured properly;
     *  - INVALID_STATE, stream is in a state that doesn't allow writes;
     *  - INVALID_OPERATION, retrieving presentation position isn't supported.
     */
    struct WriteStatus final {
        // Forward declaration for forward reference support:
        union Reply;

        union Reply final {
            // Forward declaration for forward reference support:
            struct PresentationPosition;

            struct PresentationPosition final {
                uint64_t frames __attribute__ ((aligned(8)));
                ::android::hardware::audio::V2_0::TimeSpec timeStamp __attribute__ ((aligned(8)));
            };

            static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition, frames) == 0, "wrong offset");
            static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition, timeStamp) == 8, "wrong offset");
            static_assert(sizeof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition) == 24, "wrong size");
            static_assert(__alignof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition) == 8, "wrong alignment");

            uint64_t written __attribute__ ((aligned(8)));
            ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition presentationPosition __attribute__ ((aligned(8)));
            uint32_t latencyMs __attribute__ ((aligned(4)));
        };

        static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply, written) == 0, "wrong offset");
        static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply, presentationPosition) == 0, "wrong offset");
        static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply, latencyMs) == 0, "wrong offset");
        static_assert(sizeof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply) == 24, "wrong size");
        static_assert(__alignof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply) == 8, "wrong alignment");

        ::android::hardware::audio::V2_0::Result retval __attribute__ ((aligned(4)));
        ::android::hardware::audio::V2_0::IStreamOut::WriteCommand replyTo __attribute__ ((aligned(4)));
        ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply reply __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus, retval) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus, replyTo) == 4, "wrong offset");
    static_assert(offsetof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus, reply) == 8, "wrong offset");
    static_assert(sizeof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus) == 32, "wrong size");
    static_assert(__alignof(::android::hardware::audio::V2_0::IStreamOut::WriteStatus) == 8, "wrong alignment");

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

    /**
     * Return the audio hardware driver estimated latency in milliseconds.
     * 
     * @return latencyMs latency in milliseconds.
     */
    virtual ::android::hardware::Return<uint32_t> getLatency() = 0;

    /**
     * This method is used in situations where audio mixing is done in the
     * hardware. This method serves as a direct interface with hardware,
     * allowing to directly set the volume as apposed to via the framework.
     * This method might produce multiple PCM outputs or hardware accelerated
     * codecs, such as MP3 or AAC.
     * 
     * @param left left channel attenuation, 1.0f is unity, 0.0f is zero.
     * @param right right channel attenuation, 1.0f is unity, 0.0f is zero.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setVolume(float left, float right) = 0;

    using prepareForWriting_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamOut::WriteCommand>& commandMQ, const ::android::hardware::MQDescriptorSync<uint8_t>& dataMQ, const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamOut::WriteStatus>& statusMQ, const ::android::hardware::audio::common::V2_0::ThreadInfo& threadInfo)>;
    /**
     * Set up required transports for passing audio buffers to the driver.
     * 
     * The transport consists of three message queues:
     *  -- command queue is used to instruct the writer thread what operation
     *     to perform;
     *  -- data queue is used for passing audio data from the client
     *     to the driver;
     *  -- status queue is used for reporting operation status
     *     (e.g. amount of bytes actually written or error code).
     * 
     * The driver operates on a dedicated thread. The client must ensure that
     * the thread is given an appropriate priority and assigned to correct
     * scheduler and cgroup. For this purpose, the method returns identifiers
     * of the driver thread.
     * 
     * @param frameSize the size of a single frame, in bytes.
     * @param framesCount the number of frames in a buffer.
     * @return retval OK if both message queues were created successfully.
     *                INVALID_STATE if the method was already called.
     *                INVALID_ARGUMENTS if there was a problem setting up
     *                                  the queues.
     * @return commandMQ a message queue used for passing commands.
     * @return dataMQ a message queue used for passing audio data in the format
     *                specified at the stream opening.
     * @return statusMQ a message queue used for passing status from the driver
     *                  using WriteStatus structures.
     * @return threadInfo identifiers of the driver's dedicated thread.
     */
    virtual ::android::hardware::Return<void> prepareForWriting(uint32_t frameSize, uint32_t framesCount, prepareForWriting_cb _hidl_cb) = 0;

    using getRenderPosition_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, uint32_t dspFrames)>;
    /**
     * Return the number of audio frames written by the audio DSP to DAC since
     * the output has exited standby.
     * 
     * @return retval operation completion status.
     * @return dspFrames number of audio frames written.
     */
    virtual ::android::hardware::Return<void> getRenderPosition(getRenderPosition_cb _hidl_cb) = 0;

    using getNextWriteTimestamp_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, int64_t timestampUs)>;
    /**
     * Get the local time at which the next write to the audio driver will be
     * presented. The units are microseconds, where the epoch is decided by the
     * local audio HAL.
     * 
     * @return retval operation completion status.
     * @return timestampUs time of the next write.
     */
    virtual ::android::hardware::Return<void> getNextWriteTimestamp(getNextWriteTimestamp_cb _hidl_cb) = 0;

    /**
     * Set the callback interface for notifying completion of non-blocking
     * write and drain.
     * 
     * Calling this function implies that all future 'write' and 'drain'
     * must be non-blocking and use the callback to signal completion.
     * 
     * 'clearCallback' method needs to be called in order to release the local
     * callback proxy on the server side and thus dereference the callback
     * implementation on the client side.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setCallback(const ::android::sp<::android::hardware::audio::V2_0::IStreamOutCallback>& callback) = 0;

    /**
     * Clears the callback previously set via 'setCallback' method.
     * 
     * Warning: failure to call this method results in callback implementation
     * on the client side being held until the HAL server termination.
     * 
     * @return retval operation completion status: OK or NOT_SUPPORTED.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> clearCallback() = 0;

    using supportsPauseAndResume_cb = std::function<void(bool supportsPause, bool supportsResume)>;
    /**
     * Returns whether HAL supports pausing and resuming of streams.
     * 
     * @return supportsPause true if pausing is supported.
     * @return supportsResume true if resume is supported.
     */
    virtual ::android::hardware::Return<void> supportsPauseAndResume(supportsPauseAndResume_cb _hidl_cb) = 0;

    /**
     * Notifies to the audio driver to stop playback however the queued buffers
     * are retained by the hardware. Useful for implementing pause/resume. Empty
     * implementation if not supported however must be implemented for hardware
     * with non-trivial latency. In the pause state, some audio hardware may
     * still be using power. Client code may consider calling 'suspend' after a
     * timeout to prevent that excess power usage.
     * 
     * Implementation of this function is mandatory for offloaded playback.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> pause() = 0;

    /**
     * Notifies to the audio driver to resume playback following a pause.
     * Returns error INVALID_STATE if called without matching pause.
     * 
     * Implementation of this function is mandatory for offloaded playback.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> resume() = 0;

    /**
     * Returns whether HAL supports draining of streams.
     * 
     * @return supports true if draining is supported.
     */
    virtual ::android::hardware::Return<bool> supportsDrain() = 0;

    /**
     * Requests notification when data buffered by the driver/hardware has been
     * played. If 'setCallback' has previously been called to enable
     * non-blocking mode, then 'drain' must not block, instead it must return
     * quickly and completion of the drain is notified through the callback. If
     * 'setCallback' has not been called, then 'drain' must block until
     * completion.
     * 
     * If 'type' is 'ALL', the drain completes when all previously written data
     * has been played.
     * 
     * If 'type' is 'EARLY_NOTIFY', the drain completes shortly before all data
     * for the current track has played to allow time for the framework to
     * perform a gapless track switch.
     * 
     * Drain must return immediately on 'stop' and 'flush' calls.
     * 
     * Implementation of this function is mandatory for offloaded playback.
     * 
     * @param type type of drain.
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> drain(::android::hardware::audio::V2_0::AudioDrain type) = 0;

    /**
     * Notifies to the audio driver to flush the queued data. Stream must
     * already be paused before calling 'flush'.
     * 
     * Implementation of this function is mandatory for offloaded playback.
     * 
     * @return retval operation completion status.
     */
    virtual ::android::hardware::Return<::android::hardware::audio::V2_0::Result> flush() = 0;

    using getPresentationPosition_cb = std::function<void(::android::hardware::audio::V2_0::Result retval, uint64_t frames, const ::android::hardware::audio::V2_0::TimeSpec& timeStamp)>;
    /**
     * Return a recent count of the number of audio frames presented to an
     * external observer. This excludes frames which have been written but are
     * still in the pipeline. The count is not reset to zero when output enters
     * standby. Also returns the value of CLOCK_MONOTONIC as of this
     * presentation count. The returned count is expected to be 'recent', but
     * does not need to be the most recent possible value. However, the
     * associated time must correspond to whatever count is returned.
     * 
     * Example: assume that N+M frames have been presented, where M is a 'small'
     * number. Then it is permissible to return N instead of N+M, and the
     * timestamp must correspond to N rather than N+M. The terms 'recent' and
     * 'small' are not defined. They reflect the quality of the implementation.
     * 
     * @return retval operation completion status.
     * @return frames count of presented audio frames.
     * @return timeStamp associated clock time.
     */
    virtual ::android::hardware::Return<void> getPresentationPosition(getPresentationPosition_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamOut>> castFrom(const ::android::sp<::android::hardware::audio::V2_0::IStreamOut>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamOut>> castFrom(const ::android::sp<::android::hardware::audio::V2_0::IStream>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamOut>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IStreamOut> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IStreamOut> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IStreamOut> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IStreamOut> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IStreamOut> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IStreamOut> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IStreamOut> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IStreamOut> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

constexpr int32_t operator|(const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand lhs, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand lhs, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::audio::V2_0::IStreamOut::WriteCommand>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::audio::V2_0::IStreamOut::WriteCommand> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::WRITE) == static_cast<int32_t>(::android::hardware::audio::V2_0::IStreamOut::WriteCommand::WRITE)) {
        os += (first ? "" : " | ");
        os += "WRITE";
        first = false;
        flipped |= ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::WRITE;
    }
    if ((o & ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_PRESENTATION_POSITION) == static_cast<int32_t>(::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_PRESENTATION_POSITION)) {
        os += (first ? "" : " | ");
        os += "GET_PRESENTATION_POSITION";
        first = false;
        flipped |= ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_PRESENTATION_POSITION;
    }
    if ((o & ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_LATENCY) == static_cast<int32_t>(::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_LATENCY)) {
        os += (first ? "" : " | ");
        os += "GET_LATENCY";
        first = false;
        flipped |= ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_LATENCY;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::audio::V2_0::IStreamOut::WriteCommand o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::WRITE) {
        return "WRITE";
    }
    if (o == ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_PRESENTATION_POSITION) {
        return "GET_PRESENTATION_POSITION";
    }
    if (o == ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_LATENCY) {
        return "GET_LATENCY";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

static inline std::string toString(const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".frames = ";
    os += ::android::hardware::toString(o.frames);
    os += ", .timeStamp = ";
    os += ::android::hardware::audio::V2_0::toString(o.timeStamp);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition& lhs, const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition& rhs) {
    if (lhs.frames != rhs.frames) {
        return false;
    }
    if (lhs.timeStamp != rhs.timeStamp) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition& lhs,const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply::PresentationPosition& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus::Reply& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".written = ";
    os += ::android::hardware::toString(o.written);
    os += ", .presentationPosition = ";
    os += ::android::hardware::audio::V2_0::toString(o.presentationPosition);
    os += ", .latencyMs = ";
    os += ::android::hardware::toString(o.latencyMs);
    os += "}"; return os;
}

// operator== and operator!= are not generated for Reply

static inline std::string toString(const ::android::hardware::audio::V2_0::IStreamOut::WriteStatus& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".retval = ";
    os += ::android::hardware::audio::V2_0::toString(o.retval);
    os += ", .replyTo = ";
    os += ::android::hardware::audio::V2_0::toString(o.replyTo);
    os += ", .reply = ";
    os += ::android::hardware::audio::V2_0::toString(o.reply);
    os += "}"; return os;
}

// operator== and operator!= are not generated for WriteStatus

static inline std::string toString(const ::android::sp<::android::hardware::audio::V2_0::IStreamOut>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::audio::V2_0::IStreamOut::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_0
}  // namespace audio
}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::audio::V2_0::IStreamOut::WriteCommand>
{
    const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand* begin() { return static_begin(); }
    const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand* end() { return begin() + 3; }
    private:
    static const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand* static_begin() {
        static const ::android::hardware::audio::V2_0::IStreamOut::WriteCommand kVals[3] {
            ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::WRITE,
            ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_PRESENTATION_POSITION,
            ::android::hardware::audio::V2_0::IStreamOut::WriteCommand::GET_LATENCY,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_ISTREAMOUT_H
