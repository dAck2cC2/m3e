#define LOG_TAG "android.hardware.audio@2.0::DevicesFactory"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#if 0 // M3E:
#include <android/hardware/audio/2.0/BpHwDevicesFactory.h>
#include <android/hardware/audio/2.0/BnHwDevicesFactory.h>
#include <android/hardware/audio/2.0/BsDevicesFactory.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#else
#include <android/hardware/audio/2.0/IDevicesFactory.h>
#endif
#include <hidl/ServiceManagement.h>

namespace android {
namespace hardware {
namespace audio {
namespace V2_0 {

const char* IDevicesFactory::descriptor("android.hardware.audio@2.0::IDevicesFactory");
#if 0 // M3E:
__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IDevicesFactory::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwDevicesFactory(static_cast<IDevicesFactory *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IDevicesFactory::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsDevicesFactory(static_cast<IDevicesFactory *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IDevicesFactory::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IDevicesFactory::descriptor);
};
#endif
// Methods from ::android::hardware::audio::V2_0::IDevicesFactory follow.
// no default implementation for: ::android::hardware::Return<void> IDevicesFactory::openDevice(::android::hardware::audio::V2_0::IDevicesFactory::Device device, openDevice_cb _hidl_cb)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IDevicesFactory::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hardware::audio::V2_0::IDevicesFactory::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IDevicesFactory::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IDevicesFactory::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hardware::audio::V2_0::IDevicesFactory::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IDevicesFactory::getHashChain(getHashChain_cb _hidl_cb){
#if 0 // M3E:
    _hidl_cb({
        (uint8_t[32]){77,87,156,174,28,216,122,120,63,212,146,51,225,12,231,32,186,24,60,253,29,92,205,128,20,158,105,222,92,28,115,98} /* 4d579cae1cd87a783fd49233e10ce720ba183cfd1d5ccd80149e69de5c1c7362 */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
#endif
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IDevicesFactory::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IDevicesFactory::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IDevicesFactory::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IDevicesFactory::getDebugInfo(getDebugInfo_cb _hidl_cb){
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

::android::hardware::Return<void> IDevicesFactory::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IDevicesFactory::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IDevicesFactory>> IDevicesFactory::castFrom(const ::android::sp<::android::hardware::audio::V2_0::IDevicesFactory>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hardware::audio::V2_0::IDevicesFactory>> IDevicesFactory::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
#if 0
    return ::android::hardware::details::castInterface<IDevicesFactory, ::android::hidl::base::V1_0::IBase, BpHwDevicesFactory>(
            parent, "android.hardware.audio@2.0::IDevicesFactory", emitError);
#else
    return nullptr;
#endif
}
#if 0 // M3E:
BpHwDevicesFactory::BpHwDevicesFactory(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IDevicesFactory>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.audio@2.0", "IDevicesFactory") {
}

// Methods from ::android::hardware::audio::V2_0::IDevicesFactory follow.
::android::hardware::Return<void> BpHwDevicesFactory::_hidl_openDevice(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, ::android::hardware::audio::V2_0::IDevicesFactory::Device device, openDevice_cb _hidl_cb) {
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

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IDevicesFactory::openDevice::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hardware.audio", "2.0", "IDevicesFactory", "openDevice", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    ::android::hardware::audio::V2_0::Result _hidl_out_retval;
    ::android::sp<::android::hardware::audio::V2_0::IDevice> _hidl_out_result;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwDevicesFactory::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt32((int32_t)device);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(1 /* openDevice */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readInt32((int32_t *)&_hidl_out_retval);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    {
        ::android::sp<::android::hardware::IBinder> _hidl_binder;
        _hidl_err = _hidl_reply.readNullableStrongBinder(&_hidl_binder);
        if (_hidl_err != ::android::OK) { goto _hidl_error; }

        _hidl_out_result = ::android::hardware::fromBinder<::android::hardware::audio::V2_0::IDevice,::android::hardware::audio::V2_0::BpHwDevice,::android::hardware::audio::V2_0::BnHwDevice>(_hidl_binder);
    }

    _hidl_cb(_hidl_out_retval, _hidl_out_result);

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_retval);
        _hidl_args.push_back((void *)&_hidl_out_result);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hardware.audio", "2.0", "IDevicesFactory", "openDevice", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::android::hardware::audio::V2_0::IDevicesFactory follow.
::android::hardware::Return<void> BpHwDevicesFactory::openDevice(::android::hardware::audio::V2_0::IDevicesFactory::Device device, openDevice_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hardware::audio::V2_0::BpHwDevicesFactory::_hidl_openDevice(this, this, device, _hidl_cb);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwDevicesFactory::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwDevicesFactory::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwDevicesFactory::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwDevicesFactory::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwDevicesFactory::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwDevicesFactory::BnHwDevicesFactory(const ::android::sp<IDevicesFactory> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.audio@2.0", "IDevicesFactory") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap.get(_hidl_impl, false));
}

BnHwDevicesFactory::~BnHwDevicesFactory() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hardware::audio::V2_0::IDevicesFactory follow.
::android::status_t BnHwDevicesFactory::_hidl_openDevice(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwDevicesFactory::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    ::android::hardware::audio::V2_0::IDevicesFactory::Device device;

    _hidl_err = _hidl_data.readInt32((int32_t *)&device);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IDevicesFactory::openDevice::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&device);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hardware.audio", "2.0", "IDevicesFactory", "openDevice", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_callbackCalled = false;

    static_cast<IDevicesFactory*>(_hidl_this->getImpl().get())->openDevice(device, [&](const auto &_hidl_out_retval, const auto &_hidl_out_result) {
        if (_hidl_callbackCalled) {
            LOG_ALWAYS_FATAL("openDevice: _hidl_cb called a second time, but must be called once.");
        }
        _hidl_callbackCalled = true;

        ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

        _hidl_err = _hidl_reply->writeInt32((int32_t)_hidl_out_retval);
        /* _hidl_err ignored! */

        if (_hidl_out_result == nullptr) {
            _hidl_err = _hidl_reply->writeStrongBinder(nullptr);
        } else {
            ::android::sp<::android::hardware::IBinder> _hidl_binder = ::android::hardware::toBinder<
                    ::android::hardware::audio::V2_0::IDevice>(_hidl_out_result);
            if (_hidl_binder.get() != nullptr) {
                _hidl_err = _hidl_reply->writeStrongBinder(_hidl_binder);
            } else {
                _hidl_err = ::android::UNKNOWN_ERROR;
            }
        }
        /* _hidl_err ignored! */

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            _hidl_args.push_back((void *)&_hidl_out_result);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::SERVER_API_EXIT, "android.hardware.audio", "2.0", "IDevicesFactory", "openDevice", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        _hidl_cb(*_hidl_reply);
    });

    if (!_hidl_callbackCalled) {
        LOG_ALWAYS_FATAL("openDevice: _hidl_cb not called, but must be called once.");
    }

    return _hidl_err;
}


// Methods from ::android::hardware::audio::V2_0::IDevicesFactory follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwDevicesFactory::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwDevicesFactory::getDebugInfo(getDebugInfo_cb _hidl_cb) {
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

::android::status_t BnHwDevicesFactory::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* openDevice */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hardware::audio::V2_0::BnHwDevicesFactory::_hidl_openDevice(this, _hidl_data, _hidl_reply, _hidl_cb);
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

BsDevicesFactory::BsDevicesFactory(const ::android::sp<::android::hardware::audio::V2_0::IDevicesFactory> impl) : ::android::hardware::details::HidlInstrumentor("android.hardware.audio@2.0", "IDevicesFactory"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsDevicesFactory::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}
#endif
// static
::android::sp<IDevicesFactory> IDevicesFactory::tryGetService(const std::string &serviceName, const bool getStub) {
#if 0
    return ::android::hardware::details::getServiceInternal<BpHwDevicesFactory>(serviceName, false, getStub);
#else
    return nullptr;
#endif
}

// static
::android::sp<IDevicesFactory> IDevicesFactory::getService(const std::string &serviceName, const bool getStub) {
#if 0
    return ::android::hardware::details::getServiceInternal<BpHwDevicesFactory>(serviceName, true, getStub);
#else
    return nullptr;
#endif
}
#if 0
::android::status_t IDevicesFactory::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.audio@2.0", "IDevicesFactory", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IDevicesFactory::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hardware.audio@2.0::IDevicesFactory",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");
#endif
}  // namespace V2_0
}  // namespace audio
}  // namespace hardware
}  // namespace android