#ifndef __IDATA_RENDER_H__
#define __IDATA_RENDER_H__

#include "media/MediaDefine.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class IDataRender : public RefBase
{
public:
    explicit IDataRender() {};
    virtual ~IDataRender() {};

    virtual ssize_t syncWrite(const void *data, const size_t size) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IDataRender);
};

_MEDIA_END

#endif //__IDATA_RENDER_H__

