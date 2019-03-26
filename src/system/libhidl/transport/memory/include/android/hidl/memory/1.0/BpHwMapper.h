#ifndef HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_BPHWMAPPER_H
#define HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_BPHWMAPPER_H

#include <hidl/HidlTransportSupport.h>

#include <android/hidl/memory/1.0/IHwMapper.h>

namespace android {
namespace hidl {
namespace memory {
namespace V1_0 {

struct BpHwMapper : public ::android::hardware::BpInterface<IMapper>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwMapper(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef IMapper Pure;

    virtual bool isRemote() const override { return true; }

    // Methods from IMapper follow.
    static ::android::hardware::Return<::android::sp<IMemory>>  _hidl_mapMemory(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_memory& mem);

    // Methods from IMapper follow.
    ::android::hardware::Return<::android::sp<IMemory>> mapMemory(const ::android::hardware::hidl_memory& mem) override;

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
}  // namespace memory
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_MEMORY_V1_0_BPHWMAPPER_H
