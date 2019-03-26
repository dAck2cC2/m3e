#ifndef AIDL_GENERATED_ANDROID_I_O_M_X_BUFFER_SOURCE_H_
#define AIDL_GENERATED_ANDROID_I_O_M_X_BUFFER_SOURCE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <media/OMXFenceParcelable.h>
#include <utils/StrongPointer.h>

namespace android {

class ANDROID_API_MEDIA IOMXBufferSource : public ::android::IInterface {
public:
DECLARE_META_INTERFACE(OMXBufferSource)
virtual ::android::binder::Status onOmxExecuting() = 0;
virtual ::android::binder::Status onOmxIdle() = 0;
virtual ::android::binder::Status onOmxLoaded() = 0;
virtual ::android::binder::Status onInputBufferAdded(int32_t bufferID) = 0;
virtual ::android::binder::Status onInputBufferEmptied(int32_t bufferID, const ::android::OMXFenceParcelable& fenceParcel) = 0;
enum Call {
  ONOMXEXECUTING = ::android::IBinder::FIRST_CALL_TRANSACTION + 0,
  ONOMXIDLE = ::android::IBinder::FIRST_CALL_TRANSACTION + 1,
  ONOMXLOADED = ::android::IBinder::FIRST_CALL_TRANSACTION + 2,
  ONINPUTBUFFERADDED = ::android::IBinder::FIRST_CALL_TRANSACTION + 3,
  ONINPUTBUFFEREMPTIED = ::android::IBinder::FIRST_CALL_TRANSACTION + 4,
};
};  // class IOMXBufferSource

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_I_O_M_X_BUFFER_SOURCE_H_
