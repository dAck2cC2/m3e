#ifndef __CDATA_SOURCE_H__
#define __CDATA_SOURCE_H__

#include "media/MediaDefine.h"
#include "media/IDataSource.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class CDataSource : public IDataSource
{
public:
    explicit CDataSource();
    virtual ~CDataSource();

    virtual bool sniff(String8 *mimeType, float *confidence
#ifdef ENABLE_AMESSAGE
                       , sp<AMessage> *meta
#endif // ENABLE_AMESSAGE
                      );

    DISALLOW_EVIL_CONSTRUCTORS(CDataSource);
};

_MEDIA_END

#endif // __CDATA_SOURCE_H__

