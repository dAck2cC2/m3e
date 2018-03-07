#define LOG_TAG "ServiceManager"

#include <utils/threads.h>

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

//#include <private/binder/binder_module.h>

namespace android {

class LocalServiceManager : public BnInterface<IServiceManager>, public Thread
{
public:
	LocalServiceManager() {  };

    /**
     * Retrieve an existing service, blocking for a few seconds
     * if it doesn't yet exist.
     */
    virtual sp<IBinder>         getService( const String16& name) const {return NULL;};

    /**
     * Retrieve an existing service, non-blocking.
     */
    virtual sp<IBinder>         checkService( const String16& name) const {return NULL;};

    /**
     * Register a service.
     */
    virtual status_t            addService( const String16& name,
                                            const sp<IBinder>& service,
                                            bool allowIsolated = false) {return OK;};

    /**
     * Return list of all existing services.
     */
    virtual Vector<String16>    listServices() {return mServices;};

    virtual status_t onTransact( 
            uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags = 0)
    {
        return OK;
    };

protected:
    ~LocalServiceManager() {};
    
private:
    virtual bool threadLoop()
    {
		sp<ProcessState>  proc = ProcessState::self();
        proc->becomeContextManager(NULL, NULL);

        sp<IBinder> thiz = IInterface::asBinder(this);
        Parcel parcel;
        parcel.writeStrongBinder(thiz);
        IPCThreadState::self()->transact(0, IBinder::PING_TRANSACTION, parcel, NULL, IBinder::FLAG_ONEWAY);

		IPCThreadState::self()->joinThreadPool();

        return false;
    };
    
private:
    Vector<String16>  mServices;
};

class LocalServiceManagerInit
{
public:
	LocalServiceManagerInit() { 
		sm = new LocalServiceManager();
		sm->run();
	};
	~LocalServiceManagerInit() {};
private:
	sp<LocalServiceManager> sm;
};

static LocalServiceManagerInit gLocalServiceManager;

}; // namespace android
