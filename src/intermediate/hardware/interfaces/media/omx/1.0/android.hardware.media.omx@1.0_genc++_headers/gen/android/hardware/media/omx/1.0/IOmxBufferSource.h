#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXBUFFERSOURCE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXBUFFERSOURCE_H

#include <android/hardware/media/omx/1.0/types.h>
#include <android/hardware/media/1.0/types.h>
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

struct IOmxBufferSource : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * Ref: frameworks/av/media/libmedia/aidl/android/IOMXBufferSource.aidl
     * 
     * IOmxBufferSource is an interface for a listener for certain events from an
     * IOmxNode instance. Use IOmxNode::setInputSurface() to attach an
     * IOmxBufferSource instance to an IOmxNode instance.
     * 
     * @see OMX_STATETYPE in the OpenMax IL standard.
     */
    virtual bool isRemote() const override { return false; }


    /**
     * onOmxExecuting() is invoked when the node state changes to
     * OMX_StateExecuting state.
     */
    virtual ::android::hardware::Return<void> onOmxExecuting() = 0;

    /**
     * onOmxIdle() is invoked when the node transitions from OMX_StateExecuting
     * to OMX_StateIdle.
     */
    virtual ::android::hardware::Return<void> onOmxIdle() = 0;

    /**
     * onOmxLoaded() is invoked when the node transitions from OMX_StateIdle or
     * OMX_StateExecuting to OMX_StateLoaded.
     */
    virtual ::android::hardware::Return<void> onOmxLoaded() = 0;

    /**
     * onInputBufferAdded() is invoked after a new input buffer is added to the
     * node. This may happen within IOmxNode::allocateSecureBuffer() or
     * IOmxNode::useBuffer().
     * 
     * @param[in] buffer is the id of the added buffer.
     */
    virtual ::android::hardware::Return<void> onInputBufferAdded(uint32_t buffer) = 0;

    /**
     * onInputBufferEmptied() is invoked after an input buffer is emptied. This
     * may happen within IOmxNode::emptyBuffer().
     * 
     * @param[in] buffer is the id of the emptied buffer.
     * @param[in] fence is the fence associated with the buffer.
     */
    virtual ::android::hardware::Return<void> onInputBufferEmptied(uint32_t buffer, const ::android::hardware::hidl_handle& fence) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmxBufferSource>> castFrom(const ::android::sp<::android::hardware::media::omx::V1_0::IOmxBufferSource>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmxBufferSource>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IOmxBufferSource> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmxBufferSource> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IOmxBufferSource> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IOmxBufferSource> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IOmxBufferSource> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmxBufferSource> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IOmxBufferSource> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IOmxBufferSource> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::media::omx::V1_0::IOmxBufferSource>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::omx::V1_0::IOmxBufferSource::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXBUFFERSOURCE_H
