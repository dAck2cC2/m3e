#define LOG_TAG "ServiceManager"

#include <binder/IServiceManager.h>
#include <utils/threads.h>

namespace android {

class BnServiceManager : public BnInterface<IServiceManager>, public Thread
{
public:
    BnServiceManager() {};

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
            uint32_t flags = 0) {return OK;};

protected:
    ~BnServiceManager() {};
    
private:
    virtual bool threadLoop()
    {
        return true;
    };
    
private:
    Vector<String16>  mServices;
};
    
}; // namespace android
