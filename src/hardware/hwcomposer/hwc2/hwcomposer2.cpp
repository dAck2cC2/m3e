#define LOG_TAG "android.hardware.graphics.composer@2.1::IComposer"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/graphics/composer/2.1/IComposer.h>
#include <android/hardware/graphics/composer/2.1/IComposerCallback.h>
#include <android/hardware/graphics/composer/2.2/IComposer.h>
#include <android/hardware/graphics/composer/2.2/IComposerClient.h>

#include <composer/2.0/ComposerClient.h>

#include "hwc2/hwc2_default.h"
#if ENABLE_GLFW
    #include "hwc2/hwc2_glfw.h"
#elif ENABLE_ANGLE
    #include "hwc2/hwc2_angle.h"
#endif

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

::android::sp<IComposer>  defaultComposer()
{
#if ENABLE_GLFW
    return new ComposerGLFW();
#elif ENABLE_ANGLE
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
