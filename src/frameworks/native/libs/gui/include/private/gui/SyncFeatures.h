/*
 * Copyright (C) 2013 The Android Open Source Project
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

#ifndef ANDROID_GUI_SYNC_FEATURES_H
#define ANDROID_GUI_SYNC_FEATURES_H

#include <utils/Singleton.h>
#include <utils/String8.h>


namespace android {
// ----------------------------------------------------------------------------

class ANDROID_API_GUI SyncFeatures : public Singleton<SyncFeatures> {
    friend class Singleton<SyncFeatures>;
    bool mHasNativeFenceSync;
    bool mHasFenceSync;
    bool mHasWaitSync;
    String8 mString;
    SyncFeatures();

public:
    bool useNativeFenceSync() const;
    bool useFenceSync() const;
    bool useWaitSync() const;
    String8 toString() const;
};

// ----------------------------------------------------------------------------
}; // namespace android

#endif // ANDROID_GUI_SYNC_FEATURES_H
