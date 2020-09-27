#define LOG_TAG "android.hardware.audio.effect@4.0::VirtualizerEffect"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hardware/audio/effect/4.0/BpHwVirtualizerEffect.h>
#include <android/hardware/audio/effect/4.0/BnHwVirtualizerEffect.h>
#include <android/hardware/audio/effect/4.0/BsVirtualizerEffect.h>
#include <android/hardware/audio/effect/4.0/BpHwEffect.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace audio {
namespace effect {
namespace V4_0 {

const char* IVirtualizerEffect::descriptor("android.hardware.audio.effect@4.0::IVirtualizerEffect");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IVirtualizerEffect::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwVirtualizerEffect(static_cast<IVirtualizerEffect *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IVirtualizerEffect::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsVirtualizerEffect(static_cast<IVirtualizerEffect *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IVirtualizerEffect::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IVirtualizerEffect::descriptor);
};

// Methods from ::android::hardware::audio::effect::V4_0::IEffect follow.
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::init()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setConfig(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::reset()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::enable()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::disable()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::setAndGetVolume(const ::android::hardware::hidl_vec<uint32_t>& volumes, setAndGetVolume_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::volumeChangeNotification(const ::android::hardware::hidl_vec<uint32_t>& volumes)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setAudioMode(::android::hardware::audio::common::V4_0::AudioMode mode)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setConfigReverse(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setInputDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getConfig(getConfig_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getConfigReverse(getConfigReverse_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getSupportedAuxChannelsConfigs(uint32_t maxConfigs, getSupportedAuxChannelsConfigs_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getAuxChannelsConfig(getAuxChannelsConfig_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setAuxChannelsConfig(const ::android::hardware::audio::effect::V4_0::EffectAuxChannelsConfig& config)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setAudioSource(::android::hardware::audio::common::V4_0::AudioSource source)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::offload(const ::android::hardware::audio::effect::V4_0::EffectOffloadParameter& param)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getDescriptor(getDescriptor_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::prepareForProcessing(prepareForProcessing_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setProcessBuffers(const ::android::hardware::audio::effect::V4_0::AudioBuffer& inBuffer, const ::android::hardware::audio::effect::V4_0::AudioBuffer& outBuffer)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::command(uint32_t commandId, const ::android::hardware::hidl_vec<uint8_t>& data, uint32_t resultMaxSize, command_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, const ::android::hardware::hidl_vec<uint8_t>& value)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, uint32_t valueMaxSize, getParameter_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getSupportedConfigsForFeature(uint32_t featureId, uint32_t maxConfigs, uint32_t configSize, getSupportedConfigsForFeature_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getCurrentConfigForFeature(uint32_t featureId, uint32_t configSize, getCurrentConfigForFeature_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setCurrentConfigForFeature(uint32_t featureId, const ::android::hardware::hidl_vec<uint8_t>& configData)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::close()

// Methods from ::android::hardware::audio::effect::V4_0::IVirtualizerEffect follow.
// no default implementation for: ::android::hardware::Return<bool> IVirtualizerEffect::isStrengthSupported()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::setStrength(uint16_t strength)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getStrength(getStrength_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getVirtualSpeakerAngles(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask, ::android::hardware::audio::common::V4_0::AudioDevice device, getVirtualSpeakerAngles_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> IVirtualizerEffect::forceVirtualizationMode(::android::hardware::audio::common::V4_0::AudioDevice device)
// no default implementation for: ::android::hardware::Return<void> IVirtualizerEffect::getVirtualizationMode(getVirtualizationMode_cb _hidl_cb)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IVirtualizerEffect::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::audio::effect::V4_0::IVirtualizerEffect::descriptor,
        ::android::hardware::audio::effect::V4_0::IEffect::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IVirtualizerEffect::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IVirtualizerEffect::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::audio::effect::V4_0::IVirtualizerEffect::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IVirtualizerEffect::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){232,142,82,15,140,152,166,47,204,216,213,49,108,102,135,128,143,119,93,225,69,209,64,90,122,154,102,88,126,230,160,1} /* e88e520f8c98a62fccd8d5316c6687808f775de145d1405a7a9a66587ee6a001 */,
        (uint8_t[32]){186,200,27,255,190,38,97,213,182,131,144,135,210,221,58,39,237,237,102,230,12,108,118,211,92,104,213,64,20,205,92,6} /* bac81bffbe2661d5b6839087d2dd3a27eded66e60c6c76d35c68d54014cd5c06 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IVirtualizerEffect::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IVirtualizerEffect::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IVirtualizerEffect::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IVirtualizerEffect::getDebugInfo(getDebugInfo_cb _hidl_cb){
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

::android::hardware::Return<void> IVirtualizerEffect::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IVirtualizerEffect::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IVirtualizerEffect>> IVirtualizerEffect::castFrom(const ::android::sp<::android::hardware::audio::effect::V4_0::IVirtualizerEffect>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IVirtualizerEffect>> IVirtualizerEffect::castFrom(const ::android::sp<::android::hardware::audio::effect::V4_0::IEffect>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IVirtualizerEffect, ::android::hardware::audio::effect::V4_0::IEffect, BpHwVirtualizerEffect>(
            parent, "android.hardware.audio.effect@4.0::IVirtualizerEffect", emitError);
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V4_0::IVirtualizerEffect>> IVirtualizerEffect::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IVirtualizerEffect, ::android::hidl::base::V1_0::IBase, BpHwVirtualizerEffect>(
            parent, "android.hardware.audio.effect@4.0::IVirtualizerEffect", emitError);
}

BpHwVirtualizerEffect::BpHwVirtualizerEffect(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IVirtualizerEffect>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.audio.effect@4.0", "IVirtualizerEffect") {
}

// Methods from ::android::hardware::audio::effect::V4_0::IVirtualizerEffect follow.
::android::hardware::Return<bool> BpHwVirtualizerEffect::_hidl_isStrengthSupported(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::isStrengthSupported::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "isStrengthSupported", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    bool _hidl_out_strengthSupported;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(29 /* isStrengthSupported */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_strengthSupported);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_strengthSupported);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "isStrengthSupported", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_out_strengthSupported);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::_hidl_setStrength(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint16_t strength) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::setStrength::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&strength);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "setStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint16(strength);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(30 /* setStrength */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "setStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwVirtualizerEffect::_hidl_getStrength(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getStrength_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getStrength::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval;
    uint16_t _hidl_out_strength;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(31 /* getStrength */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint16(&_hidl_out_strength);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_strength);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_strength);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwVirtualizerEffect::_hidl_getVirtualSpeakerAngles(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask, ::android::hardware::audio::common::V4_0::AudioDevice device, getVirtualSpeakerAngles_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getVirtualSpeakerAngles::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&mask);
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualSpeakerAngles", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval;
    const ::android::hardware::hidl_vec<::android::hardware::audio::effect::V4_0::IVirtualizerEffect::SpeakerAngle>* _hidl_out_speakerAngles;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32((uint32_t)mask);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32((uint32_t)device);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(32 /* getVirtualSpeakerAngles */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_speakerAngles_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_speakerAngles), &_hidl__hidl_out_speakerAngles_parent,  reinterpret_cast<const void **>(&_hidl_out_speakerAngles));

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_speakerAngles_child;

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::hidl_vec<::android::hardware::audio::effect::V4_0::IVirtualizerEffect::SpeakerAngle> &>(*_hidl_out_speakerAngles),
            _hidl_reply,
            _hidl__hidl_out_speakerAngles_parent,
            0 /* parentOffset */, &_hidl__hidl_out_speakerAngles_child);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, *_hidl_out_speakerAngles);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)_hidl_out_speakerAngles);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualSpeakerAngles", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::_hidl_forceVirtualizationMode(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::audio::common::V4_0::AudioDevice device) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::forceVirtualizationMode::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "forceVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint32((uint32_t)device);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(33 /* forceVirtualizationMode */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "forceVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwVirtualizerEffect::_hidl_getVirtualizationMode(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getVirtualizationMode_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getVirtualizationMode::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval;
    ::android::hardware::audio::common::V4_0::AudioDevice _hidl_out_device;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwVirtualizerEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(34 /* getVirtualizationMode */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readUint32((uint32_t *)&_hidl_out_device);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_device);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::android::hardware::audio::effect::V4_0::IEffect follow.
::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::init(){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_init(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setConfig(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setConfig(this, this, config, inputBufferProvider, outputBufferProvider);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::reset(){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_reset(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::enable(){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_enable(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::disable(){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_disable(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setDevice(this, this, device);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::setAndGetVolume(const ::android::hardware::hidl_vec<uint32_t>& volumes, setAndGetVolume_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setAndGetVolume(this, this, volumes, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::volumeChangeNotification(const ::android::hardware::hidl_vec<uint32_t>& volumes){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_volumeChangeNotification(this, this, volumes);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setAudioMode(::android::hardware::audio::common::V4_0::AudioMode mode){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setAudioMode(this, this, mode);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setConfigReverse(const ::android::hardware::audio::effect::V4_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V4_0::IEffectBufferProviderCallback>& outputBufferProvider){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setConfigReverse(this, this, config, inputBufferProvider, outputBufferProvider);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setInputDevice(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioDevice> device){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setInputDevice(this, this, device);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getConfig(getConfig_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getConfig(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getConfigReverse(getConfigReverse_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getConfigReverse(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getSupportedAuxChannelsConfigs(uint32_t maxConfigs, getSupportedAuxChannelsConfigs_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getSupportedAuxChannelsConfigs(this, this, maxConfigs, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getAuxChannelsConfig(getAuxChannelsConfig_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getAuxChannelsConfig(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setAuxChannelsConfig(const ::android::hardware::audio::effect::V4_0::EffectAuxChannelsConfig& config){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setAuxChannelsConfig(this, this, config);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setAudioSource(::android::hardware::audio::common::V4_0::AudioSource source){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setAudioSource(this, this, source);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::offload(const ::android::hardware::audio::effect::V4_0::EffectOffloadParameter& param){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_offload(this, this, param);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getDescriptor(getDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::prepareForProcessing(prepareForProcessing_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_prepareForProcessing(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setProcessBuffers(const ::android::hardware::audio::effect::V4_0::AudioBuffer& inBuffer, const ::android::hardware::audio::effect::V4_0::AudioBuffer& outBuffer){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setProcessBuffers(this, this, inBuffer, outBuffer);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::command(uint32_t commandId, const ::android::hardware::hidl_vec<uint8_t>& data, uint32_t resultMaxSize, command_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_command(this, this, commandId, data, resultMaxSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, const ::android::hardware::hidl_vec<uint8_t>& value){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setParameter(this, this, parameter, value);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, uint32_t valueMaxSize, getParameter_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getParameter(this, this, parameter, valueMaxSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getSupportedConfigsForFeature(uint32_t featureId, uint32_t maxConfigs, uint32_t configSize, getSupportedConfigsForFeature_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getSupportedConfigsForFeature(this, this, featureId, maxConfigs, configSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getCurrentConfigForFeature(uint32_t featureId, uint32_t configSize, getCurrentConfigForFeature_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_getCurrentConfigForFeature(this, this, featureId, configSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setCurrentConfigForFeature(uint32_t featureId, const ::android::hardware::hidl_vec<uint8_t>& configData){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_setCurrentConfigForFeature(this, this, featureId, configData);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::close(){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwEffect::_hidl_close(this, this);

    return _hidl_out;
}


// Methods from ::android::hardware::audio::effect::V4_0::IVirtualizerEffect follow.
::android::hardware::Return<bool> BpHwVirtualizerEffect::isStrengthSupported(){
    ::android::hardware::Return<bool>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_isStrengthSupported(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::setStrength(uint16_t strength){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_setStrength(this, this, strength);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getStrength(getStrength_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_getStrength(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getVirtualSpeakerAngles(::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask, ::android::hardware::audio::common::V4_0::AudioDevice device, getVirtualSpeakerAngles_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_getVirtualSpeakerAngles(this, this, mask, device, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result> BpHwVirtualizerEffect::forceVirtualizationMode(::android::hardware::audio::common::V4_0::AudioDevice device){
    ::android::hardware::Return<::android::hardware::audio::effect::V4_0::Result>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_forceVirtualizationMode(this, this, device);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getVirtualizationMode(getVirtualizationMode_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V4_0::BpHwVirtualizerEffect::_hidl_getVirtualizationMode(this, this, _hidl_cb);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwVirtualizerEffect::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwVirtualizerEffect::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwVirtualizerEffect::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwVirtualizerEffect::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwVirtualizerEffect::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwVirtualizerEffect::BnHwVirtualizerEffect(const ::android::sp<IVirtualizerEffect> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.audio.effect@4.0", "IVirtualizerEffect") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwVirtualizerEffect::~BnHwVirtualizerEffect() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::audio::effect::V4_0::IVirtualizerEffect follow.
::android::status_t BnHwVirtualizerEffect::_hidl_isStrengthSupported(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::isStrengthSupported::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "isStrengthSupported", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_out_strengthSupported = static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->isStrengthSupported();

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeBool(_hidl_out_strengthSupported);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_strengthSupported);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "isStrengthSupported", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwVirtualizerEffect::_hidl_setStrength(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint16_t strength;

    _hidl_err = _hidl_data.readUint16(&strength);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::setStrength::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&strength);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "setStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval = static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->setStrength(strength);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "setStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwVirtualizerEffect::_hidl_getStrength(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getStrength::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getStrength", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->getStrength([&](const auto &_hidl_out_retval, const auto &_hidl_out_strength) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getStrength: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint16(_hidl_out_strength);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_strength);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getStrength", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getStrength: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwVirtualizerEffect::_hidl_getVirtualSpeakerAngles(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::hidl_bitfield<::android::hardware::audio::common::V4_0::AudioChannelMask> mask;
    ::android::hardware::audio::common::V4_0::AudioDevice device;

    _hidl_err = _hidl_data.readUint32((uint32_t *)&mask);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readUint32((uint32_t *)&device);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getVirtualSpeakerAngles::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&mask);
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualSpeakerAngles", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->getVirtualSpeakerAngles(mask, device, [&](const auto &_hidl_out_retval, const auto &_hidl_out_speakerAngles) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getVirtualSpeakerAngles: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_speakerAngles_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_speakerAngles, sizeof(_hidl_out_speakerAngles), &_hidl__hidl_out_speakerAngles_parent);
        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_speakerAngles_child;

        _hidl_err = ::android::hardware::writeEmbeddedToParcel(
                _hidl_out_speakerAngles,
                _hidl_reply,
                _hidl__hidl_out_speakerAngles_parent,
                0 /* parentOffset */, &_hidl__hidl_out_speakerAngles_child);

        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_speakerAngles);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualSpeakerAngles", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getVirtualSpeakerAngles: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwVirtualizerEffect::_hidl_forceVirtualizationMode(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::audio::common::V4_0::AudioDevice device;

    _hidl_err = _hidl_data.readUint32((uint32_t *)&device);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::forceVirtualizationMode::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "forceVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V4_0::Result _hidl_out_retval = static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->forceVirtualizationMode(device);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "forceVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwVirtualizerEffect::_hidl_getVirtualizationMode(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwVirtualizerEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IVirtualizerEffect::getVirtualizationMode::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualizationMode", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IVirtualizerEffect*>(_hidl_this->getImpl().get())->getVirtualizationMode([&](const auto &_hidl_out_retval, const auto &_hidl_out_device) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getVirtualizationMode: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeUint32((uint32_t)_hidl_out_device);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_device);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "4.0", "IVirtualizerEffect", "getVirtualizationMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getVirtualizationMode: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}


// Methods from ::android::hardware::audio::effect::V4_0::IEffect follow.

// Methods from ::android::hardware::audio::effect::V4_0::IVirtualizerEffect follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwVirtualizerEffect::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwVirtualizerEffect::getDebugInfo(getDebugInfo_cb _hidl_cb) {
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

::android::status_t BnHwVirtualizerEffect::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* init */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_init(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* setConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* reset */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_reset(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 4 /* enable */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_enable(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 5 /* disable */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_disable(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 6 /* setDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 7 /* setAndGetVolume */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setAndGetVolume(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 8 /* volumeChangeNotification */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_volumeChangeNotification(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 9 /* setAudioMode */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setAudioMode(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 10 /* setConfigReverse */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setConfigReverse(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 11 /* setInputDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setInputDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 12 /* getConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 13 /* getConfigReverse */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getConfigReverse(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 14 /* getSupportedAuxChannelsConfigs */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getSupportedAuxChannelsConfigs(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 15 /* getAuxChannelsConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getAuxChannelsConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 16 /* setAuxChannelsConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setAuxChannelsConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 17 /* setAudioSource */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setAudioSource(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 18 /* offload */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_offload(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 19 /* getDescriptor */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getDescriptor(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 20 /* prepareForProcessing */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_prepareForProcessing(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 21 /* setProcessBuffers */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setProcessBuffers(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 22 /* command */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_command(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 23 /* setParameter */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setParameter(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 24 /* getParameter */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getParameter(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 25 /* getSupportedConfigsForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getSupportedConfigsForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 26 /* getCurrentConfigForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_getCurrentConfigForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 27 /* setCurrentConfigForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_setCurrentConfigForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 28 /* close */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwEffect::_hidl_close(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 29 /* isStrengthSupported */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_isStrengthSupported(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 30 /* setStrength */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_setStrength(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 31 /* getStrength */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_getStrength(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 32 /* getVirtualSpeakerAngles */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_getVirtualSpeakerAngles(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 33 /* forceVirtualizationMode */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_forceVirtualizationMode(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 34 /* getVirtualizationMode */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V4_0::BnHwVirtualizerEffect::_hidl_getVirtualizationMode(this, _hidl_data, _hidl_reply, _hidl_cb);
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

BsVirtualizerEffect::BsVirtualizerEffect(const ::android::sp<::android::hardware::audio::effect::V4_0::IVirtualizerEffect> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.audio.effect@4.0", "IVirtualizerEffect"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsVirtualizerEffect::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IVirtualizerEffect> IVirtualizerEffect::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwVirtualizerEffect>(serviceName, false, getStub);
}

// static
::android::sp<IVirtualizerEffect> IVirtualizerEffect::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwVirtualizerEffect>(serviceName, true, getStub);
}

::android::status_t IVirtualizerEffect::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.audio.effect@4.0", "IVirtualizerEffect", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IVirtualizerEffect::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.audio.effect@4.0::IVirtualizerEffect",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V4_0
}  // namespace effect
}  // namespace audio
}  // namespace hardware
}  // namespace android