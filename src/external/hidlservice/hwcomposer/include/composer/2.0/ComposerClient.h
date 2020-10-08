
#ifndef HARDWARE_GRAPHICS_COMPOSER_FACTORY_H
#define HARDWARE_GRAPHICS_COMPOSER_FACTORY_H

#if defined(_MSC_VER)
	#if !defined(EXPORT_COMPOSER)
		#define EXPORT_COMPOSER  __declspec(dllimport)
	#endif // EXPORT_COMPOSER
#else
	#define EXPORT_COMPOSER 
#endif // _MSC_VER

#include <android/hardware/graphics/composer/2.1/IComposer.h>

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

EXPORT_COMPOSER  android::sp<IComposer>  defaultComposer();

}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif // HARDWARE_GRAPHICS_COMPOSER_FACTORY_H
