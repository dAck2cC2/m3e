/*
 * Copyright (C) 2016 The Android Open Source Project
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

#define LOG_TAG "FMQ"
#include <android-base/logging.h>

// M3E: add
#if defined(_MSC_VER)
#include "fmq/MessageQueue.h"
#endif

namespace android {
namespace hardware {
namespace details {

void check(bool exp) {
    CHECK(exp);
}

void logError(const std::string &message) {
#if !defined(_MSC_VER) // M3E:
    LOG(ERROR) << message;
#endif
}

}  // namespace details
}  // namespace hardware
}  // namespace android