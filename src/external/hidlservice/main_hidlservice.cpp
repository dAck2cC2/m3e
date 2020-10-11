
//  hidl services
#include <hwc2/hwc2_impl.h>
using IComposer2_1 = ::android::hardware::graphics::composer::V2_1::IComposer;
static android::sp<IComposer2_1> gComposer;

#include <hidl/allocator/1.0/allocator.h>
using ImplAllocator1_0 = ::android::hidl::allocator::V1_0::implement::Allocator;
using IAllocator1_0 = ::android::hidl::allocator::V1_0::IAllocator;
static android::sp<IAllocator1_0> gAllocator;

#include <hidl/memory/1.0/mapper.h>
using ImplMapper1_0 = ::android::hidl::memory::V1_0::implement::Mapper;
using IMapper1_0 = ::android::hidl::memory::V1_0::IMapper;
static android::sp<IMapper1_0> gMapper;

//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define SERVICE_TAG     0xF3EC
#define SERVICE_VER     7020
#define SERVICE_ID      "hidlservice"
#define SERVICE_NAME    "hardware.hidl"
#define SERVICE_AUTHOR  "yuki.kokoto"


static int open_hidlservice(const struct hw_module_t* module, const char* id, struct hw_device_t** device);
static int close_hidlservice(struct hw_device_t* device);

hw_module_methods_t method = {
	open_hidlservice
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
	close_hidlservice // close
};


int open_hidlservice(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	//  hidl services
	if (gComposer == NULL) {
		gComposer = new ImplComposer2_1();
		LOG_ALWAYS_FATAL_IF((gComposer == NULL), "Cannot create graphic composer !");

		if (gComposer->registerAsService() != ::android::OK) {
			LOG_ALWAYS_FATAL("Cannot register graphic composer. ");
		}
	}

	if (gAllocator == NULL) {
		gAllocator = new ImplAllocator1_0();
		LOG_ALWAYS_FATAL_IF((gComposer == NULL), "Cannot create hidl alllocator !");

		if (gAllocator->registerAsService("ashmem") != ::android::OK) {
			LOG_ALWAYS_FATAL("Cannot register hidl allocator. ");
		}
	}

	if (gMapper == NULL) {
		gMapper = new ImplMapper1_0();
		LOG_ALWAYS_FATAL_IF((gMapper == NULL), "Cannot create hidl alllocator !");

		if (gMapper->registerAsService("ashmem") != ::android::OK) {
			LOG_ALWAYS_FATAL("Cannot register hidl allocator. ");
		}
	}

    if (device != NULL) {
        (*device) = &DEV;
    }
    
	return OK;
}

int close_hidlservice(struct hw_device_t* device)
{
	gMapper    = NULL;
	gAllocator = NULL;
	gComposer  = NULL;

	return OK;
}
