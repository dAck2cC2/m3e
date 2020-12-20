/*
 * Copyright (C) 2007-2014 The Android Open Source Project
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

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_UIO_H
#define _MSC_UIO_H

#include "msvc_export.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Implementation of sys/uio.h for Win32.
//

#include <stddef.h>

struct iovec {
  void* iov_base;
  size_t iov_len;
};

MSVC_EXPORT
extern int readv(int fd, struct iovec* vecs, int count);

MSVC_EXPORT
extern int writev(int fd, const struct iovec* vecs, int count);

#ifdef __cplusplus
}
#endif

#endif /* _MSC_UIO_H */
