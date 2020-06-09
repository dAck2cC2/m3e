#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXSTORE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXSTORE_H

#include <android/hardware/media/omx/1.0/IOmx.h>
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

struct IOmxStore : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * Ref: frameworks/av/include/media/IOMX.h: IOMX
     * 
     * There will be two instances of IOmxStore: "platform" and "vendor".
     * 
     * The IOmxStore service provided by the platform must present "platform" as the
     * interface name.
     * 
     * The IOmxStore service provided by the vendor must present "vendor" as the
     * instance name.
     */
    // Forward declaration for forward reference support:
    struct Attribute;
    struct NodeInfo;
    struct RoleInfo;

    /**
     * Attribute is a key-value pair of strings. The `value` member is generally
     * a stringified value of the following:
     *   enum<v1,v2,...,vn>:    v1 | v2 | ... | vn
     *   num:                   0 | [1-9][0-9]*
     *   string:                arbitrary string
     *   size:                  <num>x<num>
     *   ratio:                 <num>:<num>
     *   range<type>:           <type> | <type>-<type>
     *   list<type>:            <type> | <type>,<list<type>>
     */
    struct Attribute final {
        ::android::hardware::hidl_string key __attribute__ ((aligned(8)));
        ::android::hardware::hidl_string value __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::Attribute, key) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::Attribute, value) == 16, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::IOmxStore::Attribute) == 32, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::IOmxStore::Attribute) == 8, "wrong alignment");

    /**
     * Service attribute
     * 
     * Optional service attributes:
     *   key: 'max-video-encoder-input-buffers', value-type: num
     *   key: 'supports-multiple-secure-codecs', value-type: enum<0,1>
     *   key: 'supports-secure-with-non-secure-codec', value-type: enum<0,1>
     * 
     * For keys with prefix 'supports-', the value of 0 means "no" (not
     * supported) while the value of 1 means "yes" (supported).
     */
    typedef ::android::hardware::media::omx::V1_0::IOmxStore::Attribute ServiceAttribute;

    /**
     * Node attribute
     * 
     * Optional node attributes to describe supported values:
     *   key: 'bitrate-range', value-type: range<num>
     *   key: 'max-concurrent-instances', value-type: num
     *   key: 'max-supported-instances', value-type: num
     * 
     * Optional node attributes for audio nodes to describe supported values:
     *   key: 'max-channel-count', value-type: num
     *   key: 'sample-rate-ranges', value-type: list<range<num>>
     * 
     * Optional node attributes for video nodes to describe supported values:
     *   key: 'alignment', value-type: size
     *   key: 'block-aspect-ratio-range', value-type: range<ratio>
     *   key: 'block-count-range', value-type: range<num>
     *   key: 'block-size', value-type: size
     *   key: 'blocks-per-second-range', value-type: range<num>
     *   key: 'feature-can-swap-width-height', value-type: enum<0,1>
     *   key: 'frame-rate-range', value-type: range<num>
     *   key: 'pixel-aspect-ratio-range', value-type: range<ratio>
     *   key: 'size-range', value-type: range<size>
     * 
     * Required node attributes for video nodes that are required by Android to
     * describe measured values for this device:
     *   key: 'measured-frame-rate-<width>x<height>-range',
     *     value-type: range<num>; where width: num, height: num
     * 
     * Optional node attributes for decoders to describe supported values:
     *   key: 'feature-adaptive-playback', value: enum<0,1>
     *   key: 'feature-secure-playback', value: enum<0,1>
     *   key: 'feature-tunneled-playback', value: enum<0,1>
     * 
     * Optional node attributes for video decoders to describe supported values:
     *   key: 'feature-partial-frame', value: enum<0,1>
     * 
     * Optional node attributes for encoders to describe supported values:
     *   key: 'complexity-default', value-type: num
     *   key: 'complexity-range', value-type: range<num>
     *   key: 'feature-bitrate-modes', value-type: list<enum<VBR,CBR,CQ>>
     *   key: 'feature-intra-refresh', value-type: enum<0,1>
     *   key: 'quality-default', value-type: num
     *   key: 'quality-range', value-type: range<num>
     *   key: 'quality-scale', value-type: string
     * 
     * For keys with prefix 'feature-' and value type enum<0,1>, the value of 0
     * means "optional", while the value of 1 means "required".
     */
    typedef ::android::hardware::media::omx::V1_0::IOmxStore::Attribute NodeAttribute;

    /**
     * Information for an IOmxNode node.
     */
    struct NodeInfo final {
        ::android::hardware::hidl_string name __attribute__ ((aligned(8)));
        ::android::hardware::hidl_string owner __attribute__ ((aligned(8)));
        ::android::hardware::hidl_vec<::android::hardware::media::omx::V1_0::IOmxStore::Attribute> attributes __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo, name) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo, owner) == 16, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo, attributes) == 32, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo) == 48, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo) == 8, "wrong alignment");

    /**
     * Information about nodes provided for a supported node role
     */
    struct RoleInfo final {
        ::android::hardware::hidl_string role __attribute__ ((aligned(8)));
        ::android::hardware::hidl_string type __attribute__ ((aligned(8)));
        bool isEncoder __attribute__ ((aligned(1)));
        bool preferPlatformNodes __attribute__ ((aligned(1)));
        ::android::hardware::hidl_vec<::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo> nodes __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo, role) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo, type) == 16, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo, isEncoder) == 32, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo, preferPlatformNodes) == 33, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo, nodes) == 40, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo) == 56, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo) == 8, "wrong alignment");

    virtual bool isRemote() const override { return false; }


    using listServiceAttributes_cb = std::function<void(::android::hardware::media::omx::V1_0::Status status, const ::android::hardware::hidl_vec<::android::hardware::media::omx::V1_0::IOmxStore::Attribute>& attributes)>;
    /**
     * List attributes that are service-specific (not node-specific).
     * 
     * @return attributes The list of `Attribute`s that are specific to this
     *                    service.
     */
    virtual ::android::hardware::Return<void> listServiceAttributes(listServiceAttributes_cb _hidl_cb) = 0;

    using getNodePrefix_cb = std::function<void(const ::android::hardware::hidl_string& prefix)>;
    /**
     * Return the prefix of names of supported nodes.
     * 
     * @return prefix The prefix of the names of all nodes supported by this
     *                service.
     */
    virtual ::android::hardware::Return<void> getNodePrefix(getNodePrefix_cb _hidl_cb) = 0;

    using listRoles_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo>& roleList)>;
    /**
     * List roles of supported nodes.
     * 
     * The name of each node inside `NodeInfo` must start with the prefix
     * returned by `getNodePrefix()`.
     * 
     * @return roleList The list of `RoleInfo`s.
     * 
     * @see RoleInfo
     */
    virtual ::android::hardware::Return<void> listRoles(listRoles_cb _hidl_cb) = 0;

    /**
     * Obtain an `IOmx` instance with a specified name.
     * 
     * @param name The name of the instance.
     * @return omx The `IOmx` interface associated with `name`. This must be
     * null if the name is not found.
     */
    virtual ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmx>> getOmx(const ::android::hardware::hidl_string& name) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmxStore>> castFrom(const ::android::sp<::android::hardware::media::omx::V1_0::IOmxStore>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmxStore>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IOmxStore> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmxStore> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IOmxStore> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IOmxStore> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IOmxStore> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmxStore> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IOmxStore> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IOmxStore> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::hardware::media::omx::V1_0::IOmxStore::Attribute& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".key = ";
    os += ::android::hardware::toString(o.key);
    os += ", .value = ";
    os += ::android::hardware::toString(o.value);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::IOmxStore::Attribute& lhs, const ::android::hardware::media::omx::V1_0::IOmxStore::Attribute& rhs) {
    if (lhs.key != rhs.key) {
        return false;
    }
    if (lhs.value != rhs.value) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::IOmxStore::Attribute& lhs,const ::android::hardware::media::omx::V1_0::IOmxStore::Attribute& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".name = ";
    os += ::android::hardware::toString(o.name);
    os += ", .owner = ";
    os += ::android::hardware::toString(o.owner);
    os += ", .attributes = ";
    os += ::android::hardware::toString(o.attributes);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo& lhs, const ::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo& rhs) {
    if (lhs.name != rhs.name) {
        return false;
    }
    if (lhs.owner != rhs.owner) {
        return false;
    }
    if (lhs.attributes != rhs.attributes) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo& lhs,const ::android::hardware::media::omx::V1_0::IOmxStore::NodeInfo& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".role = ";
    os += ::android::hardware::toString(o.role);
    os += ", .type = ";
    os += ::android::hardware::toString(o.type);
    os += ", .isEncoder = ";
    os += ::android::hardware::toString(o.isEncoder);
    os += ", .preferPlatformNodes = ";
    os += ::android::hardware::toString(o.preferPlatformNodes);
    os += ", .nodes = ";
    os += ::android::hardware::toString(o.nodes);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo& lhs, const ::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo& rhs) {
    if (lhs.role != rhs.role) {
        return false;
    }
    if (lhs.type != rhs.type) {
        return false;
    }
    if (lhs.isEncoder != rhs.isEncoder) {
        return false;
    }
    if (lhs.preferPlatformNodes != rhs.preferPlatformNodes) {
        return false;
    }
    if (lhs.nodes != rhs.nodes) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo& lhs,const ::android::hardware::media::omx::V1_0::IOmxStore::RoleInfo& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::sp<::android::hardware::media::omx::V1_0::IOmxStore>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::omx::V1_0::IOmxStore::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMXSTORE_H
