#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BNHWOMXBUFFERSOURCE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BNHWOMXBUFFERSOURCE_H

#include <android/hardware/media/omx/1.0/IHwOmxBufferSource.h>

namespace android {
namespace hardware {
namespace media {
namespace omx {
namespace V1_0 {

struct BnHwOmxBufferSource : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwOmxBufferSource(const ::android::sp<IOmxBufferSource> &_hidl_impl);
    explicit BnHwOmxBufferSource(const ::android::sp<IOmxBufferSource> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwOmxBufferSource();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    typedef IOmxBufferSource Pure;

    ::android::sp<IOmxBufferSource> getImpl() { return _hidl_mImpl; };
    // Methods from IOmxBufferSource follow.
    static ::android::status_t _hidl_onOmxExecuting(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_onOmxIdle(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_onOmxLoaded(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_onInputBufferAdded(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_onInputBufferEmptied(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from IOmxBufferSource follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IOmxBufferSource> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_BNHWOMXBUFFERSOURCE_H