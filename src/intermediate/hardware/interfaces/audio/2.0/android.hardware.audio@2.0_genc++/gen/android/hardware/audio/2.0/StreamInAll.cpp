#define LOG_TAG "android.hardware.audio@2.0::StreamIn"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hardware/audio/2.0/BpHwStreamIn.h>
#include <android/hardware/audio/2.0/BnHwStreamIn.h>
#include <android/hardware/audio/2.0/BsStreamIn.h>
#include <android/hardware/audio/2.0/BpHwStream.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace audio {
namespace V2_0 {

const char* IStreamIn::descriptor("android.hardware.audio@2.0::IStreamIn");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IStreamIn::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwStreamIn(static_cast<IStreamIn *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IStreamIn::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsStreamIn(static_cast<IStreamIn *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IStreamIn::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IStreamIn::descriptor);
};

// Methods from ::android::hardware::audio::V2_0::IStream follow.
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamIn::getFrameSize()
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamIn::getFrameCount()
// no default implementation for: ::android::hardware::Return<uint64_t> IStreamIn::getBufferSize()
// no default implementation for: ::android::hardware::Return<uint32_t> IStreamIn::getSampleRate()
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getSupportedSampleRates(getSupportedSampleRates_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setSampleRate(uint32_t sampleRateHz)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioChannelMask> IStreamIn::getChannelMask()
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getSupportedChannelMasks(getSupportedChannelMasks_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setChannelMask(::android::hardware::audio::common::V2_0::AudioChannelMask mask)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioFormat> IStreamIn::getFormat()
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getSupportedFormats(getSupportedFormats_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setFormat(::android::hardware::audio::common::V2_0::AudioFormat format)
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getAudioProperties(getAudioProperties_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::addEffect(uint64_t effectId)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::removeEffect(uint64_t effectId)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::standby()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioDevice> IStreamIn::getDevice()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setDevice(const ::android::hardware::audio::V2_0::DeviceAddress& address)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setConnectedState(const ::android::hardware::audio::V2_0::DeviceAddress& address, bool connected)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setHwAvSync(uint32_t hwAvSync)
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getParameters(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V2_0::ParameterValue>& parameters)
// no default implementation for: ::android::hardware::Return<void> IStreamIn::debugDump(const ::android::hardware::hidl_handle& fd)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::start()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::stop()
// no default implementation for: ::android::hardware::Return<void> IStreamIn::createMmapBuffer(int32_t minSizeFrames, createMmapBuffer_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getMmapPosition(getMmapPosition_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::close()

// Methods from ::android::hardware::audio::V2_0::IStreamIn follow.
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getAudioSource(getAudioSource_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::V2_0::Result> IStreamIn::setGain(float gain)
// no default implementation for: ::android::hardware::Return<void> IStreamIn::prepareForReading(uint32_t frameSize, uint32_t framesCount, prepareForReading_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<uint32_t> IStreamIn::getInputFramesLost()
// no default implementation for: ::android::hardware::Return<void> IStreamIn::getCapturePosition(getCapturePosition_cb _hidl_cb)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IStreamIn::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::audio::V2_0::IStreamIn::descriptor,
        ::android::hardware::audio::V2_0::IStream::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamIn::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamIn::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::audio::V2_0::IStreamIn::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IStreamIn::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){4,104,197,114,59,13,68,197,180,81,189,250,6,21,48,0,198,243,82,253,51,54,224,173,38,151,18,123,4,183,102,223} /* 0468c5723b0d44c5b451bdfa06153000c6f352fd3336e0ad2697127b04b766df */,
        (uint8_t[32]){170,249,49,35,222,236,51,110,178,71,173,128,153,132,148,105,165,65,202,12,247,194,140,95,83,54,206,190,30,232,103,72} /* aaf93123deec336eb247ad8099849469a541ca0cf7c28c5f5336cebe1ee86748 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IStreamIn::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IStreamIn::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IStreamIn::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IStreamIn::getDebugInfo(getDebugInfo_cb _hidl_cb){
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

::android::hardware::Return<void> IStreamIn::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IStreamIn::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamIn>> IStreamIn::castFrom(const ::android::sp<::android::hardware::audio::V2_0::IStreamIn>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamIn>> IStreamIn::castFrom(const ::android::sp<::android::hardware::audio::V2_0::IStream>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IStreamIn, ::android::hardware::audio::V2_0::IStream, BpHwStreamIn>(
            parent, "android.hardware.audio@2.0::IStreamIn", emitError);
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IStreamIn>> IStreamIn::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IStreamIn, ::android::hidl::base::V1_0::IBase, BpHwStreamIn>(
            parent, "android.hardware.audio@2.0::IStreamIn", emitError);
}

BpHwStreamIn::BpHwStreamIn(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IStreamIn>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.audio@2.0", "IStreamIn") {
}

// Methods from ::android::hardware::audio::V2_0::IStreamIn follow.
::android::hardware::Return<void> BpHwStreamIn::_hidl_getAudioSource(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getAudioSource_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getAudioSource::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getAudioSource", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V2_0::Result _hidl_out_retval;
    ::android::hardware::audio::common::V2_0::AudioSource _hidl_out_source;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamIn::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(29 /* getAudioSource */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_source);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_source);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_source);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getAudioSource", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::_hidl_setGain(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, float gain) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::setGain::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&gain);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "setGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V2_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamIn::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeFloat(gain);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(30 /* setGain */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "setGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V2_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::V2_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamIn::_hidl_prepareForReading(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint32_t frameSize, uint32_t framesCount, prepareForReading_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::prepareForReading::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&frameSize);
        _hidl_args.push_back((void *)&framesCount);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "prepareForReading", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V2_0::Result _hidl_out_retval;
    const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamIn::ReadParameters>* _hidl_out_commandMQ;
    const ::android::hardware::MQDescriptorSync<uint8_t>* _hidl_out_dataMQ;
    const ::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamIn::ReadStatus>* _hidl_out_statusMQ;
    ::android::hardware::audio::common::V2_0::ThreadInfo* _hidl_out_threadInfo;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamIn::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32(frameSize);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32(framesCount);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(31 /* prepareForReading */, _hidl_data, &_hidl_reply);
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
            const_cast<::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamIn::ReadParameters> &>(*_hidl_out_commandMQ),
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
            const_cast<::android::hardware::MQDescriptorSync<::android::hardware::audio::V2_0::IStreamIn::ReadStatus> &>(*_hidl_out_statusMQ),
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "prepareForReading", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<uint32_t> BpHwStreamIn::_hidl_getInputFramesLost(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getInputFramesLost::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getInputFramesLost", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    uint32_t _hidl_out_framesLost;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamIn::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(32 /* getInputFramesLost */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readUint32(&_hidl_out_framesLost);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_framesLost);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getInputFramesLost", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<uint32_t>(_hidl_out_framesLost);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<uint32_t>(_hidl_status);
}

::android::hardware::Return<void> BpHwStreamIn::_hidl_getCapturePosition(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getCapturePosition_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getCapturePosition::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getCapturePosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V2_0::Result _hidl_out_retval;
    uint64_t _hidl_out_frames;
    uint64_t _hidl_out_time;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwStreamIn::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(33 /* getCapturePosition */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint64(&_hidl_out_frames);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint64(&_hidl_out_time);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_frames, _hidl_out_time);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_frames);
        _hidl_args.push_back((void *)&_hidl_out_time);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getCapturePosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::android::hardware::audio::V2_0::IStream follow.
::android::hardware::Return<uint64_t> BpHwStreamIn::getFrameSize(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getFrameSize(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint64_t> BpHwStreamIn::getFrameCount(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getFrameCount(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint64_t> BpHwStreamIn::getBufferSize(){
    ::android::hardware::Return<uint64_t>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getBufferSize(this, this);

    return _hidl_out;
}

::android::hardware::Return<uint32_t> BpHwStreamIn::getSampleRate(){
    ::android::hardware::Return<uint32_t>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getSampleRate(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getSupportedSampleRates(getSupportedSampleRates_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getSupportedSampleRates(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setSampleRate(uint32_t sampleRateHz){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setSampleRate(this, this, sampleRateHz);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioChannelMask> BpHwStreamIn::getChannelMask(){
    ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioChannelMask>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getChannelMask(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getSupportedChannelMasks(getSupportedChannelMasks_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getSupportedChannelMasks(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setChannelMask(::android::hardware::audio::common::V2_0::AudioChannelMask mask){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setChannelMask(this, this, mask);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioFormat> BpHwStreamIn::getFormat(){
    ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioFormat>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getFormat(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getSupportedFormats(getSupportedFormats_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getSupportedFormats(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setFormat(::android::hardware::audio::common::V2_0::AudioFormat format){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setFormat(this, this, format);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getAudioProperties(getAudioProperties_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getAudioProperties(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::addEffect(uint64_t effectId){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_addEffect(this, this, effectId);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::removeEffect(uint64_t effectId){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_removeEffect(this, this, effectId);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::standby(){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_standby(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioDevice> BpHwStreamIn::getDevice(){
    ::android::hardware::Return<::android::hardware::audio::common::V2_0::AudioDevice>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getDevice(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setDevice(const ::android::hardware::audio::V2_0::DeviceAddress& address){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setDevice(this, this, address);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setConnectedState(const ::android::hardware::audio::V2_0::DeviceAddress& address, bool connected){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setConnectedState(this, this, address, connected);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setHwAvSync(uint32_t hwAvSync){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setHwAvSync(this, this, hwAvSync);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getParameters(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getParameters(this, this, keys, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V2_0::ParameterValue>& parameters){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_setParameters(this, this, parameters);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::debugDump(const ::android::hardware::hidl_handle& fd){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_debugDump(this, this, fd);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::start(){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_start(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::stop(){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_stop(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::createMmapBuffer(int32_t minSizeFrames, createMmapBuffer_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_createMmapBuffer(this, this, minSizeFrames, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getMmapPosition(getMmapPosition_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_getMmapPosition(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::close(){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStream::_hidl_close(this, this);

    return _hidl_out;
}


// Methods from ::android::hardware::audio::V2_0::IStreamIn follow.
::android::hardware::Return<void> BpHwStreamIn::getAudioSource(getAudioSource_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStreamIn::_hidl_getAudioSource(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::V2_0::Result> BpHwStreamIn::setGain(float gain){
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStreamIn::_hidl_setGain(this, this, gain);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::prepareForReading(uint32_t frameSize, uint32_t framesCount, prepareForReading_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStreamIn::_hidl_prepareForReading(this, this, frameSize, framesCount, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<uint32_t> BpHwStreamIn::getInputFramesLost(){
    ::android::hardware::Return<uint32_t>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStreamIn::_hidl_getInputFramesLost(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getCapturePosition(getCapturePosition_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwStreamIn::_hidl_getCapturePosition(this, this, _hidl_cb);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwStreamIn::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwStreamIn::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwStreamIn::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwStreamIn::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwStreamIn::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwStreamIn::BnHwStreamIn(const ::android::sp<IStreamIn> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.audio@2.0", "IStreamIn") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwStreamIn::~BnHwStreamIn() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::audio::V2_0::IStreamIn follow.
::android::status_t BnHwStreamIn::_hidl_getAudioSource(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamIn::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getAudioSource::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getAudioSource", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamIn*>(_hidl_this->getImpl().get())->getAudioSource([&](const auto &_hidl_out_retval, const auto &_hidl_out_source) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getAudioSource: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_source);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_source);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getAudioSource", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getAudioSource: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamIn::_hidl_setGain(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamIn::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    float gain;

    _hidl_err = _hidl_data.readFloat(&gain);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::setGain::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&gain);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "setGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::V2_0::Result _hidl_out_retval = static_cast<IStreamIn*>(_hidl_this->getImpl().get())->setGain(gain);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "setGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamIn::_hidl_prepareForReading(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamIn::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint32_t frameSize;
    uint32_t framesCount;

    _hidl_err = _hidl_data.readUint32(&frameSize);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readUint32(&framesCount);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::prepareForReading::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&frameSize);
        _hidl_args.push_back((void *)&framesCount);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "prepareForReading", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamIn*>(_hidl_this->getImpl().get())->prepareForReading(frameSize, framesCount, [&](const auto &_hidl_out_retval, const auto &_hidl_out_commandMQ, const auto &_hidl_out_dataMQ, const auto &_hidl_out_statusMQ, const auto &_hidl_out_threadInfo) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("prepareForReading: _hidl_cb called a second time, but must be called once.");
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
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "prepareForReading", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("prepareForReading: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwStreamIn::_hidl_getInputFramesLost(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamIn::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getInputFramesLost::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getInputFramesLost", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    uint32_t _hidl_out_framesLost = static_cast<IStreamIn*>(_hidl_this->getImpl().get())->getInputFramesLost();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeUint32(_hidl_out_framesLost);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_framesLost);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getInputFramesLost", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwStreamIn::_hidl_getCapturePosition(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwStreamIn::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IStreamIn::getCapturePosition::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IStreamIn", "getCapturePosition", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IStreamIn*>(_hidl_this->getImpl().get())->getCapturePosition([&](const auto &_hidl_out_retval, const auto &_hidl_out_frames, const auto &_hidl_out_time) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getCapturePosition: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint64(_hidl_out_frames);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint64(_hidl_out_time);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_frames);
            _hidl_args.push_back((void *)&_hidl_out_time);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IStreamIn", "getCapturePosition", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getCapturePosition: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}


// Methods from ::android::hardware::audio::V2_0::IStream follow.

// Methods from ::android::hardware::audio::V2_0::IStreamIn follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwStreamIn::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwStreamIn::getDebugInfo(getDebugInfo_cb _hidl_cb) {
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

::android::status_t BnHwStreamIn::onTransact(
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

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getFrameSize(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* getFrameCount */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getFrameCount(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* getBufferSize */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getBufferSize(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 4 /* getSampleRate */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getSampleRate(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 5 /* getSupportedSampleRates */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getSupportedSampleRates(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 6 /* setSampleRate */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setSampleRate(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 7 /* getChannelMask */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getChannelMask(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 8 /* getSupportedChannelMasks */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getSupportedChannelMasks(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 9 /* setChannelMask */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setChannelMask(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 10 /* getFormat */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getFormat(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 11 /* getSupportedFormats */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getSupportedFormats(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 12 /* setFormat */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setFormat(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 13 /* getAudioProperties */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getAudioProperties(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 14 /* addEffect */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_addEffect(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 15 /* removeEffect */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_removeEffect(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 16 /* standby */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_standby(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 17 /* getDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 18 /* setDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 19 /* setConnectedState */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setConnectedState(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 20 /* setHwAvSync */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setHwAvSync(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 21 /* getParameters */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getParameters(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 22 /* setParameters */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_setParameters(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 23 /* debugDump */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_debugDump(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 24 /* start */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_start(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 25 /* stop */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_stop(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 26 /* createMmapBuffer */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_createMmapBuffer(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 27 /* getMmapPosition */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_getMmapPosition(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 28 /* close */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStream::_hidl_close(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 29 /* getAudioSource */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStreamIn::_hidl_getAudioSource(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 30 /* setGain */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStreamIn::_hidl_setGain(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 31 /* prepareForReading */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStreamIn::_hidl_prepareForReading(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 32 /* getInputFramesLost */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStreamIn::_hidl_getInputFramesLost(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 33 /* getCapturePosition */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwStreamIn::_hidl_getCapturePosition(this, _hidl_data, _hidl_reply, _hidl_cb);
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

BsStreamIn::BsStreamIn(const ::android::sp<::android::hardware::audio::V2_0::IStreamIn> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.audio@2.0", "IStreamIn"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsStreamIn::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IStreamIn> IStreamIn::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwStreamIn>(serviceName, false, getStub);
}

// static
::android::sp<IStreamIn> IStreamIn::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwStreamIn>(serviceName, true, getStub);
}

::android::status_t IStreamIn::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.audio@2.0", "IStreamIn", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IStreamIn::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.audio@2.0::IStreamIn",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V2_0
}  // namespace audio
}  // namespace hardware
}  // namespace android
