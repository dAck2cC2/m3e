/*
 * Copyright 2018 The Android Open Source Project
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

#ifndef ANDROID_AUDIO_STRING_H
#define ANDROID_AUDIO_STRING_H

#include <string.h>

/** similar to strlcpy but also zero fills to end of string buffer, ensures no data leak
    in parceled data sent over binder.*/
inline size_t audio_utils_strlcpy_zerofill(char *dst, const char *src, size_t dst_size) {
#if defined(_MSC_VER) // M3E: temporary implmentation which may not be proper
    strncpy(dst, src, dst_size);
    dst[dst_size - 1] = '\0';
    return strlen(dst);
#else  // M3E
    const size_t srclen = strlcpy(dst, src, dst_size);
    const size_t srclen_with_zero = srclen + 1; /* include zero termination in length. */
    if (srclen_with_zero < dst_size) {
        const size_t num_zeroes = dst_size - srclen_with_zero;
        memset(dst + srclen_with_zero, 0 /* value */, num_zeroes); /* clear remaining buffer */
    }
    return srclen;
#endif // M3E
}

#ifdef __cplusplus

/** similar to audio_utils_strlcpy_zerofill for fixed size destination string. */
template <size_t size>
inline size_t audio_utils_strlcpy_zerofill(char (&dst)[size], const char *src) {
    return audio_utils_strlcpy_zerofill(dst, src, size);
}

/** similar to strlcpy for fixed size destination string. */
template <size_t size>
inline size_t audio_utils_strlcpy(char (&dst)[size], const char *src) {
#if defined(_MSC_VER) // M3E: no strlcpy on MSVC
    return audio_utils_strlcpy_zerofill(dst, src, size);
#else  // M3E
    return strlcpy(dst, src, size);
#endif // M3E
}

#endif // __cplusplus

#endif // !ANDROID_AUDIO_STRING_H
