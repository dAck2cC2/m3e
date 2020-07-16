#ifndef AIDL_GENERATED_ANDROID_MEDIA_BP_PLAYER_H_
#define AIDL_GENERATED_ANDROID_MEDIA_BP_PLAYER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/media/IPlayer.h>

namespace android {

namespace media {

class BpPlayer : public ::android::BpInterface<IPlayer> {
public:
explicit BpPlayer(const ::android::sp<::android::IBinder>& _aidl_impl);
virtual ~BpPlayer() = default;
::android::binder::Status start() override;
::android::binder::Status pause() override;
::android::binder::Status stop() override;
::android::binder::Status setVolume(float vol) override;
::android::binder::Status setPan(float pan) override;
::android::binder::Status setStartDelayMs(int32_t delayMs) override;
::android::binder::Status applyVolumeShaper(const ::android::media::VolumeShaper::Configuration& configuration, const ::android::media::VolumeShaper::Operation& operation) override;
};  // class BpPlayer

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_BP_PLAYER_H_
