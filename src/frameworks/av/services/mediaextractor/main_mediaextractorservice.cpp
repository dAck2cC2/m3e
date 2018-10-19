

#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include "MediaExtractorService.h"

namespace android {

	class MediaExtractorServiceThread : public Thread
	{
	public:
		MediaExtractorServiceThread() {};

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
			mService = MediaExtractorService::create();

			mStartedCondition.broadcast();
			mStartedMutex.unlock();

			IPCThreadState::self()->joinThreadPool();

			return false;
		};

	private:
		sp<MediaExtractorService>  mService;
		Mutex              mStartedMutex;
		Condition          mStartedCondition;
	};

}; // namespace android {


//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define SERVICE_TAG     0xF3EC
#define SERVICE_VER     7020
#define SERVICE_ID      "mediaextractor"
#define SERVICE_NAME    "media.extractor"
#define SERVICE_AUTHOR  "yuki.kokoto"

static sp<MediaExtractorServiceThread> gService;

static int open_mediaextractorservice(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	if (gService == NULL) {
		gService = new MediaExtractorServiceThread();
		gService->waitForStarted();
	}

	return OK;
}

hw_module_methods_t method = {
	open_mediaextractorservice
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

