
#ifndef __CASYNC_ENCODER_GROUP_H__
#define __CASYNC_ENCODER_GROUP_H__

#include "EngineDefine.h"
#include "utils/Condition.h"
#include "media/stagefright/foundation/ABase.h"

#include "CAsyncEncoder.h"

ENGINE_BEGIN

class CAsyncEncoderGroup : public IAsyncEncoderObserver
{
public:
    explicit CAsyncEncoderGroup();
    virtual ~CAsyncEncoderGroup();

    void add(CAsyncEncoder * pEncoder);

    // Blocks until a object is available and returns it to the caller,
    // the returned object will have a reference count of 1.
    status_t acquire(CAsyncEncoder ** ppEncoder);

protected:
    virtual void signalReturned(CAsyncEncoder * pEncoder);

private:
    friend class CAsyncEncoder;

    Mutex mLock;
    Condition mCondition;

    CAsyncEncoder *mFirst, *mLast;

    DISALLOW_EVIL_CONSTRUCTORS(CAsyncEncoderGroup);
};



ENGINE_END

#endif // __CASYNC_ENCODER_GROUP_H__

