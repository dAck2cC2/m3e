
#define LOG_NDEBUG 0
#define LOG_TAG "BootAnimation"

#if defined(_MSC_VER)
#include <winsock2.h>
#include <windows.h>
#endif  // _MSC_VER

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

#include <binder/IBinder.h>
#include "BootAnimation.h"


using namespace android;

// Create a typedef for readability.
typedef android::BootAnimation::Animation Animation;

class DummyAnimationCallbacks : public android::BootAnimation::Callbacks {
public:
	void init(const Vector<Animation::Part>& parts) override {
	};

	void playPart(int partNumber, const Animation::Part& part, int playNumber) override {
	};

	void shutdown() override {
	};
};

static sp<BootAnimation> gBootAnimation;

//  interface for initrc

#define BOOT_ANIMATION_TAG     0xF3EC
#define BOOT_ANIMATION_VER     7020
#define BOOT_ANIMATION_ID      "bootanimation"
#define BOOT_ANIMATION_NAME    "android.os.BootAnimation"
#define BOOT_ANIMATION_AUTHOR  "yuki.kokoto"

int open_bootanimation(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	if (gBootAnimation == NULL) {
		gBootAnimation = new BootAnimation(new DummyAnimationCallbacks());
	}

	return OK;
}

hw_module_methods_t method = {
	open_bootanimation
};

#ifdef __cplusplus
extern "C"
#endif
ANDROID_API
hw_module_t HMI = {
	BOOT_ANIMATION_TAG,    // tag
	BOOT_ANIMATION_VER,    // module_api_version
	BOOT_ANIMATION_VER,    // hal_api_version
	BOOT_ANIMATION_ID,     // id
	BOOT_ANIMATION_NAME,   // name
	BOOT_ANIMATION_AUTHOR, // author
	&method, // methods
	NULL,    // dso
{ 0 }    // reserved
};
