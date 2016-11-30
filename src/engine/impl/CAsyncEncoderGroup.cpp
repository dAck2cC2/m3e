
//#define ENABLE_ADEBUG_EXT
#define LOG_TAG   "CAsyncEncoderGroup"
#include "utils/ADebugExt.h"
#include "media/stagefright/foundation/ADebug.h"
#include "media/stagefright/foundation/AMessage.h"
#include "utils/Errors.h"
#include "engine/EngineDefine.h"
#include "engine/CEngineFactory.h"
#include "impl/CAsyncEncoderGroup.h"

ENGINE_BEGIN

CAsyncEncoderGroup::CAsyncEncoderGroup()
    : mFirst(NULL),
      mLast(NULL)
{
    AUTO_LOG();
}

CAsyncEncoderGroup::~CAsyncEncoderGroup()
{
    AUTO_LOG();

    Mutex::Autolock autoLock(mLock);

    CAsyncEncoder *next;

    for (CAsyncEncoder *buffer = mFirst; buffer != NULL; buffer = next) {
        next = buffer->next();

        while (buffer->refcount() != 0) {
            mCondition.wait(mLock);
        }

        CHECK_EQ(buffer->refcount(), 0);

        buffer->setObserver(NULL);
        buffer->release();
    }
}

void CAsyncEncoderGroup::add(CAsyncEncoder * in)
{
    AUTO_LOG();

    CHECK_PTR(in);

    Mutex::Autolock autoLock(mLock);

    in->setObserver(this);

    if (mLast) {
        mLast->setNext(in);
    } else {
        mFirst = in;
    }

    mLast = in;
}

status_t CAsyncEncoderGroup::acquire(CAsyncEncoder **out)
{
    AUTO_LOG();

    CHECK_PTR_EXT(out, BAD_VALUE);

    Mutex::Autolock autoLock(mLock);

    for (;;) {
        for (CAsyncEncoder *buffer = mFirst;
                buffer != NULL; buffer = buffer->next()) {
            if (buffer->refcount() == 0) {
                buffer->add_ref();
                buffer->reset();

                *out = buffer;
                goto exit;
            }
        }

        // All buffers are in use. Block until one of them is returned to us.
        mCondition.wait(mLock);
    }

exit:
    return OK;
}

void CAsyncEncoderGroup::signalReturned(CAsyncEncoder * pEncoder_in)
{
    AUTO_LOG();

    Mutex::Autolock autoLock(mLock);

    if (pEncoder_in != NULL) {
        sp<AMessage> pInfo = new AMessage();

        if (pInfo != NULL) {
            pInfo->setString(INFO_INPUT_FILE, pEncoder_in->getSourceFile().string());

            CEngineFactory::getInstance().getMonitor()->publish(pInfo);
        }
    }

    mCondition.signal();
}

ENGINE_END

