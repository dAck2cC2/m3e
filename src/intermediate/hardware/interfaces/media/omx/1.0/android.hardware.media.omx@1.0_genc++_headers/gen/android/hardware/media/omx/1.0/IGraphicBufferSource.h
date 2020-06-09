#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IGRAPHICBUFFERSOURCE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IGRAPHICBUFFERSOURCE_H

#include <android/hardware/graphics/common/1.0/types.h>
#include <android/hardware/media/omx/1.0/IOmxNode.h>
#include <android/hardware/media/omx/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace media {
namespace omx {
namespace V1_0 {

struct IGraphicBufferSource : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * Ref: frameworks/av/media/libmedia/aidl/android/IGraphicBufferSource.aidl
     * 
     * TODO: Add documentations.
     */
    virtual bool isRemote() const override { return false; }


    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> configure(const ::android::sp<::android::hardware::media::omx::V1_0::IOmxNode>& omxNode, ::android::hardware::graphics::common::V1_0::Dataspace dataspace) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setSuspend(bool suspend, int64_t timeUs) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setRepeatPreviousFrameDelayUs(int64_t repeatAfterUs) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setMaxFps(float maxFps) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setTimeLapseConfig(double fps, double captureFps) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setStartTimeUs(int64_t startTimeUs) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setStopTimeUs(int64_t stopTimeUs) = 0;

    using getStopTimeOffsetUs_cb = std::function<void(::android::hardware::media::omx::V1_0::Status status, int64_t stopTimeOffsetUs)>;
    virtual ::android::hardware::Return<void> getStopTimeOffsetUs(getStopTimeOffsetUs_cb _hidl_cb) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setColorAspects(const ::android::hardware::media::omx::V1_0::ColorAspects& aspects) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> setTimeOffsetUs(int64_t timeOffsetUs) = 0;

    virtual ::android::hardware::Return<::android::hardware::media::omx::V1_0::Status> signalEndOfInputStream() = 0;

    using interfaceChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)>;
    virtual ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;

    using interfaceDescriptor_cb = std::function<void(const ::android::hardware::hidl_string& descriptor)>;
    virtual ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;

    using getHashChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_array<uint8_t, 32>>& hashchain)>;
    virtual ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> setHALInstrumentation() override;

    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;

    virtual ::android::hardware::Return<void> ping() override;

    using getDebugInfo_cb = std::function<void(const ::android::hidl::base::V1_0::DebugInfo& info)>;
    virtual ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> notifySyspropsChanged() override;

    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;
    // cast static functions
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IGraphicBufferSource>> castFrom(const ::android::sp<::android::hardware::media::omx::V1_0::IGraphicBufferSource>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IGraphicBufferSource>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IGraphicBufferSource> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IGraphicBufferSource> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IGraphicBufferSource> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IGraphicBufferSource> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IGraphicBufferSource> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IGraphicBufferSource> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IGraphicBufferSource> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IGraphicBufferSource> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::media::omx::V1_0::IGraphicBufferSource>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::omx::V1_0::IGraphicBufferSource::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IGRAPHICBUFFERSOURCE_H
