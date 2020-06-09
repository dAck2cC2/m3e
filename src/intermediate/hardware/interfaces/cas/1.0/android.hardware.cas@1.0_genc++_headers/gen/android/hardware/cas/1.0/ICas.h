#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_ICAS_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_ICAS_H

#include <android/hardware/cas/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {

struct ICas : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * ICas is the API to control the cas system and is accessible from both
     * Java and native level. It is used to manage sessions, provision/refresh
     * the cas system, and process the EMM/ECM messages. It also allows bi-directional,
     * scheme-specific communications between the client and the cas system.
     */
    virtual bool isRemote() const override { return false; }


    /**
     * Provide the CA private data from a CA_descriptor in the conditional
     * access table to a CasPlugin.
     * 
     * @param pvtData a byte array containing the private data, the format of
     * which is scheme-specific and opaque to the framework.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> setPrivateData(const ::android::hardware::hidl_vec<uint8_t>& pvtData) = 0;

    using openSession_cb = std::function<void(::android::hardware::cas::V1_0::Status status, const ::android::hardware::hidl_vec<uint8_t>& sessionId)>;
    /**
     * Open a session to descramble one or more streams scrambled by the
     * conditional access system.
     * 
     * @return status the status of the call.
     * @return sessionId the id of the newly opened session.
     */
    virtual ::android::hardware::Return<void> openSession(openSession_cb _hidl_cb) = 0;

    /**
     * Close a session.
     * 
     * @param sessionId the id of the session to be closed.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> closeSession(const ::android::hardware::hidl_vec<uint8_t>& sessionId) = 0;

    /**
     * Provide the CA private data from a CA_descriptor in the program map
     * table to a session.
     * 
     * @param sessionId the id of the session which the private data applies to.
     * @param pvtData a byte array containing the private data, the format of
     * which is scheme-specific and opaque to the framework.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> setSessionPrivateData(const ::android::hardware::hidl_vec<uint8_t>& sessionId, const ::android::hardware::hidl_vec<uint8_t>& pvtData) = 0;

    /**
     * Process an ECM from the ECM stream for this session’s elementary stream.
     * 
     * @param sessionId the id of the session which the ecm data applies to.
     * @param ecm a byte array containing the ecm data.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> processEcm(const ::android::hardware::hidl_vec<uint8_t>& sessionId, const ::android::hardware::hidl_vec<uint8_t>& ecm) = 0;

    /**
     * Process an in-band EMM from the EMM stream.
     * 
     * @param emm a byte array containing the emm data.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> processEmm(const ::android::hardware::hidl_vec<uint8_t>& emm) = 0;

    /**
     * Send an scheme-specific event to the CasPlugin.
     * 
     * @param event an integer denoting a scheme-specific event to be sent.
     * @param arg a scheme-specific integer argument for the event.
     * @param data a byte array containing scheme-specific data for the event.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> sendEvent(int32_t event, int32_t arg, const ::android::hardware::hidl_vec<uint8_t>& eventData) = 0;

    /**
     * Initiate a provisioning operation for a CA system.
     * 
     * @param provisionString string containing information needed for the
     * provisioning operation, the format of which is scheme and implementation
     * specific.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> provision(const ::android::hardware::hidl_string& provisionString) = 0;

    /**
     * Notify the CA system to refresh entitlement keys.
     * 
     * @param refreshType the type of the refreshment.
     * @param refreshData private data associated with the refreshment.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> refreshEntitlements(int32_t refreshType, const ::android::hardware::hidl_vec<uint8_t>& refreshData) = 0;

    /**
     * Release the descrambler instance.
     * 
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> release() = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::cas::V1_0::ICas>> castFrom(const ::android::sp<::android::hardware::cas::V1_0::ICas>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::cas::V1_0::ICas>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<ICas> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ICas> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<ICas> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<ICas> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<ICas> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ICas> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<ICas> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<ICas> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::cas::V1_0::ICas>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::cas::V1_0::ICas::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_ICAS_H
