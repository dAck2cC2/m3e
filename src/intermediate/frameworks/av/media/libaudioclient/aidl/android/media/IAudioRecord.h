#ifndef AIDL_GENERATED_ANDROID_MEDIA_I_AUDIO_RECORD_H_
#define AIDL_GENERATED_ANDROID_MEDIA_I_AUDIO_RECORD_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <media/MicrophoneInfo.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace media {

class IAudioRecord : public ::android::IInterface {
public:
DECLARE_META_INTERFACE(AudioRecord)
virtual ::android::binder::Status start(int32_t event, int32_t triggerSession) = 0;
virtual ::android::binder::Status stop() = 0;
virtual ::android::binder::Status getActiveMicrophones(::std::vector<::android::media::MicrophoneInfo>* activeMicrophones) = 0;
enum Call {
  START = ::android::IBinder::FIRST_CALL_TRANSACTION + 0,
  STOP = ::android::IBinder::FIRST_CALL_TRANSACTION + 1,
  GETACTIVEMICROPHONES = ::android::IBinder::FIRST_CALL_TRANSACTION + 2,
};
};  // class IAudioRecord

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_I_AUDIO_RECORD_H_
