#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BPHWOMXSTORE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BPHWOMXSTORE_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/media/omx/1.0/IHwOmxStore.h>

namespace android {
namespace hardware {
namespace media {
namespace omx {
namespace V1_0 {

struct BpHwOmxStore : public ::android::hardware::BpInterface<IOmxStore>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwOmxStore(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef IOmxStore Pure;

    virtual bool isRemote() const override { return true; }

    // Methods from IOmxStore follow.
    static ::android::hardware::Return<void>  _hidl_listServiceAttributes(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, listServiceAttributes_cb _hidl_cb);
    static ::android::hardware::Return<void>  _hidl_getNodePrefix(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, getNodePrefix_cb _hidl_cb);
    static ::android::hardware::Return<void>  _hidl_listRoles(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, listRoles_cb _hidl_cb);
    static ::android::hardware::Return<::android::sp<IOmx>>  _hidl_getOmx(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_string& name);

    // Methods from IOmxStore follow.
    ::android::hardware::Return<void> listServiceAttributes(listServiceAttributes_cb _hidl_cb) override;
    ::android::hardware::Return<void> getNodePrefix(getNodePrefix_cb _hidl_cb) override;
    ::android::hardware::Return<void> listRoles(listRoles_cb _hidl_cb) override;
    ::android::hardware::Return<::android::sp<IOmx>> getOmx(const ::android::hardware::hidl_string& name) override;

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
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BPHWOMXSTORE_H
