#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BPHWMEDIACASSERVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BPHWMEDIACASSERVICE_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/cas/1.0/IHwMediaCasService.h>

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {

struct BpHwMediaCasService : public ::android::hardware::BpInterface<IMediaCasService>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwMediaCasService(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef IMediaCasService Pure;

    virtual bool isRemote() const override { return true; }

    // Methods from IMediaCasService follow.
    static ::android::hardware::Return<void>  _hidl_enumeratePlugins(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, enumeratePlugins_cb _hidl_cb);
    static ::android::hardware::Return<bool>  _hidl_isSystemIdSupported(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t CA_system_id);
    static ::android::hardware::Return<::android::sp<ICas>>  _hidl_createPlugin(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t CA_system_id, const ::android::sp<ICasListener>& listener);
    static ::android::hardware::Return<bool>  _hidl_isDescramblerSupported(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t CA_system_id);
    static ::android::hardware::Return<::android::sp<IDescramblerBase>>  _hidl_createDescrambler(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int32_t CA_system_id);

    // Methods from IMediaCasService follow.
    ::android::hardware::Return<void> enumeratePlugins(enumeratePlugins_cb _hidl_cb) override;
    ::android::hardware::Return<bool> isSystemIdSupported(int32_t CA_system_id) override;
    ::android::hardware::Return<::android::sp<ICas>> createPlugin(int32_t CA_system_id, const ::android::sp<ICasListener>& listener) override;
    ::android::hardware::Return<bool> isDescramblerSupported(int32_t CA_system_id) override;
    ::android::hardware::Return<::android::sp<IDescramblerBase>> createDescrambler(int32_t CA_system_id) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V1_0
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BPHWMEDIACASSERVICE_H
