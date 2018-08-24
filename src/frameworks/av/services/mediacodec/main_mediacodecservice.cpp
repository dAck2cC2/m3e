

#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include "MediaCodecService.h"

namespace android {
    
    class MediaCodecServiceThread : public Thread
    {
    public:
        MediaCodecServiceThread() {};
        
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
            mService = MediaCodecService::create();
            
            mStartedCondition.broadcast();
            mStartedMutex.unlock();
            
            IPCThreadState::self()->joinThreadPool();
            
            return false;
        };
        
    private:
        sp<MediaCodecService>  mService;
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
#define SERVICE_ID      "mediacodecservice"
#define SERVICE_NAME    "media.codec"
#define SERVICE_AUTHOR  "yuki.kokoto"

static sp<MediaCodecServiceThread> gService;

int open_mediacodecservice(const struct hw_module_t* module, const char* id,
                      struct hw_device_t** device)
{
    if (gService == NULL) {
        gService = new MediaCodecServiceThread();
        gService->waitForStarted();
    }
    
    return OK;
}

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

