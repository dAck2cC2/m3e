#ifndef AIDL_GENERATED_ANDROID_MEDIA_BN_PLAYER_H_
#define AIDL_GENERATED_ANDROID_MEDIA_BN_PLAYER_H_

#include <binder/IInterface.h>
#include <android/media/IPlayer.h>

namespace android {

namespace media {

class BnPlayer : public ::android::BnInterface<IPlayer> {
public:
::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags = 0) override;
};  // class BnPlayer

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_BN_PLAYER_H_
