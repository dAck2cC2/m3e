#ifndef HARDWARE_GRAPHICS_COMPOSER_V2_1_IMPL_COMPOSER_H
#define HARDWARE_GRAPHICS_COMPOSER_V2_1_IMPL_COMPOSER_H

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/graphics/composer/2.1/IComposer.h>
#include <android/hardware/graphics/composer/2.1/IComposerCallback.h>
#include <android/hardware/graphics/composer/2.2/IComposer.h>
#include <android/hardware/graphics/composer/2.2/IComposerClient.h>

#include "hwc2/hwc2_default.h"
#if ENABLE_GLFW
    #include "hwc2/hwc2_glfw.h"
	using ImplComposer2_1 = android::hardware::graphics::composer::V2_1::ComposerGLFW;
#elif ENABLE_ANGLE
    #include "hwc2/hwc2_angle.h"
	using ImplComposer2_1 = android::hardware::graphics::composer::V2_1::ComposerAngle;
#else
	using ImplComposer2_1 = android::hardware::graphics::composer::V2_1::ComposerDefault;
#endif

#endif // HARDWARE_GRAPHICS_COMPOSER_V2_1_IMPL_COMPOSER_H
