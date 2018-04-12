
#include <cutils/compiler.h>
#include <hardware/hardware.h>
#include "SurfaceFlinger.h"

//  interface for initrc

#define SURFACE_FLINGER_TAG     0xF3EC
#define SURFACE_FLINGER_VER     7020
#define SURFACE_FLINGER_ID      "surfaceflinger"
#define SURFACE_FLINGER_NAME    "android.SurfaceFlinger"
#define SURFACE_FLINGER_AUTHOR  "yuki.kokoto"

int open_surfaceflinger(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device)
{
    return android::OK;
}

hw_module_methods_t method = {
    open_surfaceflinger
};

hw_module_t HMI = {
    SURFACE_FLINGER_TAG, // tag
    SURFACE_FLINGER_VER, // module_api_version
    SURFACE_FLINGER_VER, // hal_api_version
    SURFACE_FLINGER_ID,  // id
    SURFACE_FLINGER_NAME, // name
    SURFACE_FLINGER_AUTHOR, // author
    &method, // methods
    NULL,    // dso
    { 0 }    // reserved
};
