
#include <cutils/properties.h>
#include <utils/Mutex.h>
#include <utils/RefBase.h>
#include <hardware/hardware.h>

#include "initrc/initrc.h"
#include "initrc_if.h"

#define PROPERTY_DEFINE(name, value)  extern const char* const name = value

PROPERTY_DEFINE(M_PROPERTY_DISPLAY_NAME,   "native.display.name");
PROPERTY_DEFINE(M_PROPERTY_DISPLAY_WIDTH,  "native.display.width");
PROPERTY_DEFINE(M_PROPERTY_DISPLAY_HEIGHT, "native.display.height");

namespace android {

class InitRCImpl : public RefBase
{
public:
	enum {
		SERVICE_SM = 0,
		SERVICE_SF,
		SERVICE_AF,
		SERVICE_AP,
		SERVICE_MEDIA_PLAYER,
		SERVICE_MEDIA_RESOURCE,
		SERVICE_MEDIA_CODEC,
		SERVICE_MEDIA_EXTRACTOR,
		SERVICE_BOOT_ANIM,
		SERVICE_CNT
	};

	InitRCImpl();

	virtual int  Entry(int argc, char** argv);
	virtual void Run();
    
    virtual bool HasInited() const { return (mHasInited); };

private:
	~InitRCImpl();

	void ResetProperties();
	void StartService(int index);
    
private:
    bool mHasInited;
};
    
static struct {
    const char*          name;
    struct hw_device_t*  handler;
}
gServiceList[InitRCImpl::SERVICE_CNT] = {
    {"servicemanager",        NULL},
    {"surfaceflinger",        NULL},
	{"audioflinger",          NULL},
	{"audiopolicy",           NULL},
    {"mediaplayerservice",    NULL},
	{"mediaresourcemanager",  NULL},
    {"mediacodecservice",     NULL},
	{"mediaextractor",        NULL},
	{"bootanimation",         NULL}
};

InitRCImpl::InitRCImpl() : mHasInited(false)
{
    ResetProperties();
    StartService(SERVICE_SM);
}

InitRCImpl::~InitRCImpl()
{
}

void InitRCImpl::ResetProperties()
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
    property_set("ro.hardware.audio_primary",  "openal");
    property_set("ro.board.platform", "osx");
#elif defined(_MSC_VER)
    property_set("ro.hardware.audio_primary", "wasapi");
    property_set("ro.board.platform", "win");
#elif defined(__linux__)
    property_set("ro.hardware.audio_primary", "dump");
	property_set("ro.board.platform", "linux");
#else
#error Unknown Platform
#endif

	// use the omx codec of media.player service
	property_set("media.stagefright.codecremote", "false");

	// treble omx is not supported yet
	property_set("persist.media.treble_omx", "false");

	// for debug
	property_set("media.stagefright.extractremote", "false");
	property_set("debug.stagefright.omx-debug", "OMX.google.raw.decoder:4");

	// audio
	//property_set("audio.device.buffer.ms", "100");
}

void InitRCImpl::StartService(int index)
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
 
int InitRCImpl::Entry(int argc, char** argv)
{
    if (!mHasInited) {
        StartService(SERVICE_SF);
        StartService(SERVICE_AF);
        StartService(SERVICE_AP);
        StartService(SERVICE_MEDIA_PLAYER);
        StartService(SERVICE_MEDIA_RESOURCE);
        StartService(SERVICE_MEDIA_CODEC);
        StartService(SERVICE_MEDIA_EXTRACTOR);
        
        if (property_get_bool("run.start.bootanim", 0)) {
            StartService(SERVICE_BOOT_ANIM);
        }
        
        mHasInited = true;
    }
    
    return 0;
}

void InitRCImpl::Run()
{
    if ((NULL == gServiceList[SERVICE_SF].handler)
    ||  (NULL == gServiceList[SERVICE_SF].handler->module)
    ||  (NULL == gServiceList[SERVICE_SF].handler->module->dso)) {
        return;
    }
    
	sp<InitRCMainWindow> mainWindow = (InitRCMainWindow *)(gServiceList[SERVICE_SF].handler->module->dso);
	if (mainWindow != NULL) {
		mainWindow->run();
	}
}
    
}; // namespace android

static android::Mutex                    s_lockInit("Init RC");
static android::sp<android::InitRCImpl>  s_pInitRC;

int InitRC_set(const char* property, const char* value)
{
    android::AutoMutex _l(s_lockInit);

    if (s_pInitRC == NULL) {
        s_pInitRC = new android::InitRCImpl();
    }

    if (s_pInitRC->HasInited()) {
        // It is too late to set property
        return -1;
    }
    
    return (property_set(property, value));
}

int InitRC_entry(int argc, char** argv)
{
	android::AutoMutex _l(s_lockInit);

	if (s_pInitRC == NULL) {
		s_pInitRC = new android::InitRCImpl();
	}

	return (s_pInitRC->Entry(argc, argv));
}

void InitRC_run(void)
{
	android::sp<android::InitRCImpl> pInitRC;

	{
		android::AutoMutex _l(s_lockInit);
		pInitRC = s_pInitRC;
	}

	if (pInitRC == NULL) {
		return;
	}

	pInitRC->Run();

	return;
}

