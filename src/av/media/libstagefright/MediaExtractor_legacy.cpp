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

//#define LOG_NDEBUG 0
#define LOG_TAG "MediaExtractor"
#include "utils/log.h"

#include <media/stagefright/foundation/AMessage.h>
#include "media/stagefright/MediaExtractor.h"
#include "media/stagefright/DataSource.h"
#include "media/stagefright/MediaDefs.h"
#include "media/stagefright/MetaData.h"
#include "utils/String8.h"

#include "include/WAVExtractor.h"

#ifdef ENABLE_FULL_EXTRACTOR
#include "media/AMRExtractor.h"
#include "media/MP3Extractor.h"
#include "media/MPEG4Extractor.h"
#include "media/FragmentedMP4Extractor.h"
#include "media/OggExtractor.h"
#include "media/MPEG2PSExtractor.h"
#include "media/MPEG2TSExtractor.h"
#include "media/WVMExtractor.h"
#include "media/FLACExtractor.h"
#include "media/AACExtractor.h"
#include "media/MatroskaExtractor.h"
#endif // ENABLE_FULL_EXTRACTOR

#ifdef ENABLE_DRM_EXTRACTOR
#include "media/DRMExtractor.h"
#endif // ENABLE_DRM_EXTRACTOR


namespace android {

MediaExtractor::MediaExtractor()
{
    
}

sp<MetaData> MediaExtractor::getMetaData()
{
    return new MetaData;
}

uint32_t MediaExtractor::flags() const
{
    return CAN_SEEK_BACKWARD | CAN_SEEK_FORWARD | CAN_PAUSE | CAN_SEEK;
}

// static
sp<IMediaExtractor> MediaExtractor::Create(
    const sp<DataSource> &source, const char *mime)
{
    sp<AMessage> meta;

    String8 tmp;

    DataSource::RegisterDefaultSniffers();

    if (mime == NULL) {
        float confidence;

        if (!source->sniff(&tmp, &confidence, &meta)) {
            ALOGV("FAILED to autodetect media content.");

            return NULL;
        }

        mime = tmp.string();
        ALOGV("Autodetected media content as '%s' with confidence %.2f",
              mime, confidence);
    }

    bool isDrm = false;
#ifdef ENABLE_DRM_EXTRACTOR

    // DRM MIME type syntax is "drm+type+original" where
    // type is "es_based" or "container_based" and
    // original is the content's cleartext MIME type
    if (!strncmp(mime, "drm+", 4)) {
        const char *originalMime = strchr(mime + 4, '+');

        if (originalMime == NULL) {
            // second + not found
            return NULL;
        }

        ++originalMime;

        if (!strncmp(mime, "drm+es_based+", 13)) {
            // DRMExtractor sets container metadata kKeyIsDRM to 1
            return new DRMExtractor(source, originalMime);
        } else if (!strncmp(mime, "drm+container_based+", 20)) {
            mime = originalMime;
            isDrm = true;
        } else {
            return NULL;
        }
    }

#endif // ENABLE_DRM_EXTRACTOR

    MediaExtractor *ret = NULL;

    if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_WAV)) {
        ret = new WAVExtractor(source);
    }

#ifdef ENABLE_FULL_EXTRACTOR
    else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_MPEG4)
             || !strcasecmp(mime, "audio/mp4")) {
        int fragmented = 0;

        if (meta != NULL && meta->findInt32("fragmented", &fragmented) && fragmented) {
            ret = new FragmentedMP4Extractor(source);
        } else
        {
            ret = new MPEG4Extractor(source);
        }
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_MPEG)) {
        ret = new MP3Extractor(source, meta);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AMR_NB)
               || !strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AMR_WB)) {
        ret = new AMRExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_FLAC)) {
        ret = new FLACExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_WAV)) {
        ret = new WAVExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_OGG)) {
        ret = new OggExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_MATROSKA)) {
        ret = new MatroskaExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_MPEG2TS)) {
        ret = new MPEG2TSExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_WVM)) {
        // Return now.  WVExtractor should not have the DrmFlag set in the block below.
        return new WVMExtractor(source);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AAC_ADTS)) {
        ret = new AACExtractor(source, meta);
    } else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_MPEG2PS)) {
        ret = new MPEG2PSExtractor(source);
    }

#endif // ENABLE_FULL_EXTRACTOR

    if (ret != NULL) {
        if (isDrm) {
            ret->setDrmFlag(true);
        } else {
            ret->setDrmFlag(false);
        }
    }

    return ret;
}

}

