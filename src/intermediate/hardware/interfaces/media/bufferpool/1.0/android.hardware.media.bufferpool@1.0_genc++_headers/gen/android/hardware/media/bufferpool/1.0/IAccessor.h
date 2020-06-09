#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_IACCESSOR_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_IACCESSOR_H

#include <android/hardware/media/bufferpool/1.0/IConnection.h>
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

struct IAccessor : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * IAccessor creates IConnection which is used from IClientManager in order to
     * use functionality of the specified buffer pool.
     */
    virtual bool isRemote() const override { return false; }


    using connect_cb = std::function<void(::android::hardware::media::bufferpool::V1_0::ResultStatus status, const ::android::sp<::android::hardware::media::bufferpool::V1_0::IConnection>& connection, int64_t connectionId, const ::android::hardware::MQDescriptorSync<::android::hardware::media::bufferpool::V1_0::BufferStatusMessage>& mqDesc)>;
    /**
     * Registers a new client and creates IConnection to the buffer pool for
     * the client. IConnection and FMQ are used by IClientManager in order to
     * communicate with the buffer pool. Via FMQ IClientManager sends
     * BufferStatusMesage(s) to the buffer pool.
     * 
     * FMQ is used to send buffer ownership status changes to a buffer pool
     * from a buffer pool client. A buffer pool synchronizes FMQ messages when
     * there is a hidl request from the clients. Every client has its own
     * connection and FMQ to communicate with the buffer pool. So sending an
     * FMQ message on behalf of other clients is not possible.
     * 
     * FMQ messages are sent when a buffer is acquired or released. Also, FMQ
     * messages are sent when a buffer is transferred from a client to another
     * client. FMQ has its own ID from a buffer pool. A client is specified
     * with the ID.
     * 
     * To transfer a buffer, a sender must send an FMQ message. The message
     * must include a receiver's ID and a transaction ID. A receiver must send
     * the transaction ID to fetch a buffer from a buffer pool. Since the
     * sender already registered the receiver via an FMQ message, The buffer
     * pool must verify the receiver with the transaction ID. In order to
     * prevent faking a receiver, a connection to a buffer pool from client is
     * made and kept private. Also part of transaction ID is a sender ID in
     * order to prevent fake transactions from other clients. This must be
     * verified with an FMQ message from a buffer pool.
     * 
     * @return status The status of the call.
     *     OK               - A connection is made successfully.
     *     NO_MEMORY        - Memory allocation failure occurred.
     *     ALREADY_EXISTS   - A connection was already made.
     *     CRITICAL_ERROR   - Other errors.
     * @return connection The IConnection have interfaces
     *     to get shared buffers from the buffer pool.
     * @return connectionId Id of IConnection. The Id identifies
     *     sender and receiver in FMQ messages during buffer transfer.
     * @return mqDesc FMQ descriptor. The descriptor can be used to
     *     send/receive FMQ messages.
     */
    virtual ::android::hardware::Return<void> connect(connect_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IAccessor>> castFrom(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IAccessor>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IAccessor>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IAccessor> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IAccessor> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IAccessor> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IAccessor> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IAccessor> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IAccessor> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IAccessor> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IAccessor> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IAccessor>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::bufferpool::V1_0::IAccessor::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace bufferpool
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_IACCESSOR_H
