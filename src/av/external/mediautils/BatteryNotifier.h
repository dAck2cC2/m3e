
#ifndef MEDIA_BATTERY_NOTIFIER_H
#define MEDIA_BATTERY_NOTIFIER_H

#include <utils/Singleton.h>
#include <utils/String8.h>

namespace android {

/**
 * Class used for logging battery life events in mediaserver.
 */
class BatteryNotifier : public Singleton<BatteryNotifier> {

    friend class Singleton<BatteryNotifier>;
    BatteryNotifier();

public:
    ~BatteryNotifier();

    void noteStartVideo();
    void noteStopVideo();
    void noteResetVideo();
    void noteStartAudio();
    void noteStopAudio();
    void noteResetAudio();
    void noteFlashlightOn(const String8& id, int uid);
    void noteFlashlightOff(const String8& id, int uid);
    void noteResetFlashlight();
    void noteStartCamera(const String8& id, int uid);
    void noteStopCamera(const String8& id, int uid);
    void noteResetCamera();
};

}  // namespace android

#endif // MEDIA_BATTERY_NOTIFIER_H
