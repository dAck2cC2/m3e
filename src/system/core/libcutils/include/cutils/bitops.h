/*
 * Copyright (C) 2011 The Android Open Source Project
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

#ifndef __CUTILS_BITOPS_H
#define __CUTILS_BITOPS_H

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <sys/cdefs.h>

/* M3E ADD */
#include "m3e_config.h"

__BEGIN_DECLS

#if defined(CFG_NO_POPCNT)

#define POPCNT(x) \
int c = 0; \
for (; x != 0; x >>= 1) {\
if (x & 1) c++; \
}\
return c

static inline int popcount(unsigned int v) {
    POPCNT(v);
}

static inline int popcountl(unsigned long v) {
    POPCNT(v);
}

static inline int popcountll(unsigned long long v) {
    POPCNT(v);
}

#else // CFG_NO_POPCNT
static inline int popcount(unsigned int x) {
    return __builtin_popcount(x);
}

static inline int popcountl(unsigned long x) {
    return __builtin_popcountl(x);
}

static inline int popcountll(unsigned long long x) {
    return __builtin_popcountll(x);
}

#endif // CFG_NO_POPCNT

__END_DECLS

#endif /* __CUTILS_BITOPS_H */
