/*
 * Copyright 2019 The Android Open Source Project
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

#include <binder/IPCThreadState.h>
#if ENABLE_HWBINDER // M3E: no hwbinder
#include <hwbinder/IPCThreadState.h>
#endif // M3E
#include <private/gui/BufferQueueThreadState.h>
#include <unistd.h>

namespace android {

uid_t BufferQueueThreadState::getCallingUid() {
#if ENABLE_HWBINDER // M3E: no hwbinder
    if (hardware::IPCThreadState::self()->isServingCall()) {
        return hardware::IPCThreadState::self()->getCallingUid();
    }
#endif // M3E
    return IPCThreadState::self()->getCallingUid();
}

pid_t BufferQueueThreadState::getCallingPid() {
#if ENABLE_HWBINDER // M3E: no hwbinder
    if (hardware::IPCThreadState::self()->isServingCall()) {
        return hardware::IPCThreadState::self()->getCallingPid();
    }
#endif // M3E
    return IPCThreadState::self()->getCallingPid();
}

} // namespace android
