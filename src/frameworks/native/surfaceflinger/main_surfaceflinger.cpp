
#include <cutils/compiler.h>
#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <hardware/hardware.h>

#include "SurfaceFlinger.h"

//  interface for initrc

#define SURFACE_FLINGER_TAG     0xF3EC
#define SURFACE_FLINGER_VER     7020
#define SURFACE_FLINGER_ID      "surfaceflinger"
#define SURFACE_FLINGER_NAME    "android.SurfaceFlinger"
#define SURFACE_FLINGER_AUTHOR  "yuki.kokoto"

static android::sp<android::SurfaceFlinger> gSurfaceFlinger;

static int open_surfaceflinger(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device);
static int close_surfaceflinger(struct hw_device_t* device);

hw_module_methods_t method = {
    open_surfaceflinger
};

hw_module_t HMI = {
    SURFACE_FLINGER_TAG,    // tag
    SURFACE_FLINGER_VER,    // module_api_version
    SURFACE_FLINGER_VER,    // hal_api_version
    SURFACE_FLINGER_ID,     // id
    SURFACE_FLINGER_NAME,   // name
    SURFACE_FLINGER_AUTHOR, // author
    &method,                // methods
    NULL,                   // dso
    { 0 }                   // reserved
};

struct hw_device_t DEV = {
    SURFACE_FLINGER_TAG, // tag
    SURFACE_FLINGER_VER, // version
    &HMI,                // module
    { 0 },               // reserved
    close_surfaceflinger // close
};

int open_surfaceflinger(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device)
{
    if (gSurfaceFlinger == NULL) {
        android::sp<android::ProcessState> ps(android::ProcessState::self());
        
        gSurfaceFlinger = new android::SurfaceFlinger();
        gSurfaceFlinger->init();
        
        // publish surface flinger
        android::sp<android::IServiceManager> sm(android::defaultServiceManager());
        sm->addService(android::String16(android::SurfaceFlinger::getServiceName()), gSurfaceFlinger, false);
        
        HMI.dso = (void *)(gSurfaceFlinger.get());
    }
    
    if (device != NULL) {
        (*device) = &DEV;
    }
    
    return android::OK;
}

int close_surfaceflinger(struct hw_device_t* device)
{
    gSurfaceFlinger = NULL;
    
    return android::OK;
}

