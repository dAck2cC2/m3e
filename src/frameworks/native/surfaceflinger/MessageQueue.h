

#ifndef ANDROID_MESSAGE_QUEUE_H
#define ANDROID_MESSAGE_QUEUE_H

#include <utils/threads.h>
#include <utils/Timers.h>
#include <utils/Looper.h>

#include "Barrier.h"

namespace android {

class SurfaceFlinger;

// ---------------------------------------------------------------------------

class MessageBase : public MessageHandler
{
public:
    MessageBase();
    
    // return true if message has a handler
    virtual bool handler() = 0;

    // waits for the handler to be processed
    void wait() const { barrier.wait(); }

protected:
    virtual ~MessageBase();

private:
    virtual void handleMessage(const Message& message);

    mutable Barrier barrier;
};

// ---------------------------------------------------------------------------

class MessageQueue {
    class Handler : public MessageHandler {
        enum {
            eventMaskInvalidate     = 0x1,
            eventMaskRefresh        = 0x2,
            eventMaskTransaction    = 0x4
        };
        MessageQueue& mQueue;
        int32_t mEventMask;
    public:
        Handler(MessageQueue& queue) : mQueue(queue), mEventMask(0) { }
        virtual void handleMessage(const Message& message);
        void dispatchRefresh();
        void dispatchInvalidate();
    };

    friend class Handler;

    sp<SurfaceFlinger> mFlinger;
    sp<Looper> mLooper;
    sp<Handler> mHandler;

public:
    enum {
        INVALIDATE  = 0,
        REFRESH     = 1,
    };

    MessageQueue();
    ~MessageQueue();
    void init(const sp<SurfaceFlinger>& flinger);
    
    void waitMessage();
    status_t postMessage(const sp<MessageBase>& message, nsecs_t reltime=0);
};

}; // namespace android

#endif /* ANDROID_MESSAGE_QUEUE_H */
