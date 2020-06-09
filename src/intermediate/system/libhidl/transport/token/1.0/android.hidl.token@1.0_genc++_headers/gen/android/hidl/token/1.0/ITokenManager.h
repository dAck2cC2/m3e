#ifndef HIDL_GENERATED_ANDROID_HIDL_TOKEN_V1_0_ITOKENMANAGER_H
#define HIDL_GENERATED_ANDROID_HIDL_TOKEN_V1_0_ITOKENMANAGER_H

#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hidl {
namespace token {
namespace V1_0 {

struct ITokenManager : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * This facilitates converting hidl interfaces into something that
     * are more easily transferrable to other processes.
     */
    virtual bool isRemote() const override { return false; }


    using createToken_cb = std::function<void(const ::android::hardware::hidl_vec<uint8_t>& token)>;
    /**
     * Register an interface. The server must keep a strong reference
     * to the interface until the token is destroyed by calling unregister.
     * 
     * Must return empty token on failure.
     * 
     * @param store Interface which can later be fetched with the returned token.
     * @return token Opaque value which may be used as inputs to other functions.
     */
    virtual ::android::hardware::Return<void> createToken(const ::android::sp<::android::hidl::base::V1_0::IBase>& store, createToken_cb _hidl_cb) = 0;

    /**
     * Destory a token and the strong reference to the associated interface.
     * 
     * @param token Token received from createToken
     * @return success Whether or not the token was successfully unregistered.
     */
    virtual ::android::hardware::Return<bool> unregister(const ::android::hardware::hidl_vec<uint8_t>& token) = 0;

    /**
     * Fetch an interface from a provided token.
     * 
     * @param token Token received from createToken
     * @return store Interface registered with createToken and the corresponding
     *               token or nullptr.
     */
    virtual ::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>> get(const ::android::hardware::hidl_vec<uint8_t>& token) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hidl::token::V1_0::ITokenManager>> castFrom(const ::android::sp<::android::hidl::token::V1_0::ITokenManager>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hidl::token::V1_0::ITokenManager>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<ITokenManager> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ITokenManager> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<ITokenManager> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<ITokenManager> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<ITokenManager> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ITokenManager> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<ITokenManager> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<ITokenManager> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hidl::token::V1_0::ITokenManager>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hidl::token::V1_0::ITokenManager::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace token
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_TOKEN_V1_0_ITOKENMANAGER_H
