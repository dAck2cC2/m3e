
#ifndef ANDROID_THREAD_SERVICE_H
#define ANDROID_THREAD_SERVICE_H

#include <utils/threads.h>

// ---------------------------------------------------------------------------
namespace android {

class ThreadService : public Thread
{
public:
	ThreadService() {};
	virtual ~ThreadService() {};

	void waitForStarted(void) 
	{
		if (!Thread::isRunning()) {
			mThreadStartedMutex.lock();

			Thread::run();

			mThreadStartedCondition.wait(mThreadStartedMutex);
			mThreadStartedMutex.unlock();
		}
	}

	void waitForStopped(void) 
	{
		if (Thread::isRunning()) {
			mThreadStartedMutex.lock();

			mIPCThread->stopProcess();
			Thread::requestExitAndWait();
			//mIPCThread->shutdown();

			mThreadStartedMutex.unlock();
		}
	}

private:
	virtual bool startService() = 0;

	virtual bool threadLoop()
	{
		mThreadStartedMutex.lock();
		sp<ProcessState>  proc = ProcessState::self();

		bool chk = startService();

		mIPCThread = IPCThreadState::self();
		mThreadStartedCondition.broadcast();
		mThreadStartedMutex.unlock();

		if (chk) {
			IPCThreadState::self()->joinThreadPool();
		}

		return false;
	};

private:
	Mutex     mThreadStartedMutex;
	Condition mThreadStartedCondition;
	IPCThreadState* mIPCThread;;
};

}; // namespace android
// ---------------------------------------------------------------------------
#endif // ANDROID_THREAD_SERVICE_H
