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

#ifndef MEDIA_DEFS_H_

#define MEDIA_DEFS_H_

#if defined(_MSC_VER)
#define EXTERN extern ANDROID_API_MEDIA
#else
#define EXTERN extern
#endif

namespace android {

EXTERN const char *MEDIA_MIMETYPE_IMAGE_JPEG;

EXTERN const char *MEDIA_MIMETYPE_VIDEO_VP8;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_VP9;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_AVC;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_HEVC;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_MPEG4;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_H263;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_MPEG2;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_RAW;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_DOLBY_VISION;
EXTERN const char *MEDIA_MIMETYPE_VIDEO_SCRAMBLED;

EXTERN const char *MEDIA_MIMETYPE_AUDIO_AMR_NB;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_AMR_WB;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_MPEG;           // layer III
EXTERN const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_I;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_II;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_MIDI;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_AAC;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_QCELP;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_VORBIS;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_OPUS;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_G711_ALAW;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_G711_MLAW;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_RAW;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_FLAC;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_AAC_ADTS;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_MSGSM;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_AC3;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_EAC3;
EXTERN const char *MEDIA_MIMETYPE_AUDIO_SCRAMBLED;

EXTERN const char *MEDIA_MIMETYPE_CONTAINER_MPEG4;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_WAV;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_OGG;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_MATROSKA;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_MPEG2TS;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_AVI;
EXTERN const char *MEDIA_MIMETYPE_CONTAINER_MPEG2PS;

EXTERN const char *MEDIA_MIMETYPE_TEXT_3GPP;
EXTERN const char *MEDIA_MIMETYPE_TEXT_SUBRIP;
EXTERN const char *MEDIA_MIMETYPE_TEXT_VTT;
EXTERN const char *MEDIA_MIMETYPE_TEXT_CEA_608;
EXTERN const char *MEDIA_MIMETYPE_TEXT_CEA_708;
EXTERN const char *MEDIA_MIMETYPE_DATA_TIMED_ID3;

// These are values exported to JAVA API that need to be in sync with
// frameworks/base/media/java/android/media/AudioFormat.java. Unfortunately,
// they are not defined in frameworks/av, so defining them here.
enum AudioEncoding {
    kAudioEncodingPcm16bit = 2,
    kAudioEncodingPcm8bit = 3,
    kAudioEncodingPcmFloat = 4,
};

}  // namespace android

#endif  // MEDIA_DEFS_H_
