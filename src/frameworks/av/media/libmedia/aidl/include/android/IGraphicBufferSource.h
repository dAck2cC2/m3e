#ifndef AIDL_GENERATED_ANDROID_I_GRAPHIC_BUFFER_SOURCE_H_
#define AIDL_GENERATED_ANDROID_I_GRAPHIC_BUFFER_SOURCE_H_

#include <android/IOMXNode.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

class ANDROID_API_MEDIA IGraphicBufferSource : public ::android::IInterface {
public:
DECLARE_META_INTERFACE(GraphicBufferSource)
virtual ::android::binder::Status configure(const ::android::sp<::android::IOMXNode>& omxNode, int32_t dataSpace) = 0;
virtual ::android::binder::Status setSuspend(bool suspend, int64_t suspendTimeUs) = 0;
virtual ::android::binder::Status setRepeatPreviousFrameDelayUs(int64_t repeatAfterUs) = 0;
virtual ::android::binder::Status setMaxFps(float maxFps) = 0;
virtual ::android::binder::Status setTimeLapseConfig(double fps, double captureFps) = 0;
virtual ::android::binder::Status setStartTimeUs(int64_t startTimeUs) = 0;
virtual ::android::binder::Status setStopTimeUs(int64_t stopTimeUs) = 0;
virtual ::android::binder::Status getStopTimeOffsetUs(int64_t* _aidl_return) = 0;
virtual ::android::binder::Status setColorAspects(int32_t aspects) = 0;
virtual ::android::binder::Status setTimeOffsetUs(int64_t timeOffsetsUs) = 0;
virtual ::android::binder::Status signalEndOfInputStream() = 0;
enum Call {
  CONFIGURE = ::android::IBinder::FIRST_CALL_TRANSACTION + 0,
  SETSUSPEND = ::android::IBinder::FIRST_CALL_TRANSACTION + 1,
  SETREPEATPREVIOUSFRAMEDELAYUS = ::android::IBinder::FIRST_CALL_TRANSACTION + 2,
  SETMAXFPS = ::android::IBinder::FIRST_CALL_TRANSACTION + 3,
  SETTIMELAPSECONFIG = ::android::IBinder::FIRST_CALL_TRANSACTION + 4,
  SETSTARTTIMEUS = ::android::IBinder::FIRST_CALL_TRANSACTION + 5,
  SETSTOPTIMEUS = ::android::IBinder::FIRST_CALL_TRANSACTION + 6,
  GETSTOPTIMEOFFSETUS = ::android::IBinder::FIRST_CALL_TRANSACTION + 7,
  SETCOLORASPECTS = ::android::IBinder::FIRST_CALL_TRANSACTION + 8,
  SETTIMEOFFSETUS = ::android::IBinder::FIRST_CALL_TRANSACTION + 9,
  SIGNALENDOFINPUTSTREAM = ::android::IBinder::FIRST_CALL_TRANSACTION + 10,
};
};  // class IGraphicBufferSource

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_I_GRAPHIC_BUFFER_SOURCE_H_
