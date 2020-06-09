#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICLIENTMANAGER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICLIENTMANAGER_H

#include <android/hardware/media/bufferpool/1.0/IAccessor.h>
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

struct IClientManager : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * IClientManager manages IConnection(s) inside a process. A locally
     * created IConnection represents a communication node(receiver) with the
     * specified buffer pool(IAccessor).
     * IConnection(s) are not exposed to other processes(IClientManager).
     * IClientManager instance must be unique within a process.
     */
    virtual bool isRemote() const override { return false; }


    using registerSender_cb = std::function<void(::android::hardware::media::bufferpool::V1_0::ResultStatus status, int64_t connectionId)>;
    /**
     * Sets up a buffer receiving communication node for the specified
     * buffer pool. A manager must create a IConnection to the buffer
     * pool if it does not already have a connection.
     * 
     * @param bufferPool a buffer pool which is specified with the IAccessor.
     *     The specified buffer pool is the owner of received buffers.
     * @return status The status of the call.
     *     OK               - A sender was set successfully.
     *     NO_MEMORY        - Memory allocation failure occurred.
     *     ALREADY_EXISTS   - A sender was registered already.
     *     CRITICAL_ERROR   - Other errors.
     * @return connectionId the Id of the communication node to the buffer pool.
     *     This id is used in FMQ to notify IAccessor that a buffer has been
     *     sent to that connection during transfers.
     */
    virtual ::android::hardware::Return<void> registerSender(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IAccessor>& bufferPool, registerSender_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IClientManager>> castFrom(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IClientManager>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::bufferpool::V1_0::IClientManager>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IClientManager> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IClientManager> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IClientManager> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IClientManager> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IClientManager> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IClientManager> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IClientManager> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IClientManager> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::media::bufferpool::V1_0::IClientManager>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::bufferpool::V1_0::IClientManager::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace bufferpool
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_BUFFERPOOL_V1_0_ICLIENTMANAGER_H
