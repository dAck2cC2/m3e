#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICONNECTION_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICONNECTION_H

#include <android/hardware/media/bufferpool/1.0/types.h>
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
namespace bufferpool {
namespace V1_0 {

struct IConnection : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * A connection to a buffer pool which handles requests from a buffer pool
     * client. The connection must be made in order to receive buffers from
     * other buffer pool clients.
     */
    virtual bool isRemote() const override { return false; }


    using fetch_cb = std::function<void(::android::hardware::media::bufferpool::V1_0::ResultStatus status, const ::android::hardware::media::bufferpool::V1_0::Buffer& buffer)>;
    /**
     * Retrieves a buffer using bufferId. The method must be called from
     * receiving side of buffer during transferring only when the specified
     * buffer is neither cached nor used. This fails if the specified
     * transaction is not valid.
     * 
     * @param transactionId Unique transaction id for buffer transferring.
     * @param bufferId Id of the buffer to be fetched.
     * @return status The status of the call.
     *     OK               - A buffer was fetched successfully.
     *     NO_MEMORY        - Memory allocation failure occurred.
     *     NOT_FOUND        - A buffer was not found due to invalidation.
     *     CRITICAL_ERROR   - Other errors.
     * @return buffer The actual buffer which is specified with bufferId.
     */
    virtual ::android::hardware::Return<void> fetch(uint64_t transactionId, uint32_t bufferId, fetch_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IConnection>> castFrom(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IConnection>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IConnection>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IConnection> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IConnection> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IConnection> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IConnection> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IConnection> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IConnection> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IConnection> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IConnection> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IConnection>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::bufferpool::V1_0::IConnection::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace bufferpool
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICONNECTION_H
