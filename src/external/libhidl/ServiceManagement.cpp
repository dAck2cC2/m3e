
#define LOG_TAG "ServiceManagement"

#include <log/log.h>
#include <utils/Mutex.h>

//#include <hidl/HidlInternal.h>
//#include <hidl/HidlBinderSupport.h>
//#include <hidl/HidlTransportUtils.h>
#include <hidl/ServiceManagement.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hidl/manager/1.1/IServiceManager.h>
#include <android/hidl/manager/1.2/IServiceManager.h>

#include "ServiceManager.h"

// put it at last of including list, in order to avoid evil ERROR macro of MSVC
#include <android-base/logging.h>

using ::android::hidl::base::V1_0::IBase;
using IServiceManager1_0 = android::hidl::manager::V1_0::IServiceManager;
using IServiceManager1_1 = android::hidl::manager::V1_1::IServiceManager;
using IServiceManager1_2 = android::hidl::manager::V1_2::IServiceManager;

using IServiceManagerDefault = android::hidl::manager::V1_2::IServiceManager;
using ImplServiceManager = android::hidl::manager::V1_2::ImplServiceManager;

namespace android {
namespace hardware {

namespace details {
    Mutex                       gDefaultServiceManagerLock;
    sp<IServiceManagerDefault>  gDefaultServiceManager;
}  // namespace details

sp<IServiceManager1_0> defaultServiceManager() {
    return defaultServiceManager1_2();
}
sp<IServiceManager1_1> defaultServiceManager1_1() {
    return defaultServiceManager1_2();
}
sp<IServiceManager1_2> defaultServiceManager1_2() {
    {
        AutoMutex _l(details::gDefaultServiceManagerLock);
        if (details::gDefaultServiceManager != nullptr) {
            return details::gDefaultServiceManager;
        }

        details::gDefaultServiceManager = new ImplServiceManager();
    }

    return details::gDefaultServiceManager;
}

sp<IServiceManager1_0> getPassthroughServiceManager() {
    return getPassthroughServiceManager1_1();
}
sp<IServiceManager1_1> getPassthroughServiceManager1_1() {
    // EMPTY
    // No need yet
    return nullptr;
}

namespace details {
    void onRegistration(const std::string& packageName,
        const std::string& /* interfaceName */,
        const std::string& /* instanceName */) {
        // EMPTY
        return;
    }

    void waitForHwService(
        const std::string& _interface, const std::string& instanceName) {
        // EMPTY
        return;
    }

    void preloadPassthroughService(const std::string& descriptor) {
        return;
    }

    sp<::android::hidl::base::V1_0::IBase> getRawServiceInternal(const std::string& descriptor,
        const std::string& instance,
        bool retry, bool getStub) {

        const sp<IServiceManager1_1> sm = defaultServiceManager1_1();
        if (sm == nullptr) {
            ALOGE("getService: defaultServiceManager() is null");
            return nullptr;
        }

        sp<::android::hidl::base::V1_0::IBase> base = sm->get(descriptor, instance).withDefault(nullptr);

        return base;
    }

    status_t registerAsServiceInternal(const sp<IBase>& service, const std::string& name) {
        if (service == nullptr) {
            return UNEXPECTED_NULL;
        }

        sp<IServiceManager1_2> sm = defaultServiceManager1_2();
        if (sm == nullptr) {
            return INVALID_OPERATION;
        }

        bool registered = false;
        Return<void> ret = service->interfaceChain([&](const auto& chain) {
            registered = sm->addWithChain(name.c_str(), service, chain).withDefault(false);
            });

        if (!ret.isOk()) {
            LOG(ERROR) << "Could not retrieve interface chain: " << ret.description();
        }

#if 0
        if (registered) {
            onRegistrationImpl(getDescriptor(service.get()), name);
        }
#endif
        return registered ? OK : UNKNOWN_ERROR;
    }
}; // namespace details

}; // namespace hardware
}; // namespace android
