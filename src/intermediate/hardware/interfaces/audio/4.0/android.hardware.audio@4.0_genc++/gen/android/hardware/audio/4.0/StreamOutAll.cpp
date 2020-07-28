#define LOG_TAG "android.hardware.audio@4.0::StreamOut"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hardware/audio/4.0/BpHwStreamOut.h>
#include <android/hardware/audio/4.0/BnHwStreamOut.h>
#include <android/hardware/audio/4.0/BsStreamOut.h>
#include <android/hardware/audio/4.0/BpHwStream.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace audio {
namespace V4_0 {

const char* IStreamOut::descriptor("android.hardware.audio@4.0::IStreamOut");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IStreamOut::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwStreamOut(static_cast<IStreamOut *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IStreamOut::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsStreamOut(static_cast<IStreamOut *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IStreamOut::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IStreamOut::descriptor);
};

// Methods from ::android::hardware::audio::V4_0::IStream follow.
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamOut::getFrameSize()
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamOut::getFrameCount()
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamOut::getBufferSize()
// no default implementation for: ::android::hardware::Return<uint32_t> IStreamOut::getSampleRate()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getSupportedSampleRates(::android::hardware::audio::common::V4_0::AudioFormat format, getSupportedSampleRates_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setSampleRate(uint32_t sampleRateHz)
// no default implementation for: ::android::hardware::Return<::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask>> IStreamOut::getChannelMask()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getSupportedChannelMasks(::android::hardware::audio::common::V4_0::AudioFormat format, getSupportedChannelMasks_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setChannelMask(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::common::V4_0::AudioFormat> IStreamOut::getFormat()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getSupportedFormats(getSupportedFormats_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setFormat(::android::hardware::audio::common::V4_0::AudioFormat format)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getAudioProperties(getAudioProperties_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::addEffect(uint64_t effectId)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::removeEffect(uint64_t effectId)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::standby()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getDevices(getDevices_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setDevices(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::DeviceAddress>& devices)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setHwAvSync(uint32_t hwAvSync)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::start()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::stop()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::createMmapBuffer(int32_t minSizeFrames, createMmapBuffer_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getMmapPosition(getMmapPosition_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::close()

// Methods from ::android::hardware::audio::V4_0::IStreamOut follow.
// no default implementation for: ::android::hardware::Return<uint32_t> IStreamOut::getLatency()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setVolume(float left, float right)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::updateSourceMetadata(const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::prepareForWriting(uint32_t frameSize, uint32_t framesCount, prepareForWriting_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getRenderPosition(getRenderPosition_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getNextWriteTimestamp(getNextWriteTimestamp_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::setCallback(const ::android::sp<::android::hardware::audio::V4_0::IStreamOutCallback>& callback)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::clearCallback()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::supportsPauseAndResume(supportsPauseAndResume_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::pause()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::resume()
// no default implementation for: ::android::hardware::Return<bool> IStreamOut::supportsDrain()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::drain(::android::hardware::audio::V4_0::AudioDrain type)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::flush()
// no default implementation for: ::android::hardware::Return<void> IStreamOut::getPresentationPosition(getPresentationPosition_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V4_0::Result> IStreamOut::selectPresentation(int32_t presentationId, int32_t programId)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IStreamOut::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::audio::V4_0::IStreamOut::descriptor,
        ::android::hardware::audio::V4_0::IStream::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamOut::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamOut::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::audio::V4_0::IStreamOut::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamOut::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){136,138,201,6,70,19,39,250,11,217,56,84,213,16,155,232,194,146,163,58,253,180,103,22,72,38,151,10,139,213,183,137} /* 888ac906461327fa0bd93854d5109be8c292a33afdb467164826970a8bd5b789 */,
        (uint8_t[32]){62,58,203,112,196,230,199,213,120,245,17,244,164,78,231,100,171,145,38,248,135,163,191,101,213,35,196,46,64,1,43,246} /* 3e3acb70c4e6c7d578f511f4a44ee764ab9126f887a3bf65d523c42e40012bf6 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IStreamOut::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IStreamOut::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IStreamOut::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IStreamOut::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hidl::base::V1_0::DebugInfo info = {};
    info.pid = -1;
    info.ptr = 0;
    info.arch = 
    #if defined(__LP64__)
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
    #else
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
    #endif
    ;
    _hidl_cb(info);
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IStreamOut::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IStreamOut::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IStreamOut>> IStreamOut::castFrom(const ::android::sp<::android::hardware::audio::V4_0::IStreamOut>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IStreamOut>> IStreamOut::castFrom(const ::android::sp<::android::hardware::audio::V4_0::IStream>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IStreamOut, ::android::hardware::audio::V4_0::IStream, BpHwStreamOut>(
            parent, "android.hardware.audio@4.0::IStreamOut", emitError);
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V4_0::IStreamOut>> IStreamOut::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IStreamOut, ::android::hidl::base::V1_0::IBase, BpHwStreamOut>(
            parent, "android.hardware.audio@4.0::IStreamOut", emitError);
}

BpHwStreamOut::BpHwStreamOut(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IStreamOut>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.audio@4.0", "IStreamOut") {
}

// Methods from ::android::hardware::audio::V4_0::IStreamOut follow.
::android::hardware::Return<uint32_t> BpHwStreamOut::_hidl_getLatency(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getLatency::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getLatency", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    uint32_t _hidl_out_latencyMs;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(27 /* getLatency */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readUint32(&_hidl_out_latencyMs);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_latencyMs);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getLatency", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<uint32_t>(_hidl_out_latencyMs);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<uint32_t>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_setVolume(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, float left, float right) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::setVolume::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&left);
        _hidl_args.push_back((void *)&right);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "setVolume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeFloat(left);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeFloat(right);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(28 /* setVolume */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "setVolume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_updateSourceMetadata(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::updateSourceMetadata::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&sourceMetadata);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "updateSourceMetadata", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_sourceMetadata_parent;

    _hidl_err = _hidl_data.writeBuffer(&sourceMetadata, sizeof(sourceMetadata), &_hidl_sourceMetadata_parent);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = writeEmbeddedToParcel(
            sourceMetadata,
            &_hidl_data,
            _hidl_sourceMetadata_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(29 /* updateSourceMetadata */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "updateSourceMetadata", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_prepareForWriting(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint32_t frameSize, uint32_t framesCount, prepareForWriting_cb _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    if (_hidl_cb == nullptr) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                "Null synchronous callback passed.");
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::prepareForWriting::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&frameSize);
        _hidl_args.push_back((void *)&framesCount);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "prepareForWriting", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;
    const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V4_0::IStreamOut::WriteCommand>* _hidl_out_commandMQ;
    const ::android::hardware::MQDescriptorSync<uint8_t>* _hidl_out_dataMQ;
    const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V4_0::IStreamOut::WriteStatus>* _hidl_out_statusMQ;
    ::android::hardware::audio::common::V4_0::ThreadInfo* _hidl_out_threadInfo;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32(frameSize);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32(framesCount);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(30 /* prepareForWriting */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_commandMQ_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_commandMQ), &_hidl__hidl_out_commandMQ_parent,  reinterpret_cast<const void **>(&_hidl_out_commandMQ));

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::MQDescriptorSync<::android::hardware::audio::V4_0::IStreamOut::WriteCommand> &>(*_hidl_out_commandMQ),
            _hidl_reply,
            _hidl__hidl_out_commandMQ_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_dataMQ_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_dataMQ), &_hidl__hidl_out_dataMQ_parent,  reinterpret_cast<const void **>(&_hidl_out_dataMQ));

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::MQDescriptorSync<uint8_t> &>(*_hidl_out_dataMQ),
            _hidl_reply,
            _hidl__hidl_out_dataMQ_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_statusMQ_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_statusMQ), &_hidl__hidl_out_statusMQ_parent,  reinterpret_cast<const void **>(&_hidl_out_statusMQ));

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::MQDescriptorSync<::android::hardware::audio::V4_0::IStreamOut::WriteStatus> &>(*_hidl_out_statusMQ),
            _hidl_reply,
            _hidl__hidl_out_statusMQ_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_threadInfo_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_threadInfo), &_hidl__hidl_out_threadInfo_parent,  const_cast<const void**>(reinterpret_cast<void **>(&_hidl_out_threadInfo)));
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, *_hidl_out_commandMQ, *_hidl_out_dataMQ, *_hidl_out_statusMQ, *_hidl_out_threadInfo);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)_hidl_out_commandMQ);
        _hidl_args.push_back((void *)_hidl_out_dataMQ);
        _hidl_args.push_back((void *)_hidl_out_statusMQ);
        _hidl_args.push_back((void *)_hidl_out_threadInfo);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "prepareForWriting", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_getRenderPosition(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getRenderPosition_cb _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    if (_hidl_cb == nullptr) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                "Null synchronous callback passed.");
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getRenderPosition::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getRenderPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;
    uint32_t _hidl_out_dspFrames;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(31 /* getRenderPosition */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint32(&_hidl_out_dspFrames);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_dspFrames);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_dspFrames);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getRenderPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_getNextWriteTimestamp(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getNextWriteTimestamp_cb _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    if (_hidl_cb == nullptr) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                "Null synchronous callback passed.");
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getNextWriteTimestamp::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getNextWriteTimestamp", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;
    int64_t _hidl_out_timestampUs;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(32 /* getNextWriteTimestamp */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readInt64(&_hidl_out_timestampUs);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_timestampUs);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_timestampUs);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getNextWriteTimestamp", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_setCallback(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::sp<::android::hardware::audio::V4_0::IStreamOutCallback>& callback) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::setCallback::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&callback);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "setCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (callback == nullptr) {
        _hidl_err = _hidl_data.writeStrongBinder(nullptr);
    } else {
        ::android::sp<::android::hardware::IBinder> _hidl_binder = ::android::hardware::toBinder<
                ::android::hardware::audio::V4_0::IStreamOutCallback>(callback);
        if (_hidl_binder.get() != nullptr) {
            _hidl_err = _hidl_data.writeStrongBinder(_hidl_binder);
        } else {
            _hidl_err = ::android::UNKNOWN_ERROR;
        }
    }
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    ::android::hardware::ProcessState::self()->startThreadPool();
    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(33 /* setCallback */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "setCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_clearCallback(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::clearCallback::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "clearCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(34 /* clearCallback */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "clearCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_supportsPauseAndResume(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, supportsPauseAndResume_cb _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    if (_hidl_cb == nullptr) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                "Null synchronous callback passed.");
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::supportsPauseAndResume::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "supportsPauseAndResume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    bool _hidl_out_supportsPause;
    bool _hidl_out_supportsResume;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(35 /* supportsPauseAndResume */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_supportsPause);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_supportsResume);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_supportsPause, _hidl_out_supportsResume);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_supportsPause);
        _hidl_args.push_back((void *)&_hidl_out_supportsResume);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "supportsPauseAndResume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_pause(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::pause::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "pause", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(36 /* pause */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "pause", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_resume(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::resume::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "resume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(37 /* resume */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "resume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<bool> BpHwStreamOut::_hidl_supportsDrain(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::supportsDrain::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "supportsDrain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    bool _hidl_out_supports;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(38 /* supportsDrain */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_supports);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_supports);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "supportsDrain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_out_supports);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_drain(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::audio::V4_0::AudioDrain type) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::drain::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&type);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "drain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt32((int32_t)type);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(39 /* drain */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "drain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_flush(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::flush::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "flush", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(40 /* flush */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "flush", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamOut::_hidl_getPresentationPosition(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getPresentationPosition_cb _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    if (_hidl_cb == nullptr) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                "Null synchronous callback passed.");
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getPresentationPosition::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getPresentationPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;
    uint64_t _hidl_out_frames;
    ::android::hardware::audio::V4_0::TimeSpec* _hidl_out_timeStamp;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(41 /* getPresentationPosition */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint64(&_hidl_out_frames);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_timeStamp_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_timeStamp), &_hidl__hidl_out_timeStamp_parent,  const_cast<const void**>(reinterpret_cast<void **>(&_hidl_out_timeStamp)));
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_frames, *_hidl_out_timeStamp);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_frames);
        _hidl_args.push_back((void *)_hidl_out_timeStamp);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getPresentationPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::_hidl_selectPresentation(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t presentationId, int32_t programId) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::selectPresentation::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&presentationId);
        _hidl_args.push_back((void *)&programId);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "selectPresentation", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamOut::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt32(presentationId);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt32(programId);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(42 /* selectPresentation */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "selectPresentation", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V4_0::Result>(_hidl_status);
}


