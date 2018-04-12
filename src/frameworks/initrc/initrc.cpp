
#include <cutils/properties.h>
#include <hardware/hardware.h>
#include "initrc.h"

namespace android {
    
ANDROID_SINGLETON_STATIC_INSTANCE(InitRC);

static const char* gServiceList[] = {
    "servicemanager",
    "surfaceflinger",
};
#define SERVICE_LIST_CNT  (sizeof(gServiceList)/sizeof(char*))

InitRC::InitRC()
{
    ResetProperties();
    StartServices();
}

InitRC::~InitRC()
{
    // empty
}

void InitRC::ResetProperties()
{
    property_set("ro.hardware", "local");
    
#if defined(__APPLE__)
    property_set("ro.board.platform", "osx");
#elif defined(_MSC_VER)
    property_set("ro.board.platform", "win");
#else
#error Unknown Platform
#endif
}

void InitRC::StartServices()
{
    // Using the structure and interface of hardware.h just for lazy.
    // We could also define our own serivce structure and load interface.
    const hw_module_t* module = NULL;
    for (int i = 0; i < SERVICE_LIST_CNT; ++i) {
        module = NULL;
        hw_get_module(gServiceList[i], &module);
        if (module && module->methods && module->methods->open) {
            (*(module->methods->open))(module, gServiceList[i], NULL);
        }
    }
}
    
}; // namespace android
