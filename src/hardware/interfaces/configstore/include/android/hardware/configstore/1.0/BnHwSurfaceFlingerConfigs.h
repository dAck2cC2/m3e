#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_BNHWSURFACEFLINGERCONFIGS_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_BNHWSURFACEFLINGERCONFIGS_H

#include <android/hardware/configstore/1.0/IHwSurfaceFlingerConfigs.h>

namespace android {
namespace hardware {
namespace configstore {
namespace V1_0 {

struct BnHwSurfaceFlingerConfigs : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwSurfaceFlingerConfigs(const ::android::sp<ISurfaceFlingerConfigs> &_hidl_impl);
    explicit BnHwSurfaceFlingerConfigs(const ::android::sp<ISurfaceFlingerConfigs> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwSurfaceFlingerConfigs();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    typedef ISurfaceFlingerConfigs Pure;

    ::android::sp<ISurfaceFlingerConfigs> getImpl() { return _hidl_mImpl; };
    // Methods from ISurfaceFlingerConfigs follow.
    static ::android::status_t _hidl_vsyncEventPhaseOffsetNs(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_vsyncSfEventPhaseOffsetNs(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_useContextPriority(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_hasWideColorDisplay(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_hasHDRDisplay(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_presentTimeOffsetFromVSyncNs(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_useHwcForRGBtoYUV(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_maxVirtualDisplaySize(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_hasSyncFramework(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_useVrFlinger(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_maxFrameBufferAcquiredBuffers(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);


    static ::android::status_t _hidl_startGraphicsAllocatorService(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ISurfaceFlingerConfigs follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<ISurfaceFlingerConfigs> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace configstore
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_BNHWSURFACEFLINGERCONFIGS_H
