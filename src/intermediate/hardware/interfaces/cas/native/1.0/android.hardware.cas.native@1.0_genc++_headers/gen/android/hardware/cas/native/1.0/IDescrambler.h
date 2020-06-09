#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_IDESCRAMBLER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_IDESCRAMBLER_H

#include <android/hardware/cas/native/1.0/types.h>
#include <android/hardware/cas/1.0/IDescramblerBase.h>
#include <android/hardware/cas/1.0/types.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace cas {
namespace native {
namespace V1_0 {

struct IDescrambler : public ::android::hardware::cas::V1_0::IDescramblerBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * IDescrambler is the native plugin API for descrambling operations.
     */
    virtual bool isRemote() const override { return false; }


    /**
     * Associate a MediaCas session with this MediaDescrambler instance.
     * 
     * @param sessionId the id of the session to associate with this descrambler instance.
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> setMediaCasSession(const ::android::hardware::hidl_vec<uint8_t>& sessionId) = 0;

    /**
     * Query if the scrambling scheme requires the use of a secure decoder
     * to decode data of the given mime type.
     * 
     * @param mime the mime type of the media data.
     * @return result whether the descrambler requires a secure decoder.
     */
    virtual ::android::hardware::Return<bool> requiresSecureDecoderComponent(const ::android::hardware::hidl_string& mime) = 0;

    /**
     * Release the descrambler instance.
     * 
     * @return status the status of the call.
     */
    virtual ::android::hardware::Return<::android::hardware::cas::V1_0::Status> release() = 0;

    using descramble_cb = std::function<void(::android::hardware::cas::V1_0::Status status, uint32_t bytesWritten, const ::android::hardware::hidl_string& detailedError)>;
    /**
     * Descramble the data in a source SharedBuffer, described by an array of
     * SubSample structures.
     * 
     * @param scramblingControl an enumeration indicating the key that the subsamples
     * were scrambled with.
     * @param subSamples an array of SubSample structures describing the number of
     * clear and scrambled bytes within each subsample.
     * @param srcBuffer the SharedBuffer containing the source scrambled data.
     * @param srcOffset the position where the source scrambled data starts at.
     * @param dstBuffer the DestinationBuffer to hold the descrambled data.
     * @param dstOffset the position where the descrambled data should start at.
     * 
     * @return status the status of the call.
     * @return bytesWritten number of bytes that have been successfully descrambled.
     * @return detailedError a detailed message describing the error (if any).
     */
    virtual ::android::hardware::Return<void> descramble(::android::hardware::cas::native::V1_0::ScramblingControl scramblingControl, const ::android::hardware::hidl_vec<::android::hardware::cas::native::V1_0::SubSample>& subSamples, const ::android::hardware::cas::native::V1_0::SharedBuffer& srcBuffer, uint64_t srcOffset, const ::android::hardware::cas::native::V1_0::DestinationBuffer& dstBuffer, uint64_t dstOffset, descramble_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::cas::native::V1_0::IDescrambler>> castFrom(const ::android::sp<::android::hardware::cas::native::V1_0::IDescrambler>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::cas::native::V1_0::IDescrambler>> castFrom(const ::android::sp<::android::hardware::cas::V1_0::IDescramblerBase>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::cas::native::V1_0::IDescrambler>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IDescrambler> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDescrambler> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IDescrambler> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IDescrambler> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IDescrambler> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDescrambler> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IDescrambler> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IDescrambler> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::cas::native::V1_0::IDescrambler>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::cas::native::V1_0::IDescrambler::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace native
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_IDESCRAMBLER_H
