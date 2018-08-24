

#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include "MediaPlayerService.h"

namespace android {
    
    class MediaPlayerServiceThread : public Thread
    {
    public:
        MediaPlayerServiceThread() {};
        
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
            mPlayer = MediaPlayerService::instantiate();
            
            mStartedCondition.broadcast();
            mStartedMutex.unlock();
            
            IPCThreadState::self()->joinThreadPool();
            
            return false;
        };
        
    private:
        sp<MediaPlayerService>  mPlayer;
        Mutex              mStartedMutex;
        Condition          mStartedCondition;
    };
    
}; // namespace android {


//  interface for initrc

#include <cutils/compiler.h>
#include <utils/Errors.h>
#include <hardware/hardware.h>

using namespace android;

#define MEDIA_PLAYER_TAG     0xF3EC
#define MEDIA_PLAYER_VER     7020
#define MEDIA_PLAYER_ID      "mediaplayerservice"
#define MEDIA_PLAYER_NAME    "media.player"
#define MEDIA_PLAYER_AUTHOR  "yuki.kokoto"

static sp<MediaPlayerServiceThread> gService;

int open_mediaplayerservice(const struct hw_module_t* module, const char* id,
                      struct hw_device_t** device)
{
    if (gService == NULL) {
        gService = new MediaPlayerServiceThread();
        gService->waitForStarted();
    }
    
    return OK;
}

hw_module_methods_t method = {
    open_mediaplayerservice
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
hw_module_t HMI = {
    MEDIA_PLAYER_TAG,    // tag
    MEDIA_PLAYER_VER,    // module_api_version
    MEDIA_PLAYER_VER,    // hal_api_version
    MEDIA_PLAYER_ID,     // id
    MEDIA_PLAYER_NAME,   // name
    MEDIA_PLAYER_AUTHOR, // author
    &method, // methods
    NULL,    // dso
    { 0 }    // reserved
};

