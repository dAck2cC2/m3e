
#ifndef __CASYNC_ENCODER_H__
#define __CASYNC_ENCODER_H__

#include "engine/EngineDefine.h"
#include "engine/IEngineEncoder.h"
#include "utils/Thread.h"
#include "utils/String8.h"
#include "utils/ABase.h"

ENGINE_BEGIN

class AMessage;
class CAsyncEncoder;
class CAsyncEncoderGroup;

class IAsyncEncoderObserver
{
public:
    IAsyncEncoderObserver() {}
    virtual ~IAsyncEncoderObserver() {}

    virtual void signalReturned(CAsyncEncoder * pEncoder_in) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IAsyncEncoderObserver);
};


class CAsyncEncoder
{
public:
    explicit CAsyncEncoder(const sp<IEngineEncoder>& pEncoder_in, const int32_t iAffinity_in = -1);

    int asyncEncode(
        const sp<MediaSource>&     pSrc_in,
        const sp<IDataRender>&     pDst_in,
        const sp<AMessage>&        pOpt_in,
        const String8&             cSrcFile_in
    );

    String8& getSourceFile();

    // Decrements the reference count and returns the buffer to its
    // associated CAsyncEncoderGroup if the reference count drops to 0.
    void release();

    // Increments the reference count.
    void add_ref();

    int refcount() const;

    // Clears meta data and resets the range to the full extent.
    void reset();

    void setObserver(IAsyncEncoderObserver * pObserver_in);

protected:
    virtual ~CAsyncEncoder();

private:
    void setNext(CAsyncEncoder * pNext_in);
    CAsyncEncoder * next();

private:
    friend class CAsyncEncoderGroup;

private:
    int                      m_iRefCount;
    IAsyncEncoderObserver *  m_pObserver;
    CAsyncEncoder *          m_pNext;
    sp<IEngineEncoder>       m_pEncoder;
    sp<Thread>               m_pThread;
    sp<AMessage>             m_pOption;
    String8                  m_cSrcFile;
    int32_t                  m_iAffinity;

private:
    class CEncoderThread : public Thread
    {
    public:
        explicit CEncoderThread(
            CAsyncEncoder&             cParent_in,
            const sp<MediaSource>&     pSrc_in,
            const sp<IDataRender>&     pDst_in,
            const sp<AMessage>&        pOpt_in,
            const sp<IEngineEncoder>&  pEncoder_in,
            const int32_t              iAffinity_in = -1
        );
        virtual ~CEncoderThread();

    private:
        virtual bool  threadLoop();


    private:
        CAsyncEncoder&      m_cParent;
        sp<MediaSource>     m_pMediaSource;
        sp<IDataRender>     m_pDataRender;
        sp<AMessage>        m_pOption;
        sp<IEngineEncoder>  m_pEncoder;

        DISALLOW_EVIL_CONSTRUCTORS(CEncoderThread);
    };

    DISALLOW_EVIL_CONSTRUCTORS(CAsyncEncoder);
};

ENGINE_END

#endif // __CASYNC_ENCODER_H__

