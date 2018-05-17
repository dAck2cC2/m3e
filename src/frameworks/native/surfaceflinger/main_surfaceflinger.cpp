
#include <cutils/compiler.h>
#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <hardware/hardware.h>

#include "SurfaceFlinger.h"

namespace android {

	class SurfaceFlingerService : public RefBase
	{
	public:
		SurfaceFlingerService(sp<SurfaceFlinger> flinger) : mService(flinger), mMessage(flinger) {};
		~SurfaceFlingerService() {};

		void Start() {
			mService.waitForStarted();
			//mMessage.waitForStarted();
		}

	private:
		class CommonThread : public Thread
		{
		public:
			CommonThread(sp<SurfaceFlinger> flinger) : mFlinger(flinger) {};

			void waitForStarted(void) {
				if (!Thread::isRunning()) {
					mStartedMutex.lock();

					Thread::run();

					mStartedCondition.wait(mStartedMutex);
					mStartedMutex.unlock();
				}
			}

		protected:
			sp<SurfaceFlinger>  mFlinger;
			Mutex				mStartedMutex;
			Condition			mStartedCondition;
		};

		class ServiceThread : public CommonThread
		{
		public:
			ServiceThread(sp<SurfaceFlinger> flinger) : CommonThread(flinger) {};

		private:
			virtual bool threadLoop() {
				mStartedMutex.lock();

				sp<ProcessState>  proc = ProcessState::self();

				defaultServiceManager()->addService(String16(SurfaceFlinger::getServiceName()), mFlinger);

				mStartedCondition.broadcast();
				mStartedMutex.unlock();

				IPCThreadState::self()->joinThreadPool();

				return false;
			};
		};

		class MessageThread : public CommonThread
		{
		public:
			MessageThread(sp<SurfaceFlinger> flinger) : CommonThread(flinger) {};

		private:
			virtual bool threadLoop() {
				mStartedMutex.lock();

				mStartedCondition.broadcast();
				mStartedMutex.unlock();

				while (TRUE) {
					mFlinger->waitForEvent(-1);
				}

				return false;
			};
		};

		ServiceThread mService;
		MessageThread mMessage;
	};

}; // namespace android

//  interface for initrc

#define SURFACE_FLINGER_TAG     0xF3EC
#define SURFACE_FLINGER_VER     7020
#define SURFACE_FLINGER_ID      "surfaceflinger"
#define SURFACE_FLINGER_NAME    "android.SurfaceFlinger"
#define SURFACE_FLINGER_AUTHOR  "yuki.kokoto"

static android::sp<android::SurfaceFlinger> gSurfaceFlinger;
static android::sp<android::SurfaceFlingerService> gService;

static int open_surfaceflinger(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device);
static int close_surfaceflinger(struct hw_device_t* device);

hw_module_methods_t method = {
    open_surfaceflinger
};

#ifdef __cplusplus
extern "C"
#endif
ANDROID_API
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
        gSurfaceFlinger = new android::SurfaceFlinger();
        gSurfaceFlinger->init();

#if 1      
		// publish surface flinger
		android::sp<android::ProcessState> ps(android::ProcessState::self());
        android::sp<android::IServiceManager> sm(android::defaultServiceManager());
        sm->addService(android::String16(android::SurfaceFlinger::getServiceName()), gSurfaceFlinger, false);
#else
		gService = new android::SurfaceFlingerService(gSurfaceFlinger);
		gService->Start();
#endif

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

