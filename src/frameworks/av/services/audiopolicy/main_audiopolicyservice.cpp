
#include <utils/threads.h>
#include "AudioPolicyService.h"

namespace android {

	class AudioPolicyServiceThread : public Thread
	{
	public:
		AudioPolicyServiceThread() {};

		void waitForStarted(void) {
			if (!Thread::isRunning()) {
				mStartedMutex.lock();

				Thread::run("AudioPolicyService");

				mStartedCondition.wait(mStartedMutex);
				mStartedMutex.unlock();
			}
		}
	private:
		virtual bool threadLoop() {
			mStartedMutex.lock();

			sp<ProcessState>  proc = ProcessState::self();
			mService = AudioPolicyService::create();

			mStartedCondition.broadcast();
			mStartedMutex.unlock();

			IPCThreadState::self()->joinThreadPool();

			return false;
		};

	private:
		sp<AudioPolicyService>  mService;
		Mutex			  mStartedMutex;
		Condition		  mStartedCondition;
	};

}; // namespace android {


//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define AUDIO_POLICY_TAG     0xF3EC
#define AUDIO_POLICY_VER     7020
#define AUDIO_POLICY_ID      "audiopolicy"
#define AUDIO_POLICY_NAME    "media.audio_policy"
#define AUDIO_POLICY_AUTHOR  "yuki.kokoto"

static sp<AudioPolicyServiceThread> gService;

int open_audiopolicy(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	if (gService == NULL) {
		gService = new AudioPolicyServiceThread();
		gService->waitForStarted();
	}

	return OK;
}

hw_module_methods_t method = {
	open_audiopolicy
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hw_module_t HMI = {
	AUDIO_POLICY_TAG,    // tag
	AUDIO_POLICY_VER,    // module_api_version
	AUDIO_POLICY_VER,    // hal_api_version
	AUDIO_POLICY_ID,     // id
	AUDIO_POLICY_NAME,   // name
	AUDIO_POLICY_AUTHOR, // author
	&method, // methods
	NULL,    // dso
{ 0 }    // reserved
};