// Methods from ::android::hardware::audio::V4_0::IStream follow.
::android::hardware::Return<uint64_t> BpHwStreamOut::getFrameSize(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getFrameSize(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint64_t> BpHwStreamOut::getFrameCount(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getFrameCount(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint64_t> BpHwStreamOut::getBufferSize(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getBufferSize(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint32_t> BpHwStreamOut::getSampleRate(){
    ::android::hardware::Return<uint32_t>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getSampleRate(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getSupportedSampleRates(::android::hardware::audio::common::V4_0::AudioFormat format, getSupportedSampleRates_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getSupportedSampleRates(this, this, format, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setSampleRate(uint32_t sampleRateHz){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setSampleRate(this, this, sampleRateHz);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask>> BpHwStreamOut::getChannelMask(){
    ::android::hardware::Return<::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask>>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getChannelMask(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getSupportedChannelMasks(::android::hardware::audio::common::V4_0::AudioFormat format, getSupportedChannelMasks_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getSupportedChannelMasks(this, this, format, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setChannelMask(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setChannelMask(this, this, mask);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::common::V4_0::AudioFormat> BpHwStreamOut::getFormat(){
    ::android::hardware::Return<::android::hardware::audio::common::V4_0::AudioFormat>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getFormat(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getSupportedFormats(getSupportedFormats_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getSupportedFormats(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setFormat(::android::hardware::audio::common::V4_0::AudioFormat format){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setFormat(this, this, format);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getAudioProperties(getAudioProperties_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getAudioProperties(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::addEffect(uint64_t effectId){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_addEffect(this, this, effectId);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::removeEffect(uint64_t effectId){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_removeEffect(this, this, effectId);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::standby(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_standby(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getDevices(getDevices_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getDevices(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setDevices(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::DeviceAddress>& devices){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setDevices(this, this, devices);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setHwAvSync(uint32_t hwAvSync){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setHwAvSync(this, this, hwAvSync);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getParameters(this, this, context, keys, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& context, const ::android::hardware::hidl_vec<::android::hardware::audio::V4_0::ParameterValue>& parameters){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_setParameters(this, this, context, parameters);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::start(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_start(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::stop(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_stop(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::createMmapBuffer(int32_t minSizeFrames, createMmapBuffer_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_createMmapBuffer(this, this, minSizeFrames, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getMmapPosition(getMmapPosition_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_getMmapPosition(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::close(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStream::_hidl_close(this, this);

    return _hidl_out;
}


// Methods from ::android::hardware::audio::V4_0::IStreamOut follow.
::android::hardware::Return<uint32_t> BpHwStreamOut::getLatency(){
    ::android::hardware::Return<uint32_t>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_getLatency(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setVolume(float left, float right){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_setVolume(this, this, left, right);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::updateSourceMetadata(const ::android::hardware::audio::V4_0::SourceMetadata& sourceMetadata){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_updateSourceMetadata(this, this, sourceMetadata);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::prepareForWriting(uint32_t frameSize, uint32_t framesCount, prepareForWriting_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_prepareForWriting(this, this, frameSize, framesCount, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getRenderPosition(getRenderPosition_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_getRenderPosition(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getNextWriteTimestamp(getNextWriteTimestamp_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_getNextWriteTimestamp(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::setCallback(const ::android::sp<::android::hardware::audio::V4_0::IStreamOutCallback>& callback){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_setCallback(this, this, callback);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::clearCallback(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_clearCallback(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::supportsPauseAndResume(supportsPauseAndResume_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_supportsPauseAndResume(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::pause(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_pause(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::resume(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_resume(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwStreamOut::supportsDrain(){
    ::android::hardware::Return<bool>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_supportsDrain(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::drain(::android::hardware::audio::V4_0::AudioDrain type){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_drain(this, this, type);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::flush(){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_flush(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getPresentationPosition(getPresentationPosition_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_getPresentationPosition(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V4_0::Result> BpHwStreamOut::selectPresentation(int32_t presentationId, int32_t programId){
    ::android::hardware::Return<::android::hardware::audio::V4_0::Result>  _hidl_out = ::android::hardware::audio::V4_0::BpHwStreamOut::_hidl_selectPresentation(this, this, presentationId, programId);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwStreamOut::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwStreamOut::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwStreamOut::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamOut::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwStreamOut::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwStreamOut::BnHwStreamOut(const ::android::sp<IStreamOut> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.audio@4.0", "IStreamOut") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwStreamOut::~BnHwStreamOut() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::audio::V4_0::IStreamOut follow.
::android::status_t BnHwStreamOut::_hidl_getLatency(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getLatency::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getLatency", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    uint32_t _hidl_out_latencyMs = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->getLatency();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeUint32(_hidl_out_latencyMs);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_latencyMs);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getLatency", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_setVolume(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    float left;
    float right;

    _hidl_err = _hidl_data.readFloat(&left);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readFloat(&right);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::setVolume::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&left);
        _hidl_args.push_back((void *)&right);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "setVolume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->setVolume(left, right);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "setVolume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_updateSourceMetadata(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::audio::V4_0::SourceMetadata* sourceMetadata;

    size_t _hidl_sourceMetadata_parent;

    _hidl_err = _hidl_data.readBuffer(sizeof(*sourceMetadata), &_hidl_sourceMetadata_parent,  const_cast<const void**>(reinterpret_cast<void **>(&sourceMetadata)));
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = readEmbeddedFromParcel(
            const_cast<::android::hardware::audio::V4_0::SourceMetadata &>(*sourceMetadata),
            _hidl_data,
            _hidl_sourceMetadata_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::updateSourceMetadata::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)sourceMetadata);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "updateSourceMetadata", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->updateSourceMetadata(*sourceMetadata);

    (void) _hidl_cb;

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "updateSourceMetadata", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_prepareForWriting(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint32_t frameSize;
    uint32_t framesCount;

    _hidl_err = _hidl_data.readUint32(&frameSize);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readUint32(&framesCount);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::prepareForWriting::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&frameSize);
        _hidl_args.push_back((void *)&framesCount);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "prepareForWriting", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->prepareForWriting(frameSize, framesCount, [&](const auto &_hidl_out_retval, const auto &_hidl_out_commandMQ, const auto &_hidl_out_dataMQ, const auto &_hidl_out_statusMQ, const auto &_hidl_out_threadInfo) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("prepareForWriting: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_commandMQ_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_commandMQ, sizeof(_hidl_out_commandMQ), &_hidl__hidl_out_commandMQ_parent);
        /* _hidl_err ignored! */

        _hidl_err = ::android::hardware::writeEmbeddedToParcel(
                _hidl_out_commandMQ,
                _hidl_reply,
                _hidl__hidl_out_commandMQ_parent,
                0 /* parentOffset */);

        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_dataMQ_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_dataMQ, sizeof(_hidl_out_dataMQ), &_hidl__hidl_out_dataMQ_parent);
        /* _hidl_err ignored! */

        _hidl_err = ::android::hardware::writeEmbeddedToParcel(
                _hidl_out_dataMQ,
                _hidl_reply,
                _hidl__hidl_out_dataMQ_parent,
                0 /* parentOffset */);

        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_statusMQ_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_statusMQ, sizeof(_hidl_out_statusMQ), &_hidl__hidl_out_statusMQ_parent);
        /* _hidl_err ignored! */

        _hidl_err = ::android::hardware::writeEmbeddedToParcel(
                _hidl_out_statusMQ,
                _hidl_reply,
                _hidl__hidl_out_statusMQ_parent,
                0 /* parentOffset */);

        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_threadInfo_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_threadInfo, sizeof(_hidl_out_threadInfo), &_hidl__hidl_out_threadInfo_parent);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_commandMQ);
            _hidl_args.push_back((void *)&_hidl_out_dataMQ);
            _hidl_args.push_back((void *)&_hidl_out_statusMQ);
            _hidl_args.push_back((void *)&_hidl_out_threadInfo);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "prepareForWriting", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("prepareForWriting: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_getRenderPosition(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getRenderPosition::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getRenderPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->getRenderPosition([&](const auto &_hidl_out_retval, const auto &_hidl_out_dspFrames) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getRenderPosition: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint32(_hidl_out_dspFrames);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_dspFrames);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getRenderPosition", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getRenderPosition: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_getNextWriteTimestamp(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getNextWriteTimestamp::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getNextWriteTimestamp", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->getNextWriteTimestamp([&](const auto &_hidl_out_retval, const auto &_hidl_out_timestampUs) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getNextWriteTimestamp: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeInt64(_hidl_out_timestampUs);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_timestampUs);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getNextWriteTimestamp", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getNextWriteTimestamp: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_setCallback(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::sp<::android::hardware::audio::V4_0::IStreamOutCallback> callback;

    {
        ::android::sp<::android::hardware::IBinder> _hidl_binder;
        _hidl_err = _hidl_data.readNullableStrongBinder(&_hidl_binder);
        if (_hidl_err != ::android::OK) { return _hidl_err; }

        callback = ::android::hardware::fromBinder<::android::hardware::audio::V4_0::IStreamOutCallback,::android::hardware::audio::V4_0::BpHwStreamOutCallback,::android::hardware::audio::V4_0::BnHwStreamOutCallback>(_hidl_binder);
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::setCallback::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&callback);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "setCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->setCallback(callback);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "setCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_clearCallback(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::clearCallback::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "clearCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->clearCallback();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "clearCallback", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_supportsPauseAndResume(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::supportsPauseAndResume::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "supportsPauseAndResume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->supportsPauseAndResume([&](const auto &_hidl_out_supportsPause, const auto &_hidl_out_supportsResume) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("supportsPauseAndResume: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeBool(_hidl_out_supportsPause);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeBool(_hidl_out_supportsResume);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_supportsPause);
            _hidl_args.push_back((void *)&_hidl_out_supportsResume);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "supportsPauseAndResume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("supportsPauseAndResume: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_pause(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::pause::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "pause", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->pause();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "pause", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_resume(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::resume::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "resume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->resume();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "resume", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_supportsDrain(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::supportsDrain::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "supportsDrain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_out_supports = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->supportsDrain();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeBool(_hidl_out_supports);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_supports);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "supportsDrain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_drain(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::audio::V4_0::AudioDrain type;

    _hidl_err = _hidl_data.readInt32((int32_t *)&type);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::drain::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&type);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "drain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->drain(type);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "drain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_flush(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::flush::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "flush", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->flush();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "flush", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_getPresentationPosition(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::getPresentationPosition::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "getPresentationPosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamOut*>(_hidl_this->getImpl().get())->getPresentationPosition([&](const auto &_hidl_out_retval, const auto &_hidl_out_frames, const auto &_hidl_out_timeStamp) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getPresentationPosition: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint64(_hidl_out_frames);
        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_timeStamp_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_timeStamp, sizeof(_hidl_out_timeStamp), &_hidl__hidl_out_timeStamp_parent);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_frames);
            _hidl_args.push_back((void *)&_hidl_out_timeStamp);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "getPresentationPosition", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getPresentationPosition: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamOut::_hidl_selectPresentation(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamOut::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    int32_t presentationId;
    int32_t programId;

    _hidl_err = _hidl_data.readInt32(&presentationId);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readInt32(&programId);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamOut::selectPresentation::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&presentationId);
        _hidl_args.push_back((void *)&programId);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "4.0", "IStreamOut", "selectPresentation", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V4_0::Result _hidl_out_retval = static_cast<IStreamOut*>(_hidl_this->getImpl().get())->selectPresentation(presentationId, programId);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "4.0", "IStreamOut", "selectPresentation", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}


// Methods from ::android::hardware::audio::V4_0::IStream follow.

// Methods from ::android::hardware::audio::V4_0::IStreamOut follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwStreamOut::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwStreamOut::getDebugInfo(getDebugInfo_cb _hidl_cb) {
    ::android::hidl::base::V1_0::DebugInfo info = {};
    info.pid = ::android::hardware::details::getPidIfSharable();
    info.ptr = ::android::hardware::details::debuggable()? reinterpret_cast<uint64_t>(this) : 0;
    info.arch = 
    #if defined(__LP64__)
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
    #else
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
    #endif
    ;
    _hidl_cb(info);
    return ::android::hardware::Void();
}

::android::status_t BnHwStreamOut::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* getFrameSize */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getFrameSize(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* getFrameCount */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getFrameCount(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* getBufferSize */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getBufferSize(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 4 /* getSampleRate */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getSampleRate(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 5 /* getSupportedSampleRates */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getSupportedSampleRates(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 6 /* setSampleRate */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setSampleRate(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 7 /* getChannelMask */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getChannelMask(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 8 /* getSupportedChannelMasks */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getSupportedChannelMasks(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 9 /* setChannelMask */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setChannelMask(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 10 /* getFormat */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getFormat(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 11 /* getSupportedFormats */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getSupportedFormats(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 12 /* setFormat */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setFormat(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 13 /* getAudioProperties */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getAudioProperties(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 14 /* addEffect */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_addEffect(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 15 /* removeEffect */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_removeEffect(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 16 /* standby */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_standby(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 17 /* getDevices */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getDevices(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 18 /* setDevices */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setDevices(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 19 /* setHwAvSync */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setHwAvSync(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 20 /* getParameters */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getParameters(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 21 /* setParameters */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_setParameters(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 22 /* start */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_start(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 23 /* stop */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_stop(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 24 /* createMmapBuffer */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_createMmapBuffer(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 25 /* getMmapPosition */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_getMmapPosition(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 26 /* close */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStream::_hidl_close(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 27 /* getLatency */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_getLatency(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 28 /* setVolume */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_setVolume(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 29 /* updateSourceMetadata */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_updateSourceMetadata(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 30 /* prepareForWriting */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_prepareForWriting(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 31 /* getRenderPosition */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_getRenderPosition(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 32 /* getNextWriteTimestamp */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_getNextWriteTimestamp(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 33 /* setCallback */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_setCallback(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 34 /* clearCallback */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_clearCallback(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 35 /* supportsPauseAndResume */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_supportsPauseAndResume(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 36 /* pause */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_pause(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 37 /* resume */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_resume(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 38 /* supportsDrain */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_supportsDrain(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 39 /* drain */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_drain(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 40 /* flush */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_flush(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 41 /* getPresentationPosition */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_getPresentationPosition(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 42 /* selectPresentation */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V4_0::BnHwStreamOut::_hidl_selectPresentation(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        default:
        {
            return ::android::hidl::base::V1_0::BnHwBase::onTransact(
                    _hidl_code, _hidl_data, _hidl_reply, _hidl_flags, _hidl_cb);
        }
    }

    if (_hidl_err == ::android::UNEXPECTED_NULL) {
        _hidl_err = ::android::hardware::writeToParcel(
                ::android::hardware::Status::fromExceptionCode(::android::hardware::Status::EX_NULL_POINTER),
                _hidl_reply);
    }return _hidl_err;
}

BsStreamOut::BsStreamOut(const ::android::sp<::android::hardware::audio::V4_0::IStreamOut> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.audio@4.0", "IStreamOut"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsStreamOut::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IStreamOut> IStreamOut::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwStreamOut>(serviceName, false, getStub);
}

// static
::android::sp<IStreamOut> IStreamOut::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwStreamOut>(serviceName, true, getStub);
}

::android::status_t IStreamOut::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.audio@4.0", "IStreamOut", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IStreamOut::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.audio@4.0::IStreamOut",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V4_0
}  // namespace audio
}  // namespace hardware
}  // namespace android
