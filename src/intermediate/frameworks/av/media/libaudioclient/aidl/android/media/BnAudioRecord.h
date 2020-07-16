#ifndef AIDL_GENERATED_ANDROID_MEDIA_BN_AUDIO_RECORD_H_
#define AIDL_GENERATED_ANDROID_MEDIA_BN_AUDIO_RECORD_H_

#include <binder/IInterface.h>
#include <android/media/IAudioRecord.h>

namespace android {

namespace media {

class BnAudioRecord : public ::android::BnInterface<IAudioRecord> {
public:
::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags = 0) override;
};  // class BnAudioRecord

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_BN_AUDIO_RECORD_H_
