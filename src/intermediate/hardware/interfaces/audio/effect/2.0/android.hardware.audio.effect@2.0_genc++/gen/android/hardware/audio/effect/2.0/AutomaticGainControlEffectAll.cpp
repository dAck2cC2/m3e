#define LOG_TAG "android.hardware.audio.effect@2.0::AutomaticGainControlEffect"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hardware/audio/effect/2.0/BpHwAutomaticGainControlEffect.h>
#include <android/hardware/audio/effect/2.0/BnHwAutomaticGainControlEffect.h>
#include <android/hardware/audio/effect/2.0/BsAutomaticGainControlEffect.h>
#include <android/hardware/audio/effect/2.0/BpHwEffect.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace audio {
namespace effect {
namespace V2_0 {

const char* IAutomaticGainControlEffect::descriptor("android.hardware.audio.effect@2.0::IAutomaticGainControlEffect");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IAutomaticGainControlEffect::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwAutomaticGainControlEffect(static_cast<IAutomaticGainControlEffect *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IAutomaticGainControlEffect::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsAutomaticGainControlEffect(static_cast<IAutomaticGainControlEffect *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IAutomaticGainControlEffect::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IAutomaticGainControlEffect::descriptor);
};

// Methods from ::android::hardware::audio::effect::V2_0::IEffect follow.
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::init()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setConfig(const ::android::hardware::audio::effect::V2_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& outputBufferProvider)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::reset()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::enable()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::disable()
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setDevice(::android::hardware::audio::common::V2_0::AudioDevice device)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::setAndGetVolume(const ::android::hardware::hidl_vec<uint32_t>& volumes, setAndGetVolume_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::volumeChangeNotification(const ::android::hardware::hidl_vec<uint32_t>& volumes)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setAudioMode(::android::hardware::audio::common::V2_0::AudioMode mode)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setConfigReverse(const ::android::hardware::audio::effect::V2_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& outputBufferProvider)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setInputDevice(::android::hardware::audio::common::V2_0::AudioDevice device)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getConfig(getConfig_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getConfigReverse(getConfigReverse_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getSupportedAuxChannelsConfigs(uint32_t maxConfigs, getSupportedAuxChannelsConfigs_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getAuxChannelsConfig(getAuxChannelsConfig_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setAuxChannelsConfig(const ::android::hardware::audio::effect::V2_0::EffectAuxChannelsConfig& config)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setAudioSource(::android::hardware::audio::common::V2_0::AudioSource source)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::offload(const ::android::hardware::audio::effect::V2_0::EffectOffloadParameter& param)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getDescriptor(getDescriptor_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::prepareForProcessing(prepareForProcessing_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setProcessBuffers(const ::android::hardware::audio::effect::V2_0::AudioBuffer& inBuffer, const ::android::hardware::audio::effect::V2_0::AudioBuffer& outBuffer)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::command(uint32_t commandId, const ::android::hardware::hidl_vec<uint8_t>& data, uint32_t resultMaxSize, command_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, const ::android::hardware::hidl_vec<uint8_t>& value)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, uint32_t valueMaxSize, getParameter_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getSupportedConfigsForFeature(uint32_t featureId, uint32_t maxConfigs, uint32_t configSize, getSupportedConfigsForFeature_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getCurrentConfigForFeature(uint32_t featureId, uint32_t configSize, getCurrentConfigForFeature_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setCurrentConfigForFeature(uint32_t featureId, const ::android::hardware::hidl_vec<uint8_t>& configData)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::close()

// Methods from ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect follow.
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setTargetLevel(int16_t targetLevelMb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getTargetLevel(getTargetLevel_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setCompGain(int16_t compGainMb)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getCompGain(getCompGain_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setLimiterEnabled(bool enabled)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::isLimiterEnabled(isLimiterEnabled_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> IAutomaticGainControlEffect::setAllProperties(const ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::AllProperties& properties)
// no default implementation for: ::android::hardware::Return<void> IAutomaticGainControlEffect::getAllProperties(getAllProperties_cb _hidl_cb)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IAutomaticGainControlEffect::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::descriptor,
        ::android::hardware::audio::effect::V2_0::IEffect::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IAutomaticGainControlEffect::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IAutomaticGainControlEffect::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IAutomaticGainControlEffect::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){202,71,82,84,93,84,84,127,240,105,234,225,97,175,117,80,203,95,90,126,139,96,49,109,221,19,42,48,144,106,104,231} /* ca4752545d54547ff069eae161af7550cb5f5a7e8b60316ddd132a30906a68e7 */,
        (uint8_t[32]){54,165,115,105,223,220,117,24,14,139,100,174,128,177,151,13,184,246,217,8,93,191,246,202,147,23,21,3,140,192,86,225} /* 36a57369dfdc75180e8b64ae80b1970db8f6d9085dbff6ca931715038cc056e1 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IAutomaticGainControlEffect::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IAutomaticGainControlEffect::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IAutomaticGainControlEffect::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IAutomaticGainControlEffect::getDebugInfo(getDebugInfo_cb _hidl_cb){
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

::android::hardware::Return<void> IAutomaticGainControlEffect::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IAutomaticGainControlEffect::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect>> IAutomaticGainControlEffect::castFrom(const ::android::sp<::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect>> IAutomaticGainControlEffect::castFrom(const ::android::sp<::android::hardware::audio::effect::V2_0::IEffect>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IAutomaticGainControlEffect, ::android::hardware::audio::effect::V2_0::IEffect, BpHwAutomaticGainControlEffect>(
            parent, "android.hardware.audio.effect@2.0::IAutomaticGainControlEffect", emitError);
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect>> IAutomaticGainControlEffect::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IAutomaticGainControlEffect, ::android::hidl::base::V1_0::IBase, BpHwAutomaticGainControlEffect>(
            parent, "android.hardware.audio.effect@2.0::IAutomaticGainControlEffect", emitError);
}

BpHwAutomaticGainControlEffect::BpHwAutomaticGainControlEffect(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IAutomaticGainControlEffect>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.audio.effect@2.0", "IAutomaticGainControlEffect") {
}

// Methods from ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect follow.
::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::_hidl_setTargetLevel(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int16_t targetLevelMb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setTargetLevel::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&targetLevelMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt16(targetLevelMb);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(29 /* setTargetLevel */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::_hidl_getTargetLevel(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getTargetLevel_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getTargetLevel::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;
    int16_t _hidl_out_targetLevelMb;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(30 /* getTargetLevel */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readInt16(&_hidl_out_targetLevelMb);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_targetLevelMb);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_targetLevelMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::_hidl_setCompGain(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int16_t compGainMb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setCompGain::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&compGainMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt16(compGainMb);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(31 /* setCompGain */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::_hidl_getCompGain(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getCompGain_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getCompGain::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;
    int16_t _hidl_out_compGainMb;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(32 /* getCompGain */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readInt16(&_hidl_out_compGainMb);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_compGainMb);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_compGainMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::_hidl_setLimiterEnabled(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, bool enabled) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setLimiterEnabled::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&enabled);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeBool(enabled);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(33 /* setLimiterEnabled */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::_hidl_isLimiterEnabled(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, isLimiterEnabled_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::isLimiterEnabled::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "isLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;
    bool _hidl_out_enabled;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(34 /* isLimiterEnabled */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_enabled);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, _hidl_out_enabled);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_enabled);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "isLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::_hidl_setAllProperties(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::AllProperties& properties) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setAllProperties::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&properties);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_properties_parent;

    _hidl_err = _hidl_data.writeBuffer(&properties, sizeof(properties), &_hidl_properties_parent);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(35 /* setAllProperties */, _hidl_data, &_hidl_reply);
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
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_out_retval);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>(_hidl_status);
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::_hidl_getAllProperties(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getAllProperties_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getAllProperties::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval;
    ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::AllProperties* _hidl_out_properties;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwAutomaticGainControlEffect::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(36 /* getAllProperties */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl__hidl_out_properties_parent;

    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_properties), &_hidl__hidl_out_properties_parent,  const_cast<const void**>(reinterpret_cast<void **>(&_hidl_out_properties)));
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_cb(_hidl_out_retval, *_hidl_out_properties);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)_hidl_out_properties);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::android::hardware::audio::effect::V2_0::IEffect follow.
::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::init(){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_init(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setConfig(const ::android::hardware::audio::effect::V2_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& outputBufferProvider){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setConfig(this, this, config, inputBufferProvider, outputBufferProvider);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::reset(){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_reset(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::enable(){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_enable(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::disable(){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_disable(this, this);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setDevice(::android::hardware::audio::common::V2_0::AudioDevice device){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setDevice(this, this, device);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::setAndGetVolume(const ::android::hardware::hidl_vec<uint32_t>& volumes, setAndGetVolume_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setAndGetVolume(this, this, volumes, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::volumeChangeNotification(const ::android::hardware::hidl_vec<uint32_t>& volumes){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_volumeChangeNotification(this, this, volumes);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setAudioMode(::android::hardware::audio::common::V2_0::AudioMode mode){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setAudioMode(this, this, mode);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setConfigReverse(const ::android::hardware::audio::effect::V2_0::EffectConfig& config, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& inputBufferProvider, const ::android::sp<::android::hardware::audio::effect::V2_0::IEffectBufferProviderCallback>& outputBufferProvider){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setConfigReverse(this, this, config, inputBufferProvider, outputBufferProvider);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setInputDevice(::android::hardware::audio::common::V2_0::AudioDevice device){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setInputDevice(this, this, device);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getConfig(getConfig_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getConfig(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getConfigReverse(getConfigReverse_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getConfigReverse(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getSupportedAuxChannelsConfigs(uint32_t maxConfigs, getSupportedAuxChannelsConfigs_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getSupportedAuxChannelsConfigs(this, this, maxConfigs, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getAuxChannelsConfig(getAuxChannelsConfig_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getAuxChannelsConfig(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setAuxChannelsConfig(const ::android::hardware::audio::effect::V2_0::EffectAuxChannelsConfig& config){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setAuxChannelsConfig(this, this, config);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setAudioSource(::android::hardware::audio::common::V2_0::AudioSource source){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setAudioSource(this, this, source);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::offload(const ::android::hardware::audio::effect::V2_0::EffectOffloadParameter& param){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_offload(this, this, param);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getDescriptor(getDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::prepareForProcessing(prepareForProcessing_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_prepareForProcessing(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setProcessBuffers(const ::android::hardware::audio::effect::V2_0::AudioBuffer& inBuffer, const ::android::hardware::audio::effect::V2_0::AudioBuffer& outBuffer){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setProcessBuffers(this, this, inBuffer, outBuffer);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::command(uint32_t commandId, const ::android::hardware::hidl_vec<uint8_t>& data, uint32_t resultMaxSize, command_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_command(this, this, commandId, data, resultMaxSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, const ::android::hardware::hidl_vec<uint8_t>& value){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setParameter(this, this, parameter, value);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getParameter(const ::android::hardware::hidl_vec<uint8_t>& parameter, uint32_t valueMaxSize, getParameter_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getParameter(this, this, parameter, valueMaxSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getSupportedConfigsForFeature(uint32_t featureId, uint32_t maxConfigs, uint32_t configSize, getSupportedConfigsForFeature_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getSupportedConfigsForFeature(this, this, featureId, maxConfigs, configSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getCurrentConfigForFeature(uint32_t featureId, uint32_t configSize, getCurrentConfigForFeature_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_getCurrentConfigForFeature(this, this, featureId, configSize, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setCurrentConfigForFeature(uint32_t featureId, const ::android::hardware::hidl_vec<uint8_t>& configData){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_setCurrentConfigForFeature(this, this, featureId, configData);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::close(){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwEffect::_hidl_close(this, this);

    return _hidl_out;
}


// Methods from ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect follow.
::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setTargetLevel(int16_t targetLevelMb){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_setTargetLevel(this, this, targetLevelMb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getTargetLevel(getTargetLevel_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_getTargetLevel(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setCompGain(int16_t compGainMb){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_setCompGain(this, this, compGainMb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getCompGain(getCompGain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_getCompGain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setLimiterEnabled(bool enabled){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_setLimiterEnabled(this, this, enabled);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::isLimiterEnabled(isLimiterEnabled_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_isLimiterEnabled(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result> BpHwAutomaticGainControlEffect::setAllProperties(const ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::AllProperties& properties){
    ::android::hardware::Return<::android::hardware::audio::effect::V2_0::Result>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_setAllProperties(this, this, properties);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getAllProperties(getAllProperties_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::effect::V2_0::BpHwAutomaticGainControlEffect::_hidl_getAllProperties(this, this, _hidl_cb);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwAutomaticGainControlEffect::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwAutomaticGainControlEffect::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwAutomaticGainControlEffect::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwAutomaticGainControlEffect::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwAutomaticGainControlEffect::BnHwAutomaticGainControlEffect(const ::android::sp<IAutomaticGainControlEffect> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.audio.effect@2.0", "IAutomaticGainControlEffect") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwAutomaticGainControlEffect::~BnHwAutomaticGainControlEffect() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect follow.
::android::status_t BnHwAutomaticGainControlEffect::_hidl_setTargetLevel(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    int16_t targetLevelMb;

    _hidl_err = _hidl_data.readInt16(&targetLevelMb);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setTargetLevel::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&targetLevelMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval = static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->setTargetLevel(targetLevelMb);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_getTargetLevel(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getTargetLevel::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getTargetLevel", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->getTargetLevel([&](const auto &_hidl_out_retval, const auto &_hidl_out_targetLevelMb) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getTargetLevel: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeInt16(_hidl_out_targetLevelMb);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_targetLevelMb);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getTargetLevel", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getTargetLevel: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_setCompGain(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    int16_t compGainMb;

    _hidl_err = _hidl_data.readInt16(&compGainMb);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setCompGain::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&compGainMb);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval = static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->setCompGain(compGainMb);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_getCompGain(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getCompGain::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getCompGain", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->getCompGain([&](const auto &_hidl_out_retval, const auto &_hidl_out_compGainMb) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getCompGain: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeInt16(_hidl_out_compGainMb);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_compGainMb);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getCompGain", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getCompGain: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_setLimiterEnabled(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    bool enabled;

    _hidl_err = _hidl_data.readBool(&enabled);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setLimiterEnabled::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&enabled);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval = static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->setLimiterEnabled(enabled);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_isLimiterEnabled(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::isLimiterEnabled::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "isLimiterEnabled", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->isLimiterEnabled([&](const auto &_hidl_out_retval, const auto &_hidl_out_enabled) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("isLimiterEnabled: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        _hidl_err = _hidl_reply->writeBool(_hidl_out_enabled);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_enabled);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "isLimiterEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("isLimiterEnabled: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_setAllProperties(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect::AllProperties* properties;

    size_t _hidl_properties_parent;

    _hidl_err = _hidl_data.readBuffer(sizeof(*properties), &_hidl_properties_parent,  const_cast<const void**>(reinterpret_cast<void **>(&properties)));
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::setAllProperties::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)properties);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::audio::effect::V2_0::Result _hidl_out_retval = static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->setAllProperties(*properties);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "setAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}

::android::status_t BnHwAutomaticGainControlEffect::_hidl_getAllProperties(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwAutomaticGainControlEffect::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IAutomaticGainControlEffect::getAllProperties::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getAllProperties", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IAutomaticGainControlEffect*>(_hidl_this->getImpl().get())->getAllProperties([&](const auto &_hidl_out_retval, const auto &_hidl_out_properties) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("getAllProperties: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        size_t _hidl__hidl_out_properties_parent;

        _hidl_err = _hidl_reply->writeBuffer(&_hidl_out_properties, sizeof(_hidl_out_properties), &_hidl__hidl_out_properties_parent);
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_properties);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio.effect", "2.0", "IAutomaticGainControlEffect", "getAllProperties", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("getAllProperties: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}


// Methods from ::android::hardware::audio::effect::V2_0::IEffect follow.

// Methods from ::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwAutomaticGainControlEffect::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwAutomaticGainControlEffect::getDebugInfo(getDebugInfo_cb _hidl_cb) {
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

::android::status_t BnHwAutomaticGainControlEffect::onTransact(
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

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_init(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* setConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* reset */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_reset(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 4 /* enable */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_enable(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 5 /* disable */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_disable(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 6 /* setDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 7 /* setAndGetVolume */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setAndGetVolume(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 8 /* volumeChangeNotification */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_volumeChangeNotification(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 9 /* setAudioMode */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setAudioMode(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 10 /* setConfigReverse */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setConfigReverse(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 11 /* setInputDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setInputDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 12 /* getConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 13 /* getConfigReverse */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getConfigReverse(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 14 /* getSupportedAuxChannelsConfigs */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getSupportedAuxChannelsConfigs(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 15 /* getAuxChannelsConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getAuxChannelsConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 16 /* setAuxChannelsConfig */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setAuxChannelsConfig(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 17 /* setAudioSource */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setAudioSource(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 18 /* offload */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_offload(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 19 /* getDescriptor */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getDescriptor(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 20 /* prepareForProcessing */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_prepareForProcessing(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 21 /* setProcessBuffers */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setProcessBuffers(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 22 /* command */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_command(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 23 /* setParameter */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setParameter(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 24 /* getParameter */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getParameter(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 25 /* getSupportedConfigsForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getSupportedConfigsForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 26 /* getCurrentConfigForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_getCurrentConfigForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 27 /* setCurrentConfigForFeature */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_setCurrentConfigForFeature(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 28 /* close */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwEffect::_hidl_close(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 29 /* setTargetLevel */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_setTargetLevel(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 30 /* getTargetLevel */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_getTargetLevel(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 31 /* setCompGain */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_setCompGain(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 32 /* getCompGain */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_getCompGain(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 33 /* setLimiterEnabled */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_setLimiterEnabled(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 34 /* isLimiterEnabled */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_isLimiterEnabled(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 35 /* setAllProperties */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_setAllProperties(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 36 /* getAllProperties */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::effect::V2_0::BnHwAutomaticGainControlEffect::_hidl_getAllProperties(this, _hidl_data, _hidl_reply, _hidl_cb);
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

BsAutomaticGainControlEffect::BsAutomaticGainControlEffect(const ::android::sp<::android::hardware::audio::effect::V2_0::IAutomaticGainControlEffect> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.audio.effect@2.0", "IAutomaticGainControlEffect"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsAutomaticGainControlEffect::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IAutomaticGainControlEffect> IAutomaticGainControlEffect::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwAutomaticGainControlEffect>(serviceName, false, getStub);
}

// static
::android::sp<IAutomaticGainControlEffect> IAutomaticGainControlEffect::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwAutomaticGainControlEffect>(serviceName, true, getStub);
}

::android::status_t IAutomaticGainControlEffect::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.audio.effect@2.0", "IAutomaticGainControlEffect", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IAutomaticGainControlEffect::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.audio.effect@2.0::IAutomaticGainControlEffect",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V2_0
}  // namespace effect
}  // namespace audio
}  // namespace hardware
}  // namespace android
