
//#include <stdint.h>
//#include <sys/types.h>

#include <binder/IInterface.h>
#include <binder/Parcel.h>

#include <gui/IConsumerListener.h>
#include <gui/BufferItem.h>

// ---------------------------------------------------------------------------
namespace android {
// ---------------------------------------------------------------------------

enum {
    ON_FRAME_AVAILABLE = IBinder::FIRST_CALL_TRANSACTION,
    ON_BUFFER_RELEASED,
    ON_SIDEBAND_STREAM_CHANGED,
    GET_FRAME_TIMESTAMPS
};
#if 0
class BpConsumerListener : public BpInterface<IConsumerListener>
{
public:
    BpConsumerListener(const sp<IBinder>& impl)
        : BpInterface<IConsumerListener>(impl) {
    }

    virtual ~BpConsumerListener();

    virtual void onFrameAvailable(const BufferItem& item) {
        Parcel data, reply;
        data.writeInterfaceToken(IConsumerListener::getInterfaceDescriptor());
        data.write(item);
        remote()->transact(ON_FRAME_AVAILABLE, data, &reply, IBinder::FLAG_ONEWAY);
    }

    virtual void onBuffersReleased() {
        Parcel data, reply;
        data.writeInterfaceToken(IConsumerListener::getInterfaceDescriptor());
        remote()->transact(ON_BUFFER_RELEASED, data, &reply, IBinder::FLAG_ONEWAY);
    }

    virtual void onSidebandStreamChanged() {
        Parcel data, reply;
        data.writeInterfaceToken(IConsumerListener::getInterfaceDescriptor());
        remote()->transact(ON_SIDEBAND_STREAM_CHANGED, data, &reply, IBinder::FLAG_ONEWAY);
    }

    virtual bool getFrameTimestamps(uint64_t frameNumber,
            FrameTimestamps* outTimestamps) const {
        Parcel data, reply;
        status_t result = data.writeInterfaceToken(
                IConsumerListener::getInterfaceDescriptor());
        if (result != NO_ERROR) {
            ALOGE("getFrameTimestamps failed to write token: %d", result);
            return false;
        }
        result = data.writeUint64(frameNumber);
        if (result != NO_ERROR) {
            ALOGE("getFrameTimestamps failed to write: %d", result);
            return false;
        }
        result = remote()->transact(GET_FRAME_TIMESTAMPS, data, &reply);
        if (result != NO_ERROR) {
            ALOGE("getFrameTimestamps failed to transact: %d", result);
            return false;
        }
        bool found = false;
        result = reply.readBool(&found);
        if (result != NO_ERROR) {
            ALOGE("getFrameTimestamps failed to read: %d", result);
            return false;
        }
        if (found) {
            result = reply.read(*outTimestamps);
            if (result != NO_ERROR) {
                ALOGE("getFrameTimestamps failed to read timestamps: %d",
                        result);
                return false;
            }
        }
        return found;
    }
};

// Out-of-line virtual method definition to trigger vtable emission in this
// translation unit (see clang warning -Wweak-vtables)
BpConsumerListener::~BpConsumerListener() {}
#endif
IMPLEMENT_META_INTERFACE(ConsumerListener, "android.gui.IConsumerListener");

// ----------------------------------------------------------------------

status_t BnConsumerListener::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    return NO_ERROR;
}


// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------
