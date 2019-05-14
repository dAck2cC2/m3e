/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if ENABLE_POWERMANAGER
#include <android/hardware/power/1.0/IPower.h>
#endif
#include <stdint.h>
#include <sys/types.h>

#include <android/log.h>
#include <utils/Errors.h>

#include <binder/IServiceManager.h>
#if ENABLE_POWERMANAGER
#include <powermanager/IPowerManager.h>
#include <powermanager/PowerManager.h>
#endif

#include "PowerHAL.h"

#if ENABLE_POWERMANAGER
using android::hardware::power::V1_0::PowerHint;
#endif
namespace android {
// ---------------------------------------------------------------------------

status_t PowerHAL::vsyncHint(bool enabled) {
    Mutex::Autolock _l(mlock);
#if ENABLE_POWERMANAGER
    if (mPowerManager == NULL) {
        const String16 serviceName("power");
        sp<IBinder> bs = defaultServiceManager()->checkService(serviceName);
        if (bs == NULL) {
            return NAME_NOT_FOUND;
        }
        mPowerManager = interface_cast<IPowerManager>(bs);
    }
#endif
    status_t status;
#if ENABLE_POWERMANAGER
    status = mPowerManager->powerHint(static_cast<int>(PowerHint::VSYNC),
            enabled ? 1 : 0);
    if(status == DEAD_OBJECT) {
        mPowerManager = NULL;
    }
#endif
    return status;
}

// ---------------------------------------------------------------------------
}; // namespace android

