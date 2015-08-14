#ifndef __CMEDIA_FILE_SCANNER_H__
#define __CMEDIA_FILE_SCANNER_H__

#include "media/MediaDefine.h"
#include "media/CPathScanner.h"
#include "utils/ABase.h"

_MEDIA_BEGIN

class CMediaFileScanner : public CPathScanner
{
public:
    explicit CMediaFileScanner();
    virtual ~CMediaFileScanner();

    virtual int processFile(
        const char *path, const char *mimeType, const sp<IEngineScannerClient>& client);

private:
    bool FileHasAcceptableExtension(const char *extension);

    DISALLOW_EVIL_CONSTRUCTORS(CMediaFileScanner);
};

_MEDIA_END

#endif // __CMEDIA_FILE_SCANNER_H__

