
#include <cutils/compiler.h>
#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <hardware/hardware.h>

#include "SurfaceFlinger.h"

namespace android {

class SurfaceFlingerService : public Thread
{
public:
    SurfaceFlingerService()  {};
    ~SurfaceFlingerService() {};
    void waitForStarted(void) {
        if (!Thread::isRunning()) {
            mThreadStartedMutex.lock();
            
            Thread::run();
            
            mThreadStartedCondition.wait(mThreadStartedMutex);
            mThreadStartedMutex.unlock();
        }
    }
    void waitForStopped(void) {
        if (Thread::isRunning()) {
            mThreadStartedMutex.lock();
            
            mIPCThread->stopProcess();
            Thread::requestExitAndWait();
            //mIPCThread->shutdown();
            
            mThreadStartedMutex.unlock();
        }
    }
private:
    virtual bool threadLoop()
    {
        mThreadStartedMutex.lock();
        
        sp<ProcessState> ps(ProcessState::self());
        
        sp<SurfaceFlinger> flinger = new SurfaceFlinger();
        
        // publish surface flinger
        sp<IServiceManager> sm(defaultServiceManager());
        sm->addService(String16(SurfaceFlinger::getServiceName()), flinger, false);

        mIPCThread = IPCThreadState::self();
        
        mThreadStartedCondition.broadcast();
        mThreadStartedMutex.unlock();
        
        IPCThreadState::self()->joinThreadPool();
        
        return false;
    };
private:
    Mutex     mThreadStartedMutex;
    Condition mThreadStartedCondition;
    IPCThreadState* mIPCThread;;
};

}; // namespace android


//  interface for initrc

#define SURFACE_FLINGER_TAG     0xF3EC
#define SURFACE_FLINGER_VER     7020
#define SURFACE_FLINGER_ID      "surfaceflinger"
#define SURFACE_FLINGER_NAME    "android.SurfaceFlinger"
#define SURFACE_FLINGER_AUTHOR  "yuki.kokoto"

android::sp<android::SurfaceFlingerService> gSurfaceFlinger;

int open_surfaceflinger(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device)
{
    if (gSurfaceFlinger == NULL) {
        gSurfaceFlinger = new android::SurfaceFlingerService();
        if (gSurfaceFlinger != NULL) {
            gSurfaceFlinger->waitForStarted();
        }
    }
    
    return android::OK;
}

hw_module_methods_t method = {
    open_surfaceflinger
};

hw_module_t HMI = {
    SURFACE_FLINGER_TAG, // tag
    SURFACE_FLINGER_VER, // module_api_version
    SURFACE_FLINGER_VER, // hal_api_version
    SURFACE_FLINGER_ID,  // id
    SURFACE_FLINGER_NAME, // name
    SURFACE_FLINGER_AUTHOR, // author
    &method, // methods
    NULL,    // dso
    { 0 }    // reserved
};
