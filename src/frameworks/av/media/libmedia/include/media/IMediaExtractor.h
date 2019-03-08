/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifndef IMEDIA_EXTRACTOR_BASE_H_

#define IMEDIA_EXTRACTOR_BASE_H_

#include <media/IMediaSource.h>
#include <media/stagefright/DataSource.h>

namespace android {

class MetaData;

class ANDROID_API_MEDIA IMediaExtractor : public IInterface {
public:
    DECLARE_META_INTERFACE(MediaExtractor);

    virtual size_t countTracks() = 0;
    virtual sp<IMediaSource> getTrack(size_t index) = 0;

    enum GetTrackMetaDataFlags {
        kIncludeExtensiveMetaData = 1
    };
    virtual sp<MetaData> getTrackMetaData(
            size_t index, uint32_t flags = 0) = 0;

    // Return container specific meta-data. The default implementation
    // returns an empty metadata object.
    virtual sp<MetaData> getMetaData() = 0;

    enum Flags {
        CAN_SEEK_BACKWARD  = 1,  // the "seek 10secs back button"
        CAN_SEEK_FORWARD   = 2,  // the "seek 10secs forward button"
        CAN_PAUSE          = 4,
        CAN_SEEK           = 8,  // the "seek bar"
    };

    // If subclasses do _not_ override this, the default is
    // CAN_SEEK_BACKWARD | CAN_SEEK_FORWARD | CAN_SEEK | CAN_PAUSE
    virtual uint32_t flags() const = 0;

    // for DRM
    virtual void setDrmFlag(bool flag) = 0;
    virtual bool getDrmFlag() = 0;
    virtual char* getDrmTrackInfo(size_t trackID, int *len)  = 0;
    virtual void setUID(uid_t uid)  = 0;

    virtual const char * name() = 0;
};


class ANDROID_API_MEDIA BnMediaExtractor: public BnInterface<IMediaExtractor>
{
public:
    virtual status_t    onTransact(uint32_t code, const Parcel& data, Parcel* reply,
                                uint32_t flags = 0);
};

void ANDROID_API_MEDIA registerMediaExtractor(
        const sp<IMediaExtractor> &extractor,
        const sp<DataSource> &source,
        const char *mime);

void registerMediaSource(
        const sp<IMediaExtractor> &extractor,
        const sp<IMediaSource> &source);

status_t ANDROID_API_MEDIA dumpExtractors(int fd, const Vector<String16>& args);


}  // namespace android

#endif  // IMEDIA_EXTRACTOR_BASE_H_