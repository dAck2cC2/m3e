#define LOG_TAG "ServiceManager"

#include <cutils/compiler.h>

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/Status.h>

#include <utils/threads.h>
#include <utils/KeyedVector.h>

#include <hardware/hardware.h>

namespace android {

class LocalServiceManager : public BBinder, public Thread, public IBinder::DeathRecipient
{
public:
    LocalServiceManager() : mDescriptor("android.os.IServiceManager") {  };
    virtual const String16& getInterfaceDescriptor() const { return mDescriptor; };
    
    virtual status_t onTransact( 
            uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags = 0)
    {
        switch (code) {
            case IServiceManager::CHECK_SERVICE_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                String16 name = data.readString16();
                
                sp<IBinder> binder;
                ssize_t n = mServices.indexOfKey(name);
                if (n >= 0) {
                    binder = mServices.valueFor(name);
                }
                
                reply->writeStrongBinder(binder);
            }
                break;
            case IServiceManager::ADD_SERVICE_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                String16 name = data.readString16();
                sp<IBinder> binder = data.readStrongBinder();
                int32_t allowIsolated = data.readInt32();
                ssize_t n = mServices.indexOfKey(name);
                if (n < 0) {
                    n = mServices.add(name, binder);
                }
                if (n < 0) {
                    reply->writeInt32(n);
                } else {
                    binder->linkToDeath(this);
                    reply->writeInt32(binder::Status::EX_NONE);
                }
            }
                break;
            case IServiceManager::LIST_SERVICES_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                int32_t index = data.readInt32();
                
                status_t ret = BAD_INDEX;
                String16 name;
                if (index < mServices.size()) {
                    name = mServices.keyAt(index);
                    ret = NO_ERROR;
                }
                reply->writeString16(name);
                return (ret);
            }
            case IServiceManager::GET_SERVICE_TRANSACTION:
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
        
        return OK;
    };

    virtual void binderDied(const wp<IBinder>& who)
    {
        for (size_t i = 0; i < mServices.size(); ++i) {
            if (who == mServices[i]) {
                mServices.removeItemsAt(i);
                break;
            }
        }
    };

    void waitForStarted(void) {
        if (!Thread::isRunning()) {
            mThreadStartedMutex.lock();
            
            Thread::run();
            
            mThreadStartedCondition.wait(mThreadStartedMutex);
            mThreadStartedMutex.unlock();
        }
    };
    
protected:
    ~LocalServiceManager() {};
    
private:
    virtual bool threadLoop()
    {
        mThreadStartedMutex.lock();

		sp<ProcessState>  proc = ProcessState::self();
        proc->becomeContextManager(NULL, NULL);

        {
            Parcel parcel;
            parcel.writeInterfaceToken(mDescriptor);
            parcel.writeStrongBinder(this);
            IPCThreadState::self()->transact(0, IBinder::PING_TRANSACTION, parcel, NULL, IBinder::FLAG_ONEWAY);
        }
        
        mThreadStartedCondition.broadcast();
        mThreadStartedMutex.unlock();
        
		IPCThreadState::self()->joinThreadPool();

        return false;
    };
    
private:
    const android::String16              mDescriptor;
    KeyedVector<String16, sp<IBinder> >  mServices;
    
    Mutex     mThreadStartedMutex;
    Condition mThreadStartedCondition;
};

}; // namespace android

//  interface for initrc

#define SERVICE_MANAGER_TAG     0xF3EC
#define SERVICE_MANAGER_VER     7020
#define SERVICE_MANAGER_ID      "servicemanager"
#define SERVICE_MANAGER_NAME    "android.os.IServiceManager"
#define SERVICE_MANAGER_AUTHOR  "yuki.kokoto"

android::sp<android::LocalServiceManager> gServiceManager;

int open_servicemanager(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device)
{
    if (gServiceManager == NULL) {
        gServiceManager = new android::LocalServiceManager();
        if (gServiceManager != NULL) {
            gServiceManager->waitForStarted();
        }
    }
    
    return android::OK;
}

hw_module_methods_t method = {
    open_servicemanager
};

#ifdef __cplusplus
extern "C"
#endif
ANDROID_API 
hw_module_t HMI = {
    SERVICE_MANAGER_TAG,    // tag
    SERVICE_MANAGER_VER,    // module_api_version
    SERVICE_MANAGER_VER,    // hal_api_version
    SERVICE_MANAGER_ID,     // id
    SERVICE_MANAGER_NAME,   // name
    SERVICE_MANAGER_AUTHOR, // author
    &method, // methods
    NULL,    // dso
    { 0 }    // reserved
};
