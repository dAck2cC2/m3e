#define LOG_TAG "android.hardware.graphics.composer@2.1::IComposer"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/graphics/composer/2.1/IComposer.h>
#include <android/hardware/graphics/composer/2.1/IComposerCallback.h>
#include <android/hardware/graphics/composer/2.2/IComposer.h>
#include <android/hardware/graphics/composer/2.2/IComposerClient.h>

#include "hwc2/hwc2_default.h"
#include "hwc2/hwc2_angle.h"

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

::android::sp<IComposer> IComposer::getService(const std::string &serviceName, bool getStub)
{
#if ENABLE_ANGLE
    return new ComposerAngle();
#else
    return new ComposerDefault();
#endif
}

}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android


namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_2 {

::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_2::IComposer>> IComposer::castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>& parent, bool emitError)
{
    // no support for v2.2
    return nullptr;
}

::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_2::IComposerClient>> IComposerClient::castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerClient>& parent, bool emitError)
{
    // no support for v2.2
    return nullptr;
}


}  // namespace V2_2
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android
