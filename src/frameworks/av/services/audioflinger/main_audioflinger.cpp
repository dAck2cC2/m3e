
#include <utils/threads.h>
#include "AudioFlinger.h"

namespace android {

	class AudioFlingerService : public Thread
	{
	public:
		AudioFlingerService() {};

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
			mFlinger = AudioFlinger::create();

			mStartedCondition.broadcast();
			mStartedMutex.unlock();

			IPCThreadState::self()->joinThreadPool();

			return false;
		};

	private:
		sp<AudioFlinger>  mFlinger;
		Mutex			  mStartedMutex;
		Condition		  mStartedCondition;
	};

}; // namespace android {

   
//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define AUDIO_FLINGER_TAG     0xF3EC
#define AUDIO_FLINGER_VER     7020
#define AUDIO_FLINGER_ID      "audioflinger"
#define AUDIO_FLINGER_NAME    "media.audio_flinger"
#define AUDIO_FLINGER_AUTHOR  "yuki.kokoto"

static sp<AudioFlingerService> gService;

int open_audioflinger(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	if (gService == NULL) {
		gService = new AudioFlingerService();
		gService->waitForStarted();
	}

	return OK;
}

hw_module_methods_t method = {
	open_audioflinger
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hw_module_t HMI = {
	AUDIO_FLINGER_TAG,    // tag
	AUDIO_FLINGER_VER,    // module_api_version
	AUDIO_FLINGER_VER,    // hal_api_version
	AUDIO_FLINGER_ID,     // id
	AUDIO_FLINGER_NAME,   // name
	AUDIO_FLINGER_AUTHOR, // author
	&method, // methods
	NULL,    // dso
{ 0 }    // reserved
};

