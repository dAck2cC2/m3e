
#define LOG_NDEBUG 0
#define LOG_TAG "BootAnimation"

#if defined(_MSC_VER)
#include <winsock2.h>
#include <windows.h>
#endif  // _MSC_VER

#include <cutils/compiler.h>
#include <cutils/properties.h>
#include <utils/Errors.h>
#include <utils/Mutex.h>
#include <utils/Condition.h>
#include <utils/Thread.h>
#include <utils/Timers.h>
#include <hardware/hardware.h>

#include <binder/IBinder.h>
#include "BootAnimation.h"

#include "initrc_if.h"

static const char TIME_PROP_NAME[] = "service.bootanim.time";
static const char EXIT_PROP_NAME[] = "service.bootanim.exit";

using namespace android;

// Create a typedef for readability.
typedef android::BootAnimation::Animation Animation;

namespace android {

class AnimationTimeout : public Thread {
public:
	AnimationTimeout(int32_t time) :
		mTimeoutSec(time),
		mLckTimer(),
		mCndTimer()
	{
		// EMPTY
	};

private:
	virtual bool threadLoop() {
		AutoMutex _l(mLckTimer);

		mCndTimer.waitRelative(mLckTimer, s2ns(mTimeoutSec));

		// stop boot animation
		property_set(EXIT_PROP_NAME, "1");

		return false;
	};

private:
	int32_t   mTimeoutSec;
	Mutex     mLckTimer;
	Condition mCndTimer;
}; // AnimationTimeout

class AnimationCallbacks : public android::BootAnimation::Callbacks {
public:
	AnimationCallbacks(Mutex& lck, Condition& cnd, int32_t time) :
		mLck(lck), 
		mCnd(cnd), 
		mThd() 
	{
		mThd = new AnimationTimeout(time);
	};

	void init(const Vector<Animation::Part>& parts) override {
		AutoMutex _l(mLck);

		if ((mThd != NULL) && (!mThd->isRunning())) {
			mThd->run("CAnimationStatus");
		}
	};

	void playPart(int partNumber, const Animation::Part& part, int playNumber) override {
		// EMPTY
	};

	void shutdown() override {
		AutoMutex _l(mLck);

		mCnd.signal();
	};

private:
	Mutex&      mLck;
	Condition&  mCnd;
	sp<Thread>  mThd;

protected:
	virtual ~AnimationCallbacks() { mThd = NULL; };
}; // AnimationCallbacks

class CAnimationStatus : public InitRCAnimationStatus {
public:
	CAnimationStatus(int32_t time) :
		mIsRunning(true),
		mLckRunning(),
		mCndRunning()
	{ 
		mCallback = new AnimationCallbacks(mLckRunning, mCndRunning, time);
	};

	// InitRCAnimationStatus
	virtual void wait() override {
		AutoMutex _l(mLckRunning);

		if (mIsRunning) {
			mCndRunning.wait(mLckRunning);
			mIsRunning = false;
		}
	};

	sp<BootAnimation::Callbacks>& getCallback() { return mCallback;  };

private:
	bool                          mIsRunning;
	Mutex                         mLckRunning;
	Condition                     mCndRunning;
	sp<BootAnimation::Callbacks>  mCallback;

protected:
	virtual ~CAnimationStatus() { mCallback = NULL; };
}; // CAnimationStatus

} // namespace android

static sp<BootAnimation>    gBootAnimation;
static sp<CAnimationStatus> gAnimationStatus;

//  interface for initrc

#define BOOT_ANIMATION_TAG     0xF3EC
#define BOOT_ANIMATION_VER     7020
#define BOOT_ANIMATION_ID      "bootanimation"
#define BOOT_ANIMATION_NAME    "android.os.BootAnimation"
#define BOOT_ANIMATION_AUTHOR  "yuki.kokoto"

static int open_bootanimation(const struct hw_module_t* module, const char* id, struct hw_device_t** device);
static int close_bootanimation(struct hw_device_t* device);

hw_module_methods_t method = {
	open_bootanimation
};

#ifdef __cplusplus
extern "C"
#endif
ANDROID_API
hw_module_t HMI = {
	BOOT_ANIMATION_TAG,    // tag
	BOOT_ANIMATION_VER,    // module_api_version
	BOOT_ANIMATION_VER,    // hal_api_version
	BOOT_ANIMATION_ID,     // id
	BOOT_ANIMATION_NAME,   // name
	BOOT_ANIMATION_AUTHOR, // author
	&method, // methods
	NULL,    // dso
{ 0 }    // reserved
};

struct hw_device_t DEV = {
	BOOT_ANIMATION_TAG, // tag
	BOOT_ANIMATION_VER, // version
	&HMI,                // module
	{ 0 },               // reserved
	close_bootanimation // close
};


int open_bootanimation(const struct hw_module_t* module, const char* id,
	struct hw_device_t** device)
{
	int32_t timeout = property_get_int32(TIME_PROP_NAME, 0);
	if (timeout <= 0) {
		return TIMED_OUT;
	}

	if (gAnimationStatus == NULL) {
		gAnimationStatus = new CAnimationStatus(timeout);

		HMI.dso = (void*)(gAnimationStatus.get());
	}

	if (gBootAnimation == NULL) {
		gBootAnimation = new BootAnimation(gAnimationStatus->getCallback());
	}

	if (device != NULL) {
		(*device) = &DEV;
	}

	return OK;
}

int close_bootanimation(struct hw_device_t* device) 
{
	gBootAnimation   = NULL;
	gAnimationStatus = NULL;

	return OK;
}
