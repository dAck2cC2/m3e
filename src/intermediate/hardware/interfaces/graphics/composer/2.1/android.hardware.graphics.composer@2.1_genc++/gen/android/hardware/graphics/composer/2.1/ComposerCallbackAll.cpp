#define LOG_TAG "android.hardware.graphics.composer@2.1::ComposerCallback"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#if 0 /* M3E: */
#include <android/hardware/graphics/composer/2.1/BpHwComposerCallback.h>
#include <android/hardware/graphics/composer/2.1/BnHwComposerCallback.h>
#include <android/hardware/graphics/composer/2.1/BsComposerCallback.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#else
#include <android/hardware/graphics/composer/2.1/IComposerCallback.h>
#endif
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

const char* IComposerCallback::descriptor("android.hardware.graphics.composer@2.1::IComposerCallback");
#if 0 /* M3E: */
__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IComposerCallback::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwComposerCallback(static_cast<IComposerCallback *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IComposerCallback::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsComposerCallback(static_cast<IComposerCallback *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IComposerCallback::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IComposerCallback::descriptor);
};
#endif
// Methods from ::android::hardware::graphics::composer::V2_1::IComposerCallback follow.
// no default implementation for: ::android::hardware::Return<void> IComposerCallback::onHotplug(uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection connected)
// no default implementation for: ::android::hardware::Return<void> IComposerCallback::onRefresh(uint64_t display)
// no default implementation for: ::android::hardware::Return<void> IComposerCallback::onVsync(uint64_t display, int64_t timestamp)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IComposerCallback::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::graphics::composer::V2_1::IComposerCallback::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IComposerCallback::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IComposerCallback::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::graphics::composer::V2_1::IComposerCallback::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IComposerCallback::getHashChain(getHashChain_cb _hidl_cb){
#if 0
    _hidl_cb({
        (uint8_t[32]){177,157,0,235,138,139,59,0,52,160,50,31,34,232,243,33,98,191,76,42,235,188,230,218,34,192,37,245,110,69,158,162} /* b19d00eb8a8b3b0034a0321f22e8f32162bf4c2aebbce6da22c025f56e459ea2 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
#endif
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IComposerCallback::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IComposerCallback::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IComposerCallback::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IComposerCallback::getDebugInfo(getDebugInfo_cb _hidl_cb){
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

::android::hardware::Return<void> IComposerCallback::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IComposerCallback::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>> IComposerCallback::castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>> IComposerCallback::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
#if 0 /* M3E: */
    return ::android::hardware::details::castInterface<IComposerCallback, ::android::hidl::base::V1_0::IBase, BpHwComposerCallback>(
            parent, "android.hardware.graphics.composer@2.1::IComposerCallback", emitError);
#else
    return nullptr;
#endif
}

#if 0 /* M3E: */
BpHwComposerCallback::BpHwComposerCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IComposerCallback>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.graphics.composer@2.1", "IComposerCallback") {
}

// Methods from ::android::hardware::graphics::composer::V2_1::IComposerCallback follow.
::android::hardware::Return<void> BpHwComposerCallback::_hidl_onHotplug(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection connected) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onHotplug::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        _hidl_args.push_back((void *)&connected);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onHotplug", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwComposerCallback::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint64(display);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt32((int32_t)connected);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(1 /* onHotplug */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onHotplug", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwComposerCallback::_hidl_onRefresh(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint64_t display) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onRefresh::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onRefresh", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwComposerCallback::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint64(display);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(2 /* onRefresh */, _hidl_data, &_hidl_reply, 1 /* oneway */);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onRefresh", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}

::android::hardware::Return<void> BpHwComposerCallback::_hidl_onVsync(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, uint64_t display, int64_t timestamp) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onVsync::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        _hidl_args.push_back((void *)&timestamp);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onVsync", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwComposerCallback::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeUint64(display);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt64(timestamp);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(3 /* onVsync */, _hidl_data, &_hidl_reply, 1 /* oneway */);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onVsync", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::android::hardware::graphics::composer::V2_1::IComposerCallback follow.
::android::hardware::Return<void> BpHwComposerCallback::onHotplug(uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection connected){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::graphics::composer::V2_1::BpHwComposerCallback::_hidl_onHotplug(this, this, display, connected);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::onRefresh(uint64_t display){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::graphics::composer::V2_1::BpHwComposerCallback::_hidl_onRefresh(this, this, display);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::onVsync(uint64_t display, int64_t timestamp){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::graphics::composer::V2_1::BpHwComposerCallback::_hidl_onVsync(this, this, display, timestamp);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwComposerCallback::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwComposerCallback::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwComposerCallback::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwComposerCallback::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwComposerCallback::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwComposerCallback::BnHwComposerCallback(const ::android::sp<IComposerCallback> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.graphics.composer@2.1", "IComposerCallback") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwComposerCallback::~BnHwComposerCallback() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::graphics::composer::V2_1::IComposerCallback follow.
::android::status_t BnHwComposerCallback::_hidl_onHotplug(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwComposerCallback::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint64_t display;
    ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection connected;

    _hidl_err = _hidl_data.readUint64(&display);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readInt32((int32_t *)&connected);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onHotplug::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        _hidl_args.push_back((void *)&connected);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onHotplug", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    static_cast<IComposerCallback*>(_hidl_this->getImpl().get())->onHotplug(display, connected);

    (void) _hidl_cb;

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onHotplug", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    return _hidl_err;
}

::android::status_t BnHwComposerCallback::_hidl_onRefresh(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwComposerCallback::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint64_t display;

    _hidl_err = _hidl_data.readUint64(&display);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onRefresh::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onRefresh", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    static_cast<IComposerCallback*>(_hidl_this->getImpl().get())->onRefresh(display);

    (void) _hidl_cb;

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onRefresh", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    return _hidl_err;
}

::android::status_t BnHwComposerCallback::_hidl_onVsync(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwComposerCallback::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    uint64_t display;
    int64_t timestamp;

    _hidl_err = _hidl_data.readUint64(&display);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readInt64(&timestamp);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IComposerCallback::onVsync::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&display);
        _hidl_args.push_back((void *)&timestamp);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onVsync", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    static_cast<IComposerCallback*>(_hidl_this->getImpl().get())->onVsync(display, timestamp);

    (void) _hidl_cb;

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.graphics.composer", "2.1", "IComposerCallback", "onVsync", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    return _hidl_err;
}


// Methods from ::android::hardware::graphics::composer::V2_1::IComposerCallback follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwComposerCallback::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwComposerCallback::getDebugInfo(getDebugInfo_cb _hidl_cb) {
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

::android::status_t BnHwComposerCallback::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* onHotplug */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::graphics::composer::V2_1::BnHwComposerCallback::_hidl_onHotplug(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* onRefresh */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != true) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::graphics::composer::V2_1::BnHwComposerCallback::_hidl_onRefresh(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* onVsync */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != true) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::graphics::composer::V2_1::BnHwComposerCallback::_hidl_onVsync(this, _hidl_data, _hidl_reply, _hidl_cb);
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

BsComposerCallback::BsComposerCallback(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.graphics.composer@2.1", "IComposerCallback"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsComposerCallback::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IComposerCallback> IComposerCallback::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwComposerCallback>(serviceName, false, getStub);
}

// static
::android::sp<IComposerCallback> IComposerCallback::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwComposerCallback>(serviceName, true, getStub);
}

::android::status_t IComposerCallback::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.graphics.composer@2.1", "IComposerCallback", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IComposerCallback::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.graphics.composer@2.1::IComposerCallback",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");
#endif

}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android
