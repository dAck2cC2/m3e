/*
 * Copyright (C) 2014 The Android Open Source Project
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

/*
 * This file defines an NDK API.
 * Do not remove methods.
 * Do not change method signatures.
 * Do not change the value of constants.
 * Do not change the size of any of the classes defined in here.
 * Do not reference types that are not part of the NDK.
 * Do not #include files that aren't part of the NDK.
 */

#ifndef _NDK_MEDIA_FORMAT_H
#define _NDK_MEDIA_FORMAT_H

#include <sys/cdefs.h>
#include <sys/types.h>

#include "NdkMediaError.h"

__BEGIN_DECLS

struct AMediaFormat;
typedef struct AMediaFormat AMediaFormat;

#if __ANDROID_API__ >= 21

MEDIANDK_API
AMediaFormat *AMediaFormat_new();
MEDIANDK_API
media_status_t AMediaFormat_delete(AMediaFormat*);

/**
 * Human readable representation of the format. The returned string is owned by the format,
 * and remains valid until the next call to toString, or until the format is deleted.
 */
MEDIANDK_API
const char* AMediaFormat_toString(AMediaFormat*);

MEDIANDK_API
bool AMediaFormat_getInt32(AMediaFormat*, const char *name, int32_t *out);
MEDIANDK_API
bool AMediaFormat_getInt64(AMediaFormat*, const char *name, int64_t *out);
MEDIANDK_API
bool AMediaFormat_getFloat(AMediaFormat*, const char *name, float *out);
/**
 * The returned data is owned by the format and remains valid as long as the named entry
 * is part of the format.
 */
MEDIANDK_API
bool AMediaFormat_getBuffer(AMediaFormat*, const char *name, void** data, size_t *size);
/**
 * The returned string is owned by the format, and remains valid until the next call to getString,
 * or until the format is deleted.
 */
MEDIANDK_API
bool AMediaFormat_getString(AMediaFormat*, const char *name, const char **out);


MEDIANDK_API
void AMediaFormat_setInt32(AMediaFormat*, const char* name, int32_t value);
MEDIANDK_API
void AMediaFormat_setInt64(AMediaFormat*, const char* name, int64_t value);
MEDIANDK_API
void AMediaFormat_setFloat(AMediaFormat*, const char* name, float value);
/**
 * The provided string is copied into the format.
 */
MEDIANDK_API
void AMediaFormat_setString(AMediaFormat*, const char* name, const char* value);
/**
 * The provided data is copied into the format.
 */
MEDIANDK_API
void AMediaFormat_setBuffer(AMediaFormat*, const char* name, void* data, size_t size);



/**
 * XXX should these be ints/enums that we look up in a table as needed?
 */
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_ATTENUATION_FACTOR;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_BOOST_FACTOR;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_HEAVY_COMPRESSION;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_TARGET_REFERENCE_LEVEL;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_ENCODED_TARGET_LEVEL;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_MAX_OUTPUT_CHANNEL_COUNT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_PROFILE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AAC_SBR_MODE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_AUDIO_SESSION_ID;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_BITRATE_MODE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_BIT_RATE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CAPTURE_RATE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CHANNEL_COUNT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CHANNEL_MASK;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_COLOR_FORMAT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_COLOR_RANGE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_COLOR_STANDARD;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_COLOR_TRANSFER;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_COMPLEXITY;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CSD;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CSD_0;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CSD_1;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_CSD_2;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_DISPLAY_CROP;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_DISPLAY_HEIGHT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_DISPLAY_WIDTH;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_DURATION;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_FLAC_COMPRESSION_LEVEL;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_FRAME_RATE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_GRID_COLUMNS;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_GRID_ROWS;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_HDR_STATIC_INFO;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_HEIGHT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_INTRA_REFRESH_PERIOD;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_IS_ADTS;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_IS_AUTOSELECT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_IS_DEFAULT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_IS_FORCED_SUBTITLE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_I_FRAME_INTERVAL;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_LANGUAGE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_LATENCY;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_LEVEL;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_MAX_HEIGHT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_MAX_INPUT_SIZE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_MAX_WIDTH;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_MIME;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_MPEG_USER_DATA;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_OPERATING_RATE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_PCM_ENCODING;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_PRIORITY;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_PROFILE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_PUSH_BLANK_BUFFERS_ON_STOP;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_REPEAT_PREVIOUS_FRAME_AFTER;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_ROTATION;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_SAMPLE_RATE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_SEI;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_SLICE_HEIGHT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_STRIDE;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYER_ID;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYERING;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TILE_HEIGHT;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TILE_WIDTH;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TIME_US;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TRACK_ID;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_TRACK_INDEX;
MEDIANDK_API
extern const char* AMEDIAFORMAT_KEY_WIDTH;

#endif /* __ANDROID_API__ >= 21 */

#if __ANDROID_API__ >= 28
MEDIANDK_API
bool AMediaFormat_getDouble(AMediaFormat*, const char *name, double *out);
MEDIANDK_API
bool AMediaFormat_getRect(AMediaFormat*, const char *name,
                          int32_t *left, int32_t *top, int32_t *right, int32_t *bottom);

MEDIANDK_API
void AMediaFormat_setDouble(AMediaFormat*, const char* name, double value);
MEDIANDK_API
void AMediaFormat_setSize(AMediaFormat*, const char* name, size_t value);
MEDIANDK_API
void AMediaFormat_setRect(AMediaFormat*, const char* name,
                          int32_t left, int32_t top, int32_t right, int32_t bottom);
#endif /* __ANDROID_API__ >= 28 */

__END_DECLS

#endif // _NDK_MEDIA_FORMAT_H
