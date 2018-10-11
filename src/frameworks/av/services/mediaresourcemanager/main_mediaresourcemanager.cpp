

#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include "ResourceManagerService.h"

namespace android {

	class MediaResourceManagerServiceThread : public Thread
	{
	public:
		MediaResourceManagerServiceThread() {};

		void waitForStarted(void) {
			if (!Thread::isRunning()) {
				mStartedMutex.lock();

				Thread::run();

				mStartedCondition.wait(mStartedMutex);
				mStartedMutex.unlock();
			}
		}
	private:
		virtual bool threadLoop() {
			mStartedMutex.lock();

			sp<ProcessState>  proc = ProcessState::self();
			mService = ResourceManagerService::create();

			mStartedCondition.broadcast();
			mStartedMutex.unlock();

			IPCThreadState::self()->joinThreadPool();

			return false;
		};

	private:
		sp<ResourceManagerService>  mService;
		Mutex              mStartedMutex;
		Condition          mStartedCondition;
	};

}; // namespace android {


//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define MEDIA_RESOURCE_MANAGER_TAG     0xF3EC
#define MEDIA_RESOURCE_MANAGER_VER     7020
#define MEDIA_RESOURCE_MANAGER_ID      "mediaresourcemanager"
#define MEDIA_RESOURCE_MANAGER_NAME    "media.resourcemanager"
#define MEDIA_RESOURCE_MANAGER_AUTHOR  "yuki.kokoto"

static sp<MediaResourceManagerServiceThread> gService;

int open_mediaresourcemanagerservice(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	if (gService == NULL) {
		gService = new MediaResourceManagerServiceThread();
		gService->waitForStarted();
	}

	return OK;
}

hw_module_methods_t method = {
	open_mediaresourcemanagerservice
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hw_module_t HMI = {
	MEDIA_RESOURCE_MANAGER_TAG,    // tag
	MEDIA_RESOURCE_MANAGER_VER,    // module_api_version
	MEDIA_RESOURCE_MANAGER_VER,    // hal_api_version
	MEDIA_RESOURCE_MANAGER_ID,     // id
	MEDIA_RESOURCE_MANAGER_NAME,   // name
	MEDIA_RESOURCE_MANAGER_AUTHOR, // author
	&method, // methods
	NULL,    // dso
	{ 0 }    // reserved
};

