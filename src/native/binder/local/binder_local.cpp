
#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <cutils/threads.h>

#include <utils/Errors.h>
#include <utils/Vector.h>
#include <utils/Looper.h>

#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>

#include <private/binder/binder_module.h>

namespace android {

class BinderTransactionHandler : public MessageHandler
{
public:
    Parcel data;
    virtual void handleMessage(const Message& message) {
    }
};
    
static mutex_t mLock = MUTEX_INITIALIZER;
static Vector<sp<Looper> > mServices;

#define BINDER_CMD_SIZE  (sizeof(int32_t))
#define BINDER_DATA_SIZE (sizeof(binder_transaction_data))

static status_t binder_transaction(binder_transaction_data* tr)
{
    if (!tr) return BAD_VALUE;
    
    status_t result = NO_ERROR;

    sp<Looper> service;
    
    mutex_lock(&mLock);
    if ((tr->target.handle >= 0) && (tr->target.handle < mServices.size())) {
        service = mServices[tr->target.handle];
    }
    mutex_unlock(&mLock);

    if (service != NULL) {
        sp<BinderTransactionHandler> handler = new BinderTransactionHandler();
        handler->data.setData((uint8_t *)(tr->data.ptr.buffer), tr->data_size);
        Message msg;
        service->sendMessage(handler, msg);
    } else {
        result = DEAD_OBJECT;
    }
    
    return result;
}
    
status_t binder_write_read_local(binder_write_read* pbwr)
{
    status_t result = BAD_VALUE;

    if (!pbwr) return result;
    
    if (pbwr->write_buffer && pbwr->write_size >= BINDER_CMD_SIZE) {
        Parcel wData;
        result = wData.setData((uint8_t *)(pbwr->write_buffer), pbwr->write_size);
        if (result) return result;
        
        int32_t cmd = -1;
        result = wData.readInt32(&cmd);
        if (result) return result;
        
        switch (cmd) {
            case BC_TRANSACTION:
                binder_transaction_data tr;
                result = wData.read((void *)(&tr), sizeof(binder_transaction_data));
                if (result) return result;
                
                result = binder_transaction(&tr);
                break;
            case BC_ENTER_LOOPER:
            case BC_REGISTER_LOOPER:
                if (pbwr->read_buffer && pbwr->read_size) {
                    
                }
                break;
            case BC_EXIT_LOOPER:
                break;
            default:
                break;
        }
    }
    
    
    return result;
}

} // namespace android
