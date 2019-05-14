#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

#include <log/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>

#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>

#include <EGL/egl.h>

#include "com/NativeWindow.h"

/*****************************************************************************/

struct hwc_context_t {
    hwc_composer_device_1_t device;
    /* our private state goes below here */
};

static int hwc_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device);

static struct hw_module_methods_t hwc_module_methods = {
    /*.open =*/ hwc_device_open
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hwc_module_t HAL_MODULE_INFO_SYM = {
    /*.common =*/ {
        /*.tag =*/ HARDWARE_MODULE_TAG,
        /*.version_major =*/ 1,
        /*.version_minor =*/ 0,
        /*.id =*/ HWC_HARDWARE_MODULE_ID,
        /*.name =*/ "windows hwcomposer module",
        /*.author =*/ "The Android Open Source Project",
        /*.methods =*/ &hwc_module_methods,
    }
};

/*****************************************************************************/

static int32_t defaultAttribute[] = {
	0, // HWC_DISPLAY_NO_ATTRIBUTE
	1, // HWC_DISPLAY_VSYNC_PERIOD
	800, // HWC_DISPLAY_WIDTH
	600, // HWC_DISPLAY_HEIGHT
	1, // HWC_DISPLAY_DPI_X
	1, // HWC_DISPLAY_DPI_Y
	0  // HWC_DISPLAY_COLOR_TRANSFORM
};

static android::Mutex lockNativeWindow("native window");
static android::Vector< android::sp<android::NativeWindow> > nativeWindows;

static int hwc_prepare(hwc_composer_device_1_t * /*dev*/,
        size_t /*numDisplays*/, hwc_display_contents_1_t** displays) {
    if (displays && (displays[0]->flags & HWC_GEOMETRY_CHANGED)) {
        for (size_t i=0 ; i<displays[0]->numHwLayers ; i++) {
            //dump_layer(&list->hwLayers[i]);
            displays[0]->hwLayers[i].compositionType = HWC_FRAMEBUFFER;
        }
    }
    return 0;
}

static int hwc_set(hwc_composer_device_1_t * /*dev*/,
        size_t /*numDisplays*/, hwc_display_contents_1_t** displays)
{
    //for (size_t i=0 ; i<list->numHwLayers ; i++) {
    //    dump_layer(&list->hwLayers[i]);
    //}

    return 0;
}

static int hw_eventControl(struct hwc_composer_device_1* dev, int disp, int event, int enabled)
{
	return 0;
}

static int hw_blank(struct hwc_composer_device_1* dev, int disp, int blank)
{
	return 0;
}

static int hw_query(struct hwc_composer_device_1* dev, int what, int* value)
{
	return 0;
}

static void hw_registerProcs(struct hwc_composer_device_1* dev, hwc_procs_t const* procs)
{
	return;
}

void hw_dump(struct hwc_composer_device_1* dev, char *buff, int buff_len) 
{
	return;
}

static int hw_getDisplayConfigs(struct hwc_composer_device_1* dev, int disp,
	uint32_t* configs, size_t* numConfigs)
{
	int ret = 0;

	if (!dev || !configs || !numConfigs) {
		return -1;
	}

	// we only have primary display.
	if (HWC_DISPLAY_PRIMARY == disp) {
		// we only have one configuration.
		configs[0] = 0;
		*numConfigs = 1;
	}
	else {
		numConfigs = 0;
		ret = -1;
	}

	return ret;
}

static int hw_getDisplayAttributes(struct hwc_composer_device_1* dev, int disp,
	uint32_t config, const uint32_t* attributes, int32_t* values)
{
	int ret = 0;

	if (!dev || !attributes || !values) {
		return -1;
	}

	// we only have primary display and one config
	if ((HWC_DISPLAY_PRIMARY == disp) && (0 == config)) {
		for (int i = 0; attributes[i] != HWC_DISPLAY_NO_ATTRIBUTE; ++i) {
			values[i] = defaultAttribute[attributes[i]];
		}
	}
	else {
		ret = -1;
	}

	return 0;
}

static int hw_getActiveConfig(struct hwc_composer_device_1* dev, int disp)
{
	return 0;
}

static int hw_setActiveConfig(struct hwc_composer_device_1* dev, int disp,
	int index)
{
	return 0;
}

static int hw_setCursorPositionAsync(struct hwc_composer_device_1 *dev, int disp, int x_pos, int y_pos)
{
	return 0;
}


static hwc_display_t hw_nativeWindowMain(void)
{
	android::AutoMutex _l(lockNativeWindow);

	if (nativeWindows.empty()) {
		nativeWindows.add(android::CreateNativeWindow());
		LOG_ALWAYS_FATAL_IF((nativeWindows[0] == NULL), "Failed to create main window %s:%d", __FILE__, __LINE__);

		char defaultName[PROPERTY_VALUE_MAX];
		property_get("native.display.name", defaultName, "default");

		defaultAttribute[HWC_DISPLAY_WIDTH]  = property_get_int32("native.display.width",  400);
		defaultAttribute[HWC_DISPLAY_HEIGHT] = property_get_int32("native.display.height", 300);

		bool check = nativeWindows[0]->initialize(defaultName, defaultAttribute[HWC_DISPLAY_WIDTH], defaultAttribute[HWC_DISPLAY_HEIGHT]);
		LOG_ALWAYS_FATAL_IF((check == false), "Failed to intialize native window %s:%d", __FILE__, __LINE__);

		nativeWindows[0]->setVisible(false);
	}

	return (nativeWindows[0]->getNativeWindow());
}

static int hw_nativeWindowPopEvent(void)
{
	android::AutoMutex _l(lockNativeWindow);

	if (nativeWindows.empty()) {
		return (-1);
	}

	android::sp<android::NativeWindow> win = nativeWindows[0];

	// Clear events that the application did not process from this frame
	Event event;
	while (win->popEvent(&event)) {
		// If the application did not catch a close event, close now
		if (event.Type == Event::EVENT_CLOSED) {
			return (-2);
		}
	}

	return 0;
}

static hwc_display_t hw_nativeWindowCreate(const char * name)
{
	android::AutoMutex _l(lockNativeWindow);

	nativeWindows.add(android::CreateNativeWindow());
	android::sp<android::NativeWindow> win = nativeWindows[nativeWindows.size() - 1];
	LOG_ALWAYS_FATAL_IF((win == NULL), "Failed to create native window %s:%d", __FILE__, __LINE__);
	if (win == NULL) return NULL;

	bool check = win->initialize(name ? name : "", defaultAttribute[HWC_DISPLAY_WIDTH], defaultAttribute[HWC_DISPLAY_HEIGHT]);
	LOG_ALWAYS_FATAL_IF((check == false), "Failed to intialize native window %s:%d", __FILE__, __LINE__);

	win->setVisible(true);

	return (win->getNativeWindow());
}

static int hw_nativeWindowDelete(hwc_display_t hWin)
{
	android::AutoMutex _l(lockNativeWindow);

	for (int i = 0; i < nativeWindows.size(); ++i) {
		if (nativeWindows[i]->getNativeWindow() == hWin) {
			nativeWindows.removeAt(i);
			return 0;
		}
	}

	return -1;
}

static void hw_nativeWindowMessageLoop(hwc_display_t hWin)
{
	android::AutoMutex _l(lockNativeWindow);

	android::sp<android::NativeWindow> win;

	for (int i = 0; i < nativeWindows.size(); ++i) {
		if (nativeWindows[i]->getNativeWindow() == hWin) {
			win = nativeWindows[i];
		}
	}

	if (win != NULL) {
		win->messageLoop();
	}

	return;
}

/*****************************************************************************/

static int hwc_device_close(struct hw_device_t *dev)
{
	struct hwc_context_t* ctx = (struct hwc_context_t*)dev;
	if (ctx) {
		free(ctx);
	}
	return 0;
}

static int hwc_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
    int status = -EINVAL;
    if (!strcmp(name, HWC_HARDWARE_COMPOSER)) {
        struct hwc_context_t *dev;
        dev = (hwc_context_t*)malloc(sizeof(*dev));

        /* initialize our state here */
        memset(dev, 0, sizeof(*dev));

        /* initialize the procs */
        dev->device.common.tag = HARDWARE_DEVICE_TAG;
        dev->device.common.version = HWC_DEVICE_API_VERSION_1_1;
        dev->device.common.module = const_cast<hw_module_t*>(module);
        dev->device.common.close = hwc_device_close;

        dev->device.prepare = hwc_prepare;
        dev->device.set = hwc_set;
		dev->device.eventControl = hw_eventControl;
		dev->device.blank = hw_blank;
		dev->device.query = hw_query;
		dev->device.registerProcs = hw_registerProcs;
		dev->device.dump = hw_dump;
		dev->device.getDisplayConfigs = hw_getDisplayConfigs;
		dev->device.getDisplayAttributes = hw_getDisplayAttributes;
		dev->device.getActiveConfig = hw_getActiveConfig;
		dev->device.setActiveConfig = hw_setActiveConfig;
		dev->device.setCursorPositionAsync = hw_setCursorPositionAsync;

		dev->device.nativeWindowMain        = hw_nativeWindowMain;
		dev->device.nativeWindowPopEvent    = hw_nativeWindowPopEvent;
		dev->device.nativeWindowCreate      = hw_nativeWindowCreate;
		dev->device.nativeWindowDelete      = hw_nativeWindowDelete;
		dev->device.nativeWindowMessageLoop = hw_nativeWindowMessageLoop;

        *device = &dev->device.common;
        status = 0;
    }
    return status;
}
