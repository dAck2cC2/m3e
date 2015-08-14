/*
 * Copyright (C) 2010 The Android Open Source Project
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

#include "utils/UtilsDefine.h"
#include "utils/ABuffer.h"

#include "utils/ADebug.h"

//#include "utils/ALooper.h"

#ifdef ENABLE_AMESSAGE
#include "utils/AMessage.h"
#endif // ENABLE_AMESSAGE

_UTILS_BEGIN

ABuffer::ABuffer(size_t capacity)
    : mData(malloc(capacity)),
      mCapacity(capacity),
      mRangeOffset(0),
      mRangeLength(capacity),
      mInt32Data(0),
      mOwnsData(true)
{
}

ABuffer::ABuffer(void *data, size_t capacity)
    : mData(data),
      mCapacity(capacity),
      mRangeOffset(0),
      mRangeLength(capacity),
      mInt32Data(0),
      mOwnsData(false)
{
}

ABuffer::~ABuffer()
{
    if (mOwnsData) {
        if (mData != NULL) {
            free(mData);
            mData = NULL;
        }
    }

#ifdef ENABLE_AMESSAGE

    if (mFarewell != NULL) {
        mFarewell->post();
    }

#endif // ENABLE_AMESSAGE
}

void ABuffer::setRange(size_t offset, size_t size)
{
    CHECK_LE(offset, mCapacity);
    CHECK_LE(offset + size, mCapacity);

    mRangeOffset = offset;
    mRangeLength = size;
}

#ifdef ENABLE_AMESSAGE
void ABuffer::setFarewellMessage(const sp<AMessage> msg)
{
    mFarewell = msg;
}

sp<AMessage> ABuffer::meta()
{
    if (mMeta == NULL) {
        mMeta = new AMessage;
    }

    return mMeta;
}
#endif // ENABLE_AMESSAGE

_UTILS_END

