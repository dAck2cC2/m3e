
#define LOG_TAG "BatteryNotifier"
//#define LOG_NDEBUG 0

#include "mediautils/BatteryNotifier.h"

namespace android {

BatteryNotifier::BatteryNotifier() {}

BatteryNotifier::~BatteryNotifier() {
}

void BatteryNotifier::noteStartVideo() {
}

void BatteryNotifier::noteStopVideo() {
}

void BatteryNotifier::noteResetVideo() {
}

void BatteryNotifier::noteStartAudio() {
}

void BatteryNotifier::noteStopAudio() {
}

void BatteryNotifier::noteResetAudio() {
}

void BatteryNotifier::noteFlashlightOn(const String8& id, int uid) {
}

void BatteryNotifier::noteFlashlightOff(const String8& id, int uid) {
}

void BatteryNotifier::noteResetFlashlight() {
}

void BatteryNotifier::noteStartCamera(const String8& id, int uid) {
}

void BatteryNotifier::noteStopCamera(const String8& id, int uid) {
}

void BatteryNotifier::noteResetCamera() {
}

ANDROID_SINGLETON_STATIC_INSTANCE(BatteryNotifier);

}  // namespace android
