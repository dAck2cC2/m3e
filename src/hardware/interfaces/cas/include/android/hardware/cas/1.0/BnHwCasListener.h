#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BNHWCASLISTENER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BNHWCASLISTENER_H

#include <android/hardware/cas/1.0/IHwCasListener.h>

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {

struct BnHwCasListener : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwCasListener(const ::android::sp<ICasListener> &_hidl_impl);
    explicit BnHwCasListener(const ::android::sp<ICasListener> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwCasListener();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    typedef ICasListener Pure;

    ::android::sp<ICasListener> getImpl() { return _hidl_mImpl; };
    // Methods from ICasListener follow.
    static ::android::status_t _hidl_onEvent(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ICasListener follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<ICasListener> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_BNHWCASLISTENER_H
