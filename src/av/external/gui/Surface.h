
#ifndef ANDROID_GUI_SURFACE_H
#define ANDROID_GUI_SURFACE_H

#include <gui/IGraphicBufferProducer.h>
#include <gui/BufferQueue.h>
#include <ui/ANativeObjectBase.h>
#include <utils/RefBase.h>

struct ANativeWindow_Buffer;

namespace android {

/*
 * An implementation of ANativeWindow that feeds graphics buffers into a
 * BufferQueue.
 *
 * This is typically used by programs that want to render frames through
 * some means (maybe OpenGL, a software renderer, or a hardware decoder)
 * and have the frames they create forwarded to SurfaceFlinger for
 * compositing.  For example, a video decoder could render a frame and call
 * eglSwapBuffers(), which invokes ANativeWindow callbacks defined by
 * Surface.  Surface then forwards the buffers through Binder IPC
 * to the BufferQueue's producer interface, providing the new frame to a
 * consumer such as GLConsumer.
 */
class Surface
    : public ANativeObjectBase<ANativeWindow, Surface, RefBase>
{
public:

    /*
     * creates a Surface from the given IGraphicBufferProducer (which concrete
     * implementation is a BufferQueue).
     *
     * Surface is mainly state-less while it's disconnected, it can be
     * viewed as a glorified IGraphicBufferProducer holder. It's therefore
     * safe to create other Surfaces from the same IGraphicBufferProducer.
     *
     * However, once a Surface is connected, it'll prevent other Surfaces
     * referring to the same IGraphicBufferProducer to become connected and
     * therefore prevent them to be used as actual producers of buffers.
     *
     * the controlledByApp flag indicates that this Surface (producer) is
     * controlled by the application. This flag is used at connect time.
     */
    Surface(const sp<IGraphicBufferProducer>& bufferProducer, bool controlledByApp = false);

    /* getIGraphicBufferProducer() returns the IGraphicBufferProducer this
     * Surface was created with. Usually it's an error to use the
     * IGraphicBufferProducer while the Surface is connected.
     */
    sp<IGraphicBufferProducer> getIGraphicBufferProducer() const;

    /* convenience function to check that the given surface is non NULL as
     * well as its IGraphicBufferProducer */
    static bool isValid(const sp<Surface>& surface) {
        return surface != NULL && surface->getIGraphicBufferProducer() != NULL;
    }

    /* Attaches a sideband buffer stream to the Surface's IGraphicBufferProducer.
     *
     * A sideband stream is a device-specific mechanism for passing buffers
     * from the producer to the consumer without using dequeueBuffer/
     * queueBuffer. If a sideband stream is present, the consumer can choose
     * whether to acquire buffers from the sideband stream or from the queued
     * buffers.
     *
     * Passing NULL or a different stream handle will detach the previous
     * handle if any.
     */
    void setSidebandStream(const sp<NativeHandle>& stream);

    /* Allocates buffers based on the current dimensions/format.
     *
     * This function will allocate up to the maximum number of buffers
     * permitted by the current BufferQueue configuration. It will use the
     * default format and dimensions. This is most useful to avoid an allocation
     * delay during dequeueBuffer. If there are already the maximum number of
     * buffers allocated, this function has no effect.
     */
    void allocateBuffers();

    /* Sets the generation number on the IGraphicBufferProducer and updates the
     * generation number on any buffers attached to the Surface after this call.
     * See IGBP::setGenerationNumber for more information. */
    status_t setGenerationNumber(uint32_t generationNumber);

    // See IGraphicBufferProducer::getConsumerName
    String8 getConsumerName() const;

    // See IGraphicBufferProducer::getNextFrameNumber
    uint64_t getNextFrameNumber() const;

    /* Set the scaling mode to be used with a Surface.
     * See NATIVE_WINDOW_SET_SCALING_MODE and its parameters
     * in <system/window.h>. */
    int setScalingMode(int mode);

    // See IGraphicBufferProducer::setDequeueTimeout
    status_t setDequeueTimeout(nsecs_t timeout);

    /*
     * Wait for frame number to increase past lastFrame for at most
     * timeoutNs. Useful for one thread to wait for another unknown
     * thread to queue a buffer.
     */
    bool waitForNextFrame(uint64_t lastFrame, nsecs_t timeout);

    // See IGraphicBufferProducer::getLastQueuedBuffer
    // See GLConsumer::getTransformMatrix for outTransformMatrix format
    status_t getLastQueuedBuffer(sp<GraphicBuffer>* outBuffer,
            sp<Fence>* outFence, float outTransformMatrix[16]);

    // See IGraphicBufferProducer::getFrameTimestamps
    bool getFrameTimestamps(uint64_t frameNumber, nsecs_t* outPostedTime,
            nsecs_t* outAcquireTime, nsecs_t* outRefreshStartTime,
            nsecs_t* outGlCompositionDoneTime, nsecs_t* outDisplayRetireTime,
            nsecs_t* outReleaseTime);

    status_t getUniqueId(uint64_t* outId) const;

protected:
    virtual ~Surface();

private:
    // can't be copied
    Surface& operator = (const Surface& rhs);
    Surface(const Surface& rhs);

protected:
    virtual int dequeueBuffer(ANativeWindowBuffer** buffer, int* fenceFd);
    virtual int cancelBuffer(ANativeWindowBuffer* buffer, int fenceFd);
    virtual int queueBuffer(ANativeWindowBuffer* buffer, int fenceFd);
    virtual int perform(int operation, va_list args);
    virtual int setSwapInterval(int interval);

    virtual int lockBuffer_DEPRECATED(ANativeWindowBuffer* buffer);

    virtual int connect(int api);
    virtual int disconnect(int api);
    virtual int setBufferCount(int bufferCount);
    virtual int setBuffersDimensions(uint32_t width, uint32_t height);
    virtual int setBuffersUserDimensions(uint32_t width, uint32_t height);
    virtual int setBuffersFormat(PixelFormat format);
    virtual int setBuffersTransform(uint32_t transform);
    virtual int setBuffersStickyTransform(uint32_t transform);
    virtual int setBuffersTimestamp(int64_t timestamp);
    virtual int setBuffersDataSpace(android_dataspace dataSpace);
    virtual int setCrop(Rect const* rect);
    virtual int setUsage(uint32_t reqUsage);
    virtual void setSurfaceDamage(android_native_rect_t* rects, size_t numRects);

public:
    virtual int setMaxDequeuedBufferCount(int maxDequeuedBuffers);
    virtual int setAsyncMode(bool async);
    virtual int setSharedBufferMode(bool sharedBufferMode);
    virtual int setAutoRefresh(bool autoRefresh);
    virtual int lock(ANativeWindow_Buffer* outBuffer, ARect* inOutDirtyBounds);
    virtual int unlockAndPost();
    virtual int query(int what, int* value) const;

    virtual int connect(int api, const sp<IProducerListener>& listener);
    virtual int detachNextBuffer(sp<GraphicBuffer>* outBuffer,
            sp<Fence>* outFence);
    virtual int attachBuffer(ANativeWindowBuffer*);

protected:
    enum { NUM_BUFFER_SLOTS = BufferQueue::NUM_BUFFER_SLOTS };
    enum { DEFAULT_FORMAT = PIXEL_FORMAT_RGBA_8888 };
};

}; // namespace android

#endif  // ANDROID_GUI_SURFACE_H
