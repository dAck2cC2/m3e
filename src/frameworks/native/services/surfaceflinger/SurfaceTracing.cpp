/*
 * Copyright 2017 The Android Open Source Project
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
#undef LOG_TAG
#define LOG_TAG "SurfaceTracing"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS

#include "SurfaceTracing.h"
#include <SurfaceFlinger.h>

#include <android-base/file.h>
#include <android-base/stringprintf.h>
#include <log/log.h>
#include <utils/SystemClock.h>
#include <utils/Trace.h>

#if defined(_MSC_VER) // M3E
#include "Layer.h"  // sp of Layer
#endif // M3E

namespace android {

SurfaceTracing::SurfaceTracing(SurfaceFlinger& flinger)
      : mFlinger(flinger), mSfLock(flinger.mDrawingStateLock) {}

void SurfaceTracing::mainLoop() {
    addFirstEntry();
#if ENABLE_LAYER_PROTO /* M3E: */
    bool enabled = true;
    while (enabled) {
        LayersTraceProto entry = traceWhenNotified();
        enabled = addTraceToBuffer(entry);
    }
#endif // M3E
}

void SurfaceTracing::addFirstEntry() {
#if ENABLE_LAYER_PROTO /* M3E: */
    LayersTraceProto entry;
    {
        std::scoped_lock lock(mSfLock);
        entry = traceLayersLocked("tracing.enable");
    }
    addTraceToBuffer(entry);
#endif // M3E
}

#if ENABLE_LAYER_PROTO /* M3E: */
LayersTraceProto SurfaceTracing::traceWhenNotified() {
    std::unique_lock<std::mutex> lock(mSfLock);
    mCanStartTrace.wait(lock);
    android::base::ScopedLockAssertion assumeLock(mSfLock);
    LayersTraceProto entry = traceLayersLocked(mWhere);
    lock.unlock();
    return entry;
}

bool SurfaceTracing::addTraceToBuffer(LayersTraceProto& entry) {
    std::scoped_lock lock(mTraceLock);
    mBuffer.emplace(std::move(entry));
    if (mWriteToFile) {
        writeProtoFileLocked();
        mWriteToFile = false;
    }
    return mEnabled;
}
#endif // M3E

void SurfaceTracing::notify(const char* where) {
    std::scoped_lock lock(mSfLock);
    mWhere = where;
    mCanStartTrace.notify_one();
}

void SurfaceTracing::writeToFileAsync() {
    std::scoped_lock lock(mTraceLock);
    mWriteToFile = true;
    mCanStartTrace.notify_one();
}

#if ENABLE_LAYER_PROTO /* M3E: */
void SurfaceTracing::LayersTraceBuffer::reset(size_t newSize) {
    // use the swap trick to make sure memory is released
    std::queue<LayersTraceProto>().swap(mStorage);
    mSizeInBytes = newSize;
    mUsedInBytes = 0U;
}

void SurfaceTracing::LayersTraceBuffer::emplace(LayersTraceProto&& proto) {
    auto protoSize = proto.ByteSize();
    while (mUsedInBytes + protoSize > mSizeInBytes) {
        if (mStorage.empty()) {
            return;
        }
        mUsedInBytes -= mStorage.front().ByteSize();
        mStorage.pop();
    }
    mUsedInBytes += protoSize;
    mStorage.emplace();
    mStorage.back().Swap(&proto);
}

void SurfaceTracing::LayersTraceBuffer::flush(LayersTraceFileProto* fileProto) {
    fileProto->mutable_entry()->Reserve(mStorage.size());

    while (!mStorage.empty()) {
        auto entry = fileProto->add_entry();
        entry->Swap(&mStorage.front());
        mStorage.pop();
    }
}
#endif // M3E

void SurfaceTracing::enable() {
    std::scoped_lock lock(mTraceLock);

    if (mEnabled) {
        return;
    }
#if ENABLE_LAYER_PROTO /* M3E: */
    mBuffer.reset(mBufferSize);
#endif // M3E
    mEnabled = true;
    mThread = std::thread(&SurfaceTracing::mainLoop, this);
}

status_t SurfaceTracing::writeToFile() {
    mThread.join();
    return mLastErr;
}

bool SurfaceTracing::disable() {
    std::scoped_lock lock(mTraceLock);

    if (!mEnabled) {
        return false;
    }

    mEnabled = false;
    mWriteToFile = true;
    mCanStartTrace.notify_all();
    return true;
}

bool SurfaceTracing::isEnabled() const {
    std::scoped_lock lock(mTraceLock);
    return mEnabled;
}

void SurfaceTracing::setBufferSize(size_t bufferSizeInByte) {
    std::scoped_lock lock(mTraceLock);
    mBufferSize = bufferSizeInByte;
#if ENABLE_LAYER_PROTO /* M3E: */
    mBuffer.setSize(bufferSizeInByte);
#endif // M3E
}

void SurfaceTracing::setTraceFlags(uint32_t flags) {
    std::scoped_lock lock(mSfLock);
    mTraceFlags = flags;
}

#if ENABLE_LAYER_PROTO /* M3E: */
LayersTraceProto SurfaceTracing::traceLayersLocked(const char* where) {
    ATRACE_CALL();

    LayersTraceProto entry;
    entry.set_elapsed_realtime_nanos(elapsedRealtimeNano());
    entry.set_where(where);
    LayersProto layers(mFlinger.dumpProtoInfo(LayerVector::StateSet::Drawing, mTraceFlags));
    entry.mutable_layers()->Swap(&layers);

    return entry;
}

void SurfaceTracing::writeProtoFileLocked() {
    ATRACE_CALL();

    LayersTraceFileProto fileProto;
    std::string output;

    fileProto.set_magic_number(uint64_t(LayersTraceFileProto_MagicNumber_MAGIC_NUMBER_H) << 32 |
                               LayersTraceFileProto_MagicNumber_MAGIC_NUMBER_L);
    mBuffer.flush(&fileProto);
    mBuffer.reset(mBufferSize);

    if (!fileProto.SerializeToString(&output)) {
        ALOGE("Could not save the proto file! Permission denied");
        mLastErr = PERMISSION_DENIED;
    }
    if (!android::base::WriteStringToFile(output, kDefaultFileName, S_IRWXU | S_IRGRP, getuid(),
                                          getgid(), true)) {
        ALOGE("Could not save the proto file! There are missing fields");
        mLastErr = PERMISSION_DENIED;
    }

    mLastErr = NO_ERROR;
}
#endif // M3E

void SurfaceTracing::dump(std::string& result) const {
    std::scoped_lock lock(mTraceLock);
    base::StringAppendF(&result, "Tracing state: %s\n", mEnabled ? "enabled" : "disabled");
#if ENABLE_LAYER_PROTO /* M3E: */
    base::StringAppendF(&result, "  number of entries: %zu (%.2fMB / %.2fMB)\n",
                        mBuffer.frameCount(), float(mBuffer.used()) / float(1_MB),
                        float(mBuffer.size()) / float(1_MB));
#endif // M3E
}

} // namespace android
