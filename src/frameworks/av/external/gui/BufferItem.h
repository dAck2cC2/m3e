
#ifndef ANDROID_GUI_BUFFERITEM_H
#define ANDROID_GUI_BUFFERITEM_H

//#include <EGL/egl.h>
//#include <EGL/eglext.h>

//#include <ui/Rect.h>
//#include <ui/Region.h>

//#include <system/graphics.h>

#include <utils/Flattenable.h>
#include <utils/StrongPointer.h>

namespace android {

class Fence;
class GraphicBuffer;

class BufferItem : public Flattenable<BufferItem> {
    friend class Flattenable<BufferItem>;
    size_t getPodSize() const;
    size_t getFlattenedSize() const;
    size_t getFdCount() const;
    status_t flatten(void*& buffer, size_t& size, int*& fds, size_t& count) const;
    status_t unflatten(void const*& buffer, size_t& size, int const*& fds, size_t& count);

    public:
    // The default value of mBuf, used to indicate this doesn't correspond to a slot.
    enum { INVALID_BUFFER_SLOT = -1 };
    BufferItem();
    ~BufferItem();

    static const char* scalingModeName(uint32_t scalingMode);

    // mSlot is the slot index of this buffer (default INVALID_BUFFER_SLOT).
    int mSlot;

    // mTimestamp is the current timestamp for this buffer slot. This gets
    // to set by queueBuffer each time this slot is queued. This value
    // is guaranteed to be monotonically increasing for each newly
    // acquired buffer.
    union {
        int64_t mTimestamp;
        struct {
            uint32_t mTimestampLo;
            uint32_t mTimestampHi;
        };
    };
    
    // mGraphicBuffer points to the buffer allocated for this slot, or is NULL
    // if the buffer in this slot has been acquired in the past (see
    // BufferSlot.mAcquireCalled).
    sp<GraphicBuffer> mGraphicBuffer;

    // mFence is a fence that will signal when the buffer is idle.
    sp<Fence> mFence;

    // mFrameNumber is the number of the queued frame for this slot.
    union {
        uint64_t mFrameNumber;
        struct {
            uint32_t mFrameNumberLo;
            uint32_t mFrameNumberHi;
        };
    };

#if 0
    // mCrop is the current crop rectangle for this buffer slot.
    Rect mCrop;

    // mTransform is the current transform flags for this buffer slot.
    // refer to NATIVE_WINDOW_TRANSFORM_* in <window.h>
    uint32_t mTransform;

    // mScalingMode is the current scaling mode for this buffer slot.
    // refer to NATIVE_WINDOW_SCALING_* in <window.h>
    uint32_t mScalingMode;

    // mIsAutoTimestamp indicates whether mTimestamp was generated
    // automatically when the buffer was queued.
    bool mIsAutoTimestamp;

    // mDataSpace is the current dataSpace value for this buffer slot. This gets
    // set by queueBuffer each time this slot is queued. The meaning of the
    // dataSpace is format-dependent.
    android_dataspace mDataSpace;

    // mIsDroppable whether this buffer was queued with the
    // property that it can be replaced by a new buffer for the purpose of
    // making sure dequeueBuffer() won't block.
    // i.e.: was the BufferQueue in "mDequeueBufferCannotBlock" when this buffer
    // was queued.
    bool mIsDroppable;

    // Indicates whether this buffer has been seen by a consumer yet
    bool mAcquireCalled;

    // Indicates this buffer must be transformed by the inverse transform of the screen
    // it is displayed onto. This is applied after mTransform.
    bool mTransformToDisplayInverse;

    // Describes the portion of the surface that has been modified since the
    // previous frame
    Region mSurfaceDamage;

    // Indicates that the consumer should acquire the next frame as soon as it
    // can and not wait for a frame to become available. This is only relevant
    // in shared buffer mode.
    bool mAutoRefresh;

    // Indicates that this buffer was queued by the producer. When in shared
    // buffer mode acquire() can return a BufferItem that wasn't in the queue.
    bool mQueuedBuffer;

    // Indicates that this BufferItem contains a stale buffer which has already
    // been released by the BufferQueue.
    bool mIsStale;
#endif
};

} // namespace android

#endif