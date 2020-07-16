#ifndef AIDL_GENERATED_ANDROID_MEDIA_I_PLAYER_H_
#define AIDL_GENERATED_ANDROID_MEDIA_I_PLAYER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <media/VolumeShaper.h>
#include <utils/StrongPointer.h>

namespace android {

namespace media {

class IPlayer : public ::android::IInterface {
public:
DECLARE_META_INTERFACE(Player)
virtual ::android::binder::Status start() = 0;
virtual ::android::binder::Status pause() = 0;
virtual ::android::binder::Status stop() = 0;
virtual ::android::binder::Status setVolume(float vol) = 0;
virtual ::android::binder::Status setPan(float pan) = 0;
virtual ::android::binder::Status setStartDelayMs(int32_t delayMs) = 0;
virtual ::android::binder::Status applyVolumeShaper(const ::android::media::VolumeShaper::Configuration& configuration, const ::android::media::VolumeShaper::Operation& operation) = 0;
enum Call {
  START = ::android::IBinder::FIRST_CALL_TRANSACTION + 0,
  PAUSE = ::android::IBinder::FIRST_CALL_TRANSACTION + 1,
  STOP = ::android::IBinder::FIRST_CALL_TRANSACTION + 2,
  SETVOLUME = ::android::IBinder::FIRST_CALL_TRANSACTION + 3,
  SETPAN = ::android::IBinder::FIRST_CALL_TRANSACTION + 4,
  SETSTARTDELAYMS = ::android::IBinder::FIRST_CALL_TRANSACTION + 5,
  APPLYVOLUMESHAPER = ::android::IBinder::FIRST_CALL_TRANSACTION + 6,
};
};  // class IPlayer

}  // namespace media

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_MEDIA_I_PLAYER_H_
