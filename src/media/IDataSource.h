#ifndef __IDATA_SOURCE_H__
#define __IDATA_SOURCE_H__

#include "media/MediaDefine.h"
#include "utils/String8.h"
#include "utils/Errors.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

#include <sys/types.h>

_MEDIA_BEGIN

class IDataSource : public RefBase
{
public:
    explicit IDataSource() {};
    virtual ~IDataSource() {};

    virtual status_t initCheck() const = 0;
    virtual ssize_t  readAt(off64_t offset, void *data, size_t size) = 0;
    virtual bool     getUInt16(off64_t offset, uint16_t *x) = 0;
    // May return ERROR_UNSUPPORTED.
    virtual status_t getSize(off64_t *size) = 0;

    virtual void     deleteFileAfter(const bool bDelete_in) = 0;

    virtual bool sniff(String8 *mimeType, float *confidence
#ifdef ENABLE_AMESSAGE
                       , sp<AMessage> *meta = NULL
#endif // ENABLE_AMESSAGE
                      ) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IDataSource);
};

_MEDIA_END

#endif // __IDATA_SOURCE_H__

