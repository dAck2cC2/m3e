#ifndef AIDL_GENERATED_ANDROID_MEDIA_BP_AUDIO_RECORD_H_
#define AIDL_GENERATED_ANDROID_MEDIA_BP_AUDIO_RECORD_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/media/IAudioRecord.h>

namespace android {

namespace media {

class BpAudioRecord : public ::android::BpInterface<IAudioRecord> {
public:
explicit BpAudioRecord(const ::android::sp<::android::IBinder>& _aidl_impl);
virtual ~BpAudioRecord() = default;
::android::binder::Status start(int32_t event, int32_t triggerSession) override;
::android::binder::Status stop() override;
::android::binder::Status getActiveMicrophones(::std::vector<::android::media::MicrophoneInfo>* activeMicrophones) override;
};  // class BpAudioRecord

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_BP_AUDIO_RECORD_H_
