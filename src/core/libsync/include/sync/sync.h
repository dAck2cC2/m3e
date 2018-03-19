/*
 *  sync.h
 *
 *   Copyright 2012 Google, Inc
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef __SYS_CORE_SYNC_H
#define __SYS_CORE_SYNC_H

#include <cutils/compiler.h>

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

// XXX: These structs are copied from the header "linux/sync.h".
struct sync_fence_info_data {
 uint32_t len;
 char name[32];
 int32_t status;
 uint8_t pt_info[0];
};

struct sync_pt_info {
 uint32_t len;
 char obj_name[32];
 char driver_name[32];
 int32_t status;
 uint64_t timestamp_ns;
 uint8_t driver_data[0];
};

/* timeout in msecs */
ANDROID_API int sync_wait(int fd, int timeout);
ANDROID_API int sync_merge(const char *name, int fd1, int fd2);
ANDROID_API struct sync_fence_info_data *sync_fence_info(int fd);
ANDROID_API struct sync_pt_info *sync_pt_info(struct sync_fence_info_data *info,
                                  struct sync_pt_info *itr);
ANDROID_API void sync_fence_info_free(struct sync_fence_info_data *info);

__END_DECLS

#endif /* __SYS_CORE_SYNC_H */
