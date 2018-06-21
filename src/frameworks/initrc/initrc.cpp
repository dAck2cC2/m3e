
#include <cutils/properties.h>
#include <hardware/hardware.h>

#include <SurfaceFlinger.h>

#include "initrc.h"

namespace android {
    
ANDROID_SINGLETON_STATIC_INSTANCE(InitRC);

enum {
    SERVICE_SM = 0,
    SERVICE_SF,
    SERVICE_CNT
};
    
static struct {
    const char*          name;
    struct hw_device_t*  handler;
}
gServiceList[SERVICE_CNT] = {
    {"servicemanager", NULL},
    {"surfaceflinger", NULL}
};

InitRC::InitRC()
{
    ResetProperties();
    StartService(SERVICE_SM);
}

InitRC::~InitRC()
{
}

void InitRC::ResetProperties()
{
    // OpenGL & EGL
    property_set("ro.kernel.qemu", "1");
    
    // native display
    property_set("native.display.name",   "M3E");
    property_set("native.display.width",  "800");
    property_set("native.display.height", "600");
    
    // libraries of service
    property_set("ro.hardware", "local");
#if defined(__APPLE__)
    property_set("ro.board.platform", "osx");
#elif defined(_MSC_VER)
    property_set("ro.board.platform", "win");
#else
#error Unknown Platform
#endif
}

void InitRC::StartService(int index)
{
    if (index < 0 || index >= SERVICE_CNT) {
        return;
    }
    
    // Using the structure and interface of hardware.h just for lazy.
    // We could also define our own serivce structure and load interface.
    const hw_module_t*  module = NULL;
    module = NULL;
    hw_get_module(gServiceList[index].name, &module);
    if (module && module->methods && module->methods->open) {
        (*(module->methods->open))(module, gServiceList[index].name, &(gServiceList[index].handler));
    }
}
 
status_t InitRC::Entry(int argc, char** argv)
{
    StartService(SERVICE_SF);
    
    return OK;
}

void InitRC::Run()
{
    if ((NULL == gServiceList[SERVICE_SF].handler)
    ||  (NULL == gServiceList[SERVICE_SF].handler->module)
    ||  (NULL == gServiceList[SERVICE_SF].handler->module->dso)) {
        return;
    }
    
    sp<SurfaceFlinger> flinger = (SurfaceFlinger *)(gServiceList[SERVICE_SF].handler->module->dso);
    flinger->run();
}
    
}; // namespace android
