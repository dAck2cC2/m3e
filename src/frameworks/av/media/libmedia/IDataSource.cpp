//#define LOG_NDEBUG 0
#define LOG_TAG "IDataSource"
#include <utils/Log.h>
#include <utils/Timers.h>

#include <media/IDataSource.h>

namespace android {

IMPLEMENT_META_INTERFACE(DataSource, "android.media.IDataSource");

status_t BnDataSource::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
        return NO_ERROR;
    }

}
