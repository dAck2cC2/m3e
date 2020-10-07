
#define LOG_TAG "ServiceManagement"

#include <log/log.h>
#include <utils/Mutex.h>

//#include <hidl/HidlInternal.h>
//#include <hidl/HidlBinderSupport.h>
//#include <hidl/HidlTransportUtils.h>
#include <hidl/ServiceManagement.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hidl/manager/1.1/IServiceManager.h>

#include "ServiceManager.h"

using IServiceManager1_0 = android::hidl::manager::V1_0::IServiceManager;
using IServiceManager1_1 = android::hidl::manager::V1_1::IServiceManager;
using ImplServiceManager1_1 = android::hidl::manager::V1_1::ImplServiceManager;

namespace android {
namespace hardware {

namespace details {
    Mutex gDefaultServiceManagerLock;
    sp<android::hidl::manager::V1_1::IServiceManager> gDefaultServiceManager;
}  // namespace details

sp<IServiceManager1_0> defaultServiceManager() {
    return defaultServiceManager1_1();
}
sp<IServiceManager1_1> defaultServiceManager1_1() {
    {
        AutoMutex _l(details::gDefaultServiceManagerLock);
        if (details::gDefaultServiceManager != nullptr) {
            return details::gDefaultServiceManager;
        }

        details::gDefaultServiceManager = new ImplServiceManager1_1();
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
}; // namespace details

}; // namespace hardware
}; // namespace android
