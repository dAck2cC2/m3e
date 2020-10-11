
// OMX implemetation
#include <media/stagefright/omx/1.0/Omx.h>
#include <media/stagefright/omx/1.0/OmxStore.h>

// interface for initrc
#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace ::android;
using namespace ::android::hardware::media::omx::V1_0;

#define SERVICE_TAG     0xF3EC
#define SERVICE_VER     7020
#define SERVICE_ID      "mediacodecservice"
#define SERVICE_NAME    "media.codec"
#define SERVICE_AUTHOR  "yuki.kokoto"

static sp<IOmxStore> gOmxStore;
static sp<IOmx>      gOmx;

static int open_mediacodecservice(const struct hw_module_t* module, const char* id, struct hw_device_t** device);
static int close_mediacodecservice(struct hw_device_t* device);

hw_module_methods_t method = {
    open_mediacodecservice
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hw_module_t HMI = {
    SERVICE_TAG,    // tag
    SERVICE_VER,    // module_api_version
    SERVICE_VER,    // hal_api_version
    SERVICE_ID,     // id
    SERVICE_NAME,   // name
    SERVICE_AUTHOR, // author
    &method, // methods
    NULL,    // dso
    { 0 }    // reserved
};

struct hw_device_t DEV = {
    SERVICE_TAG, // tag
    SERVICE_VER, // version
    &HMI,                // module
    { 0 },               // reserved
    close_mediacodecservice // close
};

int open_mediacodecservice(const struct hw_module_t* module, const char* id,
                      struct hw_device_t** device)
{
    // Default codec services
    using namespace ::android::hardware::media::omx::V1_0;
    
    if (gOmxStore == nullptr) {
        sp<IOmxStore> gOmxStore = new implementation::OmxStore();
        if (gOmxStore == nullptr) {
            ALOGE("Cannot create IOmxStore HAL service.");
        } else if (gOmxStore->registerAsService() != OK) {
            ALOGE("Cannot register IOmxStore HAL service.");
        }
    }
    
    if (gOmx == nullptr) {
        sp<IOmx> gOmx = new implementation::Omx();
        if (gOmx == nullptr) {
            ALOGE("Cannot create IOmx HAL service.");
        } else if (gOmx->registerAsService() != OK) {
            ALOGE("Cannot register IOmx HAL service.");
        } else {
            ALOGE("IOmx HAL service created.");
        }
    }
    
    if (device != NULL) {
        (*device) = &DEV;
    }
    
    return OK;
}

int close_mediacodecservice(struct hw_device_t* device)
{
    gOmx = NULL;
    gOmxStore = NULL;
    
    return OK;
}
