//
// Copyright (C) 2017 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#define LOG_TAG "ConfigStore"

#include <android-base/logging.h>
#include <configstore/Utils.h>

namespace android {
namespace hardware {
namespace details {

bool wouldLogInfo() {
#if TODO
    return WOULD_LOG(INFO);
#else
	return false;
#endif
}

void logAlwaysInfo(const std::string& message) {
#if TODO
    LOG(INFO) << message;
#endif
}

void logAlwaysError(const std::string& message) {
#if TODO
    LOG(ERROR) << message;
#endif
}

}  // namespace details
}  // namespace hardware
}  // namespace android